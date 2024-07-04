#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
    // Check if the correct number of arguments are provided
    if(argc != 4){
        printf("not the right amount of arguments\n");
        exit(1);
    }

    char *temp = argv[1], *sentence = argv[1], *str = argv[2];
    int i, index = atoi(argv[3]) - 1;

    // Check if the replacement would go out of range
    if(index + strlen(str) > strlen(sentence)){
        printf("the length of the string and index requested to be replaced are out of range\n");
        exit(1);
    }

    // Move the temp pointer to the specified index
    for(i = 0; i < index; i++){
        temp++;
    }

    // Replace the characters in sentence with the new string
    for(i = 0; i < strlen(str); i++){
        temp[i] = str[i];
    }

    // Print the modified sentence
    printf("%s\n", sentence);

    return 0;
}
