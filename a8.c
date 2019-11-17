/*
	Name: Dylan Richards,		Class: CPS360
	Section: 22371837,		Assignment: 08
	Due: November 25, 2019		Started: November 13, 2019
	Credit: 10 points

	Problem: Model a L1, 4-way associative cache with 4096 cache-lines. Each data-block is 64 bytes.

	Solution:

	Data-structure used:

	Accessing functions for the data structure:

	Errors handled:

	Limitations:

	Acknowledgment: I wrote the program for Rattan's CPS360 class.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SETS 1024
#define LINES 4

struct cacheline{
	char valid;
	unsigned char age;
	unsigned int tag;
};
typedef struct cacheline cache;

cache l1[SETS * LINES];
int reference, miss;

int main(int argc, char *argv[]){
	void checkargs(int argc, char *argv[]);
	void initcache(void);
	void processreffile(char policy);
	void printrslts(char *label);
	
	checkargs(argc, argv);

	initcache();
	srand(time(0));

	char policy;
	policy = strcmp(argv[1], "fifo");

	processreffile(policy);

	printrslts(policy ? "Random:" : "Fifo:");

	exit(0);
}

/*
*/
void checkargs(int argc, char *argv[]){
	void usage(char *progname);
	void die(char *reason);
	
	if(argc < 2) usage(argv[0]);

	if(strcmp(argv[1], "random") && strcmp(argv[1], "fifo"))
		die("<algo> needs to be \"random\" or \"fifo\"");
}

/*	Prints usage to stderr and terminates
*/
void usage(char *progname){
	fprintf(stderr, "%s <algo> < inputfile\n", progname);
	exit(1);
}

/*	Prints out why the program was terminated and terminate
*/
void die(char *reason){
	fprintf(stderr, "%s\n", reason);
	exit(1);
}

/*	Prints the results of the cache algorithm used
*/
void printrslts(char *label){
	printf("%s\t%d references, %d misses\n", label, reference, miss);
}

/*	Initilizes the cache by looping through all indexes of l1 and
	creating a new cache with values of zeros.
*/
void initcache(void){
	int i;
	for(i = 0; i < SETS * LINES; i++)
		l1[i] = (cache) {};
}

/*
*/
int getindex(unsigned int ref){
	return ((ref >> 6) & 0x3ff) << 2;
}

/*
*/
unsigned int gettag(unsigned int ref){
	return (ref >> 16) & 0xffff;
}

/*
*/
int isahit(unsigned int ref){
	int idx = getindex(ref);
	unsigned int tag = gettag(ref);

	int i;
	for(i = 0; i < 4; i++)
		if(l1[idx + i].valid && l1[idx + i].tag == tag)
			return 1;
	return 0;
}

/*
*/
int isamiss(unsigned int ref){
	return !isahit(ref);
}

/*
*/
int fillemptyline(cache *line, int index){
	int i;
	for(i = index; i < index + 4; i++){
		if(!l1[i].valid){
			l1[i] = *line;
			return 1;
		}
	}
	return 0;
}

/*	Random between 0 and 3.
*/
void randomalgo(cache *line, unsigned int ref){
	int idx = getindex(ref);

	line->valid = 1;
	if(fillemptyline(line, idx)) return;

	int rnd = rand() % 4;
	l1[idx + rnd] = *line;
}

/*
*/
void processreffile(char policy){
	int nextref;
	while(scanf("%x", &nextref) != EOF){
		reference++;
		if(isamiss(nextref)){
			miss++;

			cache line = {
				.tag = gettag(nextref)
			};
			
			if(policy) randomalgo(&line, nextref);
			else printf("FIFO:");
		}
	}
}
