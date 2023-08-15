#include <stdio.h>
#include "./controller.h"


int run_command(char* args[]);

int main(int argc, char** argv) {
    if (argc == 1) {
        printf("Usage: <command> <params>\n");
        printf("Examples:\n - set foo bar\n");
        printf(" - get foo\n");
        return 0;
    }

    // We skip the first param (file name) with +1 to the pointer
    return run_command(argv + 1); 
}





