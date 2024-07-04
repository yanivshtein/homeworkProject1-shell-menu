#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>

// Function to find and copy the specific part of the sentence
void findSend(char* sentence, char* findSentence, int lenArg1, int lenArg2, int lenSentence){
    int i;
    // Move the pointer to the start of the substring to be copied
    for(i = 0; i < lenArg1 + lenArg2 + 2; i++){
        sentence++;
    }
    // Copy the substring into findSentence
    for(i = 0; i < lenSentence; i++){
        findSentence[i] = *sentence;
        sentence++;
    }
    // Null-terminate the findSentence string
    findSentence[lenSentence - lenArg2 - lenArg1 - 1] = '\0';
}

// Function to replace and split the sentence into parts
int replaceSend(char *sentence, char* findSentence, char* args2, char* args3){
    char *token, *token2, args[26];
    int i = 0;

    // Split the sentence by double quotes
    token = strtok(sentence, "\"");
    while(token != NULL){
        // Copy the first quoted string to findSentence
        if(i == 1){
            strcpy(findSentence, token);
        }
        // Copy the second quoted string to args
        if(i == 2){
            strcpy(args, token);
        }
        token = strtok(NULL, "\"");
        i++;
    }
    args[strlen(args)] = '\0';
    i = 0;

    // Split args by spaces and copy to args2 and args3
    token2 = strtok(args, " ");
    while(token2 != NULL){
        if(i == 0){
            strcpy(args2, token2);
        }
        if(i == 1){
            strcpy(args3, token2);
        }
        token2 = strtok(NULL, " ");
        i++;
    }

    // Return if more than two tokens are found
    return i > 2;
}

// Function to count the number of lines in a file
int numLines(int fd){
    int count = 0, i, offset = lseek(fd, 0, SEEK_END), rbytes;
    char buff[256];

    // Check for error in getting the offset
    if(offset == -1){
        printf("Error getting offset");
        exit(1);
    }
    // Set the cursor to the beginning of the file
    if((offset = lseek(fd, 0, SEEK_SET)) == -1){
        printf("Error setting cursor to beginning");
        exit(1);
    }
    // Read the file and count the number of newlines
    while((rbytes = read(fd, buff, 255)) > 0){
        for(i = 0; i < rbytes; i++){
            if(buff[i] == '\n'){
                count++;
            }
        }
    }
    // Check for error in reading the file
    if(rbytes == -1){
        printf("Error reading file");
        exit(1);
    }
    // Reset the cursor to the original offset
    if(lseek(fd, offset, SEEK_SET) == -1){
        printf("Error setting offset");
        exit(1);
    }

    // Return the line count, adding 1 for the last line
    return count + 1;
}

// Function to convert a number to a character string
void numToChar(int line, char* charLine){
    int i = 0, digit, numofNumbers, currentLines = line;

    // Count the number of digits in the line number
    while(currentLines > 0){
        i++;
        currentLines /= 10;
    }
    numofNumbers = i;

    // Convert each digit to a character
    while(line > 0){
        digit = line % 10;
        i--;
        charLine[i] = digit + '0';
        line /= 10;
    }

    // Null-terminate the charLine string
    charLine[numofNumbers] = '\0';
}

int main(int argc, char* argv[]){
    char cmdLine[10], str[100], args[4][30], *token, file[40], findSentence[100], sentence[100], args2[20], args3[5], charLine[10];
    int flag = 0, fd_to, i, amountCommands = 0, findFlag = 0, line;

    // Check if the right amount of arguments are received
    if(argc != 1){
        printf("not the right amount of arguments\n");
        exit(1);
    }

    // Set all the args to be empty strings
    for(i = 0; i < 4; i++){
        strcpy(args[i], "");
    }

    // Create a directory if it doesn't exist yet
    if(opendir("Commands/String") == NULL){
        if(mkdir("Commands/String", 0775) == -1){
            printf("error creating folder\n");
            exit(1);
        }
    }
    strcpy(file, "Commands/String/String_Commands.txt");

    // Check if the file exists and get the number of lines it has if it exists
    if((fd_to = open(file, O_CREAT | O_RDONLY, 0664)) == -1){
        printf("error opening file\n");
        exit(1);
    }
    line = numLines(fd_to);
    close(fd_to);

    // Create a file if it doesn't exist yet
    if((fd_to = open(file, O_WRONLY | O_APPEND | O_CREAT, 0664)) == -1){
        printf("error opening file\n");
        exit(1);
    }

    // Loop until "Cls" is entered
    while(1){
        printf("StringShell > ");

        // Build the str that I want to save in String_commands
        numToChar(line, charLine);
        if(write(fd_to, charLine, strlen(charLine)) == -1){
            printf("error writing to file\n");
            exit(1);
        }
        cmdLine[0] = '.';
        cmdLine[1] = ' ';
        cmdLine[2] = '\0';
        if(write(fd_to, cmdLine, strlen(cmdLine)) == -1){
            printf("error writing to file\n");
            exit(1);
        }

        // Receive the whole command
        fgets(str, 99, stdin);

        // Write the command to the file
        if(write(fd_to, str, strlen(str)) == -1){
            printf("error writing to file\n");
            exit(1);
        }

        // Replace \n with \0 in the string
        str[strcspn(str, "\n")] = '\0';
        strcpy(sentence, str);

        // If "Cls" is entered, finish this program and return to Standard_shell
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

        // Check if "PrintFile" was entered with the right amount of arguments, and if so execute the program
        if(strcmp(args[0], "PrintFile") == 0 && strcmp(args[1], "") != 0 && strcmp(args[2], "") == 0){
            flag = 1;
            if(fork() == 0){
                execl(args[0], args[0], args[1], NULL);
                printf("executing PrintFile failed\n");
                exit(1);
            }
        }

        // Check if "Find" was entered with the right amount of arguments, and if so execute the program
        if(strcmp(args[0], "Find") == 0 && strcmp(args[1], "") != 0 && strcmp(args[2], "") != 0){
            flag = 1;
            findSend(sentence, findSentence, strlen(args[0]), strlen(args[1]), strlen(sentence));
            if(fork() == 0){
                execl(args[0], args[0], args[1], findSentence, NULL);
                printf("executing Find failed\n");
                exit(1);
            }
        }

        // Check if "Replace" was entered with the right amount of arguments, and if so execute the program
        if(strcmp(args[0], "Replace") == 0){
            if(!replaceSend(sentence, findSentence, args2, args3)){
                flag = 1;
                if(fork() == 0){
                    execl(args[0], args[0], findSentence, args2, args3, NULL);
                    printf("executing Replace failed\n");
                    exit(1);
                }
            }
        }

        // Check if "History" was entered with the right amount of arguments, and if so execute the program
        if(strcmp(args[0], "History") == 0){
            flag = 1;
            if(fork() == 0){
                execl("History", "History", "3", NULL);
                printf("executing History failed\n");
                exit(1);
            }
        }

        // If an unsupported command was given
        if(flag != 1){
            printf("NOT SUPPORTED\n");
        }

        // Wait for the one child process (if exists) that was picked in this iteration to come back
        wait(NULL);

        // Reset the arguments
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
