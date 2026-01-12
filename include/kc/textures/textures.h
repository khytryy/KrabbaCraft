#pragma once

#include <kc/common/common.h>
#include <kc/debug/debug.h>

#include "stb_image.h"

typedef struct {
    int     width, height, channels;
    ubyte   *data;
} image_t;

typedef struct {
    uint    id;
} texture_t;

typedef struct {

} tile_t;

image_t loadImage(const char *path);
texture_t createTextureFromImage(image_t image);

void freeImage(image_t image);