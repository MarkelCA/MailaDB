#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "./utils.h"
#include "./controller.h"

int main() {
    // Create a socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Define the server address
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
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

    // Receive and send messages
    char buffer[1024];
    while (1) {
        ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesRead <= 0) {
            perror("Connection closed or error");
            break;
        }

        // Find the position of the newline character
        size_t newlinePos = strcspn(buffer, "\n");

        // Remove the newline character, if present
        if (newlinePos < bytesRead) {
            buffer[newlinePos] = '\0';
        }

        printf("Received: %s", buffer);
        char** tokens = str_split(buffer, ' ');
        printf("Token 0: %s", tokens[0]);
        printf("here");
        printf("%i", run_command(tokens));
        printf("finishid run command");
        free(tokens);

        // Echo back the message
        send(clientSocket, buffer, bytesRead, 0);
    }

    // Close the sockets
    close(clientSocket);
    close(serverSocket);

    return 0;
}

