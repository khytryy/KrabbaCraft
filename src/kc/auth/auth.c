#include <kc/auth/auth.h>

uint64_t authTokenToInt(const char *token) {
    uint64_t hash = 0;
    while (*token) {
        if (*token != '-') {
            hash = hash * 31 + (unsigned char)(*token);
        }
        token++;
    }
    return hash;
}