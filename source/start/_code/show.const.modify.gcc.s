	.file	"show.const.modify.c"
	.text
	.section	.rodata
.LC0:
	.string	"%p: %d, %p: %d\n"
.LC1:
	.string	"%d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$1, -20(%rbp)
	leaq	-20(%rbp), %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rax
	movl	(%rax), %esi
	movl	-20(%rbp), %edx
	movq	-16(%rbp), %rcx
	leaq	-20(%rbp), %rax
	movl	%esi, %r8d
	movq	%rax, %rsi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-16(%rbp), %rax
	movl	$2, (%rax)
	movq	-16(%rbp), %rax
	movl	(%rax), %esi
	movl	-20(%rbp), %edx
	movq	-16(%rbp), %rcx
	leaq	-20(%rbp), %rax
	movl	%esi, %r8d
	movq	%rax, %rsi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movq	-16(%rbp), %rax
	movl	(%rax), %edx
	movl	-20(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, %esi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	movq	-8(%rbp), %rdi
	xorq	%fs:40, %rdi
	je	.L3
	call	__stack_chk_fail@PLT
.L3:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (GNU) 8.3.0"
	.section	.note.GNU-stack,"",@progbits
