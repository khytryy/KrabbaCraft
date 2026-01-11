#include <kc/common/common.h>

char *loadFile(const char *path) {
    FILE *f = fopen(path, "r");
    if (!f) {
        dbgWrite("FILE", LOG_LEVEL_ERROR, "Error opening %s: ", path);
        perror("");

        abort();
    }

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);

    char *data = malloc(size + 1);
    if (!data) {
        fclose(f);

        dbgWrite("FILE", LOG_LEVEL_ERROR, "Error in malloc");
        perror("");

        abort();
    }

    fread(data, 1, size, f);
    data[size] = '\0';

    fclose(f);
    return data;
}