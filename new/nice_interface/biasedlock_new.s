	.file	"biasedlock_new.cpp"
	.section	.text._Z3incP11shared_dataIiEPv,"axG",@progbits,_Z3incP11shared_dataIiEPv,comdat
	.p2align 4,,15
	.weak	_Z3incP11shared_dataIiEPv
	.type	_Z3incP11shared_dataIiEPv, @function
_Z3incP11shared_dataIiEPv:
.LFB1022:
	.cfi_startproc
	addl	$1, 24(%rdi)
	ret
	.cfi_endproc
.LFE1022:
	.size	_Z3incP11shared_dataIiEPv, .-_Z3incP11shared_dataIiEPv
	.text
	.p2align 4,,15
.globl _Z3fooP10threaddataIiE
	.type	_Z3fooP10threaddataIiE, @function
_Z3fooP10threaddataIiE:
.LFB1023:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	movq	%rdi, %r12
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	movl	$100000000, %ebp
	.cfi_offset 6, -24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	subq	$16, %rsp
	.cfi_def_cfa_offset 48
	.p2align 4,,10
	.p2align 3
.L8:
	movq	8(%r12), %rbx
	.cfi_offset 3, -32
	movl	(%r12), %edx
	movzbl	4(%rbx), %eax
	testb	%al, %al
	je	.L3
	movl	(%rbx), %eax
	cmpl	%eax, %edx
	je	.L14
	movq	8(%rbx), %rdi
	call	pthread_spin_lock
	leaq	(%rsp), %rax
	movq	$_Z3incP11shared_dataIiEPv, (%rsp)
	movq	$0, 8(%rsp)
	movq	%rax, 16(%rbx)
#APP
# 52 "../lib/blalgorithms_new.h" 1
	mfence
# 0 "" 2
#NO_APP
	movq	16(%rbx), %rax
	cmpq	$0, (%rax)
	je	.L12
	.p2align 4,,10
	.p2align 3
.L9:
#APP
# 53 "../lib/blalgorithms_new.h" 1
	pause
# 0 "" 2
#NO_APP
	movq	16(%rbx), %rax
	cmpq	$0, (%rax)
	jne	.L9
.L12:
	movq	8(%rbx), %rdi
	call	pthread_spin_unlock
.L5:
	subl	$1, %ebp
	jne	.L8
	addq	$16, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 32
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L3:
	.cfi_restore_state
	movq	8(%rbx), %rdi
	call	pthread_spin_lock
	addl	$1, 24(%rbx)
	jmp	.L12
	.p2align 4,,10
	.p2align 3
.L14:
	movq	16(%rbx), %rax
	addl	$1, 24(%rbx)
	cmpq	$0, (%rax)
	je	.L5
	movq	16(%rbx), %rax
	movq	16(%rbx), %rdx
	movq	%rbx, %rdi
	movq	8(%rdx), %rsi
	call	*(%rax)
	movq	16(%rbx), %rax
	movq	$0, (%rax)
#APP
# 39 "../lib/blalgorithms_new.h" 1
	mfence
# 0 "" 2
#NO_APP
	jmp	.L5
	.cfi_endproc
.LFE1023:
	.size	_Z3fooP10threaddataIiE, .-_Z3fooP10threaddataIiE
	.p2align 4,,15
.globl _Z3barP10threaddataIiE
	.type	_Z3barP10threaddataIiE, @function
_Z3barP10threaddataIiE:
.LFB1024:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	movq	%rdi, %r12
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	movl	$142, %ebp
	.cfi_offset 6, -24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	subq	$16, %rsp
	.cfi_def_cfa_offset 48
	.p2align 4,,10
	.p2align 3
.L21:
	movq	8(%r12), %rbx
	.cfi_offset 3, -32
	movl	(%r12), %edx
	movzbl	4(%rbx), %eax
	testb	%al, %al
	je	.L16
	movl	(%rbx), %eax
	cmpl	%eax, %edx
	je	.L26
	movq	8(%rbx), %rdi
	call	pthread_spin_lock
	leaq	(%rsp), %rax
	movq	$_Z3incP11shared_dataIiEPv, (%rsp)
	movq	$0, 8(%rsp)
	movq	%rax, 16(%rbx)
#APP
# 52 "../lib/blalgorithms_new.h" 1
	mfence
# 0 "" 2
#NO_APP
	movq	16(%rbx), %rax
	cmpq	$0, (%rax)
	je	.L25
	.p2align 4,,10
	.p2align 3
.L22:
#APP
# 53 "../lib/blalgorithms_new.h" 1
	pause
# 0 "" 2
#NO_APP
	movq	16(%rbx), %rax
	cmpq	$0, (%rax)
	jne	.L22
.L25:
	movq	8(%rbx), %rdi
	call	pthread_spin_unlock
.L18:
	subl	$1, %ebp
	jne	.L21
	movl	$1, 16(%r12)
	addq	$16, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 32
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L16:
	.cfi_restore_state
	movq	8(%rbx), %rdi
	call	pthread_spin_lock
	addl	$1, 24(%rbx)
	jmp	.L25
	.p2align 4,,10
	.p2align 3
.L26:
	movq	16(%rbx), %rax
	addl	$1, 24(%rbx)
	cmpq	$0, (%rax)
	je	.L18
	movq	16(%rbx), %rax
	movq	16(%rbx), %rdx
	movq	%rbx, %rdi
	movq	8(%rdx), %rsi
	call	*(%rax)
	movq	16(%rbx), %rax
	movq	$0, (%rax)
#APP
# 39 "../lib/blalgorithms_new.h" 1
	mfence
# 0 "" 2
#NO_APP
	jmp	.L18
	.cfi_endproc
.LFE1024:
	.size	_Z3barP10threaddataIiE, .-_Z3barP10threaddataIiE
	.p2align 4,,15
.globl _Z8get_timev
	.type	_Z8get_timev, @function
_Z8get_timev:
.LFB28:
	.cfi_startproc
	pushq	%rbx
	.cfi_def_cfa_offset 16
#APP
# 7 "../lib/timing.h" 1
	xorl %eax,%eax
cpuid
rdtsc
# 0 "" 2
#NO_APP
	salq	$32, %rdx
	leaq	(%rdx,%rax), %rax
	popq	%rbx
	.cfi_offset 3, -16
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE28:
	.size	_Z8get_timev, .-_Z8get_timev
	.p2align 4,,15
	.type	_GLOBAL__I__Z8get_timev, @function
_GLOBAL__I__Z8get_timev:
.LFB1045:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	movl	$_ZStL8__ioinit, %edi
	call	_ZNSt8ios_base4InitC1Ev
	movl	$__dso_handle, %edx
	movl	$_ZStL8__ioinit, %esi
	movl	$_ZNSt8ios_base4InitD1Ev, %edi
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	jmp	__cxa_atexit
	.cfi_endproc
.LFE1045:
	.size	_GLOBAL__I__Z8get_timev, .-_GLOBAL__I__Z8get_timev
	.section	.ctors,"aw",@progbits
	.align 8
	.quad	_GLOBAL__I__Z8get_timev
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.string	"Tipping point hit, non dom threads not complete, x: "
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC1:
	.string	"time: "
.LC2:
	.string	"x: "
	.text
	.p2align 4,,15
.globl main
	.type	main, @function
main:
.LFB1025:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA1025
	pushq	%r13
	.cfi_def_cfa_offset 16
	movl	$4, %edi
	pushq	%r12
	.cfi_def_cfa_offset 24
	pushq	%rbp
	.cfi_def_cfa_offset 32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	subq	$280, %rsp
	.cfi_def_cfa_offset 320
.LEHB0:
	.cfi_offset 3, -40
	.cfi_offset 6, -32
	.cfi_offset 12, -24
	.cfi_offset 13, -16
	call	_Znwm
	movl	$32, %edi
	movl	$0, (%rax)
	movq	%rax, %r12
	call	_Znwm
.LEHE0:
	movl	$4, %edi
	movl	$0, (%rax)
	movb	$1, 4(%rax)
	movq	%rax, %rbp
.LEHB1:
	call	_Znwm
	movl	$0, (%rax)
	movq	%rax, 8(%rbp)
	xorl	%esi, %esi
	movq	8(%rbp), %rdi
	call	pthread_spin_init
	movl	$16, %edi
	call	_Znwm
.LEHE1:
	movq	%rax, 16(%rbp)
	movq	16(%rbp), %rax
	movl	$80, %edi
	movq	16(%rbp), %rbx
	movq	$0, (%rax)
	call	malloc
	movl	$0, (%rsp)
	movq	%rax, 8(%rbx)
	movq	%rbp, 8(%rsp)
	movl	$0, 16(%rsp)
	movq	%rbp, 32(%rsp)
	movl	$0, 40(%rsp)
	movl	$1, 24(%rsp)
	movq	%rbp, 56(%rsp)
	movl	$0, 64(%rsp)
	movl	$2, 48(%rsp)
	movq	%rbp, 80(%rsp)
	movl	$0, 88(%rsp)
	movl	$3, 72(%rsp)
	movq	%rbp, 104(%rsp)
	movl	$0, 112(%rsp)
	movl	$4, 96(%rsp)
	movq	%rbp, 128(%rsp)
	movl	$0, 136(%rsp)
	movl	$5, 120(%rsp)
	movq	%rbp, 152(%rsp)
	movl	$0, 160(%rsp)
	movl	$6, 144(%rsp)
	movq	%rbp, 176(%rsp)
	movl	$0, 184(%rsp)
	movl	$7, 168(%rsp)
#APP
# 7 "../lib/timing.h" 1
	xorl %eax,%eax
cpuid
rdtsc
# 0 "" 2
#NO_APP
	salq	$32, %rdx
	leaq	192(%rsp), %rdi
	xorl	%esi, %esi
	leaq	(%rdx,%rax), %rax
	movq	%rsp, %rcx
	movl	$_Z3fooP10threaddataIiE, %edx
	movq	%rax, start(%rip)
	call	pthread_create
	leaq	24(%rsp), %rcx
	leaq	200(%rsp), %rdi
	xorl	%esi, %esi
	movl	$_Z3barP10threaddataIiE, %edx
	call	pthread_create
	leaq	48(%rsp), %rcx
	leaq	208(%rsp), %rdi
	xorl	%esi, %esi
	movl	$_Z3barP10threaddataIiE, %edx
	call	pthread_create
	leaq	72(%rsp), %rcx
	leaq	216(%rsp), %rdi
	xorl	%esi, %esi
	movl	$_Z3barP10threaddataIiE, %edx
	call	pthread_create
	leaq	96(%rsp), %rcx
	leaq	224(%rsp), %rdi
	xorl	%esi, %esi
	movl	$_Z3barP10threaddataIiE, %edx
	call	pthread_create
	leaq	120(%rsp), %rcx
	leaq	232(%rsp), %rdi
	xorl	%esi, %esi
	movl	$_Z3barP10threaddataIiE, %edx
	call	pthread_create
	leaq	144(%rsp), %rcx
	leaq	240(%rsp), %rdi
	xorl	%esi, %esi
	movl	$_Z3barP10threaddataIiE, %edx
	call	pthread_create
	leaq	168(%rsp), %rcx
	leaq	248(%rsp), %rdi
	xorl	%esi, %esi
	movl	$_Z3barP10threaddataIiE, %edx
	call	pthread_create
	movq	192(%rsp), %rdi
	xorl	%esi, %esi
.LEHB2:
	call	pthread_join
	movl	40(%rsp), %r9d
	testl	%r9d, %r9d
	je	.L75
.L30:
	movl	64(%rsp), %r8d
	testl	%r8d, %r8d
	je	.L76
	movl	88(%rsp), %edi
	testl	%edi, %edi
	je	.L77
.L39:
	movl	112(%rsp), %esi
	testl	%esi, %esi
	je	.L78
.L43:
	movl	136(%rsp), %ecx
	testl	%ecx, %ecx
	je	.L79
.L47:
	movl	160(%rsp), %edx
	testl	%edx, %edx
	je	.L80
.L51:
	movl	184(%rsp), %eax
	testl	%eax, %eax
	je	.L81
.L55:
#APP
# 7 "../lib/timing.h" 1
	xorl %eax,%eax
cpuid
rdtsc
# 0 "" 2
#NO_APP
	salq	$32, %rdx
	movl	$.LC1, %esi
	movl	$_ZSt4cout, %edi
	leaq	(%rdx,%rax), %rax
	movl	$6, %edx
	movq	%rax, 264(%rsp)
	movq	264(%rsp), %rbx
	movq	start(%rip), %r12
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	movq	%rbx, %rsi
	movl	$_ZSt4cout, %edi
	subq	%r12, %rsi
	call	_ZNSo9_M_insertIyEERSoT_
	movq	%rax, %rbx
	movq	(%rax), %rax
	movq	-24(%rax), %rax
	movq	240(%rbx,%rax), %r12
	testq	%r12, %r12
	je	.L74
	cmpb	$0, 56(%r12)
	je	.L60
	movzbl	67(%r12), %eax
.L61:
	movsbl	%al, %esi
	movq	%rbx, %rdi
	call	_ZNSo3putEc
	movq	%rax, %rdi
	call	_ZNSo5flushEv
	movl	24(%rbp), %ebp
	movl	$3, %edx
	movl	$.LC2, %esi
	movl	$_ZSt4cout, %edi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	movl	%ebp, %esi
	movl	$_ZSt4cout, %edi
	call	_ZNSolsEi
	movq	%rax, %rbx
	movq	(%rax), %rax
	movq	-24(%rax), %rax
	movq	240(%rbx,%rax), %rbp
	testq	%rbp, %rbp
	je	.L74
	cmpb	$0, 56(%rbp)
	je	.L63
	movzbl	67(%rbp), %eax
.L64:
	movq	%rbx, %rdi
	movsbl	%al, %esi
	call	_ZNSo3putEc
	movq	%rax, %rdi
	call	_ZNSo5flushEv
	addq	$280, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L60:
	.cfi_restore_state
	movq	%r12, %rdi
	call	_ZNKSt5ctypeIcE13_M_widen_initEv
	movq	(%r12), %rax
	movl	$10, %esi
	movq	%r12, %rdi
	call	*48(%rax)
	jmp	.L61
	.p2align 4,,10
	.p2align 3
.L63:
	movq	%rbp, %rdi
	call	_ZNKSt5ctypeIcE13_M_widen_initEv
	movq	0(%rbp), %rax
	movl	$10, %esi
	movq	%rbp, %rdi
	call	*48(%rax)
	jmp	.L64
	.p2align 4,,10
	.p2align 3
.L81:
	movl	(%r12), %ebx
	movl	$52, %edx
	movl	$.LC0, %esi
	movl	$_ZSt4cout, %edi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	movl	%ebx, %esi
	movl	$_ZSt4cout, %edi
	call	_ZNSolsEi
	movq	%rax, %rbx
	movq	(%rax), %rax
	movq	-24(%rax), %rax
	movq	240(%rbx,%rax), %r12
	testq	%r12, %r12
	je	.L74
	cmpb	$0, 56(%r12)
	je	.L57
	movzbl	67(%r12), %eax
.L58:
	movq	%rbx, %rdi
	movsbl	%al, %esi
	call	_ZNSo3putEc
	movq	%rax, %rdi
	call	_ZNSo5flushEv
	jmp	.L55
	.p2align 4,,10
	.p2align 3
.L76:
	movl	(%r12), %ebx
	movl	$52, %edx
	movl	$.LC0, %esi
	movl	$_ZSt4cout, %edi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	movl	%ebx, %esi
	movl	$_ZSt4cout, %edi
	call	_ZNSolsEi
	movq	%rax, %rbx
	movq	(%rax), %rax
	movq	-24(%rax), %rax
	movq	240(%rbx,%rax), %r13
	testq	%r13, %r13
	je	.L74
	cmpb	$0, 56(%r13)
	je	.L82
	movzbl	67(%r13), %eax
.L38:
	movsbl	%al, %esi
	movq	%rbx, %rdi
	call	_ZNSo3putEc
	movq	%rax, %rdi
	call	_ZNSo5flushEv
	movl	88(%rsp), %edi
	testl	%edi, %edi
	jne	.L39
.L77:
	movl	(%r12), %ebx
	movl	$52, %edx
	movl	$.LC0, %esi
	movl	$_ZSt4cout, %edi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	movl	%ebx, %esi
	movl	$_ZSt4cout, %edi
	call	_ZNSolsEi
	movq	%rax, %rbx
	movq	(%rax), %rax
	movq	-24(%rax), %rax
	movq	240(%rbx,%rax), %r13
	testq	%r13, %r13
	je	.L74
	cmpb	$0, 56(%r13)
	je	.L83
	movzbl	67(%r13), %eax
.L42:
	movsbl	%al, %esi
	movq	%rbx, %rdi
	call	_ZNSo3putEc
	movq	%rax, %rdi
	call	_ZNSo5flushEv
	movl	112(%rsp), %esi
	testl	%esi, %esi
	jne	.L43
.L78:
	movl	(%r12), %ebx
	movl	$52, %edx
	movl	$.LC0, %esi
	movl	$_ZSt4cout, %edi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	movl	%ebx, %esi
	movl	$_ZSt4cout, %edi
	call	_ZNSolsEi
	movq	%rax, %rbx
	movq	(%rax), %rax
	movq	-24(%rax), %rax
	movq	240(%rbx,%rax), %r13
	testq	%r13, %r13
	je	.L74
	cmpb	$0, 56(%r13)
	je	.L84
	movzbl	67(%r13), %eax
.L46:
	movsbl	%al, %esi
	movq	%rbx, %rdi
	call	_ZNSo3putEc
	movq	%rax, %rdi
	call	_ZNSo5flushEv
	movl	136(%rsp), %ecx
	testl	%ecx, %ecx
	jne	.L47
.L79:
	movl	(%r12), %ebx
	movl	$52, %edx
	movl	$.LC0, %esi
	movl	$_ZSt4cout, %edi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	movl	%ebx, %esi
	movl	$_ZSt4cout, %edi
	call	_ZNSolsEi
	movq	%rax, %rbx
	movq	(%rax), %rax
	movq	-24(%rax), %rax
	movq	240(%rbx,%rax), %r13
	testq	%r13, %r13
	je	.L74
	cmpb	$0, 56(%r13)
	je	.L85
	movzbl	67(%r13), %eax
.L50:
	movsbl	%al, %esi
	movq	%rbx, %rdi
	call	_ZNSo3putEc
	movq	%rax, %rdi
	call	_ZNSo5flushEv
	movl	160(%rsp), %edx
	testl	%edx, %edx
	jne	.L51
.L80:
	movl	(%r12), %ebx
	movl	$52, %edx
	movl	$.LC0, %esi
	movl	$_ZSt4cout, %edi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	movl	%ebx, %esi
	movl	$_ZSt4cout, %edi
	call	_ZNSolsEi
	movq	%rax, %rbx
	movq	(%rax), %rax
	movq	-24(%rax), %rax
	movq	240(%rbx,%rax), %r13
	testq	%r13, %r13
	je	.L74
	cmpb	$0, 56(%r13)
	je	.L86
	movzbl	67(%r13), %eax
.L54:
	movq	%rbx, %rdi
	movsbl	%al, %esi
	call	_ZNSo3putEc
	movq	%rax, %rdi
	call	_ZNSo5flushEv
	jmp	.L51
	.p2align 4,,10
	.p2align 3
.L75:
	movl	(%r12), %ebx
	movl	$52, %edx
	movl	$.LC0, %esi
	movl	$_ZSt4cout, %edi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	movl	%ebx, %esi
	movl	$_ZSt4cout, %edi
	call	_ZNSolsEi
	movq	%rax, %rbx
	movq	(%rax), %rax
	movq	-24(%rax), %rax
	movq	240(%rbx,%rax), %r13
	testq	%r13, %r13
	je	.L74
	cmpb	$0, 56(%r13)
	je	.L87
	movzbl	67(%r13), %eax
.L34:
	movq	%rbx, %rdi
	movsbl	%al, %esi
	call	_ZNSo3putEc
	movq	%rax, %rdi
	call	_ZNSo5flushEv
	jmp	.L30
	.p2align 4,,10
	.p2align 3
.L82:
	movq	%r13, %rdi
	call	_ZNKSt5ctypeIcE13_M_widen_initEv
	movq	0(%r13), %rax
	movl	$10, %esi
	movq	%r13, %rdi
	call	*48(%rax)
	jmp	.L38
	.p2align 4,,10
	.p2align 3
.L57:
	movq	%r12, %rdi
	call	_ZNKSt5ctypeIcE13_M_widen_initEv
	movq	(%r12), %rax
	movl	$10, %esi
	movq	%r12, %rdi
	call	*48(%rax)
	jmp	.L58
	.p2align 4,,10
	.p2align 3
.L83:
	movq	%r13, %rdi
	call	_ZNKSt5ctypeIcE13_M_widen_initEv
	movq	0(%r13), %rax
	movl	$10, %esi
	movq	%r13, %rdi
	call	*48(%rax)
	jmp	.L42
	.p2align 4,,10
	.p2align 3
.L86:
	movq	%r13, %rdi
	call	_ZNKSt5ctypeIcE13_M_widen_initEv
	movq	0(%r13), %rax
	movl	$10, %esi
	movq	%r13, %rdi
	call	*48(%rax)
	jmp	.L54
	.p2align 4,,10
	.p2align 3
.L87:
	movq	%r13, %rdi
	call	_ZNKSt5ctypeIcE13_M_widen_initEv
	movq	0(%r13), %rax
	movl	$10, %esi
	movq	%r13, %rdi
	call	*48(%rax)
	jmp	.L34
	.p2align 4,,10
	.p2align 3
.L84:
	movq	%r13, %rdi
	call	_ZNKSt5ctypeIcE13_M_widen_initEv
	movq	0(%r13), %rax
	movl	$10, %esi
	movq	%r13, %rdi
	call	*48(%rax)
	jmp	.L46
	.p2align 4,,10
	.p2align 3
.L85:
	movq	%r13, %rdi
	call	_ZNKSt5ctypeIcE13_M_widen_initEv
	movq	0(%r13), %rax
	movl	$10, %esi
	movq	%r13, %rdi
	call	*48(%rax)
	jmp	.L50
.L74:
	call	_ZSt16__throw_bad_castv
.L66:
	movq	%rax, %rbx
	movq	%rbp, %rdi
	call	_ZdlPv
	movq	%rbx, %rdi
	call	_Unwind_Resume
.LEHE2:
	.cfi_endproc
.LFE1025:
	.size	main, .-main
.globl __gxx_personality_v0
	.section	.gcc_except_table,"a",@progbits
.LLSDA1025:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE1025-.LLSDACSB1025
.LLSDACSB1025:
	.uleb128 .LEHB0-.LFB1025
	.uleb128 .LEHE0-.LEHB0
	.uleb128 0x0
	.uleb128 0x0
	.uleb128 .LEHB1-.LFB1025
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L66-.LFB1025
	.uleb128 0x0
	.uleb128 .LEHB2-.LFB1025
	.uleb128 .LEHE2-.LEHB2
	.uleb128 0x0
	.uleb128 0x0
.LLSDACSE1025:
	.text
.globl start
	.bss
	.align 8
	.type	start, @object
	.size	start, 8
start:
	.zero	8
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.weakref	_ZL20__gthrw_pthread_oncePiPFvvE,pthread_once
	.weakref	_ZL27__gthrw_pthread_getspecificj,pthread_getspecific
	.weakref	_ZL27__gthrw_pthread_setspecificjPKv,pthread_setspecific
	.weakref	_ZL22__gthrw_pthread_createPmPK14pthread_attr_tPFPvS3_ES3_,pthread_create
	.weakref	_ZL20__gthrw_pthread_joinmPPv,pthread_join
	.weakref	_ZL21__gthrw_pthread_equalmm,pthread_equal
	.weakref	_ZL20__gthrw_pthread_selfv,pthread_self
	.weakref	_ZL22__gthrw_pthread_detachm,pthread_detach
	.weakref	_ZL22__gthrw_pthread_cancelm,pthread_cancel
	.weakref	_ZL19__gthrw_sched_yieldv,sched_yield
	.weakref	_ZL26__gthrw_pthread_mutex_lockP15pthread_mutex_t,pthread_mutex_lock
	.weakref	_ZL29__gthrw_pthread_mutex_trylockP15pthread_mutex_t,pthread_mutex_trylock
	.weakref	_ZL31__gthrw_pthread_mutex_timedlockP15pthread_mutex_tPK8timespec,pthread_mutex_timedlock
	.weakref	_ZL28__gthrw_pthread_mutex_unlockP15pthread_mutex_t,pthread_mutex_unlock
	.weakref	_ZL26__gthrw_pthread_mutex_initP15pthread_mutex_tPK19pthread_mutexattr_t,pthread_mutex_init
	.weakref	_ZL29__gthrw_pthread_mutex_destroyP15pthread_mutex_t,pthread_mutex_destroy
	.weakref	_ZL30__gthrw_pthread_cond_broadcastP14pthread_cond_t,pthread_cond_broadcast
	.weakref	_ZL27__gthrw_pthread_cond_signalP14pthread_cond_t,pthread_cond_signal
	.weakref	_ZL25__gthrw_pthread_cond_waitP14pthread_cond_tP15pthread_mutex_t,pthread_cond_wait
	.weakref	_ZL30__gthrw_pthread_cond_timedwaitP14pthread_cond_tP15pthread_mutex_tPK8timespec,pthread_cond_timedwait
	.weakref	_ZL28__gthrw_pthread_cond_destroyP14pthread_cond_t,pthread_cond_destroy
	.weakref	_ZL26__gthrw_pthread_key_createPjPFvPvE,pthread_key_create
	.weakref	_ZL26__gthrw_pthread_key_deletej,pthread_key_delete
	.weakref	_ZL30__gthrw_pthread_mutexattr_initP19pthread_mutexattr_t,pthread_mutexattr_init
	.weakref	_ZL33__gthrw_pthread_mutexattr_settypeP19pthread_mutexattr_ti,pthread_mutexattr_settype
	.weakref	_ZL33__gthrw_pthread_mutexattr_destroyP19pthread_mutexattr_t,pthread_mutexattr_destroy
	.ident	"GCC: (Ubuntu/Linaro 4.5.2-8ubuntu4) 4.5.2"
	.section	.note.GNU-stack,"",@progbits
