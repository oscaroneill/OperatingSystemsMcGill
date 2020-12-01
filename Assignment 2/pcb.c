/*
When a program is launched, a PCB is created, and the PCB’s PC field points to the
first line of the program. The PCB’s PC is updated after the quanta is finished.
*/

#include <stdlib.h>
#include <stdio.h>

typedef struct PCB {
	/* PC field is not the CPU instruction pointer, therefore it is updated only after
	a task switch */
	int PC; // int refererring to cell number of ram[] containing the instruction to execute
	int start; // contains the cell number of ram[] of the first instruction
	int end; // contains the cell number of ram[] of the last instruction
} PCB;

struct PCB* makePCB(int start, int end) {
	PCB *pcb = (PCB *)malloc(sizeof(PCB));
	pcb->PC = start;
	pcb->start = start;
	pcb->end = end;
	return pcb;
}