#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

// Function to calculate the negative binary representation
int negative(int num){
	int bits = 1;
	while(bits < num){
		bits *= 2;
	}
	bits *= 4; // Adjust to get the proper bit range
	return bits - num; // Return the negative representation
}

int main(int argc, char* argv[]){
	// Check if the right amount of arguments are received
	if(argc != 2){
		printf("not the right amount of arguments");
		exit(1);
	}

	int bits = 1, num = atoi(argv[1]), count = 0;

	// Check that the number received is valid
	if(strcmp(argv[1],"0") != 0 && num == 0){
		printf("invalid number received\n");
		exit(1);
	}

	// If the number is negative, convert to its negative binary representation
	if(num < 0){
		num = negative(-num);
	}

	// Find the highest bit value less than or equal to num
	while(bits < num){
		bits *= 2;
	}

	// Construct the binary representation
	while(num > 0){
		count *= 10;
		if(num >= bits){
			num -= bits;
			count++;
		} 
		bits /= 2;
		// Pad with zeros while num is zero and there are still bits to process
		while(num == 0 && bits != 0){
			count *= 10;
			bits /= 2;
		}
	}

	// Print the final binary representation
	printf("%d\n",count);
	return count;
}
