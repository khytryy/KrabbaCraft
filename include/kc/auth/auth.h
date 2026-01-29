#pragma once

#include <time.h>
#include <stdint.h>

#include <arpa/inet.h>
#include <string.h>

typedef struct {
    char        uuid[24];
    char        username[32];

    char        access_token[24];
    char        client_token[24];

    uint64_t    expires_after;

} auth_info_t;

typedef struct {
    uint64_t    access_token;
    uint64_t    client_token;

    char        uuid[24];
    char        username[32];

    uint64_t    expires_after;
} auth_info_s_t;

uint64_t authTokenToInt(const char *token);

auth_info_s_t authCreateSockAuthInfo(auth_info_t info);

uint64_t htonll(uint64_t value);