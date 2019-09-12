/*
	Name: Dylan Richards,		Class: CPS360
	Section: 22371837,		Assignment: 02
	Due: September 20, 2019		Started: September 12, 2019
	Credit: 10 points

	Problem:

	Solution:

	Data-structure used:

	Accessing functions for the data structure:

	Errors handled: None.

	Limitations:

	Acknowledgment: I wrote the program for Rattan's CPS360 class.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RANGE 5

struct lnode {int value; struct lnode *next;};

typedef struct lnode lnode;

/*
*/
int main(int argc, char *argv[]){
	void usage(char *progname);
	int nextnum();
	
	int repeatcount;
	if(argc == 2){
		repeatcount = atoi(argv[1]);
	} else {
		usage("a2"); 	
	}

	srand(time(0));
	
	int i;
	for(i = 0; i < repeatcount; i++){
		int num = nextnum();

		if(num & 1){
			printf("Odd: %d\n", num);
		} else {	
			printf("Even: %d\n", num);
		}
	}

	exit(0);
}

/*	Prints usage to stderr and terminates
*/
void usage(char *progname){
	fprintf(stderr, "./%s <rep-count>\n", progname);
	exit(1);
}

/*	Generates the next number
*/
int nextnum(){
	return (rand() % RANGE);
}

/*	Gets a node for list using malloc(). The caller should check for call failure.
*/
void getnode(lnode **ptr){
	*ptr = malloc(sizeof(lnode));
}

/*	Returns node storage to system using free().
*/
void freenode(lnode **ptr){
	if(*ptr) free(*ptr);
	*ptr = NULL;
}

/*	Searches list for node containing x.
	If found, crnt is defined and pred points to crnt’s predecessor node.
	Crnt is undefined otherwise and pred has no meaning.
*/
void search(lnode *list, lnode **crnt, lnode **pred, int x){
	*crnt = list;
	*pred = NULL;
	while(*crnt){
		if((*crnt) -> value == x) return;
		*pred = *crnt;
		*crnt = (*crnt) -> next;
	}
}

/*	Inserts x at the front of list if found in list, deletes it from the list otherwise.
 *	Returns 1 on success, 0 otherwise, calls search()
*/
int insertinlist(lnode **list, int x);

/*	Deletes the node from list that is successor of the node pointed by after.
	Returns 1 on success, 0 otherwise.
*/
int delfromlist(lnode **list, lnode *after);

/*	Prints the contents of given list (on one line on stdout)
*/
void printlist(lnode *list);

/*	Returns the node storage to system for nodes in the list, one node at a time.
	Calls freenode(). Returns empty list to caller.
*/
void freelist(lnode **list){
	lnode *ptr, *tp;
	ptr = *list;
	while(ptr){
		tp = ptr;
		ptr = ptr -> next;
		freenode(&tp);
	}
	*list = NULL;
}
