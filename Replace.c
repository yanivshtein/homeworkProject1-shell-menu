#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
	char *temp= argv[1], *sentence = argv[1], *str = argv[2];
	int i, index = atoi(argv[3])-1;
	for(i = 0; i < index; i++){
		temp++;
	}
	for(i = 0; i < strlen(str); i++){
		temp[i] = str[i];
	}
	printf("%s\n",sentence);
	return 0;
} 
			
