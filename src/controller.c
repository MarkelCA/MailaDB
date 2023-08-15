#include <string.h>
#include <stdlib.h>
#include "./utils.h"
#include <stdio.h>
#include "./storage.h"

int run_command(char* args[]) {
    char* input = args[0];
    printf("\ncmd: %s\n", input);
    if (strcmp(input, "get") == 0) {
        char* result = get(args[1]);
        printf("\ngetting %s: %s",args[1], result);
        if (result != NULL) {
            printf("%s", result);
        } else {
            printf("not found");
        }
        free(result);
    } else if (strcmp(input, "set") == 0) {
        set(args[1], args[2]);
    } else {
        perror("\nCommand not valid");
        return 1;
    }

    return 0;
}
