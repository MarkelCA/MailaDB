#include <stdio.h>
#include <string.h>

#include "./utils.h"
#include "./storage.h"

int run_command(char* args[]);

int main(int argc, char* argv[]) {
    if (argc == 1) {
        printf("Usage: <command> <params>\n");
        printf("Examples:\n - set foo bar\n");
        printf(" - get foo\n");
        return 0;
    }

    char* input = argv[1];
    char** tokens = str_split(input, ' ');

    int res = run_command(argv);
    return res;
}

int run_command(char* args[]) {
    char* input = args[1];
    if (strcmp(input, "get") == 0) {
        get(args[2]);
    } else if (strcmp(input, "set") == 0) {
        set(args[2], args[3]);
    } else {
        printf("\nCommand not valid");
        return 1;
    }

    return 0;
}



