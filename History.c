#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
	char buff[256], file [50];
	int rbytes, fd_from;
	if(argc != 2){
		printf("not the right amount of arguments\n");
		exit(1);
	}
	if(strcmp(argv[1],"1") == 0){
		strcpy(file,"Commands/Math/Math_Commands.txt");
	}else if(strcmp(argv[1],"2") == 0){
		strcpy(file,"Commands/Logic/Logic_Commands.txt");
	}else{
		strcpy(file,"Commands/String/String_Commands.txt");
	}
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
			
