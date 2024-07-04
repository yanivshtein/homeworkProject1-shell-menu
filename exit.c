#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]){
    // Check if the right amount of arguments are received
    if(argc != 1){
        printf("not the right amount of arguments");
        exit(1);
    }

    // Create a child process to execute the "rm" command
    if(fork() == 0){
        // Remove the "Commands" directory recursively and forcefully
        execlp("rm", "rm", "-rf", "Commands", NULL);
        // If execlp fails, print an error message
        printf("error removing Commands directory");
        exit(1);
    }

    // Print goodbye message
    printf("Goodbye...\n");

    return 0;
}
