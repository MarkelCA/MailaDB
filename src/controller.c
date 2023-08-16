#include <string.h>
#include <stdlib.h>
#include "./utils.h"
#include <stdio.h>
#include "./storage.h"

char* run_command(char* args[]) {
    char* input = args[0];
    if (strcmp(input, "get") == 0) {
        char* result = get(args[1]);
        return result;
    } else if (strcmp(input, "set") == 0) {
        set(args[1], args[2]);
        return "Done";
    } else {
        return "Command not valid";
    }
}

