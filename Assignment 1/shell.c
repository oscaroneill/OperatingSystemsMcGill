/*
The file shell.c is the primary programming file.
It contains the main() and parse() functions.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "interpreter.h"
#include "shellmemory.h"

char prompt = '$'; // Prompt character
bool running = true; // Has the user quit?
char input[50]; // User input
const char delim[2] = " "; // Delimiter for strtok 
char *userCommand; // COMMAND
char *varName; // VAR
char *varString; // VALUE

void parse() {
	printf("%c", prompt); // Print prompt
	scanf("%[^\n]%*c", input); // Scan for user input
	userCommand = strtok(input, delim); // Get command token of user input

	if (strcmp(userCommand, "help") == 0) { // If help command inputted
		help();
	} else if (strcmp(userCommand, "quit") == 0) { // Else, if quit command inputted
		quit();
	} else if (strcmp(userCommand, "set") == 0) { // Else, if set command inputted
		set();
	} else if (strcmp(userCommand, "print") == 0) { // Else, if print command inputted
		print();
	} else if (strcmp(userCommand, "run") == 0) { // Else, if run command inputted
		run();
	} else {
		printf("Unknown command\n"); // Otherwise, command is unknown
	}
}

int main() {
	// Welcome message
	printf("Welcome to the Oscar shell!\nVersion 1.0 Created January 2020\n");
	// Repeat until user quits
	while (running) {
		parse();
	}
	return 0;
}