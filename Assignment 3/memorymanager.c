#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "pcb.h"
#include "time.h"
#include "kernel.h"

char fName[1000];
struct PCB* PCBTable[10] = {NULL};

int countTotalPages(FILE* f) {
  char line[1000];
  int lines = 0;

  while(fgets(line, 999, f) != NULL) {
    lines++;
  }

  fseek(f, 0, SEEK_SET);

  if (lines % 4 == 0) {
    int pages = lines / 4;
    return pages;
  } else {
    int pages = (lines / 4) + 1;
    return pages;
  }
}

char* getFileName(FILE* f) {
  if (f != NULL) {
    int fileNum = fileno(f);
    char temp[1000];

    sprintf(temp, "/proc/self/fd/%d", fileNum);

    int i = readlink(temp, fName, 999);
    fName[i] = '\0';

    return fName;
  } else {
    return NULL;
  }
}

int findFrame(FILE* page) {
  int i = 0;

  while (i < 10 && ram[i] != NULL) {
    i++;
  }

  if ( ram[9] != NULL && i >= 9) {
    return -1;
  } else {
    return i;
  }
}

FILE* findPage(int pageNumber, FILE* f) {
  FILE* f2 = fopen(getFileName(f), "rt");
  char line[1000];

  for (int i = 0; i < (pageNumber * 4); i++) {
    fgets(line, 999, f2);
  }

  return f2;
}

int updateFrame(int frameNumber, int victimFrame, FILE* page) {
  if (frameNumber == -1) {
    ram[victimFrame] = page;
  } else {
    ram[frameNumber] = page;
  }

  return 1;
}

int findVictim(struct PCB* p) {
  srand(time(NULL));

  int a = rand() % 10;

  for (int i = 0; i < (p->pages_max); i++) {
    if (p->pageTable[i] == a) {
      a++;
      i = 0;
    }

    if (a == 10) {
      a = 0;
      i = 0;
    }
  }

  return a;
}

int updatePageTable(struct PCB* p, int pageNumber, int frameNumber, int victimFrame) {
  if (frameNumber == -1) {
    p->pageTable[pageNumber] = victimFrame;

    PCBTable[victimFrame]->pageTable[pageNumber] = 100;
    PCBTable[victimFrame] = p;
  } else {
    p->pageTable[pageNumber] = frameNumber;
    PCBTable[frameNumber] = p;
  }

  return 1;
}

int launcher(FILE* p, char* name) {
  char command[1000];

  sprintf(command, "cp %s BackingStore", name);
  system(command);

  fclose(p);

  system("cd BackingStore");
  FILE* q = fopen(name, "rt");

  struct PCB* pcb = makePCB(q);
  pcb->fileName = name;

  if (pcb->pages_max <= 1) {
    int currVictimNum;
    int currFrameNum = findFrame(findPage(0, q));

    if (currFrameNum == -1) {
      currVictimNum = findVictim(pcb);
    } else {
      currVictimNum = 0;
    }

    updateFrame(currFrameNum, currVictimNum, findPage(0,q));
    updatePageTable(pcb, 0, currFrameNum, currVictimNum);
  } else {
    int currVictimNum2;
    int currFrameNum2 = findFrame(findPage(0, q));

    if (currFrameNum2 == -1) {
      currVictimNum2 = findVictim(pcb);
    } else {
      currVictimNum2 = 0;
    }

    updateFrame(currFrameNum2, currVictimNum2, findPage(0, q));
    updatePageTable(pcb, 0, currFrameNum2, currVictimNum2);

    int currFrameNum3 = findFrame(findPage(1, q));
    int currVictimNum3;

    if (currFrameNum3 == -1) {
      currVictimNum3 = findVictim(pcb);
    } else {
      currVictimNum3 = 0;
    }

    updateFrame(currFrameNum3, currVictimNum3, findPage(1,q));
    updatePageTable(pcb, 1, currFrameNum3, currVictimNum3);
  }

  addToReady(pcb);

  return 1;
}
