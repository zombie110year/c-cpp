	.text
	.file	"show.const.modify.c"
	.globl	main                    # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$64, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	movl	$0, -16(%rbp)
	movl	$1, -12(%rbp)
	leaq	-12(%rbp), %rax
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rcx
	movl	(%rcx), %r8d
	leaq	.L.str(%rip), %rdx
	xorl	%esi, %esi
	movb	%sil, %dil
	movl	$1, %esi
	movb	%dil, -25(%rbp)         # 1-byte Spill
	movq	%rdx, %rdi
	movl	%esi, -32(%rbp)         # 4-byte Spill
	movq	%rax, %rsi
	movl	-32(%rbp), %r9d         # 4-byte Reload
	movq	%rdx, -40(%rbp)         # 8-byte Spill
	movl	%r9d, %edx
	movb	-25(%rbp), %r10b        # 1-byte Reload
	movq	%rax, -48(%rbp)         # 8-byte Spill
	movb	%r10b, %al
	callq	printf@PLT
	movq	-24(%rbp), %rcx
	movl	$2, (%rcx)
	movq	-24(%rbp), %rcx
	movl	(%rcx), %r8d
	movq	-40(%rbp), %rdi         # 8-byte Reload
	movq	-48(%rbp), %rsi         # 8-byte Reload
	movl	-32(%rbp), %edx         # 4-byte Reload
	movb	-25(%rbp), %r10b        # 1-byte Reload
	movl	%eax, -52(%rbp)         # 4-byte Spill
	movb	%r10b, %al
	callq	printf@PLT
	movq	-24(%rbp), %rcx
	movl	(%rcx), %edx
	addl	$1, %edx
	leaq	.L.str.1(%rip), %rdi
	movl	%edx, %esi
	movb	-25(%rbp), %r10b        # 1-byte Reload
	movl	%eax, -56(%rbp)         # 4-byte Spill
	movb	%r10b, %al
	callq	printf@PLT
	movq	%fs:40, %rcx
	movq	-8(%rbp), %rdi
	cmpq	%rdi, %rcx
	movl	%eax, -60(%rbp)         # 4-byte Spill
	jne	.LBB0_2
# %bb.1:
	xorl	%eax, %eax
	addq	$64, %rsp
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.LBB0_2:
	.cfi_def_cfa %rbp, 16
	callq	__stack_chk_fail@PLT
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.type	.L.str,@object          # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"%p: %d, %p: %d\n"
	.size	.L.str, 16

	.type	.L.str.1,@object        # @.str.1
.L.str.1:
	.asciz	"%d\n"
	.size	.L.str.1, 4


	.ident	"clang version 8.0.0 (tags/RELEASE_800/final)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym printf
	.addrsig_sym __stack_chk_fail
