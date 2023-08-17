#include <stdio.h>
#include <stdlib.h>
#include "./controller.h"


char* run_command(char* args[]);

int main(int argc, char** argv) {
    if (argc == 1) {
        printf("Usage: <command> <params>\n");
        printf("Examples:\n - set foo bar\n");
        printf(" - get foo\n");
        return 0;
    }

    // We skip the first param (file name) with +1 to the pointer
    char* result = run_command(argv + 1);
    printf("%s", result) ;
     free(result);
    return 0;
}





