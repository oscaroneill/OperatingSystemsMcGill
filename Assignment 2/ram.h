#ifndef RAM_H
#define RAM_H

#include <stdio.h>

void addToRAM(FILE *p, int *start, int *end);
extern int startCell;
extern int endCell;
extern char *ram[1000];

#endif