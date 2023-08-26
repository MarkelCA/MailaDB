#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "./utils.h"
#include "./controller.h"
#include "./socket.h"

void client_handler(const int* p_client_socket) {
    // Receive and send messages
    int client_socket = *p_client_socket;
    char buffer[1024]; // Has to change given the maximum value lenght (65KB)

    while(1) {
        memset(&buffer, 0, sizeof(buffer));

        ssize_t bytes_read = read_message(client_socket, buffer, sizeof(buffer), 0);

        if (bytes_read <= 0) {
            perror("Connection closed or error");
            break;
        }

        // Delete the \r char at the end
        size_t carriagePos = strcspn(buffer, "\r");
        if (carriagePos < bytes_read) {
            buffer[carriagePos] = '\0';
        }

        char** tokens = str_split(buffer, ' ');
        char* final_result;
        size_t value_lenght;
        char* result = run_command(tokens);

        if(result != NULL) {
            value_lenght = strlen(result) + 4; // +4 because of the \n and \0 chars and the quotes
            final_result = (char*)calloc(value_lenght, sizeof(char) );

            strcpy(final_result, "\"");
            strcat(final_result, result);
            strcat(final_result, "\"");
            strcat(final_result, "\n\0");
        } else {
            char* str_nil = "(nil)\n\0";
            value_lenght = strlen(str_nil);
            final_result = (char*)calloc(value_lenght,sizeof(char));
            strcat(final_result, str_nil);
        }

        // Echo back the message
        send_message(client_socket, final_result, value_lenght, 0);

        free(tokens);
        free(result);
        free(final_result);
        tokens = NULL;
        result = NULL;
        final_result = NULL;
    }
}

int main() {
    int server_socket = init_socket();
    while (1) {
        // Accept a connection
        int client_socket;
        struct sockaddr_in client_addr;
        socklen_t addr_len = sizeof(client_addr);

        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_len);
        if (client_socket == -1) {
            perror("Accepting connection failed");
            exit(EXIT_FAILURE);
        }

        printf("Connection established with client (id: %d).\n", client_socket);

        pthread_t tid;
        if (pthread_create(&tid, NULL, (void*)client_handler, &client_socket) != 0) {
            perror("Thread creation failed");
            close_socket(client_socket);
            continue;
        }
    }
}
