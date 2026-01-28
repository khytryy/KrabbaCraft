#pragma once

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include <stdint.h>
#include <assert.h>

#include <time.h>
#include <stdbool.h>

#include <pthread.h>

typedef enum {
    PACKET_TYPE_MESSAGE,
    PACKET_TYPE_PLAYER_POS,
    PACKET_TYPE_BLOCK_CHANGE,
    PACKET_TYPE_PLAYER_CONNECTED,
    PACKET_TYPE_PLAYER_DISCONNECTED,
    PACKET_TYPE_SERVER_MESSAGE,
} packet_type_t;

typedef struct {
    packet_type_t       packet_type;

    uint8_t             *payload;
} packet_t;

typedef struct {
    int queueSize;
    int port;
} server_settings_t;

void *kcServerStart(void *server_settings);
void kcSendPacket(packet_t packet);

void *kcHandleClient(void *client_fd);