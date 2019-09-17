/*
	Name: Dylan Richards,		Class: CPS360
	Section: 22371837,		Assignment: 02
	Due: September 23, 2019		Started: September 12, 2019
	Credit: 10 points

	Problem:

	Solution:

	Data-structure used:

	Accessing functions for the data structure:

	Errors handled: Command line arguments handled. If no arguments are specified, the program closes.

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
	if(argc < 2){
		void usage(char *progname);
		usage(argv[0]);
	}
	
	int repeatcount = atoi(argv[1]);

	srand(time(0));
	
	int insertinlist(lnode **list, int x);

	lnode *evenptr, **levens;
	levens = &evenptr;
	
	lnode *oddptr, **lodds;
	lodds = &oddptr;

	int i;
	for(i = 0; i < repeatcount; i++){
		int nextnum();
		int num = nextnum();

		if(num & 1){
			printf("Odd: %d\n", num);
			if(!insertinlist(lodds, num)) printf("ERROR Inserting");

		} else {
			printf("Even: %d\n", num);	
			if(!insertinlist(levens, num)) printf("ERROR Inserting");

		}
	}
	
	if(*levens == NULL){
		printf("Error");
		exit(1);
	}


	void printlist(lnode *list);
	printf("Evens: ");
	printlist(*levens);
	printf("Odds: ");
	printlist(*lodds);

	void freelist(lnode **list);
	freelist(levens);
	freelist(lodds);

	exit(0);
}

/*	Prints usage to stderr and terminates
*/
void usage(char *progname){
	fprintf(stderr, "%s <rep-count>\n", progname);
	exit(1);
}

/*	Generates the next number
*/
int nextnum(){
	return (rand() % RANGE) + 1;
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
	Returns 1 on success, 0 otherwise, calls search()
*/
int insertinlist(lnode **list, int x){
	void search(lnode *list, lnode **crnt, lnode **pred, int x);
	
	lnode *prev = *list;
	void getnode(lnode **ptr);
	
	getnode(list);
		
	if(*list == NULL) return 0;

	(*list) -> value = x;
	(*list) -> next = prev;

	return 1;
}

/*	Deletes the node from list that is successor of the node pointed by after.
	Returns 1 on success, 0 otherwise.
*/
int delfromlist(lnode **list, lnode *after);

/*	Prints the contents of given list (on one line on stdout)
*/
void printlist(lnode *list){
	int i;

	printf("%d", list -> value);
	for(i = 0; list -> next != NULL; i++){
		list = list -> next;
		printf(", %d", list -> value);
	}

	printf("\n");
}

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
