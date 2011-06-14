	.file	"biasedlock.cpp"
	.text
	.p2align 4,,15
.globl _Z8get_timev
	.type	_Z8get_timev, @function
_Z8get_timev:
.LFB12:
	pushq	%rbx
.LCFI0:
#APP
# 7 "../../lib/timing.h" 1
	xorl %eax,%eax
cpuid
rdtsc
# 0 "" 2
#NO_APP
	salq	$32, %rdx
	leaq	(%rdx,%rax), %rax
	popq	%rbx
	ret
.LFE12:
	.size	_Z8get_timev, .-_Z8get_timev
	.p2align 4,,15
	.type	_GLOBAL__I__Z8get_timev, @function
_GLOBAL__I__Z8get_timev:
.LFB1184:
	subq	$8, %rsp
.LCFI1:
	movl	$_ZStL8__ioinit, %edi
	call	_ZNSt8ios_base4InitC1Ev
	movl	$__dso_handle, %edx
	movl	$_ZStL8__ioinit, %esi
	movl	$_ZNSt8ios_base4InitD1Ev, %edi
	addq	$8, %rsp
	jmp	__cxa_atexit
.LFE1184:
	.size	_GLOBAL__I__Z8get_timev, .-_GLOBAL__I__Z8get_timev
	.section	.ctors,"aw",@progbits
	.align 8
	.quad	_GLOBAL__I__Z8get_timev
	.text
	.p2align 4,,15
.globl _Z3fooP10threaddata
	.type	_Z3fooP10threaddata, @function
_Z3fooP10threaddata:
.LFB1024:
	pushq	%r12
.LCFI2:
	movq	%rdi, %r12
	pushq	%rbp
.LCFI3:
	pushq	%rbx
.LCFI4:
	movq	(%rdi), %rax
	movq	8(%rdi), %rbx
	movl	(%rax), %eax
	testl	%eax, %eax
	jne	.L6
	movq	16(%rdi), %rcx
	xorl	%edx, %edx
	.p2align 4,,10
	.p2align 3
.L9:
	movl	(%rcx), %esi
	leal	1(%rsi), %eax
	movl	%eax, (%rcx)
	movl	8(%rbx), %eax
	testl	%eax, %eax
	je	.L7
	movl	8(%rbx), %eax
	subl	$1, %eax
	jne	.L7
	leal	2(%rsi), %eax
	movl	%eax, (%rcx)
	movl	$0, 8(%rbx)
	movl	$1, 4(%rbx)
#APP
# 24 "biasedlock.cpp" 1
	mfence
# 0 "" 2
#NO_APP
.L7:
	addl	$1, %edx
	cmpl	$1000000000, %edx
	jne	.L9
	popq	%rbx
	popq	%rbp
	popq	%r12
	ret
.L6:
	movl	$16, %edi
	xorl	%ebp, %ebp
	call	_Znwm
	movq	$1, 8(%rax)
	.p2align 4,,10
	.p2align 3
.L13:
	movq	%rbx, %rdi
	call	pthread_spin_lock
	movq	8(%r12), %rax
	movl	$0, 4(%rbx)
	movl	$1, 8(%rax)
	movl	4(%rbx), %eax
	testl	%eax, %eax
	jne	.L11
	.p2align 4,,10
	.p2align 3
.L15:
#APP
# 49 "biasedlock.cpp" 1
	pause
# 0 "" 2
#NO_APP
	movl	4(%rbx), %eax
	testl	%eax, %eax
	je	.L15
.L11:
	movq	%rbx, %rdi
	addl	$1, %ebp
	call	pthread_spin_unlock
	cmpl	$3333, %ebp
	jne	.L13
	movb	$1, 32(%r12)
	popq	%rbx
	popq	%rbp
	popq	%r12
	ret
.LFE1024:
	.size	_Z3fooP10threaddata, .-_Z3fooP10threaddata
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.string	"Tipping point hit, non dom threads not complete, x: "
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC1:
	.string	"time: "
.LC2:
	.string	"x: "
.LC3:
	.string	" y: "
	.text
	.p2align 4,,15
.globl main
	.type	main, @function
main:
.LFB1025:
	pushq	%r15
.LCFI5:
	movl	$12, %edi
	pushq	%r14
.LCFI6:
	pushq	%r13
.LCFI7:
	pushq	%r12
.LCFI8:
	pushq	%rbp
.LCFI9:
	pushq	%rbx
.LCFI10:
	subq	$520, %rsp
.LCFI11:
	movq	%fs:40, %rax
	movq	%rax, 504(%rsp)
	xorl	%eax, %eax
	call	_Znwm
	xorl	%esi, %esi
	movq	%rax, %r12
	movq	%rax, %rdi
	call	pthread_spin_init
	movl	$0, 8(%r12)
	movl	$1, 4(%r12)
	movl	$4, %edi
	call	_Znwm
	movl	$4, %edi
	movl	$0, (%rax)
	movq	%rax, %r15
	call	_Znwm
	movq	%rax, 24(%rsp)
	movl	$0, (%rax)
#APP
# 7 "../../lib/timing.h" 1
	xorl %eax,%eax
cpuid
rdtsc
# 0 "" 2
#NO_APP
	salq	$32, %rdx
	leaq	32(%rsp), %rbx
	leaq	192(%rsp), %rbp
	addq	%rax, %rdx
	movl	$4, %edi
	movq	%r12, 40(%rsp)
	movq	%rdx, start(%rip)
	movq	24(%rsp), %rdx
	leaq	72(%rbx), %r13
	movq	%r15, 48(%rsp)
	movq	%rdx, 56(%rsp)
	call	_Znwm
	movq	%rbx, %rcx
	movl	$_Z3fooP10threaddata, %edx
	xorl	%esi, %esi
	movq	%rbp, %rdi
	movl	$0, (%rax)
	movq	%rax, 32(%rsp)
	movb	$0, 64(%rsp)
	call	pthread_create
	movq	24(%rsp), %rax
	movl	$4, %edi
	movq	%r12, 80(%rsp)
	movq	%r15, 88(%rsp)
	movq	%rax, 96(%rsp)
	call	_Znwm
	leaq	40(%rbx), %rcx
	leaq	8(%rbp), %rdi
	xorl	%esi, %esi
	movl	$_Z3fooP10threaddata, %edx
	movl	$1, (%rax)
	movq	%rax, 72(%rsp)
	movb	$0, 104(%rsp)
	call	pthread_create
	movq	24(%rsp), %rdx
	movl	$4, %edi
	movq	%r12, 120(%rsp)
	movq	%r15, 128(%rsp)
	movq	%rdx, 136(%rsp)
	call	_Znwm
	leaq	80(%rbx), %rcx
	leaq	16(%rbp), %rdi
	movl	$_Z3fooP10threaddata, %edx
	xorl	%esi, %esi
	movl	$2, (%rax)
	movq	%rax, 112(%rsp)
	movb	$0, 144(%rsp)
	call	pthread_create
	movq	24(%rsp), %rax
	movl	$4, %edi
	movq	%r12, 160(%rsp)
	movq	%r15, 168(%rsp)
	leaq	240(%rsp), %r12
	movq	%rax, 176(%rsp)
	call	_Znwm
	leaq	120(%rbx), %rcx
	leaq	24(%rbp), %rdi
	movl	$_Z3fooP10threaddata, %edx
	xorl	%esi, %esi
	movl	$3, (%rax)
	movq	%rax, 152(%rsp)
	movb	$0, 184(%rsp)
	addq	$192, %rbx
	call	pthread_create
	movq	192(%rsp), %rdi
	xorl	%esi, %esi
	call	pthread_join
	leaq	256(%r12), %rdx
	movq	%rbx, 8(%rsp)
	movq	%rdx, 16(%rsp)
.L27:
	cmpb	$0, (%r13)
	je	.L49
.L21:
	addq	$40, %r13
	cmpq	8(%rsp), %r13
	jne	.L27
#APP
# 7 "../../lib/timing.h" 1
	xorl %eax,%eax
cpuid
rdtsc
# 0 "" 2
#NO_APP
	salq	$32, %rdx
	movl	$.LC1, %esi
	movl	$_ZSt4cout, %edi
	addq	%rax, %rdx
	movq	%rdx, 232(%rsp)
	movq	232(%rsp), %rbx
	movl	$6, %edx
	movq	start(%rip), %r12
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	movl	$_ZSt4cout, %edi
	subq	%r12, %rbx
	movq	%rbx, %rsi
	call	_ZNSo9_M_insertIyEERSoT_
	movq	%rax, %r13
	movq	(%rax), %rax
	movq	-24(%rax), %rax
	movq	240(%r13,%rax), %rbp
	testq	%rbp, %rbp
	je	.L48
	xorl	%eax, %eax
	cmpb	$0, 56(%rbp)
	leaq	240(%rsp), %r12
	jne	.L50
	.p2align 4,,10
	.p2align 3
.L41:
	movb	%al, (%r12,%rax)
	addq	$1, %rax
	cmpq	$256, %rax
	jne	.L41
	movq	(%rbp), %rax
	leaq	57(%rbp), %rbx
	movq	%r12, %rsi
	movq	%rbp, %rdi
	leaq	256(%r12), %rdx
	movq	%rbx, %rcx
	call	*56(%rax)
	movb	$1, 56(%rbp)
	movl	$256, %ecx
	movq	%r12, %rsi
	movq	%rbx, %rdi
	repz cmpsb
	jne	.L51
.L32:
	movq	(%rbp), %rax
	movl	$10, %esi
	movq	%rbp, %rdi
	call	*48(%rax)
.L30:
	movsbl	%al,%esi
	movq	%r13, %rdi
	call	_ZNSo3putEc
	movq	%rax, %rdi
	call	_ZNSo5flushEv
	movq	24(%rsp), %rax
	movl	(%r15), %ebx
	movl	$3, %edx
	movl	$.LC2, %esi
	movl	$_ZSt4cout, %edi
	movl	(%rax), %r12d
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	movl	%ebx, %esi
	movl	$_ZSt4cout, %edi
	call	_ZNSolsEi
	movl	$4, %edx
	movq	%rax, %rbx
	movl	$.LC3, %esi
	movq	%rax, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	movl	%r12d, %esi
	movq	%rbx, %rdi
	call	_ZNSolsEi
	movq	%rax, %r13
	movq	(%rax), %rax
	movq	-24(%rax), %rax
	movq	240(%r13,%rax), %rbp
	testq	%rbp, %rbp
	je	.L48
	xorl	%eax, %eax
	cmpb	$0, 56(%rbp)
	leaq	240(%rsp), %r12
	jne	.L52
	.p2align 4,,10
	.p2align 3
.L40:
	movb	%al, (%r12,%rax)
	addq	$1, %rax
	cmpq	$256, %rax
	jne	.L40
	movq	(%rbp), %rax
	leaq	57(%rbp), %rbx
	movq	%r12, %rsi
	movq	%rbp, %rdi
	leaq	256(%r12), %rdx
	movq	%rbx, %rcx
	call	*56(%rax)
	movb	$1, 56(%rbp)
	movl	$256, %ecx
	movq	%r12, %rsi
	movq	%rbx, %rdi
	repz cmpsb
	jne	.L53
.L37:
	movq	(%rbp), %rax
	movl	$10, %esi
	movq	%rbp, %rdi
	call	*48(%rax)
.L35:
	movsbl	%al,%esi
	movq	%r13, %rdi
	call	_ZNSo3putEc
	movq	%rax, %rdi
	call	_ZNSo5flushEv
	xorl	%eax, %eax
	movq	504(%rsp), %rdx
	xorq	%fs:40, %rdx
	jne	.L54
	addq	$520, %rsp
	popq	%rbx
	popq	%rbp
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	ret
	.p2align 4,,10
	.p2align 3
.L49:
	movl	(%r15), %ebx
	movl	$52, %edx
	movl	$.LC0, %esi
	movl	$_ZSt4cout, %edi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	movl	%ebx, %esi
	movl	$_ZSt4cout, %edi
	call	_ZNSolsEi
	movq	%rax, %r14
	movq	(%rax), %rax
	movq	-24(%rax), %rax
	movq	240(%r14,%rax), %rbp
	testq	%rbp, %rbp
	je	.L48
	xorl	%eax, %eax
	cmpb	$0, 56(%rbp)
	jne	.L55
	.p2align 4,,10
	.p2align 3
.L42:
	movb	%al, (%r12,%rax)
	addq	$1, %rax
	cmpq	$256, %rax
	jne	.L42
	movq	(%rbp), %rax
	leaq	57(%rbp), %rbx
	movq	%r12, %rsi
	movq	%rbp, %rdi
	movq	16(%rsp), %rdx
	movq	%rbx, %rcx
	call	*56(%rax)
	movb	$1, 56(%rbp)
	movq	%r12, %rsi
	movq	%rbx, %rdi
	movl	$256, %ecx
	repz cmpsb
	je	.L26
	movb	$2, 56(%rbp)
.L26:
	movq	(%rbp), %rax
	movl	$10, %esi
	movq	%rbp, %rdi
	call	*48(%rax)
.L24:
	movq	%r14, %rdi
	movsbl	%al,%esi
	call	_ZNSo3putEc
	movq	%rax, %rdi
	call	_ZNSo5flushEv
	jmp	.L21
.L55:
	movzbl	67(%rbp), %eax
	.p2align 4,,4
	.p2align 3
	jmp	.L24
.L51:
	movb	$2, 56(%rbp)
	.p2align 4,,7
	.p2align 3
	jmp	.L32
.L53:
	movb	$2, 56(%rbp)
	.p2align 4,,5
	.p2align 3
	jmp	.L37
.L50:
	movzbl	67(%rbp), %eax
	.p2align 4,,5
	.p2align 3
	jmp	.L30
.L52:
	movzbl	67(%rbp), %eax
	.p2align 4,,5
	.p2align 3
	jmp	.L35
.L48:
	.p2align 4,,7
	.p2align 3
	call	_ZSt16__throw_bad_castv
.L54:
	.p2align 4,,6
	.p2align 3
	call	__stack_chk_fail
.LFE1025:
	.size	main, .-main
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
	.weakref	_ZL22__gthrw_pthread_cancelm,pthread_cancel
	.weakref	_ZL26__gthrw_pthread_mutex_lockP15pthread_mutex_t,pthread_mutex_lock
	.weakref	_ZL29__gthrw_pthread_mutex_trylockP15pthread_mutex_t,pthread_mutex_trylock
	.weakref	_ZL28__gthrw_pthread_mutex_unlockP15pthread_mutex_t,pthread_mutex_unlock
	.weakref	_ZL26__gthrw_pthread_mutex_initP15pthread_mutex_tPK19pthread_mutexattr_t,pthread_mutex_init
	.weakref	_ZL30__gthrw_pthread_cond_broadcastP14pthread_cond_t,pthread_cond_broadcast
	.weakref	_ZL25__gthrw_pthread_cond_waitP14pthread_cond_tP15pthread_mutex_t,pthread_cond_wait
	.weakref	_ZL26__gthrw_pthread_key_createPjPFvPvE,pthread_key_create
	.weakref	_ZL26__gthrw_pthread_key_deletej,pthread_key_delete
	.weakref	_ZL30__gthrw_pthread_mutexattr_initP19pthread_mutexattr_t,pthread_mutexattr_init
	.weakref	_ZL33__gthrw_pthread_mutexattr_settypeP19pthread_mutexattr_ti,pthread_mutexattr_settype
	.weakref	_ZL33__gthrw_pthread_mutexattr_destroyP19pthread_mutexattr_t,pthread_mutexattr_destroy
	.section	.eh_frame,"a",@progbits
.Lframe1:
	.long	.LECIE1-.LSCIE1
.LSCIE1:
	.long	0x0
	.byte	0x1
.globl __gxx_personality_v0
	.string	"zPR"
	.uleb128 0x1
	.sleb128 -8
	.byte	0x10
	.uleb128 0x6
	.byte	0x3
	.long	__gxx_personality_v0
	.byte	0x3
	.byte	0xc
	.uleb128 0x7
	.uleb128 0x8
	.byte	0x90
	.uleb128 0x1
	.align 8
.LECIE1:
.LSFDE1:
	.long	.LEFDE1-.LASFDE1
.LASFDE1:
	.long	.LASFDE1-.Lframe1
	.long	.LFB12
	.long	.LFE12-.LFB12
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI0-.LFB12
	.byte	0xe
	.uleb128 0x10
	.byte	0x83
	.uleb128 0x2
	.align 8
.LEFDE1:
.LSFDE3:
	.long	.LEFDE3-.LASFDE3
.LASFDE3:
	.long	.LASFDE3-.Lframe1
	.long	.LFB1184
	.long	.LFE1184-.LFB1184
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI1-.LFB1184
	.byte	0xe
	.uleb128 0x10
	.align 8
.LEFDE3:
.LSFDE5:
	.long	.LEFDE5-.LASFDE5
.LASFDE5:
	.long	.LASFDE5-.Lframe1
	.long	.LFB1024
	.long	.LFE1024-.LFB1024
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI2-.LFB1024
	.byte	0xe
	.uleb128 0x10
	.byte	0x8c
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI3-.LCFI2
	.byte	0xe
	.uleb128 0x18
	.byte	0x4
	.long	.LCFI4-.LCFI3
	.byte	0xe
	.uleb128 0x20
	.byte	0x83
	.uleb128 0x4
	.byte	0x86
	.uleb128 0x3
	.align 8
.LEFDE5:
.LSFDE7:
	.long	.LEFDE7-.LASFDE7
.LASFDE7:
	.long	.LASFDE7-.Lframe1
	.long	.LFB1025
	.long	.LFE1025-.LFB1025
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI5-.LFB1025
	.byte	0xe
	.uleb128 0x10
	.byte	0x4
	.long	.LCFI6-.LCFI5
	.byte	0xe
	.uleb128 0x18
	.byte	0x4
	.long	.LCFI7-.LCFI6
	.byte	0xe
	.uleb128 0x20
	.byte	0x4
	.long	.LCFI8-.LCFI7
	.byte	0xe
	.uleb128 0x28
	.byte	0x4
	.long	.LCFI9-.LCFI8
	.byte	0xe
	.uleb128 0x30
	.byte	0x4
	.long	.LCFI10-.LCFI9
	.byte	0xe
	.uleb128 0x38
	.byte	0x4
	.long	.LCFI11-.LCFI10
	.byte	0xe
	.uleb128 0x240
	.byte	0x83
	.uleb128 0x7
	.byte	0x86
	.uleb128 0x6
	.byte	0x8c
	.uleb128 0x5
	.byte	0x8d
	.uleb128 0x4
	.byte	0x8e
	.uleb128 0x3
	.byte	0x8f
	.uleb128 0x2
	.align 8
.LEFDE7:
	.ident	"GCC: (Ubuntu 4.3.3-5ubuntu4) 4.3.3"
	.section	.note.GNU-stack,"",@progbits
