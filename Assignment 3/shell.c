#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "interpreter.h"

void UI() {
  printf("Kernel 2.0 loaded!\nWelcome to the Oscar Shell!\nShell Version 3.0 Updated April 2020\n");
}

int parse(char input[]) {
  char temp[200];
  char* words[100] = {NULL};
  int first;
  int second;
  int word = 0;

  for (first = 0; input[first] == ' ' && first < 1000; first++);

  while (first < 1000 && input[first] != '\r' && input[first] != '\0' && input[first] != '\n') {
    while (input[first] == ' ') {
      first++;
    }

    for (second = 0;  first < 1000 && input[first] != ' ' && input[first] != '\r' && input[first] != '\0' && input[first] != '\n'; second++, first++) {
      temp[second] = input[first];
    }

    temp[second] = '\0';

    words[word] = strdup(temp);

    word++;
    first++;
  }

  if (words[0] == NULL) {
    return 0;
  }

  return interpreter(words);
}
