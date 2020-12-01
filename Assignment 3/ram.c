#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "kernel.h"

int addToRAM(FILE* p) {
  int i = 0;

  while (i < 10 && ram[i] != NULL) {
    i++;
  }

  if (i < 10) {
    ram[i] = p;
  }

  return i;
}
