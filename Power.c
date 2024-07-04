#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

int main(int argc, char* argv[]){
	int ans, num = atoi(argv[1]), pow1 = atoi(argv[2]);
	//check if the right amount of arguments are recieved
	if(argc != 3){
		printf("not the right amount of arguments\n");
		exit(1);
	}
	//check that the numbers recieved are valid
	if(strcmp(argv[1],"0") != 0 && num == 0 || strcmp(argv[2],"0") != 0 && pow1 == 0){
		printf("cant sqrt this\n");
		exit(1);
	}
	//perform num to the power of pow1
	ans = pow(num,pow1);
	printf("%d\n",ans);
	return ans;
} 
			
