	.text
	.file	"overload.show.cpp"
	.globl	_Z3absi                 # -- Begin function _Z3absi
	.p2align	4, 0x90
	.type	_Z3absi,@function
_Z3absi:                                # @_Z3absi
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movl	%edi, -4(%rbp)
	cmpl	$0, -4(%rbp)
	jge	.LBB0_2
# %bb.1:
	xorl	%eax, %eax
	subl	-4(%rbp), %eax
	movl	%eax, -8(%rbp)          # 4-byte Spill
	jmp	.LBB0_3
.LBB0_2:
	movl	-4(%rbp), %eax
	movl	%eax, -8(%rbp)          # 4-byte Spill
.LBB0_3:
	movl	-8(%rbp), %eax          # 4-byte Reload
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end0:
	.size	_Z3absi, .Lfunc_end0-_Z3absi
	.cfi_endproc
                                        # -- End function
	.globl	_Z3absd                 # -- Begin function _Z3absd
	.p2align	4, 0x90
	.type	_Z3absd,@function
_Z3absd:                                # @_Z3absd
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movsd	%xmm0, -8(%rbp)
	xorps	%xmm0, %xmm0
	ucomisd	-8(%rbp), %xmm0
	jbe	.LBB1_2
# %bb.1:
	movsd	-8(%rbp), %xmm0         # xmm0 = mem[0],zero
	movq	%xmm0, %rax
	movabsq	$-9223372036854775808, %rcx # imm = 0x8000000000000000
	xorq	%rcx, %rax
	movq	%rax, %xmm0
	movsd	%xmm0, -16(%rbp)        # 8-byte Spill
	jmp	.LBB1_3
.LBB1_2:
	movsd	-8(%rbp), %xmm0         # xmm0 = mem[0],zero
	movsd	%xmm0, -16(%rbp)        # 8-byte Spill
.LBB1_3:
	movsd	-16(%rbp), %xmm0        # 8-byte Reload
                                        # xmm0 = mem[0],zero
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end1:
	.size	_Z3absd, .Lfunc_end1-_Z3absd
	.cfi_endproc
                                        # -- End function

	.ident	"clang version 8.0.1 (tags/RELEASE_801/final)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
