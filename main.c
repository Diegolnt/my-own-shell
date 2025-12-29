#include <stdio.h>
#include <unistd.h>

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

