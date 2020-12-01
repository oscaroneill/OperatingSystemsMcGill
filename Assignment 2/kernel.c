/*
- Calls void addToRAM(FILE *p, int *start, int *end) from ram.c to add the source code
to the next available cells in ram[].
- Calls PCB* makePCB(int start, int end) from pcb.c to create a PCB instance using
malloc.
- Calls void addToReady(PCB *) from kernel.c to add the PCB to the tail of the Ready
Queue
*/

#include "shell.h"
#include "ram.h"
#include "pcb.h"
#include "cpu.h"

#include <stdlib.h>
#include <stdio.h>

typedef struct readyQueueNode {
	struct PCB *pcb;
	struct readyQueueNode *next;
} readyQueueNode;

struct readyQueueNode *head, *tail;
int quanta = 2;
struct readyQueueNode *currentlyExecuting;

int addToRAMError = 0;

// Adds the PCB to the tail of the Ready Queue
void addToReady(struct PCB *pcb) {
	/*
	if (head->pcb == NULL) {
		// First node
		head->pcb = pcb;
		head->next = NULL;
		tail = NULL;
		currentlyExecuting = head;
	} else {
		// Not first node
		// Loop until tail
		int tailNotFoundBool = 1; // 1 is true, 0 is false
		struct readyQueueNode *currentPCB = head;
		while (tailNotFoundBool == 1) {
			if (currentPCB->next != NULL) {
				currentPCB = currentPCB->next;
			} else {
				tailNotFoundBool = 0;
			}
		}
		// Add as tail
		tail->next = currentPCB;
		tail = currentPCB;
	}
	*/
}

int myInit(char *filename) {
	// Open file
	FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Script not found\n");
        return 1;
    }

    int *start;
    int *end;
    addToRAM(file, start, end);
    if (addToRAMError == 1) {
    	return 1;
    }
    // Call makePCB(int start, int end) to create a PCB instance using malloc
    struct PCB *pcb = makePCB(startCell, endCell);
    // Call addtoReady(PCB *) to add the PCB to the tail of the Ready Queue
    addToReady(pcb);
    fclose(file);
    return 0;
}

/*
- scheduler() is called after all the programs have been loaded into the simulator
- It is our main simulation execution loop

Steps:
1. It checks to see if the CPU is available (quanta is finished or nothing is currently
assigned to the CPU)
2. It copies the PC from the PCB into the IP of the CPU
3. It calls the run(quanta) function within cpu.c to run the script by copying quanta
lines of code from ram[] using IP into the IR, which then calls interpreter(IR)
4. This executes quanta instructions from the script or until the script file is at end
5. If the program is not at the end, then the PCB PC pointer is updated with the IP
value and the PCB is placed at the tail of the ready queue
6. If the program is at the end, then the PCB terminates (as described previously)
*/
void scheduler() {
	/*
	// Check if the CPU quanta is finished or nothing is currently assigned
	if (busyBool == 0) {
		// Copy PC from the PCB into the IP of the CPU (think I need ready queue for this)
		cpu->IP = head->pcb->PC;
		run(quanta);
		// If the program is not at the end, then the PCB PC pointer is updated with the IP 
		// value and the PCB is placed at the tail of the ready queue.
		// If the program is at the end, then the PCB terminates
	}
	*/
}

int main(int argc, const char *argv[]) {
	shellUI();
    return 0;
}