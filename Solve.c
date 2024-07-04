#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

int main(int argc, char* argv[]){
    // Check if the right amount of arguments are received
    if(argc != 4){
        printf("not the right amount of arguments\n");
        exit(1);
    }

    double ans1, ans2, a = atof(argv[1]), b = atof(argv[2]), c = atof(argv[3]);

    // Check that the numbers received are valid
    if((strcmp(argv[1], "0") != 0 && a == 0) || (strcmp(argv[2], "0") != 0 && b == 0) || (strcmp(argv[3], "0") != 0 && c == 0)){
        printf("invalid number received\n");
        exit(1);
    }

    // Check if the discriminant is negative
    if((pow(b, 2) - 4 * a * c) < 0){
        printf("No Sol!\n");
        exit(1);
    }

    // Calculate the solutions of the quadratic equation
    ans1 = (-b + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
    ans2 = (-b - sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);

    // Print the solutions
    if(ans1 == ans2){
        printf("%g\n", ans1);
    } else {
        printf("%g\n", ans1);
        printf("%g\n", ans2);
    }

    return 0;
}
