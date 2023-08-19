#include "socket.h"
#include <unistd.h>
#include <arpa/inet.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>

int init_socket() {

    // Create a socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set the SO_REUSEADDR socket option
    int reuse = 1;
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int)) == -1) {
        perror("Setting SO_REUSEADDR failed");
        exit(EXIT_FAILURE);
    }

    // Define the server address
    struct sockaddr_in serverAddr;
    serverAddr.sin_addr.s_addr = INADDR_ANY; // Accept connections from the host.
    serverAddr.sin_port = htons(8080); // Port number

    // Bind the socket to the address
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(serverSocket, 5) == -1) {
        perror("Listening failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port 8080...\n");

    // Accept a connection
    int clientSocket;
    struct sockaddr_in clientAddr;
    socklen_t addrLen = sizeof(clientAddr);

    clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &addrLen);
    if (clientSocket == -1) {
        perror("Accepting connection failed");
        exit(EXIT_FAILURE);
    }

    printf("Connection established with client.\n");

    return clientSocket;
}

ssize_t read_message(int socket, char* buffer, int flags) {
    return recv(socket, buffer, sizeof(buffer), 0);
}

void send_message(int socket, char* message, size_t size, int flags) {
    send(socket, message, size, flags);
}

void close_socket(int socket) {
    close(socket);
}
