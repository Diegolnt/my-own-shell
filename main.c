/*
A simple Unix Shell
Author: Diego Echverría
Date: January 2026
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h> // Needed for strlen
#include <sys/types.h>
#include <sys/wait.h> // For wait()

#define BUFFER_SIZE 1024
#define MAX_ARGS 32
#define DELIMETERS " \t\n"

const char *builtinstr[] = {
	"ls",
	"pwd",
	"cat",
	"echo",
	"mkdir", "rm", "cp", "mv",
	"grep", "find", "wc"
};


char *read_line(void); // Receive line
char **parse_line(char *args); // Split instructions into array
int is_builtin(char *cmd); // Receive instruction  and decide
int num_builtins(){
	return sizeof(builtinstr)/sizeof(char *); // Dynamic calculaition of num of builtins (not necesary but good practice)
}
			   
int main(){
	// Buffer
	char buffer[1024];

	printf("Begin Initialization [+]\n");
	while (1){
		printf("<>:"); // Receive input
		char *result = read_line();
		printf("Result: %s \n",result);
		char **results = parse_line(result);
		int i = 0;
		while (results[i]!=NULL){
			printf("Resultado 2: %s \n",results[i]);
			printf("Resultado 3 (isbuiltin): %d \n", is_builtin(results[i]));
			i++;
		}
	}
	return 0; // just for standard practice
}



char *read_line(void){
	char *line = NULL;
	size_t buffsize = 1024; // Trying fgets replacement

	if (getline(&line,&buffsize,stdin)==-1){
		perror("read_line getline error");
	}
 
	return line;
}

char **parse_line(char *line){
	int position = 0;	
	char **tokens = malloc(MAX_ARGS * sizeof(char*));
	char *token;

	if (!tokens){
		fprintf(stderr, "Allocation error \n");
		exit(1);
	}
	token = strtok(line, DELIMETERS);
	while (token != NULL){
		tokens[position] = token;
		position++;

		token = strtok(NULL, DELIMETERS);
	}

	return tokens;
}

int is_builtin(char *instruction){
	if (instruction == NULL) return 0;
	for (int i=0; i<num_builtins(); i++){
		if (strcmp(instruction, builtinstr[i]) == 0){
			return 1; // Is a built in
		}
	}
	return 0; // not found in builtin array
}
