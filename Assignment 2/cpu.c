/*
Since we are not implementing threads, all concurrent programs access the same
shell memory space. We are using the shell memory of Assignment 1 as one global
memory space where all the scripts will read and write, even the command line scripts.
*/

#include <stdlib.h>
#include <string.h>

#include "ram.h"
#include "interpreter.h"

int busyBool; // 1 is true, 0 is false

typedef struct CPU {
	int IP; // Points to next instruction to execute from ram[]
	/*
	Note: the IR stores the instruction that will be sent to the interpreter() for execution.
	This simulates how the assembler instruction is loaded from RAM into the CPU’s IR.
	The interpreter() function simulates the CPU’s sequencer, which executes the instruction.
	*/
	char IR[1000]; // Stores currently executing instruction
	int quanta; // Quanta assummed to be equal to 2 lines of code
} CPU;

CPU *cpu;

void run(int quanta) {
	/*
	// Set if busy
	busyBool = 1;
	// Run script by copying quanta lines of code from ram[] using IP into the IR
	while (quanta > 0) {
		strcpy(cpu->IR, ram[cpu->IP]);
		// Call interpreter(IR)
		interpreter(cpu->IR);
		quanta--;
	}
	busyBool = 0;
	*/
}