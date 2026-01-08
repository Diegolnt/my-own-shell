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

// Functions Declaration
int shell_cd(char **args);
int shell_exit(char **args);
int shell_help(char **args);

// Builtins Array
const char *builtinstr[] = {
	"cd", "exit", "help"
};

// We declare an array of pointers to functions that receive arrays of text and return integers
int (*builtin_func[]) (char**) = {
	&shell_cd,
	&shell_exit,
	&shell_help
};

int shell_num_builtins() {
    return sizeof(builtinstr) / sizeof(char *);
}

char *read_line(void); // Receive line
char **parse_line(char *args); // Split instructions into array
int is_builtin(char *cmd); // Receive instruction  and decide

//Shell Builtins
int shell_cd(char **args);
int shell_exit(char **args);
int shell_help(char **args);

//Externals 
int shell_launch(char **args);
//Router
int shell_execute(char **args);
			   
int main(){
	// Buffer
	char buffer[1024];
	char **args;
	int status;

	printf("Begin Initialization [+]\n");

	do {
		printf("<>:"); // Receive input
		char *line = read_line();	
		char **args = parse_line(line);
		

		status = shell_execute(args); // Router
					      			
		// Free memory+
		free(line);
		free(args);
	} while (status);

	return 0; // just for standard practice
}



char *read_line(void){
	char *line = NULL;
	size_t buffsize = 0; 

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
	tokens[position] = NULL;
	return tokens;

}

int shell_launch(char **args){
	pid_t pid, wpid;
	int status;

	pid = fork();
	// Create Fork
	if (pid==0){
		//Child Process
		if (execvp(args[0], args) == 1){
			perror("Shell");
		}
		exit(EXIT_FAILURE);
	} else if (pid < 0){
		//Error Forking
		perror("Shell");
	} else {
		//Parent Process
		do {
			wpid = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return 1;
}

int shell_execute(char **args) {
    if (args[0] == NULL) {
        return 1; // Comando vacío
    }

    // Iteramos buscando si es builtin
    for (int i = 0; i < shell_num_builtins(); i++) {
        if (strcmp(args[0], builtinstr[i]) == 0) {
            // Si hay match, ejecutamos la función del puntero
            return (*builtin_func[i])(args);
        }
    }

    // Si no fue builtin, lanzamos externo
    return shell_launch(args);
}

int shell_cd(char **args){
	if (args[1] == NULL){
		perror("Shell: expected argument to \"cd\"\n");
	} else {
	  if (chdir(args[1]) != 0){
		perror("Shell");
	  }
	}
	return 1;
}

int shell_exit(char **args){
	return 0; // Break loop
}

int shell_help(char **args){
	printf("This is Diego's Shell\n");
	printf("Type program names and arguments, and hit enter. \n");
	printf("The following are built in:\n");

	for(int i = 0; i < shell_num_builtins(); i++){
		printf(" %s\n", builtinstr[i]);
	}
	return 1;
}



