	.text
	.def	 @feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.file	"extern_c.show.cpp"
	.def	 add;
	.scl	2;
	.type	32;
	.endef
	.globl	add                     # -- Begin function add
	.p2align	4, 0x90
add:                                    # @add
.seh_proc add
# %bb.0:
	pushq	%rax
	.seh_stackalloc 8
	.seh_endprologue
	movl	%edx, 4(%rsp)
	movl	%ecx, (%rsp)
	movl	(%rsp), %ecx
	addl	4(%rsp), %ecx
	movl	%ecx, %eax
	popq	%rcx
	retq
	.seh_handlerdata
	.text
	.seh_endproc
                                        # -- End function
	.def	 div;
	.scl	2;
	.type	32;
	.endef
	.globl	div                     # -- Begin function div
	.p2align	4, 0x90
div:                                    # @div
.seh_proc div
# %bb.0:
	pushq	%rax
	.seh_stackalloc 8
	.seh_endprologue
	movl	%edx, 4(%rsp)
	movl	%ecx, (%rsp)
	movl	(%rsp), %eax
	cltd
	idivl	4(%rsp)
	popq	%rcx
	retq
	.seh_handlerdata
	.text
	.seh_endproc
                                        # -- End function
	.def	 "?mul@@YAHHH@Z";
	.scl	2;
	.type	32;
	.endef
	.globl	"?mul@@YAHHH@Z"         # -- Begin function ?mul@@YAHHH@Z
	.p2align	4, 0x90
"?mul@@YAHHH@Z":                        # @"?mul@@YAHHH@Z"
.seh_proc "?mul@@YAHHH@Z"
# %bb.0:
	pushq	%rax
	.seh_stackalloc 8
	.seh_endprologue
	movl	%edx, 4(%rsp)
	movl	%ecx, (%rsp)
	movl	(%rsp), %ecx
	imull	4(%rsp), %ecx
	movl	%ecx, %eax
	popq	%rcx
	retq
	.seh_handlerdata
	.text
	.seh_endproc
                                        # -- End function

	.addrsig
