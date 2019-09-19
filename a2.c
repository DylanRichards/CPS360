/*
	Name: Dylan Richards,		Class: CPS360
	Section: 22371837,		Assignment: 02
	Due: September 23, 2019		Started: September 12, 2019
	Credit: 10 points

	Problem: Create two linked lists of random numbers in a specified range. One list for even numbers, the other for odd numbers.
	If the random number generated is already in the linked list, delete it.

	Solution: Created two linked lists with the lnode struct. Determined if the random number was odd or even.
	Then searched corresponding list. If found, delete the node, otherwise add random number to list.

	Data-structure used: struct lnode with two members - a value and a pointer to the next lnode in the list.

	Accessing functions for the data structure: Standard C functions for accessing structs and modules.

	Errors handled: Command line arguments handled. If no arguments are specified, the program closes.

	Limitations: Normal system limitations on memory.

	Acknowledgment: I wrote the program for Rattan's CPS360 class.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RANGE 5

struct lnode {int value; struct lnode *next;};

typedef struct lnode lnode;

/*	Check if proper arguments were supplied. If not, print proper usage.
	Get repeated count from command line argument.
	Seed the random number generator with the system clock.
	Generate a random number and determine if it is even or odd. Insert number in list.
	Continue that process as specified in the command line argument.
	Print both lists and return the memory from the lists back to they system.
*/
int main(int argc, char *argv[]){
	if(argc < 2){
		void usage(char *progname);
		usage(argv[0]);
	}

	int repeatcount = atoi(argv[1]);

	srand(time(0));

	lnode *evenptr, **levens;
	levens = &evenptr;

	lnode *oddptr, **lodds;
	lodds = &oddptr;

	int insertinlist(lnode **list, int x);

	int i;
	for(i = 0; i < repeatcount; i++){
		int nextnum();
		int num = nextnum();

		if(num & 1){
			if(!insertinlist(lodds, num)) printf("ERROR Inserting\n");
		} else {
			if(!insertinlist(levens, num)) printf("ERROR Inserting\n");
		}
	}

	void printlist(lnode *list);
	printf("odd-list: ");
	printlist(*lodds);
	printf("even-list: ");
	printlist(*levens);

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
		if((*crnt) -> value == x)return;
		*pred = *crnt;
		*crnt = (*crnt) -> next;
	}
}

/*	Inserts x at the front of list if found in list, deletes it from the list otherwise.
	Returns 1 on success, 0 otherwise, calls search()
*/
int insertinlist(lnode **list, int x){
	void search(lnode *list, lnode **crnt, lnode **pred, int x);
	lnode *crntptr, **crnt;
	lnode *predptr, **pred;

	crnt = &crntptr;
	pred = &predptr;

	lnode *prev = *list;

	search(*list, crnt, pred, x);

	if(*crnt){
		int delfromlist(lnode **list, lnode *after);
		return delfromlist(list, predptr);
	} else {
		void getnode(lnode **ptr);
		getnode(list);

		if(!(*list)) return 0;

		(*list) -> value = x;
		(*list) -> next = prev;
	}

	return 1;
}

/*	Deletes the node from list that is successor of the node pointed by after.
	Returns 1 on success, 0 otherwise.
*/
int delfromlist(lnode **list, lnode *after){
	if(!*list) return 0;

	lnode *deletenode;

	if(!after){
		deletenode = *list;
		*list = deletenode -> next;
	} else {
		deletenode = after -> next;
		after -> next = deletenode -> next;
	}

	void freenode(lnode **ptr);
	freenode(&deletenode);
	return 1;
}

/*	Prints the contents of given list (on one line on stdout)
*/
void printlist(lnode *list){
	if(!list){
		printf("empty\n");
		return;
	}

	while(list){
		printf(" %d ", list -> value);
		list = list -> next;
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
