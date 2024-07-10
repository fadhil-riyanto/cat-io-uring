	.file	"syscall_rev.c"
	.text
	.globl	main
	.type	main, @function
main:
	pushq	%rbp
	movq	%rsp, %rbp
	movl	$39, %edi
	movl	$0, %eax
	call	syscall@PLT
	movl	$9, %eax
	popq	%rbp
	ret
	.size	main, .-main
	.ident	"GCC: (GNU) 14.1.1 20240522"
	.section	.note.GNU-stack,"",@progbits
