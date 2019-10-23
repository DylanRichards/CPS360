/*	Problem: Compute the algebraic expression
	a*b - c/d + b%a + b*c*d
	in assembly where a,b,c,d are %i0,%i1,%i2,%i3 respectively
	
	Solution: Store a*b in local register, compute c/d,
	then subtract the result and store in local register.
	Add b%a to the result. Compute b*c and then multiply that with d.
	Add the product to the original resul and store in %i0 as the return value.
*/

	.global compute2
compute2: save %sp, -64, %sp
	mov %i0, %o0 ! Move a to 1st operand
	mov %i1, %o1 ! Move b to 2nd operand
	call .mul    ! (a*b) in %o0
	nop
	mov %o0, %l0 ! (a*b) in %l0

	mov %i2, %o0 ! Move c to 1st operand
	mov %i3, %o1 ! Move d to 2nd operand
	call .div    ! (c/d) in %o0
	nop

	sub %l0, %o0, %l0 ! (a*b - c/d) in %l0
	
	mov %i1, %o0 ! Move b to 1st operand
	mov %i0, %o1 ! Move a to 2nd operand
	call .rem    ! (b%a) in %o0
	nop

	add %l0, %o0, %l0 ! (a*b - c/d + b%a) in %l0

	mov %i1, %o0 ! Move b to 1st operand
	mov %i2, %o1 ! Move c to 2nd operand
	call .mul    ! (b*c) in %o0
	nop

	mov %i3, %o1 ! Move d to 2nd operand
	call .mul    ! (b*c*d) in %o0
	nop

	add %l0, %o0, %i0 ! (a*b - c/d + b%a + b*c*d) in %i0

	ret
	restore
