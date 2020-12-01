#ifndef KERNEL_H
#define KERNEL_H

int myInit(char *filename);
void scheduler();
typedef struct readyQueueNode {
	struct PCB *pcb;
	struct readyQueueNode *next;
} readyQueueNode;
extern int addToRAMError;

#endif