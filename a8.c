/*
	Name: Dylan Richards,		Class: CPS360
	Section: 22371837,		Assignment: 08
	Due: November 25, 2019		Started: November 13, 2019
	Credit: 10 points

	Problem: Model a L1, 4-way associative cache with 4096 cache-lines. Each data-block is 64 bytes.
	A victim should be chosen by a command line argument of either random or fifo. The random
	algorithm should select one of the 4 lines at random to be replaced. The fifo algorithm should
	use a First In First Out data structure. The victim would be the oldest cache line in the set.

	Solution: The cache is an array of cachelines, the length is the number of sets (1024)
	times the number of lines per set (4). The random number algorithm generates a number
	between 0 and 3 and uses it to replace that cache line. The fifo algorithm uses the age
	to determine the oldes one to become the victim.

	Data-structure used: cacheline struct with valid, age, and tag members.

	Accessing functions for the data structure: Standard C functions for system calls and structs.

	Errors handled: Command line arguments.

	Limitations: Basic limitations regarding a 4 way associative cache. Only two victim selecting algorithms.

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

/*	Check arguments, create cache, seed random number generator.
	Set policy to 0 if algo is fifo.
	Processreffile and print results.
*/
int main(int argc, char *argv[]){
	void checkargs(int argc, char *argv[]);
	void initcache(void);
	void processreffile(char policy);
	void printrslts(char *label);
	
	checkargs(argc, argv);
	initcache();
	srand(time(0));
	char policy = strcmp(argv[1], "fifo");

	processreffile(policy);
	printrslts(policy ? "Random:" : "Fifo:");

	exit(0);
}

/*	Check the command line arguments to ensure program is run correctly
	There needs to be at least 2 arguments, if not display usage.
	The second argument must be random or fifo.
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

/*	Return the next 10 bits after the tag and shift that by two, to multiply by 4.
	Because that is the next entry in a 4-way associative cache.
*/
int getindex(unsigned int ref){
	return ((ref >> 6) & 0x3ff) << 2;
}

/*	Return the top 2 bytes of the reference which is used as the tag.
*/
unsigned int gettag(unsigned int ref){
	return (ref >> 16) & 0xffff;
}

/*	Check if the reference is already in the cache by comparing the tags.
	Return 1 if there is a hit and 0 if it is a miss.
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

/*	Check if it was not a hit.
*/
int isamiss(unsigned int ref){
	return !isahit(ref);
}

/*	If there is an empty slot in the cache, insert the line.
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

/*	Random line between 0 and 3 add the offset index.
*/
void randomalgo(cache *line, int index){
	int victim = rand() % 4 + index;
	l1[victim] = *line;
}

/*	Uses a First In First Out algorithm to determine the victim.
	This is implemented by finding the max age and choosing that as the victim.
	Every time this function is called it should also increase the age of the lines.
*/
void fifoalgo(cache *line, int index){
	int max = 0, victim = 0;

	int i;
	for(i = index; i < index + 4; i++){
		if(l1[i].age > max){
			max = l1[i].age;
			victim = i;
		}
		l1[i].age++;
	}

	l1[victim] = *line;
}

/*	Loops through the file and sets nextref to the hexedicimal number
	Then it checks if it is in the cache. If it is a miss,
	create new cache line, check if there is an empty spot available,
	if not, choose a victim by the specified algorithm.
*/
void processreffile(char policy){
	unsigned int nextref;
	while(scanf("%x", &nextref) != EOF){
		reference++;
		if(isamiss(nextref)){
			miss++;

			cache line = {
				.valid = 1,
				.tag = gettag(nextref)
			};
			
			int idx = getindex(nextref);
			
			if(fillemptyline(&line, idx)) continue;
			
			if(policy) randomalgo(&line, idx);
			else fifoalgo(&line, idx);
		}
	}
}
