#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

int main(int argc, char* argv[]){
    // Check if the right amount of arguments are received
    if(argc != 2){
        printf("not the right amount of arguments\n");
        exit(1);
    }

    double ans, num = atof(argv[1]);

    // Check that the number received is valid
    if(strcmp(argv[1], "0") != 0 && num == 0){
        printf("cant sqrt this\n");
        exit(1);
    }

    // Check if the number is greater than 0
    if(num < 0){
        printf("Math Error!\n");
        exit(1);
    }

    // Calculate the square root of the number
    ans = sqrt(num);

    // Print the result
    printf("%g\n", ans);

    return 0;
}
