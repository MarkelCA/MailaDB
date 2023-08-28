#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "./utils.h"
#include "./storage.h"

char* run_command(char* args[]) {
    char* input = args[0];
    char* result;
    if (strcmp(input, "get") == 0) {
        result = get(args[1]);
    } else if (strcmp(input, "set") == 0) {
        set(args[1], args[2]);
        char* str_done = "OK";
        result = (char*) calloc(strlen(str_done), sizeof(char));
        strcat(result, str_done);
    } else if (strcmp(input, "del") == 0) {
        char* del_str = "Not implemented yet!";
        result = (char*) calloc(strlen(del_str), sizeof(char));
        strcat(result, del_str);
    } else if (strcmp(input, "list") == 0) {
        char* str_list = list();
        result = (char*) calloc(strlen(str_list), sizeof(char));
        strcat(result, str_list);
    } else {
        char* command_not_valid = "Command not valid";
        result = (char*)calloc(strlen(command_not_valid), sizeof(char));
        strcat(result, command_not_valid);
    }
    return result;
}

/**
 * Creates the database file if it doesn't exist.
 */
void controller_create_database() {
    create_database();
}
