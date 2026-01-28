#include <kc/net/server.h>

int server_fd;
int opt = 1;

bool running = true;

struct sockaddr_in address;
socklen_t addrlen = sizeof(address);

void *kcServerStart(void *args) {
    server_settings_t *settings = (server_settings_t*)args;
    
    printf("[SERVER/INFO] Starting integrated server...\n");

    // Create a socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("[SERVER/ERROR] Failed to create a socket");
    }

    if (setsockopt(server_fd, SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt))) {
        perror("[SERVER/ERROR] Error in setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(settings->port);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("[SERVER/ERROR] Error in port binding\n");
        exit(EXIT_FAILURE);
    }

    assert(settings->queueSize > 0);

    if (listen(server_fd, settings->queueSize) < 0) {
        perror("[SERVER/ERROR] Error in listen");
        exit(EXIT_FAILURE);
    }

    printf("[SERVER/INFO] Server online on port %d!\n", settings->port);

    while (1) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);

        int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);

        if (client_fd < 0) {
            perror("[SERVER/ERROR] Error while accepting client");
            continue;
        }

        pthread_t client_handler;
        pthread_create(&client_handler, NULL, kcHandleClient, &client_fd);

        if (!running) {
            close(client_fd);
            close(server_fd);
            break;
        }
    }

}

void kcSendPacket(packet_t packet) {
    
}

void *kcHandleClient(void *args) {
    int *client_fd = (int *)args;

    // Await for an authorization package
    
}