#ifndef CPU_H
#define RAM_H

void run(int quanta);
extern int busyBool;
typedef struct CPU {
	int IP;
	char IR[1000];
	int quanta;
} CPU;
CPU *cpu;

#endif