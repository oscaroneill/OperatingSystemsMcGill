#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "memorymanager.h"

struct PCB  {
  FILE* PC;
  int PC_page;
  int PC_offset;
  int pages_max;
  int pageTable[10];
  struct PCB* next;
  FILE* file;
  char* fileName;
} PCB;

struct PCB* makePCB(FILE* p) {
  struct PCB* newPCB = (struct PCB*)malloc(sizeof(struct PCB));

  newPCB->PC = p;
  newPCB->file = fopen(getFileName(p), "rt");

  for (int i = 0; i < 10; i++) {
    newPCB->pageTable[i] = 100;
  }

  newPCB->PC_page = 0;
  newPCB->PC_offset = 0;
  newPCB->pages_max = countTotalPages(p);
  newPCB->next = NULL;

  return newPCB;
}
