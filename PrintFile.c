#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
	char buff[256], *file;
	int rbytes, fd_from;
	if(argc != 2){
		printf("not the right amount of arguments\n");
		exit(1);
	}
	file = argv[1];
	if((fd_from = open(file,O_RDONLY)) == -1){
		printf("error opening file\n");
		exit(1);
	}
	if((rbytes = read(fd_from,buff,255)) == -1){
		printf("error reading from file\n");
		exit(1);
	}
	buff[rbytes] = '\0';
	while(rbytes > 0){
		printf("%s",buff);
		if((rbytes = read(fd_from,buff,255)) == -1){
			printf("error reading from file\n");
			exit(1);
		}
		buff[rbytes] = '\0';
	}	 
	return 0;
} 
			
