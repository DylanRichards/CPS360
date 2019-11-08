/*
	Name: Dylan Richards,		Class: CPS360
	Section: 22371837,		Assignment: 07
	Due: November 12, 2019		Started: November 6, 2019
	Credit: 10 points

	Problem: Read input from a file and output a psudo memory dump of the contents.
	List out what the starting address is, the contents in hexidecimal, and the character
	representation of it.

	Solution: Use a variety of system calls to access a specific file in the file system.
	Read the file contents to a char array. Print them out from a user defined address
	to the user defined end address or until the end of file.

	Data-structure used: struct sbuf to read file size and a one dimensional char array to store file contents.

	Accessing functions for the data structure: Standard C functions for system calls and structs.

	Errors handled: Command line errors, file operation errors, and memory errors.

	Limitations: System limitations on size of file being loaded in.

	Acknowledgment: I wrote the program for Rattan's CPS360 class.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

/*	Gather input from command line arguments.
	Check the input to ensure correct running parameters.
	Allocate memory to store the file contents.
	Print out file contents and free the memory.
*/
int main(int argc, char *argv[]){
	if(argc < 4){
		void usage(char *progname);
		usage(argv[0]);
	}

	void die(char *reason);
	int getfilesize(char *path);

	struct stat sbuf;
	int size;
	char *startcheck, *endcheck;
	int start = strtol(argv[2], &startcheck, 16);
	int end = strtol(argv[3], &endcheck, 16);

	if(stat(argv[1], &sbuf)) die("FILEPATH NOT VALID");
	if(!(size = getfilesize(argv[1]))) die("EMPTY FILE");
	if(startcheck == argv[2]) die("START INDEX NOT VALID");
	if(endcheck == argv[3]) die("END INDEX NOT VALID");

	int loadimage(char *path, unsigned char mem[], int size);
	void mdump(unsigned char mem[], int size, int first, int last);

	unsigned char *mem = malloc(size);
	if(!mem) die("MEMORY ALLOCATION FAILURE");
	if(!loadimage(argv[1], mem, size)) die("COULD NOT LOAD IMAGE");
	mdump(mem, size, start, end);
	free(mem);

	exit(0);
}

/*	Prints usage to stderr and terminates
*/
void usage(char *progname){
	fprintf(stderr, "%s <filepath> <start-address> <end-address>\n", progname);
	exit(1);
}

/*	Prints out why the program was terminated and terminate
*/
void die(char *reason){
	fprintf(stderr, "Terminated - %s\n", reason);
	exit(1);
}

/*	Return the file size in bytes for a given file path.
	Returns 0 if there was an error
*/
int getfilesize(char *path){
	struct stat sbuf;
	if(stat(path, &sbuf)) return 0;
	return sbuf.st_size;
}

/*	Open file from path. If file was opened properly, read contents into mem.
	If there was an error reading return 0. Otherwise, close the file.
	If the file was closed properly, return 1. Otherwise return 0.
*/
int loadimage(char *path, unsigned char mem[], int size){
	int fdin, retval, nread;

	fdin = open(path, O_RDONLY);
	if(fdin != -1) {
		nread = read(fdin, mem, size);
		if(nread == -1) return 0;

		retval = close(fdin);
		if(!retval) return 1;
	}

	return 0;
}

/*	Print out the header. Ensure that the first and last addresses are in the correct range.
	Loop through each address. Print the address and loop through and print 4 bytes with a space in between.
	Loop through and print out the character if it is in the ASCII range of 0x20 - 0x7e.
	Otherwise, print a period.
*/
void mdump(unsigned char mem[], int size, int first, int last){
	printf("Address   Words in Hexadecimal                 ASCII characters\n");
	printf("--------  -----------------------------------  -----------------\n");

	if(first < 0) first = 0;
	if(last > size) last = size;

	int i, j, k = 0;
	for(i = first; i < last; i += 16){
		printf("%08x ", i);
		
		for(j = i; j < i+16; j++, k++){
			if(!(k&3)) printf(" ");
			printf("%02x", mem[j]);
		}
		printf("  ");
		for(j = i; j < i+16; j++){
			if(mem[j] < 0x20 || mem[j] > 0x7e) printf(".");
			else printf("%c", mem[j]);
		}

		printf("\n");
	}
}


