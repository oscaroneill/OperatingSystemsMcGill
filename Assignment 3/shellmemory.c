#include <stdlib.h>
#include <string.h>

char* data[1000] = {NULL};

int matchTwo(char* str, char* var) {
  int i;
  int length = strlen(var);
  int matches = 0;

  if (str == NULL) {
    return 0;
  } else {
    for (i = 0; i < length; i++) {

      if (*(str + i) == *(var + i)) {
        matches++;
      }
    }
  }

  if (matches == length) {
    return 1;
  } else {
    return 0;
  }
}

char* extract(char* str) {
  char tok = '=';
  char val[1000];

  int i;
  int j;
  int length = strlen(str);

  for (i = 0; *(str + i) != tok && i < length; i++);

  for (i = i + 1, j = 0; i < length; i++, j++) {
    val[j] = *(str + i);
  }

  val[j] = '\0';

  return strdup(val);
}

int set(char* str, char* var)  {
  int i = 0;

  for (i = 0; i < 1000; i++) {
    if (matchTwo(data[i], var) == 1) {
      data[i] = strdup(str);

      return 0;
    } else if (data[i] == NULL) {
      data[i] = strdup(str);

      return 0;
    }
  }

  return 0;
}

char* get(char* var) {
  int i = 0;

  for (i = 0; i < 1000; i++) {
    if (matchTwo(data[i], var)) {

      return extract(data[i]);
    }
  }

  return "Variable does not exist.";
}
