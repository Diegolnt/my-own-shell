#include <stdio.h>
#include <unistd.h> # UNIX libraries
#include <sys/wait.h> # Wait forks use this
#include <sys/types.h> # Types of data
#include <stdlib.h> # Memory Management

int main(){
	
	while(1){
		char buffer[100]; //Buffer of the input maximum of 99 characters plus null terminator
		printf("Input$: ");
		if (fgets(buffer, sizeof(buffer), stdin) != NULL){
			printf("This is your input: %s \n", buffer);
		}
	}
	return 0;
}

