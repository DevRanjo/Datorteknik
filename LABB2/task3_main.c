#include <stdio.h>

int XOR(int, int);
int axor(int, int);

int main(){
	
	printf("För 3 XOR 5:\n");
	printf("c: %d\n", XOR(3,5));
	printf("assembly: %d\n", axor(3,5));
	
	printf("\nFör 15 XOR 25:\n");
	printf("c: %d\n", XOR(15,25));
	printf("assembly: %d\n", axor(15,25));
	
	printf("\nFör 42 XOR 76:\n");
	printf("c: %d\n", XOR(42,76));
	printf("assembly: %d\n", axor(42,76));
	
	printf("\nFör 7 XOR 14:\n");
	printf("c: %d\n", XOR(7,14));
	printf("assembly: %d\n", axor(7,14));
}