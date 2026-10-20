
#include "common.h"
#include "error.h"

const char *default_entry_point = "main";
const WgslLowerEnv default_vulkan_version = WGSL_LOWER_ENV_VULKAN_1_3;

const SsirModule* ast_to_ir(
    WgslAstNode *code,
    const WgslResolver *resolver,
    const WgslLowerOptions *opts
) {
    WgslLowerResult result = wgsl_lower_create(code, resolver, opts);
    check_if_diagnostic_error(result.diags);
    
    WgslLower *lower_result = result.value;
    
    const SsirModule *ir_module = wgsl_lower_get_ssir(lower_result);

    return ir_module;
}