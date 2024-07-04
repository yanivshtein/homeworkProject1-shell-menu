#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>

int numLines(int fd){
	int count = 0, i, offset = lseek(fd,0,SEEK_END), rbytes;
	char buff[256];
	if(offset == -1){
		printf("Error getting offset\n");
		exit(1);
	}
	if((offset = lseek(fd,0,SEEK_SET)) == -1){
		printf("Error setting cursor to beggining\n");
		exit(1);
	}
	while((rbytes = read(fd,buff,255)) > 0){
		for(i = 0; i < rbytes; i++){
			if(buff[i] == '\n'){
				count++;
				
			}
		}
	}
	if(rbytes == -1){
		printf("Error reading file\n");
		exit(1);
	}
	if(lseek(fd,offset,SEEK_SET) == -1){
		printf("Error setting offset\n");
		exit(1);
	}
	return count + 1;
}


void numToChar(int line, char* charLine){
	int i = 0, digit, numofNumbers, currentLines = line;
	while(currentLines > 0){
		i++;
		currentLines /= 10;
	}
	numofNumbers = i;
	while(line > 0){
		digit = line % 10;
		i--;
		charLine[i] = digit + '0';
		line /= 10;
	}
	charLine[numofNumbers] = '\0';
}


int main(int argc, char* argv[]){
	char cmdLine[4], str[100], args[4][30],*token, file[40], charLine[10];
	int flag = 0, fd_to, i, amountCommands = 0, line;
	//check if the right amount of arguments are recieved
	if(argc != 1){
		printf("not the right amount of arguments\n");
		exit(1);
	}
	//set all the args to be empty strings
	for(i = 0; i < 4; i++){
		strcpy(args[i], "");
	}
	//create a directory if it dosent exist yet
	if(opendir("Commands/Math") == NULL){
		if(mkdir("Commands/Math", 0775) == -1){
			printf("error creating folder\n");
			exit(1);
		}
	}
	strcpy(file,"Commands/Math/Math_Commands.txt");
	//check if the file exists and get the amount of lines that it has if it exists
	if((fd_to = open(file, O_CREAT | O_RDONLY, 0664)) == -1){
		printf("error opening file\n");
		exit(1);
	}
	line = numLines(fd_to);
	close(fd_to);
	//create a file if it dosent exist yet
	if((fd_to = open(file,O_WRONLY | O_APPEND | O_CREAT, 0664)) == -1){
		printf("error opening file\n");
		exit(1);
	}
	//loop until cls is entered
	while(1){
		printf("MathShell > ");
		//build the str that i want to save in Math_commands
		numToChar(line, charLine);
		if(write(fd_to,charLine,strlen(charLine)) == -1){
			printf("error writing to file\n");
			exit(1);
		}
		cmdLine[0] = '.';
		cmdLine[1] = ' ';
		cmdLine[2] = '\0';
		if(write(fd_to,cmdLine,strlen(cmdLine)) == -1){
			printf("error writing to file\n");
			exit(1);
		}
		//recieve the whole command
		fgets(str, 99, stdin);
		//write the command to the file
		if(write(fd_to,str,strlen(str)) == -1){
			printf("error writing to file\n");
			exit(1);
		}
		//replace \n with \0 in the string
		str[strcspn(str,"\n")] = '\0';
		//if cls is entered then finish this program and return to Standard_shell
		if(strcmp(str,"Cls") == 0){
			break;
		}
		//split the command recieved by space, and put in args
		i = 0;
		token = strtok(str," ");
		while(token != NULL){
			amountCommands++;
			strcpy(args[i], token);
			token = strtok(NULL," ");
			i++;
		}
		//check if Sqrt was entered with the right amount of arguments, and if so execute the program
		if(strcmp(args[0],"Sqrt") == 0 && strcmp(args[1],"") != 0 && strcmp(args[2],"") == 0){
			flag = 1;
			if(fork() == 0){
				execl(args[0],args[0],args[1],NULL);
				printf("executing Sqrt failed\n");
				exit(1);
			}
		}
		//check if Power was entered with the right amount of arguments, and if so execute the program
		if(strcmp(args[0],"Power") == 0 && strcmp(args[1],"") != 0 && strcmp(args[2],"") != 0 && strcmp(args[3],"") == 0){
			flag = 1;
			if(fork() == 0){
				execl(args[0],args[0],args[1],args[2],NULL);
				printf("executing Power failed\n");
				exit(1);
			}
		}
		//check if Solve was entered with the right amount of arguments, and if so execute the program
		if(strcmp(args[0],"Solve") == 0 && strcmp(args[1],"") != 0 && strcmp(args[2],"") != 0 && strcmp(args[3],"") != 0 && amountCommands < 5){
			flag = 1;
			if(fork() == 0){
				execl(args[0],args[0],args[1],args[2],args[3],NULL);
				printf("executing Solve failed\n");
				exit(1);
			}
		}
		//check if History was entered with the right amount of arguments, and if so execute the program
		if(strcmp(args[0],"History") == 0 ){
			flag = 1;
			if(fork() == 0){
				execl("History","History","1" ,NULL);
				printf("executing History failed\n");
				exit(1);
			}
		}
		//if an unsupported command was given
		if(flag != 1){
			printf("NOT SUPPORTED\n");
		}	
		//wait for the one son (if exists) that was picked on this iteration to come back
		wait(NULL);
		//reset the arguments
		flag = 0;
		for(i = 0; i < 4; i++){
			strcpy(args[i], "");
		}
		line++;
		amountCommands = 0;
	}
	close(fd_to);		
	return 0;
} 
			
