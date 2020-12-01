#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "shell.h"

struct CPU {
  FILE* IP;
  char IR[1000];
  int quanta;
  int offset;
} CPU;

int run() {
  for (int i = 0; i < CPU.quanta; i++) {
    int errorCode = 0;

    if (fgets(CPU.IR, 999, CPU.IP) != NULL) {
      errorCode = parse(CPU.IR);

      CPU.offset++;
      // Page fault
      if (CPU.offset == 4) {
        return 2;
      }

      // Quit
      if (errorCode == 1) {
        return 1;
      }
    } else {
      // File completed
      return 9;
    }

    return 0;
  }
}
