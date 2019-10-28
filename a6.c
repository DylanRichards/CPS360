/*
	Name: Dylan Richards,		Class: CPS360
	Section: 22371837,		Assignment: 06
	Due: October 30, 2019		Started: October 27, 2019
	Credit: 10 points

	Problem: Given a list of students exams calculate the high, low, and average means.
	One implementation should be in C and the second implementations is in assembly.

	Solution: Get input from stdin. Create an implemention of procdata in C using pointers instead of array notation.
	The assembly implementation is in procdata1.s

	Data-structure used: A one dimentional array.

	Accessing functions for the data structure: Standard C functions for accessing modules.

	Errors handled: Input errors and wrong number of students.

	Limitations: Normal integer limitations on the size of the number.

	Acknowledgment: I wrote the program for Rattan's CPS360 class.
*/

#include <stdio.h>
#include <stdlib.h>

/*	Create a students exam array from numbers inputed from standard input.
	Print out the student who averaged the highest and lowest.
	Print out the overall average of all exams.
*/
int main(void){
	int getcount(void);
	int getdata(int data[], int nstudents);
	void procdata(int tscores[], int nstudents, int *lowmean, int *highmean, int *meanofmean);
	void procdata1(int tscores[], int nstudents, int *lowmean, int *highmean, int *meanofmean);
	void printresults(char *label, int mlow, int mhigh, int mmean);

	int nstudents = getcount();
	int *scores = (int *) malloc(sizeof(int) * (nstudents * 3));

	nstudents = getdata(scores, nstudents);

	int lowmean, highmean, meanofmean;

	procdata(scores, nstudents, &lowmean, &highmean, &meanofmean);
	printresults("Procdata produced:", lowmean, highmean, meanofmean);

	printf("\n");

	procdata1(scores, nstudents, &lowmean, &highmean, &meanofmean);
	printresults("Procdata1 produced:", lowmean, highmean, meanofmean);
	
	exit(0);
}

/*	Problem: Get a count of students
	Solution: Return the first line using scanf
*/
int getcount(void){
	int count;
	scanf("%d", &count);
	return count;
}

/*	Problem: Fill the array data with the scores from stdin.
	Return: The count of students actually read in.
*/
int getdata(int data[], int nstudents){
	int i;
	int exam1, exam2, exam3;

	for(i = 0; i < nstudents; i++){
		scanf("%d %d %d", &exam1, &exam2, &exam3);
		if(exam1 == -1 || exam2 == -1 || exam3 == -1) break;
		*(data + i * 3 + 0) = exam1;
		*(data + i * 3 + 1) = exam2;
		*(data + i * 3 + 2) = exam3;
	}

	return i;
}

/*	Calculate the mean of each students score.
	Set the lowmean with the student with the lowest average exams.
	Set highmean to the highest averge exam grade.
*/
void procdata(int tscores[], int nstudents, int *lowmean, int *highmean, int *meanofmean){
	int i, sum = 0, mean = 0;
	*lowmean = 100;
	*highmean = 0;

	for(i = 0; i < nstudents; i++){
		mean = (*(tscores + i * 3 + 0) + *(tscores + i * 3 + 1) + *(tscores + i * 3 + 2)) / 3;
		sum += mean;
		if(*lowmean > mean) *lowmean = mean;
		if(*highmean < mean) *highmean = mean;
	}

	*meanofmean = sum / nstudents;
}

/*	Print the label and low, high, and mean scores.
*/
void printresults(char *label, int mlow, int mhigh, int mmean){
	printf("%s\n\n", label);
	printf("Lowest score : %d\n", mlow);
	printf("Highest score: %d\n", mhigh);
	printf("Mean score   : %d\n", mmean);
}
