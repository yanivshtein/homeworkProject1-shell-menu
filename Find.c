#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
	// Check if the correct number of arguments are received
    if(argc != 3){
        printf("not the right amount of arguments\n");
        exit(1);
    }

    // Buffer to hold part of the file content to compare
    char buff[strlen(argv[2]) + 1], *str = argv[2], *file;
    int flag = 0, rbytes, fd, size = strlen(argv[2]), offset = 0;


    file = argv[1];

    // Open the file in read-only mode
    if((fd = open(file,O_RDONLY)) == -1){
        printf("error opening file\n");
        exit(1);
    }

    // Read the first part of the file
    if((rbytes = read(fd,buff,size)) == -1){
        printf("error reading from file\n");
        exit(1);
    }
    buff[rbytes] = '\0'; // Null-terminate the buffer

    offset++;

    // Move the file offset by one byte
    if(lseek(fd,offset,SEEK_SET) == -1){
        printf("Error getting offset\n");
        exit(1);
    }

    // Compare the input string with the buffer content
    if(strcmp(str,buff) == 0){
        printf("WIN\n");
        return 0;
    }

    // Continue reading and comparing while there are bytes left to read
    while(rbytes > 0){
        if(strcmp(str,buff) == 0){
            printf("WIN\n");
            return 0;
        }
        if((rbytes = read(fd,buff,size)) == -1){
            printf("error reading from file\n");
            exit(1);
        }
        buff[rbytes] = '\0'; // Null-terminate the buffer
        offset++;

        // Move the file offset by one byte
        if(lseek(fd,offset,SEEK_SET) == -1){
            printf("Error getting offset\n");
            exit(1);
        }
    }

    printf("Try Again\n"); 
    return 0;
}
