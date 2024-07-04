#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]){
    // Check if the right amount of arguments are received
    if(argc != 2){
        printf("not the right amount of arguments");
        exit(1);
    }

    // Print the integer argument as a hexadecimal number
    printf("%X\n", atoi(argv[1]));
    
    return 1;
}
