	.text
	.globl	sum
	.type	sum, @function
sum:
	push	%rbp
	mov	%rsp, %rbp

	# You should not change anything above here.

	# This next line determines the total size of your stack
	# frame. Here, we are saving 40 bytes in the stack frame,
	# which is definitely overkill for this small example. You can
	# change this if you want, but there's no need to do so.
	sub	$40, %rsp

	# Implement the body of this function below these comments.
	# The parameter for this function is stored in register %rdi
	# You can use the registers: %rax, %rcx, %rdx, .. to store local
	# variables. You can also use memory on the stack at offsets of
	# -8(%rbp) and -16(%rbp) for local variables.
	# The order of the local variables i and res on the stack and
	# in local variables is up to you.

	mov $1, %rcx
	mov $0, %rax
	cmp $0, %rdi
	jle l1 
	jmp start

body:
	add %rcx, %rax
	add $1, %rcx 

start:
	cmp %rcx, %rdi
	jge body
	leaveq
	retq

l1:
	mov $-1, %rax
	leaveq
	retq 

	# The return value is stored in the register %rax. As written,
	# this function returns 0. Change this next line so that it
	# returns the value stored in the variable res.
	# mov	$0, %rax

	# You should not change anything below here.
	leaveq
	retq
	.size	sum, .-sum
