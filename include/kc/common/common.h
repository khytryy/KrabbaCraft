#pragma once

#include <stdint.h>
#include <stdio.h>

#include <kc/debug/debug.h>
#include <stdlib.h>

#define GAME_VER "Krabbacraft v26.01.03-dev"

#define uint unsigned int
#define u8 unsigned char
#define u16 unsigned short

#define null ((void *)0)

char *loadFile(const char *path);

typedef struct {
    float   x;
    float   y;

} vector2_t;

typedef struct {
    float   x;
    float   y;
    float   z;

} vector3_t;

typedef struct {
    float   x;
    float   y;
    float   z;
    float   w;

} vector4_t;

typedef struct {
    u8      r;
    u8      g;
    u8      b;
    u8      a;

} color_t;

#define BLACK (color_t){0, 0, 0, 255}