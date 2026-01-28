#pragma once

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include <kc/nbt/nbt.h>
#include <kc/debug/debug.h>
#include <kc/auth/auth.h>
#include <kc/net/server.h>

void *kcClientStart(char* ip, int port, auth_info_t auth_info);

void kcClientSendPacket(packet_t packet);
void kcClientSendNBT(nbt_value_t value);