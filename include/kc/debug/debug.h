#pragma once

#include <glad/glad.h>
#include <stdio.h>

#include <stdarg.h>

typedef enum {
    INFO,
    DEBUG,
    WARNING,
    ERROR
} error_t;

void _dbgGetError(const char *file, int line, const char *function);
#define dbgGetError() _dbgGetError(__FILE__, __LINE__, __func__)

void dbgWrite(const char *name, error_t error_type, const char *restrict format, ...);
void dbgPerror(const char *name, const char *restrict format, ...);