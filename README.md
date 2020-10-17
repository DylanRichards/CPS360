# CPS 360 - Computer Design and Architecture

## A1
Using a data set of integers, the program will find the:
- Largest value
- Smallest value
- Average value
- Count of values that are greater than the average value (found in (C))

## A2
Exercise on
- Pointers
- Command-line arguments
- Singly linked list
- Dynamic allocation/deallocation of memory
- Random number generation.

## A3
- Bit operations
- Bitmaps
- Fixed size sets

## A4
Simulation of combinational circuits using bitwise operators
(&, |, ˜, ^, >>, <<)
- Half adder
- Full adder
- Ripple-carry 
- Look-ahead-carry
- Even parity generator
- Odd parity generator
- 2x1 Multiplexer
- 4x1 Multiplexer

## A5 compute2
Learn RISC processor assembly language and write assembly language function callable from C-main().
Learn to use gdb to single step statement (C) and instruction (assembly).

## A6 procdata1
Learn structure/layout of an array in memory. SPARC memory view of an array using load/store instructions.
Control-flow construct based on 2’s complement branching (using N and Z condition codes).

## A7
Learn data representation of both integers and address sizes in the computer being used.
Program to produce a dump of a memory block in base-16 digits and in ASCII.

## A8
4-way associative cache memory.
Model:
- L1, 4-way associative cache with 4096 cache-lines
- data-block is 64 bytes (16 32-bit words)
- address size 32 bits
- explore two policies for choosing a victim for replacement
 (used only when all entries in the set-in-question are in use):
 1. Choose a victim at random using random number generator (random number: in range 0..3 for 4-way)
 2. Replacement policy is first-in-first-out (FIFO) algorithm:
    on a miss oldest entry in the set is the victim for replacement, (any time there is a replacement on a miss, set the cache entry age to 0 and increment the age of all other entries in the set)
  . on a hit do nothing!
