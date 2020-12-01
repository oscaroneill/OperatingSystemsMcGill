#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "shell.h"
#include "pcb.h"
#include "dirent.h"
#include "cpu.h"
#include "memorymanager.h"

FILE* ram[10];

struct PCB* head;
struct PCB* tail;

char prompt[100] = {'$', '\0'};
char userInput[1000];

int errorCode = 0;

void addToReady(struct PCB* p) {
  if (head == NULL) {
    head = p;
    tail = p;
  } else {
    tail->next = p;
    tail = tail->next;
  }
}

void terminate() {
  struct PCB* temp = head;
  for (int i = 0; i < head->pages_max; i++) {
    if (ram[head->pageTable[i]] != NULL && head->pageTable[i] != 100) {
      fclose(ram[head->pageTable[i]]);
    }

    ram[head->pageTable[i]] = NULL;
  }

  if (head->file != NULL) {
    fclose(head->file);
  }

  char command[1000];
  sprintf(command, "BackingStore/%s", head->fileName);

  int s;
  int d;
  if ((strcmp(head->fileName, head->next->fileName) == 0) && head->next != NULL) {
    s = 0;
  } else {
    s = 1;
  }

  if ((strcmp(head->fileName, head->next->next->fileName) == 0) && head->next->next != NULL && head->next != NULL) {
    d = 0;
  } else {
     d = 1;
  }

  if (d != 0 && s != 0 && fopen(command, "r") != NULL) {
    sprintf(command, "rm -r BackingStore/%s", head->fileName);

    system(command);
  }

  head = head->next;
  temp->next = NULL;

  free(temp);
}

int scheduler() {
  while (head != NULL) {
    if (CPU.quanta == 2) {
      CPU.IP = head->PC;
      CPU.offset = head->PC_offset;

      int num = run();
      if (num == 9) {
        // Program complete
        terminate();
      } else if (num == 1) {
        // Quit
        while (head != NULL) {
          struct PCB* temp = head;

          if (head->file != NULL) {
            fclose(head->file);
          }
          head = head->next;

          free(temp);
        }

        int i = 0;
        while (i < 10) {
          if (ram[i] != NULL) {
            fclose(ram[i]);
          }

          ram[i] = NULL;
          i++;
        }

        return 1;
      } else if (num == 2) {
        // Page fault
        (head->PC_page)++;
        CPU.offset = 0;

        if ((head->PC_page) >= (head->pages_max)) {
          terminate();
        } else if (head->pageTable[head->PC_page] != 100) {
          (head->PC) = ram[head->pageTable[head->PC_page]];
          (head->PC_offset) = 0;

          tail->next = head;
          head = head->next;
          tail = tail->next;
          tail->next = NULL;
        } else {
          int frameNum = findFrame(findPage(head->PC_page, head->file));
          int victimFrameNum;

          if (frameNum == -1) {
            victimFrameNum = findVictim(head);
          } else {
            victimFrameNum = 0;
          }

          updateFrame(frameNum, victimFrameNum, findPage(head->PC_page, head->file));
          updatePageTable(head, head->PC_page, frameNum, victimFrameNum);

          head->PC_offset=0;
          tail->next = head;
          head = head->next;
          tail = tail->next;
          tail->next = NULL;
        }
      } else {
        // Switch task
        head->PC = CPU.IP;
        head->PC_offset = CPU.offset;
        tail->next = head;

        head = head->next;
        tail = tail->next;
        tail->next = NULL;
      }
    }
  }

  int i = 0;
  while (i < 10) {
    if (ram[i] != NULL) {
      fclose(ram[i]);
    }

    ram[i] = NULL;
    i++;
  }

  return 0;
}

void boot() {
  for (int i = 0; i < 10; i++) {
    ram[i] = NULL;
  }

  DIR* dir = opendir("BackingStore");

  if(dir) {
    closedir(dir);

    // Remove directory
    system("rm -r BackingStore");
  }

  // Create directory
  system("mkdir BackingStore");
}

int main(int argc, char *argv[]) {
  boot();
  UI();

  CPU.quanta = 2;
  CPU.offset = 0;

  head = NULL;
  tail = NULL;

  while(1) {
    printf("%s", prompt);
    fgets(userInput, 999, stdin);

    errorCode = parse(userInput);
    if (errorCode == 1) {
      exit(99);
    }
  }

}
