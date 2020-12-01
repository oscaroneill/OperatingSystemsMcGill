/*
- Each program executed by the shell’s exec command is loaded into ram[]
- Programs need to be in ram[] at the same time
- Each line from the source file is loaded into its own cell in the array
- Enough space for 1000 lines of code, so 333 lines of code, on average, per program
- If there is not enough space to store all the lines in the script then the load terminates
with an error
- A NULL pointer indicates that there is no code at that cell location in ram[]

When a program is loaded to ram[] the following operations happen:
1. fopen the script
2. Find the next available cell in ram[]
3. Copy all the lines of code into ram[]
4. Remember the start cell number and the ending cell number of that script in ram[]

To read a line from the program do:
- fgets(file,buffer,limit);
- ram[k] = strdup(buffer);
where k is the current line of the program

When the program has finished executing do:
- ram[k]=NULL;
for all the lines of code in ram[]
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "kernel.h"

char *ram[1000];
int startCell;
int endCell;
    
// Adds the source code to the next available cells in ram[]
// How to use start and end inputted variables?
// Need to control for max lines depending on number of processes
void addToRAM(FILE *p, int *start, int *end) {
	if (p == NULL) {
        printf("Script not found\n");
    } else {
        char buffer[100];
        int lineNum = 0;
        // Until we get to end of file
        while (!feof(p) && addToRAMError == 0) {
            // Until we get to end of file
            // Get next line
            if (fgets(buffer, 100, p) != NULL && addToRAMError == 0) {
                // Find next open spot of RAM
                for (int i = 0; i < 1001; i++) {
                    if (i == 1000) {
                        // Not enough space, terminate with error
                        addToRAMError == 1;
                        for (int j = 0; j < 1000; j++) {
                            ram[j] = NULL;
                        }
                        break;
                    } else if (ram[i] == NULL) {
                        // Put the line in RAM
                        ram[i] = strdup(buffer);
                        if (lineNum == 0) {
                            startCell = i;
                            endCell = startCell-1;
                        }
                        endCell++;
                        lineNum++;
                        // Print call to see each loaded instruction and its position in RAM
                        //printf("i: %d = %s\n", i, ram[i]);
                        break;
                    }
                }
            }
        }
        // Print calls to see start and end ram cells of scripts
        //printf("startCell = %d\n", startCell);
        //printf("endCell = %d\n", endCell);
    }

    fclose(p);
}