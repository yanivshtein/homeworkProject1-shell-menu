#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]){
	if(argc != 1){
		printf("not the right amount of arguments");
		exit(1);
	}
	if(fork() == 0){
		execlp("rm","rm","-rf","Commands",NULL);
		printf("error removing Commands directory");
		exit(1);
	}
	printf("Goodbye...\n");
	return 0;
} 
			
