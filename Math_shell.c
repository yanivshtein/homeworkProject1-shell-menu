#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>

// Function to count the number of lines in a file
int numLines(int fd){
	int count = 0, i, offset = lseek(fd,0,SEEK_END), rbytes;
	char buff[256];

	// Get the offset (file size)
	if(offset == -1){
		printf("Error getting offset\n");
		exit(1);
	}

	// Set the file cursor to the beginning
	if((offset = lseek(fd,0,SEEK_SET)) == -1){
		printf("Error setting cursor to beginning\n");
		exit(1);
	}

	// Read the file and count lines
	while((rbytes = read(fd,buff,255)) > 0){
		for(i = 0; i < rbytes; i++){
			if(buff[i] == '\n'){
				count++;
			}
		}
	}

	// Check for read errors
	if(rbytes == -1){
		printf("Error reading file\n");
		exit(1);
	}

	// Set the file cursor back to its original position
	if(lseek(fd,offset,SEEK_SET) == -1){
		printf("Error setting offset\n");
		exit(1);
	}

	// Return the count of lines
	return count + 1;
}

// Function to convert a number to a string
void numToChar(int line, char* charLine){
	int i = 0, digit, numofNumbers, currentLines = line;

	// Determine the number of digits in the line number
	while(currentLines > 0){
		i++;
		currentLines /= 10;
	}
	numofNumbers = i;

	// Convert the line number to a string
	while(line > 0){
		digit = line % 10;
		i--;
		charLine[i] = digit + '0';
		line /= 10;
	}
	charLine[numofNumbers] = '\0'; // Null-terminate the string
}

// Main function
int main(int argc, char* argv[]){
	char cmdLine[4], str[100], args[4][30], *token, file[40], charLine[10];
	int flag = 0, fd_to, i, amountCommands = 0, line;

	// Check if the right amount of arguments are received
	if(argc != 1){
		printf("not the right amount of arguments\n");
		exit(1);
	}

	// Initialize arguments array
	for(i = 0; i < 4; i++){
		strcpy(args[i], "");
	}

	// Create a directory if it doesn't exist
	if(opendir("Commands/Math") == NULL){
		if(mkdir("Commands/Math", 0775) == -1){
			printf("error creating folder\n");
			exit(1);
		}
	}

	// Specify the file path
	strcpy(file,"Commands/Math/Math_Commands.txt");

	// Check if the file exists and get the number of lines if it does
	if((fd_to = open(file, O_CREAT | O_RDONLY, 0664)) == -1){
		printf("error opening file\n");
		exit(1);
	}
	line = numLines(fd_to); // Get number of lines in the file
	close(fd_to);

	// Open the file for writing, append mode
	if((fd_to = open(file, O_WRONLY | O_APPEND | O_CREAT, 0664)) == -1){
		printf("error opening file\n");
		exit(1);
	}

	// Loop until "Cls" is entered
	while(1){
		printf("MathShell > ");

		// Build the line number string
		numToChar(line, charLine);

		// Write the line number to the file
		if(write(fd_to, charLine, strlen(charLine)) == -1){
			printf("error writing to file\n");
			exit(1);
		}

		// Write the separator and command string to the file
		cmdLine[0] = '.';
		cmdLine[1] = ' ';
		cmdLine[2] = '\0';
		if(write(fd_to, cmdLine, strlen(cmdLine)) == -1){
			printf("error writing to file\n");
			exit(1);
		}

		// Receive the whole command from stdin
		fgets(str, 99, stdin);

		// Write the command to the file
		if(write(fd_to, str, strlen(str)) == -1){
			printf("error writing to file\n");
			exit(1);
		}

		// Replace \n with \0 in the string
		str[strcspn(str, "\n")] = '\0';

		// If "Cls" is entered, break out of the loop
		if(strcmp(str, "Cls") == 0){
			break;
		}

		// Split the command received by space, and put in args
		i = 0;
		token = strtok(str, " ");
		while(token != NULL){
			amountCommands++;
			strcpy(args[i], token);
			token = strtok(NULL, " ");
			i++;
		}

		// Check if supported commands are entered with the right amount of arguments, and execute them
		if(strcmp(args[0], "Sqrt") == 0 && strcmp(args[1], "") != 0 && strcmp(args[2], "") == 0){
			flag = 1;
			if(fork() == 0){
				execl(args[0], args[0], args[1], NULL);
				printf("executing Sqrt failed\n");
				exit(1);
			}
		}
		if(strcmp(args[0], "Power") == 0 && strcmp(args[1], "") != 0 && strcmp(args[2], "") != 0 && strcmp(args[3], "") == 0){
			flag = 1;
			if(fork() == 0){
				execl(args[0], args[0], args[1], args[2], NULL);
				printf("executing Power failed\n");
				exit(1);
			}
		}
		if(strcmp(args[0], "Solve") == 0 && strcmp(args[1], "") != 0 && strcmp(args[2], "") != 0 && strcmp(args[3], "") != 0 && amountCommands < 5){
			flag = 1;
			if(fork() == 0){
				execl(args[0], args[0], args[1], args[2], args[3], NULL);
				printf("executing Solve failed\n");
				exit(1);
			}
		}
		if(strcmp(args[0], "History") == 0){
			flag = 1;
			if(fork() == 0){
				execl("History", "History", "1", NULL);
				printf("executing History failed\n");
				exit(1);
			}
		}

		// If an unsupported command was given
		if(flag != 1){
			printf("NOT SUPPORTED\n");
		}

		// Wait for the child process to return
		wait(NULL);

		// Reset arguments and counters
		flag = 0;
		for(i = 0; i < 4; i++){
			strcpy(args[i], "");
		}
		line++;
		amountCommands = 0;
	}

	// Close the file descriptor
	close(fd_to);

	return 0;
}
