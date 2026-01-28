#pragma once

#include <glad/glad.h>
#include <stdio.h>

#include <stdarg.h>
#include <stdlib.h>

typedef enum {
    LOG_LEVEL_INFO,
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_FATAL_ERROR
    
} log_level_t;

void _dbgGetError(const char *file, int line, const char *function);
#define dbgGetError() _dbgGetError(__FILE__, __LINE__, __func__)

void dbgWrite(const char *name, log_level_t log_level, const char *restrict format, ...);
void dbgPerror(const char *name, const char *restrict format, ...);