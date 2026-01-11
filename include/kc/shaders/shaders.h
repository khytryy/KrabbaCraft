#pragma once

#define KC_MAX_LOCS 32

#include <kc/debug/debug.h>
#include <kc/common/common.h>

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <cglm/cglm.h>

typedef struct {
    uint    program;
    int     *locs;
} shader_t;

shader_t loadShader(const char *vertex_path, const char *fragment_path);
shader_t loadShaderMem(const char *vertex, const char *fragment);

void useShader(shader_t shader);

void shaderSetBool(shader_t shader, const char* name, bool value);
void shaderSetInt(shader_t shader, const char* name, int value);
void shaderSetFloat(shader_t shader, const char* name, float value);

void shaderSetVec2(shader_t shader, const char* name, vector2_t value);
void shaderSetVec3(shader_t shader, const char* name, vector3_t value);
void shaderSetVec4(shader_t shader, const char* name, vector4_t value);

void shaderSetMat4(shader_t shader, const char* name, mat4 value);