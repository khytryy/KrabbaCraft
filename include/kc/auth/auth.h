#pragma once

#include <time.h>
#include <stdint.h>

typedef struct {
    char    *uuid;
    char    *username;

    char    *access_token;
    char    *client_token;

    time_t  expires_after;

} auth_info_t;

uint64_t authTokenToInt(const char *token);