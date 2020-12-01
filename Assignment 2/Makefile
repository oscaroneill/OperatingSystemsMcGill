CC=gcc -g 

all : interpreter.o shell.o shellmemory.o
	$(CC) interpreter.o shell.o shellmemory.o -o mysh

interpreter.o : interpreter.c 
	$(CC) -c interpreter.c 

shell.o : shell.c 
	$(CC) -c shell.c 

shellmemory.o : shellmemory.c
	$(CC) -c shellmemory.c 

.PHONY:
clean:
	rm -f interpreter.o shell.o shellmemory.o
	rm -f mysh