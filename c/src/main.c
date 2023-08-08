#include <stdio.h>

void get() {

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
  set("key", "val");
  return 0;
}
