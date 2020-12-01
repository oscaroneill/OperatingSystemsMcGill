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
struct PCB* makePCB(FILE* p);
