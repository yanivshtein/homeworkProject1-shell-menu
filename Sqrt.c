#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <math.h>


int main(int argc, char* argv[]){
	double ans, num = atoi(argv[1]);
	//check if the right amount of arguments are recieved
	if(argc != 2){
		printf("not the right amount of arguments\n");
		exit(1);
	}
	//check that the number recieved is valid
	if(strcmp(argv[1],"0") != 0 && num == 0){
		printf("cant sqrt this\n");
		exit(1);
	}
	//check if number is bigger than 0
	if(num < 0){
		printf("Math Error!\n");
		exit(1);
	}
	ans = sqrt(num);
	//perform the sqrt of the numbe
	printf("%g\n", ans);
	return ans;
} 
			
