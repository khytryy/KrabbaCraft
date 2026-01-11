#include <kc/debug/debug.h>

void _dbgGetError(const char *file, int line, const char *function) {
    GLenum error_code;

    while ((error_code = glGetError()) != GL_NO_ERROR) {
        char *error;

        switch (error_code) {
            case GL_INVALID_ENUM:
                error = "Invalid enum";
            case GL_INVALID_VALUE:
                error = "Invalid value";
            case GL_INVALID_OPERATION:
                error = "Invalid operation";
            case GL_OUT_OF_MEMORY:
                error = "Out fo memory";
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                error = "Invalid framebuffer operation";
        }
        fprintf(stderr, "[DEBUG/ERROR] %s (line %d at %s)\n", error, line, file);
    }
}

void dbgWrite(const char *name, log_level_t log_level, const char *restrict format, ...) {
    va_list args;
    va_start(args, format);

    char *error;
    char *error_color;
    
    switch (log_level) {
        case LOG_LEVEL_INFO:
            error = "INFO";
            error_color = "";

            break;
        case LOG_LEVEL_DEBUG:
            error = "DEBUG";
            error_color = "\033[35m";

            break;
        case LOG_LEVEL_WARNING:
            error = "WARNING";
            error_color = "\033[33m";

            break;
        case LOG_LEVEL_ERROR:
            error = "ERROR";
            error_color = "\033[91m";

            break;
        case LOG_LEVEL_FATAL_ERROR:
            error = "FATAL";
            error_color = "\033[31m";

            break;
    }

    printf("%s[%s/%s] ", error_color, name, error);
    vprintf(format, args);
    printf("\033[0m");
    
    va_end(args);
}

void dbgPerror(const char *name, const char *restrict format, ...) {
    va_list args;
    va_start(args, format);

    printf("[%s/ERROR] ", name);
    vprintf(format, args);
    perror("");

    va_end(args);
}