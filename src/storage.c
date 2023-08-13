#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stddef.h>
#include <sys/types.h>

#define BUFFER_SIZE 4096
#define DATABASE_PATH "/home/markel/estudio/databases/MailaDB/data/out.db"

void get(char* key) {
    assert(key != NULL);
    FILE *file = NULL;
    char line[BUFFER_SIZE];

    file = fopen(DATABASE_PATH, "r");
    if (file == NULL) {
        perror("Failed to open the file");
    }
    char* key_data = NULL;
    char* val_data = NULL;

    // We iterate through all the file
    while (!feof(file)) {
        u_int8_t current_key_length = 0;
        char* current_key_data  = NULL;
        uint current_val_lenght = 0;
        char* current_val_data  = NULL;

        // We read the key
        fread(&current_key_length, sizeof(u_int8_t), 1, file);
        current_key_data = (char*)malloc(sizeof(char)*current_key_length);
        fread(current_key_data, sizeof(char), current_key_length, file);

        // We read the value
        fread(&current_val_lenght, sizeof(uint), 1, file);
        current_val_data = (char*)malloc(sizeof(char)*current_val_lenght);
        fread(current_val_data, sizeof(char), current_val_lenght, file);

        // If we find the key we store it along with the value
        if(strcmp(key, current_key_data) == 0) {
            key_data   = current_key_data;
            val_data   = current_val_data;
        }
    }

    if (key_data != NULL && val_data != NULL) {
        printf("%s -> %s\n", key_data, val_data);
    }

    free(key_data);
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

    u_int8_t key_length   = strlen(key);    // Max key lenght in bytes = 1 (key data: ~255 B)
    uint val_lenght  = strlen(value); //  Max val lenght in bytes = 2 (val data: ~65 KB)

    // Write key length and data
    fwrite(&key_length, sizeof(u_int8_t), 1, file);
    fwrite(key, sizeof(char), key_length, file);

    // Write value length and data
    fwrite(&val_lenght, sizeof(uint), 1, file);
    fwrite(value, sizeof(char), val_lenght, file);

    fclose(file);
}
