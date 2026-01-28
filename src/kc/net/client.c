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

    // Send the login info to the server to validate
    uint64_t access_token = authTokenToInt(auth_info.access_token);
    uint64_t client_token = authTokenToInt(auth_info.client_token);

}

void kcClientSendPacket(packet_t packet);
void kcClientSendNBT(nbt_value_t value);