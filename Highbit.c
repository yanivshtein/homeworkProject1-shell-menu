#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]){
	int bits = 1, num = atoi(argv[1]), count = 0;
	//check if the right amount of arguments are recieved
	if(argc != 2){
		printf("not the right amount of arguments");
		exit(1);
	}
	//check that the number recieved is valid
	if(strcmp(argv[1],"0") != 0 && num == 0 || num < 0){
		printf("invalid number recieved\n");
		exit(1);
	}
	//calculate the amount of bits
	while(bits < num){
		bits = bits * 2;
	}
	while(num > 0 && bits > 0){
		if(num >= bits){
			num = num - bits;
			count++;
		}
		bits = bits/2;
	}
	printf("%d\n",count);
	return count;
} 
			
