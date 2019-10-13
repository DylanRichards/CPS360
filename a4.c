/*
	Name: Dylan Richards,		Class: CPS360
	Section: 22371837,		Assignment: 04
	Due: October 16, 2019		Started: October 7, 2019
	Credit: 10 points

	Problem: Simulate combinational circuits using only bitwise operators.
	Half adder, full adder, 4-bit ripple carry adder, 4-bit look ahead adder
	Even parity 3-bit generator, Odd parity 4-bit check
	2x1 and 4x1 multiplexier. The input will be three hexidecimal numbers.
	Output will be printed in binary.

	Solution: The program uses simple bitwise operators (or, and, bit shifting)
	to implement the functionality of simple circuts. The boolean expression of the
	combinational circuit was implimented.	

	Data-structure used: None.

	Accessing functions for the data structure: Standard C functions for accessing modules.

	Errors handled: The program insures four parameters were entered including the program name

	Limitations: Limitations are based on the combinational circuit implemented.

	Acknowledgment: I wrote this program for Rattan's CPS360 class.
*/

#include <stdio.h>
#include <stdlib.h>

/*	Check if the program was started with the correct arguments. Parse the three hex inputs.
	Call circuit simulation modules and print the results.
*/
int main(int argc, char *argv[]){
	if(argc < 4){
		void usage(char *progname);
		usage(argv[0]);
	}

	int a = strtol(argv[1], NULL, 16);
	int b = strtol(argv[2], NULL, 16);
	int c = strtol(argv[3], NULL, 16);

	void printresult(char *label, int a);

	int sum, outcary;
	
	void halfaddr(int a, int b, int *sum, int *outcary);
	halfaddr(a, b, &sum, &outcary);
	printf("halfadder:\n");
	printresult("sum:", sum);
	printresult("outcary:", outcary);

	printf("\n");

	void fulladdr(int a, int b, int incary, int *sum, int *outcary);
	fulladdr(a, b, c, &sum, &outcary);
	printf("fulladder:\n");
	printresult("sum:", sum);
	printresult("outcary:", outcary);

	printf("\n");

	void rcadd4(int a, int b, int incary, int *sum, int *outcary);
	rcadd4(a, b, c, &sum, &outcary);
	printf("rcadd4 (4-bit-adder):\n");
	printresult("sum:", sum);
	printresult("outcary:", outcary);

	printf("\n");
	
	void lacadd4(int a, int b, int incary, int *sum, int *outcary);
	lacadd4(a, b, c, &sum, &outcary);
	printf("lacadd4 (4-bit-adder):\n");
	printresult("sum:", sum);
	printresult("outcary:", outcary);

	printf("\n");

	void evenparity3gen(int a, int *paritybit);
	int paritybit;
	evenparity3gen(a, &paritybit);
	printf("evenparity3gen:\n");
	printresult("paritybit:", paritybit);

	printf("\n");

	void oddparity4chk(int a, int *checkbit);
	int checkbit;
	oddparity4chk(a, &checkbit);
	printf("oddparity4chk:\n");
	printresult("checkbit:", checkbit);

	printf("\n");

	int yout;

	void mux2by1(int a, int b, int *yout);
	mux2by1(a, b, &yout);
	printf("mux2by1:\n");
	printresult("yout:", yout);

	printf("\n");

	void mux4by1(int a, int b, int *yout);
	mux4by1(a, b, &yout);
	printf("mux4by1:\n");
	printresult("yout:", yout);
	
	exit(0);
}

/*	Problem: Inform user if the program was started incorrectly
	Solution: Print how the user should start the program to stderr
*/
void usage(char *progname){
	fprintf(stderr, "%s <arg-a> <arg-b> <arg-c>\n", progname);
	exit(1);
}

/*	Problem: Simulate HA on bit 0 of a and b
	Solution: set a and b to the LSB.
	sum = a (XOR) b
	outcary = ab
*/
void halfaddr(int a, int b, int *sum, int *outcary){
	a = a & 1; b = b & 1;

	*sum = a ^ b;
	*outcary = a & b;
}

/*	Problem: Simulate full adder on bit 0 of a, b, and incary
	Solution: Set a, b, and incary to the LSB.
	sum = a (XOR) b (XOR) incary
	outcary = ab + incary(a+b)
*/
void fulladdr(int a, int b, int incary, int *sum, int *outcary){
	a = a & 1; b = b & 1; incary = incary & 1;

	*sum = a ^ b ^ incary;
	*outcary = (a & b) | (incary & (a ^ b));
}

/*	Problem: Simulate a 4 bit ripple carry adder
	Solution: For each bit use the fulladdr. The outcary is used as the incary to the next full adder
*/
void rcadd4(int a, int b, int incary, int *sum, int *outcary){
	void fulladdr(int a, int b, int incary, int *sum, int *outcary);
	
	int a3 = (a >> 3)&1, a2 = (a >> 2)&1, a1 = (a >> 1)&1, a0 = a&1;
	int b3 = (b >> 3)&1, b2 = (b >> 2)&1, b1 = (b >> 1)&1, b0 = b&1;

	int sum3, sum2, sum1, sum0;
	int *s3 = &sum3, *s2 = &sum2, *s1 = &sum1, *s0 = &sum0;

	fulladdr(a0, b0, incary, s0, outcary);
	fulladdr(a1, b1, *outcary, s1, outcary);
	fulladdr(a2, b2, *outcary, s2, outcary);
	fulladdr(a3, b3, *outcary, s3, outcary);
	
	*sum = (sum3 << 3) | (sum2 << 2) | (sum1 << 1) | sum0;
}

/*	Problem: Simulate a look ahead carry adder.
	Solution: Calculate the out carries before using the full adder.
	sumi = use fulladdr
	ci+1 = (ai*bi) + (ci(ai XOR bi))
*/
void lacadd4(int a, int b, int incary, int *sum, int *outcary){
	void fulladdr(int a, int b, int incary, int *sum, int *outcary);
	
	int a3 = (a >> 3)&1, a2 = (a >> 2)&1, a1 = (a >> 1)&1, a0 = a&1;
	int b3 = (b >> 3)&1, b2 = (b >> 2)&1, b1 = (b >> 1)&1, b0 = b&1;

	int c1 = (a0 & b0) | (incary & (a0 ^ b0));
	int c2 = (a1 & b1) | (c1 & (a1 ^ b1));
	int c3 = (a2 & b2) | (c2 & (a2 ^ b2));

	int sum3, sum2, sum1, sum0;
	int *s3 = &sum3, *s2 = &sum2, *s1 = &sum1, *s0 = &sum0;

	fulladdr(a0, b0, incary, s0, outcary);
	fulladdr(a1, b1, c1, s1, outcary);
	fulladdr(a2, b2, c2, s2, outcary);
	fulladdr(a3, b3, c3, s3, outcary);
	
	*sum = (sum3 << 3) | (sum2 << 2) | (sum1 << 1) | sum0;	
}

/*	Problem: Generate an even parity bit for 3 bit input
	Solution: paritybit = a2 XOR a1 XOR a0
*/
void evenparity3gen(int a, int *paritybit){
	int a2 = (a >> 2)&1, a1 = (a >> 1)&1, a0 = a&1;
	*paritybit = a2 ^ a1 ^ a0;
}

/*	Problem: Generate a error checking bit.
	If the number of 1 bits is odd return 0
	If the number of 1 bits is even return 1 as there is an error.
	Solution: Use formula for evenparity check and XOR it with 1 to invert.
	checkbit = (a3 XOR a2 XOR a1 XOR a0) XOR 1
*/
void oddparity4chk(int a, int *checkbit){
	int a3 = (a >> 3)&1, a2 = (a >> 2)&1, a1 = (a >> 1)&1, a0 = a&1;
	*checkbit = (a3^a2^a1^a0) ^ 1;
}

/*	Problem: Simulate a 2x1 multiplexer.
	2 inputs are a1 and a0. b0 is the selection input
	Solution: b0' = b0n
	yout = (a0 * b0n) + (a1 * b0)
*/
void mux2by1(int a, int b, int *yout){
	int a1 = (a >> 1)&1, a0 = a&1;
	int b0 = b&1;
	int b0n = b0 ^ 1;
	
	*yout = (a0 & b0n) | (a1 & b0);
}

/*	Problem: Simulate a 4x1 multiplexer.
	4 inputs are a3, a2, a1, a0. b1 an b0 are selectors.
	Solution:
	yout = a0(b1n*b0n) + a1(b1n*b0) + a2(b1*b0n) + a3(b1*b0)
*/
void mux4by1(int a, int b, int *yout){
	int a3 = (a >> 3)&1, a2 = (a >> 2)&1, a1 = (a >> 1)&1, a0 = a&1;
	int b1 = (b >> 1)&1, b0 = b&1;
	int b1n = b1 ^ 1, b0n = b0^1;

	*yout = (a0 & (b1n & b0n)) | (a1 & (b1n & b0)) | (a2 & (b1 & b0n)) | (a3 & (b1 & b0));
}

/*	Problem: Print all bits in a as 8-bit groups
	Solution: Referenced bitprint.c in the handout
*/
void printresult(char *label, int a){
	printf("%-16s", label);

	int i, j;
	for(i = 31, j = 0; i >=0; i--, j++){
		if((j & 0x7) == 0) putchar(' ');
		(a & (1 << i)) ? putchar('1') : putchar('0');
	}
	
	printf("\n");
}

