/*
	Name: Dylan Richards,		Class: CPS360
	Section: 22371837,		Assignment: 01
	Due: September 11, 2019		Started: September 4, 2019
	Credit: 10 points

	Problem: Create a simple C program that compiles using a Makefile on a Linux operating system.
	The program should output simple statistics on a list of numbers.
	The statistics include the largest and smallest value, the integer average,
	and the count of numbers above the average.
	The list of numbers was printed with eight digit columns, right justified.
	The data array was printed with the same integer representation with seven numbers per line.	

	Solution: The list of numbers were stored in an int array. Four calculation modules were made
	largest, smallest, average, abvaverage. Two output modules were made printdata and printrslts.
	The calulation modules were executed first to gather the insights and then were printed out to the console.
	The output took advantage of printf's formatting of numbers to get the desired output.

	Data-structure used: A one dimensional array was used to hold the list of numbers.

	Accessing functions for the data structure: Standard C functions for accessing arrays and modules.

	Errors handled: None.

	Limitations: Normal int limitations on the size of the number. System limitations on the array size.

	Acknowledgment: I wrote the program independently for Dr. Rattan's CPS360 class.
*/

#include <stdio.h>
#include <stdlib.h>

/*	Creates a data array and prints out the array and features of it, including
	the largest and smallest value
	the average integer value
	and the count of numbers in the array that are above the average.
*/
int main(void){
	int data[29] = {1, 2, 3, -3, -99, 999, 42, 14, 56, 76, 99, 12,
		-2345, 3456789, 199, 123, 234, -567, -999, 21, 32,
		-12345, 324, 345, 387, 456, 4095, 1999, 8192};
	int size;
	
	int largest(int d[], int size);
	int smallest(int d[], int size);
	int average(int d[], int size);
	int abvaverage(int d[], int size, int average);
	void printdata(int d[], int size);
	void printrslts(int largest, int smallest, int average, int abvaverage);
	
	size = 29;
	
	if (size > 0){
		int lrgst = largest(data, size);
		int smllst = smallest(data, size);
		int avrg = average(data, size);
		int abvavrg = abvaverage(data, size, avrg);
		
		printf("Data set:\n");
		printdata(data, size);
		
		printf("\n\n");
		printrslts(lrgst, smllst, avrg, abvavrg);
	}
	
	exit(0);
}

/*	For a given int array and the size of the array, largest will return the biggest number in the array
	First, set the largest value to the first item in the array.
	Then, go through each item in the array, if an item is greater than the current largest number,
	update the largest number with the current number.
*/
int largest(int d[], int size){
	int lrgst;

	if(size > 0){
		lrgst = d[0];
	}

	int i;
	for(i = 1; i < size; i++){
		if(d[i] > lrgst){
			lrgst = d[i];
		}
	}

	return lrgst;
}


/*	For a given int array and the size of the array, smallest will return the lowest number in the array
	First, set the smallest value to the first item in the array.
	Then, go through each item in the array, if an item is less than the current smallest number,
	update the smallest number with the current number.
*/
int smallest(int d[], int size){
	int smllst;
	
	if(size > 0){
		smllst = d[0];
	}

	int i;
	for(i = 1; i < size; i++){
		if(d[i] < smllst){
			smllst = d[i];
		}
	}

	return smllst;
}

/*	For a given int array and the size of the array, average will return the average integer value of the array.
	Go through the array and create a running total of the sum of all the numbers.
	Divide the sum of the array by the number of items in the array and return that value.
*/
int average(int d[], int size){
	int avg;

	int i;
	for(i = 0; i < size; i++){
		avg += d[i];
	}

	avg = avg / size;
	
	return avg;
}

/*	For a given int array, size of the array, and the average integer value of the array,
	abvaverage will return the number of items in the array whos values are greater than the average.
	Go through every item in the array and check if the current value is grater than the average,
	if the current value of the array is greater than the average increment a counter and return it.
*/
int abvaverage(int d[], int size, int average){
	int count = 0;

	int i;
	for(i = 0; i < size; i++){
		if(d[i] > average){
			count++;
		}
	}

	return count;
}


/*	Prints out integer array with seven numbers per line
	Each integer is printed in eight columns right justified
*/
void printdata(int d[], int size){
	int i;
	for(i = 0; i < size; i++){
		if(i % 7 == 0 && i != 0){
			printf("\n");
		}

		printf("%8d\t", d[i]);
	}
}

/*	Prints out largest, smallest, average, and the count above average
	where each integer is printed right justified with eight columns
*/
void printrslts(int largest, int smallest, int average, int abvaverage){
	printf("Largest value:       %8d \n", largest);
	printf("Smallest value:      %8d \n", smallest);
	printf("Average value:       %8d \n", average);
	printf("Count above average: %8d \n", abvaverage);
}
