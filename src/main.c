#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./utils.h"

#define BUFFER_SIZE 4096
#define DATABASE_PATH "./data/out.db"

int run_command(char* args[]);
void get(char* key);
void set(const char* key, const char* value);
void write_test();

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
        // write_test();
    } else {
        printf("\nCommand not valid");
        return 1;
    }

    return 0;
}


void get(char* key) {
    assert(key != NULL);
    FILE *file;
    char line[BUFFER_SIZE];

    file = fopen(DATABASE_PATH, "r");
    if (file == NULL) {
        perror("Failed to open the file");
    }


    int key_length;
    char* key_data;

    int val_lenght;
    char* val_data = malloc(sizeof(char)*val_lenght);

    while (!feof(file)) {
        char* current_key_data;
        int current_key_length;

        fread(&current_key_length, sizeof(int), 1, file);

        current_key_data = malloc(sizeof(char)*current_key_length);
        fread(current_key_data, sizeof(char), current_key_length, file);

        if(strcmp(key, current_key_data) == 0) {
            // Read Key into buffer
            key_length = current_key_length;
            key_data = current_key_data;
            printf("found! (%s)\n", current_key_data);

            // Read Data into buffer
            fread(&val_lenght, sizeof(int), 1, file);
            fread(val_data, sizeof(char), val_lenght, file);
        } 
    }

    printf("%s -> %s\n", key_data, val_data);

    free(val_data);
    fclose(file);
}

void set(const char* key, const char* value) {
    FILE *file = fopen(DATABASE_PATH, "ab+");
    assert(key && value);
    
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    int keyLength = strlen(key);
    int valueLength = strlen(value);

    // Write key length and data
    fwrite(&keyLength, sizeof(int), 1, file);
    fwrite(key, sizeof(char), keyLength, file);

    // Write value length and data
    fwrite(&valueLength, sizeof(int), 1, file);
    fwrite(value, sizeof(char), valueLength, file);

    fclose(file);
}
