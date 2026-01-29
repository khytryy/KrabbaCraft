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

auth_info_s_t authCreateSockAuthInfo(auth_info_t info) {
    auth_info_s_t sinfo;

    sinfo.access_token = htonll(info.access_token);
    sinfo.client_token = htonll(info.client_token);

    sinfo.expires_after = htonll(info.expires_after);

    memcpy(sinfo.username, info.username, sizeof(sinfo.username));
    memcpy(sinfo.uuid, info.uuid, sizeof(sinfo.uuid));

    return sinfo;

}

uint64_t htonll(uint64_t value) {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    return ((uint64_t)htonl(value & 0xFFFFFFFFULL) << 32) |
            htonl(value >> 32);
#else
    return value;
#endif
}