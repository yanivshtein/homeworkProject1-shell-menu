#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

int main(int argc, char* argv[]){
	double ans1, ans2, a = atoi(argv[1]), b = atoi(argv[2]), c = atoi(argv[3]);
	//check if the right amount of arguments are recieved
	if(argc != 4){
		printf("not the right amount of arguments\n");
		exit(1);
	}
	//check that the numbers recieved are valid
	if(strcmp(argv[1],"0") != 0 && 1 == 0 || strcmp(argv[2],"0") != 0 && b == 0 || strcmp(argv[2],"0") != 0 && c == 0){
		printf("cant sqrt this\n");
		exit(1);
	}
	if((pow(b,2) - 4*a*c) < 0){
		printf("No Sol!\n");
		exit(1);
	}
	ans1 = (-b + sqrt(pow(b,2) - 4*a*c))/2;
	ans2 = (-b - sqrt(pow(b,2) - 4*a*c))/2;
	if(ans1 == ans2){
		printf("%g\n", ans1);
	}else{
		printf("%g\n", ans1);
		printf("%g\n", ans2);
	}
	
	return 0;
} 
			
