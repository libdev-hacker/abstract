
#include <string.h>
#include <stdbool.h>

#include <simple_wgsl.h>

#include "common.h"
#include "error.h"

static const SsirModule* wgsl_to_ir(const char *code, const char *entry_point);

const SpirvCode wgsl_shader_to_spirv(const char *wgsl_code, const char *entry_point) {

    const SsirModule *ssir = wgsl_to_ir(wgsl_code, entry_point);

    const SsirToSpirvOptions spirv_opts = {0};

    uint32_t *spirv;
    size_t spirv_size = 0;
    SsirToSpirvResult spirv_result = ssir_to_spirv(ssir, &spirv_opts, &spirv, &spirv_size);
    
    check_if_error(spirv_result, NULL);

    SAFE_FREE(ssir);

    SpirvCode ret = {
        .spirv_code = spirv,
        .code_size = spirv_size
    };

    return ret;
}

const char* wgsl_shader_to_glsl(const char *wgsl_code, WgslStage stage, const char *entry_point) {

    const SsirModule *wgsl_ssir = wgsl_to_ir(wgsl_code, entry_point);

    const SsirToGlslOptions glsl_opts = {
        .preserve_names = true
    };

    char *glsl_code = NULL;
    char *errors = NULL;
    SsirToGlslResult glsl_result = ssir_to_glsl(wgsl_ssir, stage, &glsl_opts, &glsl_code, &errors);
    check_if_error(glsl_result, errors);

    SAFE_FREE(wgsl_ssir)

    return glsl_code;
}

const char* wgsl_shader_to_msl(const char *wgsl_code, const char *entry_point) {

    const SsirModule *wgsl_ssir = wgsl_to_ir(wgsl_code, entry_point);

    const SsirToMslOptions msl_opts = {
        .preserve_names = true
    };

    char *msl_code  = NULL;
    char *errors = NULL;
    SsirToMslResult msl_result = ssir_to_msl(wgsl_ssir, &msl_opts, &msl_code, &errors);
    check_if_error(msl_result, errors);

    SAFE_FREE(wgsl_ssir)

    return msl_code;
}

const char* wgsl_shader_to_hlsl(const char *wgsl_code, WgslStage stage, char *entry_point) {

    const SsirModule *ssir = wgsl_to_ir(wgsl_code, entry_point);

    const SsirToHlslOptions hlsl_opts = {
        .preserve_names = true
    };

    char *hlsl_code = NULL;
    char *errors = NULL;
    SsirToHlslResult hlsl_result = ssir_to_hlsl(
        ssir,
        wgsl_stage_to_ssir_stage(stage),
        &hlsl_opts,
        &hlsl_code,
        &errors
    );
    check_if_error(hlsl_result, errors);

    SAFE_FREE(ssir);

    return hlsl_code;
}

static const SsirModule* wgsl_to_ir(const char *code, const char *entry_point) {

    WgslParseResult wgsl_ast = wgsl_parse(code);
    check_if_diagnostic_error(wgsl_ast.diags);
    
    WgslResolveResult wgsl_resolver = wgsl_resolver_build(wgsl_ast.value);
    check_if_diagnostic_error(wgsl_resolver.diags);

    const WgslLowerOptions opts = {
        .entry_point = entry_point != NULL && strcmp(entry_point, "") != 0 ? entry_point : default_entry_point,
        .env = default_vulkan_version
    };

    const SsirModule *ssir = ast_to_ir(wgsl_ast.value, wgsl_resolver.value, &opts);

    wgsl_resolve_free(wgsl_resolver.value);
    wgsl_free_ast(wgsl_ast.value);

    return ssir;
}