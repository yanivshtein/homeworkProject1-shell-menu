#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

int main(int argc, char* argv[]){
    int ans;
    int num = atoi(argv[1]);
    int pow1 = atoi(argv[2]);

    // Check if the right amount of arguments are received
    if(argc != 3){
        printf("not the right amount of arguments\n");
        exit(1);
    }

    // Check that the numbers received are valid
    if((strcmp(argv[1], "0") != 0 && num == 0) || (strcmp(argv[2], "0") != 0 && pow1 == 0)){
        printf("invalid number received\n");
        exit(1);
    }

    // Perform num to the power of pow1
    ans = pow(num, pow1);

    // Print the result
    printf("%d\n", ans);

    return ans;
}
