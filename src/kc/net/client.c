#include <kc/net/client.h>

void *kcClientStart(char* ip, int port, auth_info_t auth_info) {
    int client_fd, status;

    struct sockaddr_in server_addr;
    if (client_fd = socket(AF_INET, SOCK_STREAM, 0) < 0) {
        dbgWrite("CLIENT", LOG_LEVEL_ERROR, "Error creating a socket\n");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, ip, &server_addr.sin_addr) <= 0) {
        dbgWrite("CLIENT", LOG_LEVEL_ERROR, "Invalid address or address not supported\n");
        exit(1);
    }

    if (status = connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        dbgWrite("CLIENT", LOG_LEVEL_ERROR, "Failed to connect to the server\n");
        exit(1);
    }

    nbt_buffer_t *buffer;

    // Send the login data
    nbtBufferWriteU64(buffer, auth_info.expires_after);
    nbtBufferWriteU64(buffer, auth_info.access_token);
    nbtBufferWriteU64(buffer, auth_info.client_token);

    nbtReserverBuffer(buffer, 32);
    memcpy(buffer->data + buffer->size, auth_info.username, 32);
    buffer->size += 32;

    nbtReserverBuffer(buffer, 32);
    memcpy(buffer->data + buffer->size, auth_info.uuid, 32);
    buffer->size += 32;

    send(client_fd, buffer->data, buffer->size, 0);

}

void kcClientSendPacket(packet_t packet);
void kcClientSendNBT(nbt_value_t value);