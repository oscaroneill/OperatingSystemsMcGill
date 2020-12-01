#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "shell.h"
#include "shellmemory.h"
#include "kernel.h"
#include "memorymanager.h"

int exec(char* first, char* second, char* third) {
  FILE* file = fopen(first, "rt");
  if (file == NULL) {
    printf("Script %s not found\n", first);
  } else {
    launcher(file, first);
  }

  if (second != NULL) {
    FILE* file2 = fopen(second, "rt");
    if (file2 == NULL) {
      printf("Script %s not found\n", second);
    } else {
      launcher(file2, second);
    }
  }

  if (third != NULL) {
    FILE* file3 = fopen(third, "rt");
    if (file3 == NULL) {
      printf("Script %s not found\n", third);
      } else {
        launcher(file3, third);
      }
  }

  return scheduler();
}

int run2(FILE* file) {
  char line[1000];
  int errCode = 0;

  while(fgets(line, 999, file) != NULL) {
    errCode = parse(line);

    if (errCode == 1) {
      fclose(file);

      return 1;
    }
  }
  fclose(file);

  return 0;
}

int interpreter(char* words[]) {
  int errorCode = 0;
  char a[100];

  if (strcmp(words[0], "help") == 0 && (words[1] == NULL)) {
    printf("help\t\t\t\tDisplays all commands\n");
    printf("quit\t\t\t\tTerminates the shell\n");
    printf("set VAR STRING\t\t\tAssigns the value STRING to the shell memory variable VAR\n");
    printf("print VAR\t\t\tDisplays the STRING value assigned to the shell memory variable VAR\n");
    printf("run SCRIPT.TXT\t\t\tExecutes the file SCRIPT.txt\n");
    printf("exec p1 p2 p3\t\t\tExecutes programs p1 p2 p3 concurrently\n");
  } else if (strcmp(words[0], "quit") == 0 && (words[1] == NULL)) {
    printf("Bye!\n");
    return 1;
  } else if (strcmp(words[0], "set") == 0 && (words[1] != NULL) && (words[2] != NULL) && (words[3] == NULL)) {
    strcpy(a, words[1]);
    strcat(a, "=");
    strcat(a, words[2]);

    set(a, words[1]);
  } else if (strcmp(words[0], "print") == 0 && (words[1] != NULL) && (words[2] == NULL)) {
    printf("%s\n", get(words[1]));
  } else if (strcmp(words[0], "run") == 0 && (words[1] != NULL) && (words[2] == NULL)) {
    FILE* file = fopen(words[1], "rt");

    if (file == NULL) {
      printf("Script not found\n");
      return 0;
    } else {
      return run2(file);
    }

  } else if (strcmp(words[0], "exec") == 0 && (words[1] != NULL) && (words[4] == NULL)) {

    return exec(words[1], words[2], words[3]);
  } else {
    printf("Unknown command\n");
  }
  return errorCode;
}
