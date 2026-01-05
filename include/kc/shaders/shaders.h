#pragma once

#define KC_MAX_LOCS 32

#include <kc/debug/debug.h>
#include <kc/common/common.h>

#include <stdlib.h>
#include <stdio.h>

typedef struct {
    uint    program;
    int     *locs;
} shader_t;

shader_t loadShader(const char *vertex_path, const char *fragment_path);
shader_t loadShaderMem(const char *vertex, const char *fragment);

void useShader(shader_t shader);