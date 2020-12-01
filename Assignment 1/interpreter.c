/*
Each command the interpreter() function accepts has a corresponding function
that implements the command’s functionality.
Give the function the same name as the command.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "shell.h"

void interpreter() {
	
}

void help() {
	// Print all commands
	printf("help - Displays all the commands\n");
	printf("quit - Exits / terminates the shell\n");
	printf("set VAR STRING - Assigns a value to the shell memory\n");
	printf("print VAR - Displays the STRING assigned to VAR\n");
	printf("run SCRIPT.txt - Executes the file SCRIPT.TXT\n");
}

void quit() {
	printf("Bye!\n"); // Say goodbye
	running = false; // Stop running
}

void set() {
	varName = strtok(NULL, delim); // Get variable name
	//printf("VAR: %s\n", varName);
	varString = strtok(NULL, delim); // Get string
	//printf("VALUE: %s\n", varString);
	/*
	// Check if variable already exists
	for (int i = 0; i < (sizeof(memArray) / sizeof(memArray[0])); i++) { // Go through all variables
		if (strcmp(memArray[i].var, varName) == 0) { // If the variable already exists
			strcpy(memArray[i].value, varString); // Overwrite the value
			break;
		} else if (strcmp(memArray[i].var, varName) != 0 && i == ((sizeof(memArray) / sizeof(memArray[0]))-1)) { // If not
			// Add new entry to shell memory
		}
	}
	*/
}

void print() {
	// Check if variable already exists
	/*
	for (int i = 0; i < sizeof(memArray) / sizeof(MEM); i++) { // Go through all variables
		if (strcmp(memArray[i].var, varName) == 0) { // If the variable already exists
			printf("%s\n", memArray[i].value); // Display the string
			break;
		} else if (strcmp(memArray[i].var, varName) != 0 && i == (sizeof(memArray) / sizeof(MEM))-1) { // If not
			printf("Variable does not exist\n");
		}
	}
	*/
}

void run() {
	// Assume text file exists
	// Open text file (Display "Script not found" if not found)
	// Send each line to interpreter one at a time
	// Interpreter treats each line as a command, each affecting the shell and UI
	// Command line prompt not displayed while script runs
	// At end of the script, close the file and display command line prompt again
}