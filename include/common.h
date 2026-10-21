#pragma once

#include <stdlib.h>

#include <simple_wgsl.h>

#define SAFE_FREE(x)\
if (x != NULL)\
{\
    free((void*)x);\
    x = NULL;\
}

extern const char *default_entry_point;
extern const WgslLowerEnv default_vulkan_version;

typedef struct {
    uint32_t* spirv_code;
    size_t code_size;
} SpirvCode;

const SsirModule* ast_to_ir(
    WgslAstNode *code,
    const WgslResolver *resolver,
    const WgslLowerOptions *opts
);

static inline SsirStage wgsl_stage_to_ssir_stage(WgslStage stage) {
    switch (stage) {
        case WGSL_STAGE_VERTEX:
            return SSIR_STAGE_VERTEX;
        case WGSL_STAGE_FRAGMENT:
            return SSIR_STAGE_FRAGMENT;
        case WGSL_STAGE_COMPUTE:
            return SSIR_STAGE_COMPUTE;
        default:
            return SSIR_STAGE_VERTEX; // Assumes vertex shader (will probably break at some point yay!)
    }
}