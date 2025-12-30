#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

// First Introduction to Forks

int main(){
	
	int pid = fork();
	
	if (pid == 0){
		printf("this is the child process with this parent id: %d and this child id: %d",getpid(),pid);
		}
	else if (pid!=0){
		printf("this is the parent process with this parent id: %d",getpid());
		}
	while(1){
		char buffer[100]; //Buffer of the input maximum of 99 characters plus null terminator
		printf("Input$: ");
		if (fgets(buffer, sizeof(buffer), stdin) != NULL){
			printf("This is your input: %s \n", buffer);
		}
	}
	return 0;
}

