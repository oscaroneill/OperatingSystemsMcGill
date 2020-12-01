#ifndef PCB_H
#define PCB_H

struct PCB* makePCB(int start, int end);

typedef struct PCB {
	int PC;
	int start;
	int end;
} PCB;

#endif