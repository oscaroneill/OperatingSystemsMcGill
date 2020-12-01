COMP 310 Operating Systems - Assignment #2
Oscar O'Neill - Student no. 260934264

I only used the Linux machines on the 3rd floor of Trottier for this assignment.

Functions I haven't implemented:
- kernel.c:
	- void scheduler(), though there's a commented attempt
	- void addToReady(struct PCB *pcb), though there's a commented attempt
- cpu.c
	- void run(int quanta), though there's a commented attempt

Functions I have implemented:
- interpreter.c:
	- int exec(char **tokens)
- kernel.c:
	- int myInit(char **filename)
- pcb.c:
	- struct PCB* makePCB(int start, int end)
- ram.c:
	- void addToRAM(FILE *p, int *start, int *end)

My program can take the exec command as input, with one, two, or three scripts, and gives correct error messages.
It then calls myInit() correctly, and successfully adds each line of each script into RAM.
Unfortunately, I couldn't implement the actual running of the lines in RAM, though you can un-comment the print statements on lines 69, 76 and 77 to see each line loaded in RAM, along with their indexes and the scripts start and end cells in RAM.
My program constructs the PCBs, though it can't add them to the ready queue successfully (but I do have the ready queue data structure implemented).
The CPU data structure is also implemented.

My program can be tested with the TESTFILE.TXT file.

I've never made a bash file before so I just did what someone said to do on Piazza, sorry if it doesn't work!
