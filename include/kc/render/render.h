#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <kc/debug/debug.h>
#include <kc/common/common.h>
#include <kc/shaders/shaders.h>

extern GLFWwindow *render_window;
extern double previous_time;

extern int render_width, render_height;

void renderErrorCallback(int error, const char *description);
void renderFramebufferSizeCallback(GLFWwindow *window, int width, int height);

void renderInit(int width, int height, bool fullscreen);
void renderTerminate(void);

void renderBeginDrawing(void);
void renderEndDrawing(void);

void renderFillBackground(color_t color);

void renderBeginShader(shader_t shader);
void renderEndShader(void);

int renderGetFPS(void);

bool renderWindowShouldClose(void);