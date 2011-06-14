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
.LFB1190:
	subq	$8, %rsp
.LCFI1:
	movl	$_ZStL8__ioinit, %edi
	call	_ZNSt8ios_base4InitC1Ev
	movl	$__dso_handle, %edx
	movl	$_ZStL8__ioinit, %esi
	movl	$_ZNSt8ios_base4InitD1Ev, %edi
	addq	$8, %rsp
	jmp	__cxa_atexit
.LFE1190:
	.size	_GLOBAL__I__Z8get_timev, .-_GLOBAL__I__Z8get_timev
	.section	.ctors,"aw",@progbits
	.align 8
	.quad	_GLOBAL__I__Z8get_timev
	.text
	.p2align 4,,15
.globl _Z25this_is_so_fucking_stupidPm
	.type	_Z25this_is_so_fucking_stupidPm, @function
_Z25this_is_so_fucking_stupidPm:
.LFB1025:
	movq	(%rdi), %rdi
	xorl	%esi, %esi
	jmp	pthread_join
.LFE1025:
	.size	_Z25this_is_so_fucking_stupidPm, .-_Z25this_is_so_fucking_stupidPm
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"time: "
.LC1:
	.string	"thread "
.LC2:
	.string	" done"
	.text
	.p2align 4,,15
.globl _Z3fooP10threaddata
	.type	_Z3fooP10threaddata, @function
_Z3fooP10threaddata:
.LFB1024:
	pushq	%r14
.LCFI2:
	pushq	%r13
.LCFI3:
	pushq	%r12
.LCFI4:
	pushq	%rbp
.LCFI5:
	movq	%rdi, %rbp
	pushq	%rbx
.LCFI6:
	subq	$272, %rsp
.LCFI7:
	movq	8(%rdi), %rbx
	movq	%fs:40, %rax
	movq	%rax, 264(%rsp)
	xorl	%eax, %eax
	movq	(%rdi), %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	jne	.L8
	movq	16(%rdi), %rcx
	xorl	%edx, %edx
	.p2align 4,,10
	.p2align 3
.L11:
	addl	$1, (%rcx)
	movl	8(%rbx), %eax
	testl	%eax, %eax
	je	.L9
	movl	8(%rbx), %eax
	subl	$1, %eax
	jne	.L9
	addl	$1, (%rcx)
	movl	$0, 8(%rbx)
	movl	$1, 4(%rbx)
#APP
# 24 "biasedlock.cpp" 1
	mfence
# 0 "" 2
#NO_APP
.L9:
	addl	$1, %edx
	cmpl	$1000000000, %edx
	jne	.L11
.L40:
	cmpb	$0, 24(%rbp)
	jne	.L30
	.p2align 4,,10
	.p2align 3
.L41:
	movl	8(%rbx), %eax
	testl	%eax, %eax
	je	.L41
	movl	8(%rbx), %eax
	subl	$1, %eax
	jne	.L41
	addl	$1, (%rcx)
	movl	$0, 8(%rbx)
	movl	$1, 4(%rbx)
#APP
# 34 "biasedlock.cpp" 1
	mfence
# 0 "" 2
#NO_APP
	jmp	.L40
.L8:
	movl	$16, %edi
	xorl	%r12d, %r12d
	call	_Znwm
	movq	$1, 8(%rax)
	.p2align 4,,10
	.p2align 3
.L19:
	movq	%rbx, %rdi
	call	pthread_spin_lock
	movq	8(%rbp), %rax
	movl	$0, 4(%rbx)
	movl	$1, 8(%rax)
	movl	4(%rbx), %eax
	testl	%eax, %eax
	jne	.L17
	.p2align 4,,10
	.p2align 3
.L34:
#APP
# 52 "biasedlock.cpp" 1
	pause
# 0 "" 2
#NO_APP
	movl	4(%rbx), %eax
	testl	%eax, %eax
	je	.L34
.L17:
	movq	%rbx, %rdi
	addl	$1, %r12d
	call	pthread_spin_unlock
	cmpl	$17543859, %r12d
	jne	.L19
	movb	$1, 24(%rbp)
#APP
# 7 "../../lib/timing.h" 1
	xorl %eax,%eax
cpuid
rdtsc
# 0 "" 2
#NO_APP
	movq	start(%rip), %rbx
	movq	%rdx, %r12
	movq	%rax, %r13
	movl	$6, %edx
	movl	$.LC0, %esi
	movl	$_ZSt4cout, %edi
	salq	$32, %r12
	subq	%rbx, %r13
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	leaq	(%r13,%r12), %rsi
	movl	$_ZSt4cout, %edi
	call	_ZNSo9_M_insertIyEERSoT_
	movq	%rax, %r14
	movq	(%rax), %rax
	movq	-24(%rax), %rax
	movq	240(%r14,%rax), %r13
	testq	%r13, %r13
	je	.L42
	xorl	%eax, %eax
	cmpb	$0, 56(%r13)
	movq	%rsp, %r12
	jne	.L44
	.p2align 4,,10
	.p2align 3
.L33:
	movb	%al, (%r12,%rax)
	addq	$1, %rax
	cmpq	$256, %rax
	jne	.L33
	movq	(%r13), %rax
	leaq	57(%r13), %rbx
	movq	%rsp, %rsi
	movq	%r13, %rdi
	leaq	256(%r12), %rdx
	movq	%rbx, %rcx
	call	*56(%rax)
	movb	$1, 56(%r13)
	movl	$256, %ecx
	movq	%r12, %rsi
	movq	%rbx, %rdi
	repz cmpsb
	je	.L24
	movb	$2, 56(%r13)
.L24:
	movq	(%r13), %rax
	movl	$10, %esi
	movq	%r13, %rdi
	call	*48(%rax)
.L22:
	movsbl	%al,%esi
	movq	%r14, %rdi
	call	_ZNSo3putEc
	movq	%rax, %rdi
	call	_ZNSo5flushEv
	movq	(%rbp), %rax
	movl	$7, %edx
	movl	$.LC1, %esi
	movl	$_ZSt4cout, %edi
	movl	(%rax), %ebx
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	movl	$_ZSt4cout, %edi
	movl	%ebx, %esi
	call	_ZNSolsEi
	movl	$5, %edx
	movq	%rax, %r13
	movl	$.LC2, %esi
	movq	%rax, %rdi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	movq	(%r13), %rax
	movq	-24(%rax), %rax
	movq	240(%r13,%rax), %rbp
	testq	%rbp, %rbp
	je	.L42
	xorl	%eax, %eax
	cmpb	$0, 56(%rbp)
	movq	%rsp, %r12
	jne	.L45
	.p2align 4,,10
	.p2align 3
.L32:
	movb	%al, (%r12,%rax)
	addq	$1, %rax
	cmpq	$256, %rax
	jne	.L32
	movq	(%rbp), %rax
	leaq	57(%rbp), %rbx
	movq	%rsp, %rsi
	movq	%rbp, %rdi
	leaq	256(%r12), %rdx
	movq	%rbx, %rcx
	call	*56(%rax)
	movb	$1, 56(%rbp)
	movl	$256, %ecx
	movq	%r12, %rsi
	movq	%rbx, %rdi
	repz cmpsb
	je	.L29
	movb	$2, 56(%rbp)
.L29:
	movq	(%rbp), %rax
	movl	$10, %esi
	movq	%rbp, %rdi
	call	*48(%rax)
.L27:
	movq	%r13, %rdi
	movsbl	%al,%esi
	call	_ZNSo3putEc
	movq	%rax, %rdi
	call	_ZNSo5flushEv
.L30:
	movq	264(%rsp), %rax
	xorq	%fs:40, %rax
	jne	.L46
	addq	$272, %rsp
	popq	%rbx
	popq	%rbp
	popq	%r12
	popq	%r13
	popq	%r14
	ret
.L45:
	movzbl	67(%rbp), %eax
	jmp	.L27
.L44:
	movzbl	67(%r13), %eax
	jmp	.L22
.L42:
	.p2align 4,,7
	.p2align 3
	call	_ZSt16__throw_bad_castv
.L46:
	.p2align 4,,6
	.p2align 3
	call	__stack_chk_fail
.LFE1024:
	.size	_Z3fooP10threaddata, .-_Z3fooP10threaddata
	.section	.rodata.str1.1
.LC3:
	.string	"done should now be true "
.LC4:
	.string	"x: "
	.text
	.p2align 4,,15
.globl main
	.type	main, @function
main:
.LFB1026:
	pushq	%r14
.LCFI8:
	movl	$12, %edi
	pushq	%r13
.LCFI9:
	pushq	%r12
.LCFI10:
	pushq	%rbp
.LCFI11:
	pushq	%rbx
.LCFI12:
	subq	$448, %rsp
.LCFI13:
	movq	%fs:40, %rax
	movq	%rax, 440(%rsp)
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
	movq	%rax, %r14
	movl	$0, (%rax)
#APP
# 7 "../../lib/timing.h" 1
	xorl %eax,%eax
cpuid
rdtsc
# 0 "" 2
#NO_APP
	leaq	128(%rsp), %rbx
	salq	$32, %rdx
	movl	$4, %edi
	addq	%rax, %rdx
	movq	%r14, 16(%rsp)
	movq	%r12, 8(%rsp)
	movq	%rdx, start(%rip)
	call	_Znwm
	movq	%rsp, %rcx
	xorl	%esi, %esi
	movl	$_Z3fooP10threaddata, %edx
	movq	%rbx, %rdi
	movl	$0, (%rax)
	movq	%rax, (%rsp)
	movb	$0, 24(%rsp)
	call	pthread_create
	movl	$4, %edi
	movq	%r14, 48(%rsp)
	movq	%r12, 40(%rsp)
	call	_Znwm
	leaq	32(%rsp), %rcx
	leaq	8(%rbx), %rdi
	xorl	%esi, %esi
	movl	$_Z3fooP10threaddata, %edx
	movl	$1, (%rax)
	movq	%rax, 32(%rsp)
	movb	$0, 56(%rsp)
	call	pthread_create
	movl	$4, %edi
	movq	%r14, 80(%rsp)
	movq	%r12, 72(%rsp)
	call	_Znwm
	leaq	64(%rsp), %rcx
	leaq	16(%rbx), %rdi
	xorl	%esi, %esi
	movl	$_Z3fooP10threaddata, %edx
	movl	$2, (%rax)
	movq	%rax, 64(%rsp)
	movb	$0, 88(%rsp)
	call	pthread_create
	movl	$4, %edi
	movq	%r14, 112(%rsp)
	movq	%r12, 104(%rsp)
	call	_Znwm
	leaq	96(%rsp), %rcx
	leaq	24(%rbx), %rdi
	xorl	%esi, %esi
	movl	$_Z3fooP10threaddata, %edx
	movl	$3, (%rax)
	movq	%rax, 96(%rsp)
	movb	$0, 120(%rsp)
	call	pthread_create
	leaq	168(%rsp), %rdi
	movq	%rbx, %rcx
	movl	$_Z25this_is_so_fucking_stupidPm, %edx
	xorl	%esi, %esi
	call	pthread_create
	movq	136(%rsp), %rdi
	xorl	%esi, %esi
	call	pthread_join
	movq	144(%rsp), %rdi
	xorl	%esi, %esi
	call	pthread_join
	movq	152(%rsp), %rdi
	xorl	%esi, %esi
	call	pthread_join
	movb	$1, 24(%rsp)
#APP
# 103 "biasedlock.cpp" 1
	mfence
# 0 "" 2
#NO_APP
	movl	$24, %edx
	movl	$.LC3, %esi
	movl	$_ZSt4cout, %edi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	leaq	24(%rsp), %rsi
	movl	$_ZSt4cout, %edi
	call	_ZNSo9_M_insertIPKvEERSoT_
	movq	%rax, %r13
	movq	(%rax), %rax
	movq	-24(%rax), %rax
	movq	240(%r13,%rax), %rbp
	testq	%rbp, %rbp
	je	.L72
	xorl	%eax, %eax
	cmpb	$0, 56(%rbp)
	leaq	176(%rsp), %r12
	jne	.L73
	.p2align 4,,10
	.p2align 3
.L67:
	movb	%al, (%r12,%rax)
	addq	$1, %rax
	cmpq	$256, %rax
	jne	.L67
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
	jne	.L74
.L52:
	movq	(%rbp), %rax
	movl	$10, %esi
	movq	%rbp, %rdi
	call	*48(%rax)
.L50:
	movsbl	%al,%esi
	movq	%r13, %rdi
	call	_ZNSo3putEc
	movq	%rax, %rdi
	call	_ZNSo5flushEv
	movq	168(%rsp), %rdi
	xorl	%esi, %esi
	call	pthread_join
#APP
# 7 "../../lib/timing.h" 1
	xorl %eax,%eax
cpuid
rdtsc
# 0 "" 2
#NO_APP
	salq	$32, %rdx
	movl	$.LC0, %esi
	movl	$_ZSt4cout, %edi
	addq	%rax, %rdx
	movq	%rdx, 160(%rsp)
	movq	160(%rsp), %rbx
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
	je	.L72
	xorl	%eax, %eax
	cmpb	$0, 56(%rbp)
	leaq	176(%rsp), %r12
	jne	.L75
	.p2align 4,,10
	.p2align 3
.L66:
	movb	%al, (%r12,%rax)
	addq	$1, %rax
	cmpq	$256, %rax
	jne	.L66
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
	jne	.L76
.L57:
	movq	(%rbp), %rax
	movl	$10, %esi
	movq	%rbp, %rdi
	call	*48(%rax)
.L55:
	movsbl	%al,%esi
	movq	%r13, %rdi
	call	_ZNSo3putEc
	movq	%rax, %rdi
	call	_ZNSo5flushEv
	movl	(%r14), %ebx
	movl	$3, %edx
	movl	$.LC4, %esi
	movl	$_ZSt4cout, %edi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	movl	%ebx, %esi
	movl	$_ZSt4cout, %edi
	call	_ZNSolsEi
	movq	%rax, %r13
	movq	(%rax), %rax
	movq	-24(%rax), %rax
	movq	240(%r13,%rax), %rbp
	testq	%rbp, %rbp
	je	.L72
	xorl	%eax, %eax
	cmpb	$0, 56(%rbp)
	leaq	176(%rsp), %r12
	jne	.L77
	.p2align 4,,10
	.p2align 3
.L65:
	movb	%al, (%r12,%rax)
	addq	$1, %rax
	cmpq	$256, %rax
	jne	.L65
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
	jne	.L78
.L62:
	movq	(%rbp), %rax
	movl	$10, %esi
	movq	%rbp, %rdi
	call	*48(%rax)
.L60:
	movsbl	%al,%esi
	movq	%r13, %rdi
	call	_ZNSo3putEc
	movq	%rax, %rdi
	call	_ZNSo5flushEv
	xorl	%eax, %eax
	movq	440(%rsp), %rdx
	xorq	%fs:40, %rdx
	jne	.L79
	addq	$448, %rsp
	popq	%rbx
	popq	%rbp
	popq	%r12
	popq	%r13
	popq	%r14
	ret
.L74:
	movb	$2, 56(%rbp)
	jmp	.L52
.L76:
	movb	$2, 56(%rbp)
	jmp	.L57
.L78:
	movb	$2, 56(%rbp)
	.p2align 4,,5
	.p2align 3
	jmp	.L62
.L73:
	movzbl	67(%rbp), %eax
	.p2align 4,,5
	.p2align 3
	jmp	.L50
.L75:
	movzbl	67(%rbp), %eax
	.p2align 4,,5
	.p2align 3
	jmp	.L55
.L77:
	movzbl	67(%rbp), %eax
	.p2align 4,,5
	.p2align 3
	jmp	.L60
.L72:
	.p2align 4,,7
	.p2align 3
	call	_ZSt16__throw_bad_castv
.L79:
	.p2align 4,,6
	.p2align 3
	call	__stack_chk_fail
.LFE1026:
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
	.long	.LFB1190
	.long	.LFE1190-.LFB1190
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI1-.LFB1190
	.byte	0xe
	.uleb128 0x10
	.align 8
.LEFDE3:
.LSFDE5:
	.long	.LEFDE5-.LASFDE5
.LASFDE5:
	.long	.LASFDE5-.Lframe1
	.long	.LFB1025
	.long	.LFE1025-.LFB1025
	.uleb128 0x0
	.align 8
.LEFDE5:
.LSFDE7:
	.long	.LEFDE7-.LASFDE7
.LASFDE7:
	.long	.LASFDE7-.Lframe1
	.long	.LFB1024
	.long	.LFE1024-.LFB1024
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI2-.LFB1024
	.byte	0xe
	.uleb128 0x10
	.byte	0x4
	.long	.LCFI3-.LCFI2
	.byte	0xe
	.uleb128 0x18
	.byte	0x4
	.long	.LCFI4-.LCFI3
	.byte	0xe
	.uleb128 0x20
	.byte	0x4
	.long	.LCFI5-.LCFI4
	.byte	0xe
	.uleb128 0x28
	.byte	0x86
	.uleb128 0x5
	.byte	0x8c
	.uleb128 0x4
	.byte	0x8d
	.uleb128 0x3
	.byte	0x8e
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI6-.LCFI5
	.byte	0xe
	.uleb128 0x30
	.byte	0x4
	.long	.LCFI7-.LCFI6
	.byte	0xe
	.uleb128 0x140
	.byte	0x83
	.uleb128 0x6
	.align 8
.LEFDE7:
.LSFDE9:
	.long	.LEFDE9-.LASFDE9
.LASFDE9:
	.long	.LASFDE9-.Lframe1
	.long	.LFB1026
	.long	.LFE1026-.LFB1026
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI8-.LFB1026
	.byte	0xe
	.uleb128 0x10
	.byte	0x4
	.long	.LCFI9-.LCFI8
	.byte	0xe
	.uleb128 0x18
	.byte	0x4
	.long	.LCFI10-.LCFI9
	.byte	0xe
	.uleb128 0x20
	.byte	0x4
	.long	.LCFI11-.LCFI10
	.byte	0xe
	.uleb128 0x28
	.byte	0x4
	.long	.LCFI12-.LCFI11
	.byte	0xe
	.uleb128 0x30
	.byte	0x4
	.long	.LCFI13-.LCFI12
	.byte	0xe
	.uleb128 0x1f0
	.byte	0x83
	.uleb128 0x6
	.byte	0x86
	.uleb128 0x5
	.byte	0x8c
	.uleb128 0x4
	.byte	0x8d
	.uleb128 0x3
	.byte	0x8e
	.uleb128 0x2
	.align 8
.LEFDE9:
	.ident	"GCC: (Ubuntu 4.3.3-5ubuntu4) 4.3.3"
	.section	.note.GNU-stack,"",@progbits
