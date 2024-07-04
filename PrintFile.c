#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
    char buff[256], *file; // Buffer to store file contents, pointer to file name
    int rbytes, fd_from; // Number of bytes read, file descriptor

    // Check if the correct number of arguments are provided
    if(argc != 2){
        printf("not the right amount of arguments\n");
        exit(1);
    }

    file = argv[1]; // Assign the file name from command line arguments

    // Open the file for reading
    if((fd_from = open(file, O_RDONLY)) == -1){
        printf("error opening file\n");
        exit(1);
    }

    // Read from the file and print its contents
    while((rbytes = read(fd_from, buff, 255)) > 0){
        buff[rbytes] = '\0'; // Null-terminate the buffer after reading
        printf("%s", buff); // Print the contents of the buffer
    }

    // Check for read errors
    if(rbytes == -1){
        printf("error reading from file\n");
        exit(1);
    }

    // Close the file descriptor
    close(fd_from);

    return 0;
}
