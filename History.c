#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
	char buff[256], file[50];
	int rbytes, fd_from;

	// Check if the right amount of arguments are received
	if(argc != 2){
		printf("not the right amount of arguments\n");
		exit(1);
	}

	// Determine which file to open based on the argument provided
	if(strcmp(argv[1],"1") == 0){
		strcpy(file,"Commands/Math/Math_Commands.txt");
	}else if(strcmp(argv[1],"2") == 0){
		strcpy(file,"Commands/Logic/Logic_Commands.txt");
	}else{
		strcpy(file,"Commands/String/String_Commands.txt");
	}

	// Open the specified file for reading
	if((fd_from = open(file,O_RDONLY)) == -1){
		printf("error opening file\n");
		exit(1);
	}

	// Read data from the file and display it
	if((rbytes = read(fd_from,buff,255)) == -1){
		printf("error reading from file\n");
		exit(1);
	}
	buff[rbytes] = '\0'; // Null-terminate the buffer

	while(rbytes > 0){
		printf("%s",buff); // Print the contents of the buffer
		if((rbytes = read(fd_from,buff,255)) == -1){
			printf("error reading from file\n");
			exit(1);
		}
		buff[rbytes] = '\0'; // Null-terminate the buffer
	}

	close(fd_from); // Close the file descriptor

	return 0;
}
