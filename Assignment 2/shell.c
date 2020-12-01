#include "interpreter.h"
#include "shellmemory.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int shellUI() {
    printf("Kernel 1.0 loaded!\n"
           "Welcome to the Oscar shell!\n"
           "Shell version 2.0 Updated February 2020\n");

    shell_memory_initialize();

    while (!feof(stdin)) {
        printf("$ ");
        fflush(stdout);

        char *line = NULL;
        size_t linecap = 0;
        
        if (getline(&line, &linecap, stdin) == -1) {
            break;
        }

        (void)interpreter(line);
        free(line);
    }

    shell_memory_destroy();
    return 0;
}