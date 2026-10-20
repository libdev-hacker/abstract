
#include <stdbool.h>
#include <string.h>

#include <simple_wgsl.h>

#include "glsl.h"
#include "common.h"
#include "error.h"

static char* get_include(void *data, const char *path);

static GlslIncludeOptions include_opts = {
    .reader = get_include
};

static callback_t callback;

static const SsirModule* glsl_to_ir(const char *glsl_code, WgslStage stage, const char *entry_point);


const uint32_t* glsl_shader_to_spirv(const char *glsl_code, WgslStage stage, const char *entry_point) {

    const SsirModule *ssir = glsl_to_ir(glsl_code, stage, entry_point);

    SsirToSpirvOptions opts = {
        .enable_debug_names = true
    };

    uint32_t *spirv;
    size_t spirv_size = 0;

    SsirToSpirvResult spirv_result = ssir_to_spirv(ssir, &opts, &spirv, &spirv_size);
    check_if_error(spirv_result, NULL);

    SAFE_FREE(ssir)

    return spirv;
}

// State machine for function callback setter
// Saves me having to pass structs w/ function pointers
// between C# -> C boundary

void glsl_shader_set_include_callback(callback_t fn) {
    callback = fn;
}

static char* get_include(void *data, const char *path) {
    callback(path);
}

void glsl_shader_set_includes(const char *const *include_path) {
    include_opts.search_dirs = include_path;
    include_opts.search_dir_count = 1;
}

char* glsl_shader_to_msl(const char *glsl_code, WgslStage stage, const char *entry_point) {

    const SsirModule *ssir = glsl_to_ir(glsl_code, stage, entry_point);

    const SsirToMslOptions msl_opts = {
        .preserve_names = true
    };

    char *msl_string = NULL;
    char *error = NULL;
    SsirToMslResult msl_result = ssir_to_msl(
        ssir,
        &msl_opts,
        &msl_string,
        &error
    );

    check_if_error(msl_result, error);

    SAFE_FREE(ssir);

    if (msl_result != SSIR_TO_MSL_OK) {
        ssir_to_msl_free(error);
        return NULL;
    }

    return msl_string;
}

char* glsl_shader_to_hlsl(const char *glsl_code, WgslStage stage, const char *entry_point) {

    const SsirModule *ssir = glsl_to_ir(glsl_code, stage, entry_point);

    const SsirToHlslOptions hlsl_opts = {
        .preserve_names = true
    };

    char *hlsl_code = NULL;
    char *errors = NULL;
    SsirToHlslResult hlsl = ssir_to_hlsl(ssir, wgsl_stage_to_ssir_stage(stage), &hlsl_opts, &hlsl_code, &errors);
    check_if_error(hlsl, errors);

    SAFE_FREE(ssir);

    return hlsl_code;
}

static const SsirModule* glsl_to_ir(const char *glsl_code, WgslStage stage, const char *entry_point) {
    
    WgslAstNode *glsl_ast = glsl_parse(glsl_code, NULL, stage, &include_opts);

    WgslResolveResult glsl_resolver = wgsl_resolver_build(glsl_ast);
    check_if_diagnostic_error(glsl_resolver.diags);

    WgslLowerOptions opts = {
        .env = default_vulkan_version,
        .entry_point = entry_point != NULL && strcmp(entry_point, "") != 0 ? entry_point : default_entry_point
    };

    const SsirModule *ssir = ast_to_ir(glsl_ast, glsl_resolver.value, &opts);

    wgsl_resolve_free(glsl_resolver.value);
    wgsl_free_ast(glsl_ast);

    return ssir;
}