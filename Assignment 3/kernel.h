extern FILE* ram[10];
extern struct PCB* head;
extern struct PCB* tail;
void addToReady(struct PCB* p);
int scheduler();
