#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "./utils.h"
#include "./controller.h"
#include "./socket.h"

int main() {
    // Init the socket
    int socket = init_socket();

    // Receive and send messages
    char buffer[1024]; // Has to change given the maximum value lenght (65KB)
    memset(&buffer, 0, sizeof(buffer));
    while (1) {
        ssize_t bytes_read = read_message(socket, buffer, sizeof(buffer), 0);
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
        send_message(socket,final_result, value_lenght, 0);

        free(tokens);
        free(result);
        tokens = NULL;
        result = NULL;
    }

    close_socket(socket);

    return 0;
}
