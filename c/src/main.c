#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./utils.h"

#define BUFFER_SIZE 4096

// From now it just prints the file
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

int main() {
  // set("key", "val");
  get();
  return 0;
}
