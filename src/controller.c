#include <string.h>
#include <stdlib.h>
#include "./utils.h"
#include <stdio.h>
#include "./storage.h"

char* run_command(char* args[]) {
    char* input = args[0];
    char* result;
    if (strcmp(input, "get") == 0) {
        result = get(args[1]);
    } else if (strcmp(input, "set") == 0) {
        set(args[1], args[2]);
        char* str_done = "Done";
        result = (char*) malloc(sizeof(char) * strlen(str_done));
        memset(result,0, strlen(str_done));
        strcat(result, str_done);
    } else {

        char* command_not_valid = "Command not valid";
        result = (char*) malloc(sizeof(char) * strlen(command_not_valid));
        memset(result,0, strlen(command_not_valid));
        strcat(result, command_not_valid);
    }
    return result;
}

