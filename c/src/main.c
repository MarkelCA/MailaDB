#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./utils.h"

#define BUFFER_SIZE 4096

int run_command(char* args[]);
void get();
void set(const char* key, const char* value);

int main(int argc, char* argv[]) {
    if (argc == 1) {
        printf("Usage: <command> <params>\n");
        printf("Examples:\n - set foo bar\n");
        printf(" - get foo\n");
        return 1;
    }

    char* input = argv[1];
    char** tokens = str_split(input, ' ');

    int res = run_command(argv);
    return res;
}

int run_command(char* args[]) {
    char* input = args[1];
    if (strcmp(input, "get") == 0) {
        get();
    } else if (strcmp(input, "set") == 0) {
        set(args[2], args[3]);
    } else {
        printf("\nError");
        return 1;
    }

    return 0;
}

void get() {
    FILE *file;
    char line[BUFFER_SIZE];

    file = fopen("data/output.txt", "r");
    if (file == NULL) {
        perror("Failed to open the file");
    }

    while (fgets(line, sizeof(line), file)) {
        char** tokens = str_split(line, ';');
        if (tokens) {
            printf("%s -> %s", *tokens, *(tokens+1));
            free(tokens);
        }
    }

    fclose(file);
}

void set(const char* key, const char* value) {
    FILE *file = fopen("data/output.txt", "a");
    
    if (file == NULL) {
        perror("Error opening file");
    }
    
    fprintf(file, "%s;%s\n",key,value);

    fclose(file);
}

