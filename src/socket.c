#include "socket.h"
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>


int init_socket() {

    // Create a socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set the SO_REUSEADDR socket option
    int reuse = 1;
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int)) == -1) {
        perror("Setting SO_REUSEADDR failed");
        exit(EXIT_FAILURE);
    }

    // Define the server address
    struct sockaddr_in serverAddr;
    serverAddr.sin_addr.s_addr = INADDR_ANY; // Accept connections from the host.
    serverAddr.sin_port = htons(8080);       // Port number

    // Bind the socket to the address
    if (bind(server_socket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_socket, 5) == -1) {
        perror("Listening failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port 8080...\n");

    return server_socket;
}

ssize_t read_message(int socket, char* buffer, size_t size, int flags) {
    return recv(socket, buffer, size, 0);
}

void send_message(int socket, char* message, size_t size, int flags) {
    send(socket, message, size, flags);
}

void close_socket(int socket) {
    close(socket);
}
