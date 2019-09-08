#################################################################
# Read the handout makeandmakefile.pdf for details.
# variables, flags for CFLAGS
# -Wall flags all errors
# -Werror treats warning as an error
# -g  includes symbol table to help gdb
#
# ****** do not change the CFLAGS line **** 
#
#################################################################
CFLAGS  = -g -Wformat-security -Wall -Wextra -Werror -ansi
LDFLAGS = 
CC	= gcc
LD	= gcc

TARG	= a0

OBJS    = a0.o

#################################################################
# rules:
# indented lines have a tab (^I) at the start of line!!
#################################################################

$(TARG): $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(TARG)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o $(TARG) 

#################################################################
# dependencies -- none in this program
#################################################################
