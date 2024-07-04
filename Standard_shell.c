#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char* argv[]){
	char args[4][30], *token, str[100];
	int i, flag = 0, amountCommands = 0;
	//check if the right amount of arguments are recieved
	if(argc != 1){
		printf("not the right amount of arguments\n");
		exit(1);
	}
	//loop until exit is entered
	while(1){
		printf("StandShell > ");
		//recieve the whole command
		fgets(str, 99, stdin);
		//replace \n with \0 in the string
		str[strcspn(str,"\n")] = '\0';
		//if exit is entered execute exit file which prints goodbye
		//break the loop and finish the program
		if(strcmp(str,"exit") == 0){
			if(fork() == 0){
				execl("exit", "exit", NULL);
				printf("error executing file\n");
				exit(1);
			}
			wait(NULL);
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
		//check if the args[1] is empty, and then check if it is a command we made up, and execute the program according to the command
		if(strcmp(args[1],"") == 0){
			if(strcmp(args[0],"Math") == 0){
				flag = 1;
				if(fork() == 0){
					execl("Math_shell", "Math_shell", NULL);
					printf("executing Math shell failed\n");
					exit(1);
				}
			}else if(strcmp(args[0],"Logic") == 0){
					flag = 1;
					if(fork() == 0){
						execl("Logic_shell", "Logic_shell", NULL);
						printf("executing Logic shell failed\n");
						exit(1);
					}
			}else if(strcmp(args[0],"String") == 0){
					flag = 1;
					if(fork() == 0){
						execl("String_shell", "String_shell", NULL);
						printf("executing String shell failed\n");
						exit(1);
					}
			}	
		}
		//if non of our commands were executed, check if it is built-in command, and execute with however many args there are
		if(flag != 1 && amountCommands < 5){
			if(strcmp(args[0],"") == 0){
			}else if(fork() == 0){
				if(strcmp(args[1],"") == 0){
					execlp(args[0],args[0], NULL);
					printf("NOT SUPPORTED\n");
					exit(1);
				}else if(strcmp(args[2],"") == 0){
						execlp(args[0], args[0], args[1], NULL);
						printf("NOT SUPPORTED\n");
						exit(1);
				}else if(strcmp(args[3],"") == 0){
						execlp(args[0], args[0], args[1], args[2], NULL);
						printf("NOT SUPPORTED\n");
						exit(1);
				}else{
					execlp(args[0], args[0], args[1], args[2], args[3], NULL);
					printf("NOT SUPPORTED\n");
					exit(1);
				}
			}
		}else if(amountCommands > 4){
			printf("NOT SUPPORTED\n");
		}
		//wait for the one son (if exists) that was picked on this iteration to come back
		wait(NULL);
		//reset the arguments
		for(i = 0; i < 4; i++){
			strcpy(args[i], "");
		}
		flag = 0;
		amountCommands = 0;
		
	}
	return 0;
} 
			
