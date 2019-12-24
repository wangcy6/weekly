	.file	"test.cpp"
	.text
	.globl	_Z5printccc
	.type	_Z5printccc, @function
_Z5printccc:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%esi, %ecx
	movl	%edx, %eax
	movb	%dil, -4(%rbp)
	movb	%cl, -8(%rbp)
	movb	%al, -12(%rbp)
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	_Z5printccc, .-_Z5printccc
	.globl	_Z5printfdf
	.type	_Z5printfdf, @function
_Z5printfdf:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movss	%xmm0, -4(%rbp)
	movsd	%xmm1, -16(%rbp)
	movss	%xmm2, -8(%rbp)
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	_Z5printfdf, .-_Z5printfdf
	.ident	"GCC: (Ubuntu 4.8.2-19ubuntu1) 4.8.2"
	.section	.note.GNU-stack,"",@progbits
