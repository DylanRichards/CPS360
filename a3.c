/*
	Name: Dylan Richards,		Class: CPS360
	Section: 22371837,		Assignment: 03
	Due: October 04, 2019		Started: September 24, 2019
	Credit: 10 points

	Problem: Implement a fixed size set with element range of 0 - 255.

	Solution: Used a bitmap and a mask to change bit to one if the element is in the set.

	Data-structure used: A set struct comprised of the data and set count.

	Accessing functions for the data structure:

	Errors handled: None.

	Limitations: Elements cannot be outside the range of 0-255.

	Acknowledgment: I wrote the program for Rattan's CPS360 class.
*/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 32

struct set{
	char data[SIZE];
	int count;
};

typedef struct set set;

/*	Problem: Create two sets, do basic set operations, repeat 4 times
	Solution: Create two sets with two properties: a char array used as bitmap and
	the count of number of elements in the set. Print out simple set operations or
	build failure if input text is not formed correctly
*/
int main(void){
	set seta, setb;
	int i;

	void initaset(set *s1);
	void clearaset(set *s1);
	int buildaset(set *s1);
	void printaset(char *label, set s1);
	void dosetops(set seta, set setb);

	initaset(&seta);
	initaset(&setb);

	for(i = 0; i < 4; i++){
		if(!buildaset(&seta) || !buildaset(&setb)){
			fprintf(stderr, "Set build failure. \n");
			clearaset(&seta);
			clearaset(&setb);
			continue;
		}
		printaset("Set A:", seta);
		printaset("Set B:", setb);
		dosetops(seta, setb);
		clearaset(&seta);
		clearaset(&setb);
	}

	exit(0);
}

/*	Problem: Create a set with no elements
	Solution: Initializes the set to be empty - bits and count are cleared
*/
void initaset(set *s1){
	int i;

	s1->count = 0;
	for(i = 0; i < SIZE; i++) s1->data[i] = 0;
}

/*	Problem: Add elm to s1 if it does't already exist
	Solution: Add elm to set s1, updates the count member
*/
void addtoset(int elm, set *s1){
	int i, j;
	int isinset(int elm, set st);

	if(isinset(elm, *s1)) return;

	i = elm >> 3;
	j = elm & 7;

	s1->data[i] = s1->data[i] | (1<<j);
	s1->count += 1;
}

/*	Problem: Check if element is already in the set
	Solution: Checks if elm is in s1, returns 1 on success, 0 otherwise
*/
int isinset(int elm, set st){
	int i, j;

	i = elm >> 3;
	j = elm & 7;

	if(st.data[i] & (1<<j)) return 1;
	
	return 0;
}

/*	Problem: Perform a union operation on two sets
	Solution: s3 is a union of sets s1 and s2
*/
void setunion(set s1, set s2, set *s3){
	int i;
	for(i = 0; i < SIZE; i++){
		char uni = s1.data[i] | s2.data[i];
		
		if(uni){
			s3 -> data[i] = uni;
			int j;
			for(j = 0; j < 8; j++)
				if(uni & (1<<j)) s3->count++;
		}
	}
}

/*	Problem: Perform an intersection of two sets
	Soluction: s3 is an intersecion set of sets s1 and s2
*/
void setintersect(set s1, set s2, set *s3){
	int i;
	for(i = 0; i < SIZE; i++){
		char intr = s1.data[i] & s2.data[i];
		
		if(intr){
			s3 -> data[i] = intr;
			int j;
			for(j = 0; j < 8; j++)
				if(intr & (1<<j)) s3->count++;
		}
	}
}

/*	Problem: Perform a differents of two sets
	Solution: s3 contains elements that are in s1 and not in s2 -> s1-s2
*/
void setdiff(set s1, set s2, set *s3){
	int i;
	for(i = 0; i < SIZE; i++){
		char diff = s1.data[i] & ~s2.data[i];
		
		if(diff){
			s3 -> data[i] = diff;
			int j;
			for(j = 0; j < 8; j++)
				if(diff & (1<<j)) s3->count++;
		}
	}
}

/*	Perform the set operations and print results as needed.
	Result sets will have to cleared after each operation
*/
void dosetops(set seta, set setb){
	void initaset(set *s1);
	void clearaset(set *s1);
	void printaset(char *label, set s1);
	void setunion(set s1, set s2, set *s3);
	void setintersect(set s1, set s2, set *s3);
	void setdiff(set s1, set s2, set *s3);

	set setresult;	
	initaset(&setresult);

	setunion(seta, setb, &setresult);
	printaset("A union B:", setresult);
	
	clearaset(&setresult);
	setintersect(seta, setb, &setresult);
	printaset("A intersection B:", setresult);
	
	clearaset(&setresult);
	setdiff(seta, setb, &setresult);
	printaset("A difference B:", setresult);
	
	clearaset(&setresult);
	setdiff(setb, seta, &setresult);
	printaset("B difference A:", setresult);

	printf("\n");
}

/*	Writes the label (a C-string) followed by members of s1 to stderr
*/
void printaset(char *label, set s1){
	printf("%s", label);

	if(!s1.count){
		printf(" empty\n");
		return;
	}

	int i;
	for(i = 0; i < SIZE; i++){
		if(s1.data[i]){
			int index = i << 3;
			
			char a = s1.data[i];
			int j;
			for(j = 0; j < 8; j++)
				if(a & (1<<j)) printf(" %d ", index | j);
		}
	}

	printf("\n");
}

/*	Populates the set using values read from stdin,
	Upates the count of elements, checks for bad input,
	returns 1 on success 0 otherwise
*/
int buildaset(set *s1){
	void addtoset(int elm, set *s1);
	
	int i, count;
	if(!scanf("%d", &count)) return 0;
	
	for(i = 0; i < count; i++){
		int val;
		if(!scanf("%d", &val)) return 0;

		if(val < 0 || val > 255) continue;

		addtoset(val, s1);
	}

	return 1;
}

/*	Wrapper for initaset() call
*/
void clearaset(set *s1){
	void initaset(set *s1);
	initaset(s1);
}

