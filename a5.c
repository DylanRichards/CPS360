/*
	Name: Dylan Richards,		Class: CPS360
	Section: 22371837,		Assignment: 05
	Due: October 24, 2019		Started: October 20, 2019
	Credit: 10 points

	Problem: Compute an algebraic expression, implementation one should be in C and the second implementations is in assembly.

	Solution: Implemented compute1 in C. The assembly implementation is in compute2.s

	Data-structure used: None.

	Accessing functions for the data structure: Standard C functions for accessing modules.

	Errors handled: Command line arguments handled. If incorrect arguments are specified, the program closes.
	Handled division by 0 errors.

	Limitations: Normal integer limitations on the size of the number.

	Acknowledgment: I wrote the program for Rattan's CPS360 class.
*/

#include <stdio.h>
#include <stdlib.h>

/*	Check if proper arguments were supplied. If not, print proper usage.
	Get a, b, c, d from command line and convert to an integer.
	Check if a or d is 0 to ensure there are no divisions by zero.
	Call the C implementation compute1.
	Call the assembly implementation compute2.
	Print the results of both implementations.
*/
int main(int argc, char *argv[]){
	if(argc < 5){
		void usage(char *progname);
		usage(argv[0]);
	}

	int a = atoi(argv[1]);
	int b = atoi(argv[2]);
	int c = atoi(argv[3]);
	int d = atoi(argv[4]);

	if(a == 0 || d == 0){
		fprintf(stderr, "a and/or d can not be 0\n");
		exit(1);
	}

	int compute1(int a, int b, int c, int d);
	int result1 = compute1(a, b, c, d);

	int compute2(int a, int b, int c, int d);
	int result2 = compute2(a, b, c, d);

	void printrslt(char *label, int result);
	printrslt("Compute1:", result1);
	printrslt("Compute2:", result2);

	exit(0);
}

/*	Prints usage to stderr and terminates
*/
void usage(char *progname){
	fprintf(stderr, "%s <a-value> <b-value> <c-value> <d-value>\n", progname);
	exit(1);
}

/*	Problem: Compute a mathematical expression and return the result
	Solution: Return the value of the algebraic expression
*/
int compute1(int a, int b, int c, int d){
	return a * b - c / d + b % a + b * c * d;
}

/*	Problem: Print the label and the result
	Solution: Print label a tab and the result with a new line
*/
void printrslt(char *label, int result){
	printf("%s \t %d\n", label, result);
}
