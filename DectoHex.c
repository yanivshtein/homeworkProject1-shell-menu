#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]){
	//check if the right amount of arguments are recieved
	if(argc != 2){
		printf("not the right amount of arguments");
		exit(1);
	}
	printf("%X\n",atoi(argv[1]));
	return 1;
} 
			
