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

void dbgWrite(const char *name, error_t error_type, const char *restrict format, ...) {
    va_list args;
    va_start(args, format);

    char *error;
    switch (error_type) {
        case INFO:
            error = "INFO";
            break;
        case DEBUG:
            error = "DEBUG";
            break;
        case WARNING:
            error = "WARNING";
            break;
        case ERROR:
            error = "ERROR";
            break;
    }

    fprintf(stderr, "[%s/%s] ", name, error);
    vfprintf(stderr, format, args);
    
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