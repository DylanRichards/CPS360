/*	Problem: Given a list of students exams calculate the high, low, and average means.

	Parameters:
	i0 - test scores pointer
	i1 - number of students
	i2 - low mean pointer
	i3 - high mean pointer
	i4 - mean of means pointer
	
	Registers:
	l0 - index
	l1 - sum
	l2 - mean
	l3 - lowmean
	l4 - highmean
	l5 - array offset
	l6 - exam1
	l7 - temp exam 2 & 3

	Solution:
	Clear out registers. Set low mean to 100. Set high mean to 0.
	Loop from index 0 until number of students * 3. This is the number of test scores.
	Multiply the index by size of int, which is 4.
	Load exam1 to local register 6.
	Increment the index and load exam2 into local register 7.
	Add the exam1 and exam2. Store result in local register 6.
	Increment the index and load exam3 into local register 7.
	Add local register 6 and 7. Divide the sum of exams by 3.
	Store the mean in local register 2.
	Compound the new mean with the current running sum.
	Check if the mean is less than the low mean or greater than the high mean.
	If so set the new lowmean or highmean.
	Store the results in the correct memory locations when the loop finishes.
*/


	.global procdata1
procdata1: save %sp, -64, %sp

	clr %l0
	clr %l1
	clr %l2
	mov 100, %l3
	clr %l4

	mov %i1, %o0
	mov 3, %o1
	call .mul
	nop
	mov %o0, %l5

	loop:
		cmp %l0, %l5
		bge done
		nop

		sll %l0, 2, %l6
		ld [%i0 + %l6], %l6
		inc %l0
		sll %l0, 2, %l7
		ld [%i0 + %l7], %l7
		add %l6, %l7, %l6
		inc %l0
		sll %l0, 2, %l7
		ld [%i0 + %l7], %l7
		add %l6, %l7, %l6

		mov %l6, %o0
		mov 3, %o1
		call .div
		nop
		mov %o0, %l2

		add %l1, %l2, %l1

		lowmean:
			cmp %l2, %l3
			bge highmean
			nop
			mov %l2, %l3
		highmean:
			cmp %l2, %l4
			ble continue
			nop
			mov %l2, %l4
		continue:
			inc %l0
			ba loop
			nop

	done:
		mov %l1, %o0
		mov %i1, %o1
		call .div
		nop
		st %o0, [%i4]
		st %l3, [%i2]
		st %l4, [%i3]
		ret
		restore

