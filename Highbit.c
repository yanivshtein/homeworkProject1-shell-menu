#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]){
    int bits = 1, num = atoi(argv[1]), count = 0;

    // Check if the right amount of arguments are received
    if(argc != 2){
        printf("not the right amount of arguments");
        exit(1);
    }

    // Check that the number received is valid
    if((strcmp(argv[1], "0") != 0 && num == 0) || num < 0){
        printf("invalid number received\n");
        exit(1);
    }

    // Calculate the amount of bits required to represent the number
    while(bits < num){
        bits = bits * 2;
    }

    // Count the number of bits set to 1
    while(num > 0 && bits > 0){
        if(num >= bits){
            num = num - bits;
            count++;
        }
        bits = bits / 2;
    }

    // Print the count of bits set to 1
    printf("%d\n", count);

    return count;
}
