
#include <stdint.h>

#include <simple_wgsl.h>

const uint32_t* wgsl_shader_to_spirv(const char *wgsl_code, const char *entry_point);

const char* wgsl_shader_to_glsl(const char *wgsl_code, WgslStage stage, const char *entry_point);

const char* wgsl_shader_to_hlsl(const char *wgsl_code, WgslStage stage, const char *entry_point);

const char* wgsl_shader_to_msl(const char *wgsl_code, const char *entry_point);