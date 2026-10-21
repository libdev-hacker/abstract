#pragma once

#include <stdint.h>

#include "common.h"

typedef char *(*callback_t)(const char *path);

const SpirvCode glsl_shader_to_spirv(const char *glsl_code, WgslStage stage, const char *entry_point);

void glsl_shader_set_include_callback(callback_t fn);

void glsl_shader_set_includes(const char *const *include_path);

char* glsl_shader_to_msl(const char *glsl_code, WgslStage stage, const char *entry_point);

char* glsl_shader_to_hlsl(const char *glsl_code, WgslStage stage, const char *entry_point);