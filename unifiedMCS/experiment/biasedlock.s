	.file	"biasedlock.cpp"
	.section	.text._ZN10threaddataC1Ev,"axG",@progbits,_ZN10threaddataC1Ev,comdat
	.align 2
	.weak	_ZN10threaddataC1Ev
	.type	_ZN10threaddataC1Ev, @function
_ZN10threaddataC1Ev:
.LFB4:
	pushq	%rbp
.LCFI0:
	movq	%rsp, %rbp
.LCFI1:
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	$0, 8(%rax)
	movq	-8(%rbp), %rax
	movq	$0, 16(%rax)
	leave
	ret
.LFE4:
	.size	_ZN10threaddataC1Ev, .-_ZN10threaddataC1Ev
	.section	.text._ZN8spinlock7unlockNEPi,"axG",@progbits,_ZN8spinlock7unlockNEPi,comdat
	.weak	_ZN8spinlock7unlockNEPi
	.type	_ZN8spinlock7unlockNEPi, @function
_ZN8spinlock7unlockNEPi:
.LFB15:
	pushq	%rbp
.LCFI2:
	movq	%rsp, %rbp
.LCFI3:
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	$0, (%rax)
	leave
	ret
.LFE15:
	.size	_ZN8spinlock7unlockNEPi, .-_ZN8spinlock7unlockNEPi
	.text
.globl _Z8get_timev
	.type	_Z8get_timev, @function
_Z8get_timev:
.LFB957:
	pushq	%rbp
.LCFI4:
	movq	%rsp, %rbp
.LCFI5:
	pushq	%rbx
.LCFI6:
#APP
# 20 "biasedlock.cpp" 1
	xorl %eax,%eax
cpuid
rdtsc
# 0 "" 2
#NO_APP
	movq	%rax, -16(%rbp)
	movq	%rdx, -24(%rbp)
	movq	-24(%rbp), %rax
	salq	$32, %rax
	addq	-16(%rbp), %rax
	popq	%rbx
	leave
	ret
.LFE957:
	.size	_Z8get_timev, .-_Z8get_timev
	.section	.text._Z4incyPiP3lll,"axG",@progbits,_Z4incyPiP3lll,comdat
	.weak	_Z4incyPiP3lll
	.type	_Z4incyPiP3lll, @function
_Z4incyPiP3lll:
.LFB960:
	pushq	%rbp
.LCFI7:
	movq	%rsp, %rbp
.LCFI8:
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	movl	(%rax), %eax
	leal	1(%rax), %edx
	movq	-8(%rbp), %rax
	movl	%edx, (%rax)
	movq	-16(%rbp), %rax
	movq	$0, 8(%rax)
	movq	-16(%rbp), %rax
	movl	$1, 4(%rax)
#APP
# 41 "biasedlock.cpp" 1
	mfence
# 0 "" 2
#NO_APP
	leave
	ret
.LFE960:
	.size	_Z4incyPiP3lll, .-_Z4incyPiP3lll
	.text
	.type	_Z41__static_initialization_and_destruction_0ii, @function
_Z41__static_initialization_and_destruction_0ii:
.LFB974:
	pushq	%rbp
.LCFI9:
	movq	%rsp, %rbp
.LCFI10:
	subq	$16, %rsp
.LCFI11:
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	cmpl	$1, -4(%rbp)
	jne	.L11
	cmpl	$65535, -8(%rbp)
	jne	.L11
	movl	$_ZStL8__ioinit, %edi
	call	_ZNSt8ios_base4InitC1Ev
	movl	$_ZNSt8ios_base4InitD1Ev, %edi
	movl	$__dso_handle, %edx
	movl	$_ZStL8__ioinit, %esi
	call	__cxa_atexit
.L11:
	leave
	ret
.LFE974:
	.size	_Z41__static_initialization_and_destruction_0ii, .-_Z41__static_initialization_and_destruction_0ii
	.type	_GLOBAL__I_start, @function
_GLOBAL__I_start:
.LFB975:
	pushq	%rbp
.LCFI12:
	movq	%rsp, %rbp
.LCFI13:
	movl	$65535, %esi
	movl	$1, %edi
	call	_Z41__static_initialization_and_destruction_0ii
	leave
	ret
.LFE975:
	.size	_GLOBAL__I_start, .-_GLOBAL__I_start
	.section	.ctors,"aw",@progbits
	.align 8
	.quad	_GLOBAL__I_start
	.section	.rodata
.LC0:
	.string	"time: "
	.text
.globl main
	.type	main, @function
main:
.LFB964:
	pushq	%rbp
.LCFI14:
	movq	%rsp, %rbp
.LCFI15:
	pushq	%r12
.LCFI16:
	pushq	%rbx
.LCFI17:
	addq	$-128, %rsp
.LCFI18:
	movl	$16, %edi
	call	_Znwm
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	$0, 8(%rax)
	movq	-32(%rbp), %rax
	movl	$1, 4(%rax)
	movl	$4, %edi
	call	_Znwm
	movl	$0, (%rax)
	movq	%rax, -40(%rbp)
	movl	$4, %edi
	call	_Znwm
	movl	$0, (%rax)
	movq	%rax, -48(%rbp)
	movq	$_Z4incyPiP3lll, -56(%rbp)
	call	_Z8get_timev
	movq	%rax, start(%rip)
	movl	$0, -20(%rbp)
	jmp	.L15
.L16:
	movl	$4, %edi
	call	_Znwm
	movq	%rax, %rdx
	movl	-20(%rbp), %eax
	movl	%eax, (%rdx)
	movq	%rdx, -64(%rbp)
	movl	-20(%rbp), %r12d
	movl	$32, %edi
	call	_Znwm
	movq	%rax, %rbx
	movq	%rbx, %rdi
	call	_ZN10threaddataC1Ev
	movslq	%r12d,%rax
	movq	%rbx, -144(%rbp,%rax,8)
	movl	-20(%rbp), %eax
	cltq
	movq	-144(%rbp,%rax,8), %rdx
	movq	-40(%rbp), %rax
	movq	%rax, 8(%rdx)
	movl	-20(%rbp), %eax
	cltq
	movq	-144(%rbp,%rax,8), %rdx
	movq	-48(%rbp), %rax
	movq	%rax, 16(%rdx)
	movl	-20(%rbp), %eax
	cltq
	movq	-144(%rbp,%rax,8), %rdx
	movq	-64(%rbp), %rax
	movq	%rax, (%rdx)
	movl	-20(%rbp), %eax
	cltq
	movq	-144(%rbp,%rax,8), %rdx
	movq	-32(%rbp), %rax
	movq	%rax, 24(%rdx)
	movl	-20(%rbp), %eax
	cltq
	movq	-144(%rbp,%rax,8), %rcx
	movl	$_Z3fooP10threaddata, %esi
	movl	-20(%rbp), %eax
	leaq	-112(%rbp), %rdx
	cltq
	salq	$3, %rax
	leaq	(%rdx,%rax), %rdi
	movq	%rsi, %rdx
	movl	$0, %esi
	call	pthread_create
	addl	$1, -20(%rbp)
.L15:
	cmpl	$3, -20(%rbp)
	jle	.L16
	movl	$0, -24(%rbp)
	jmp	.L17
.L18:
	movl	-24(%rbp), %eax
	cltq
	movq	-112(%rbp,%rax,8), %rdi
	movl	$0, %esi
	call	pthread_join
	addl	$1, -24(%rbp)
.L17:
	cmpl	$3, -24(%rbp)
	jle	.L18
	call	_Z8get_timev
	movq	%rax, -72(%rbp)
	movq	start(%rip), %rdx
	movq	-72(%rbp), %rax
	movq	%rax, %rbx
	subq	%rdx, %rbx
	movl	$.LC0, %esi
	movl	$_ZSt4cout, %edi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movq	%rax, %rdi
	movq	%rbx, %rsi
	call	_ZNSolsEy
	movq	%rax, %rdi
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	call	_ZNSolsEPFRSoS_E
	movl	$0, %eax
	subq	$-128, %rsp
	popq	%rbx
	popq	%r12
	leave
	ret
.LFE964:
	.size	main, .-main
	.section	.text._ZN8spinlock5lockNEPi,"axG",@progbits,_ZN8spinlock5lockNEPi,comdat
	.weak	_ZN8spinlock5lockNEPi
	.type	_ZN8spinlock5lockNEPi, @function
_ZN8spinlock5lockNEPi:
.LFB14:
	pushq	%rbp
.LCFI19:
	movq	%rsp, %rbp
.LCFI20:
	movq	%rdi, -24(%rbp)
	movl	$0, -4(%rbp)
.L21:
	movq	-24(%rbp), %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	jne	.L21
	movq	-24(%rbp), %rcx
	movl	$0, -36(%rbp)
	movl	$1, %edx
	movl	-36(%rbp), %eax
	lock cmpxchgl	%edx, (%rcx)
	sete	%al
	movzbl	%al, %eax
	movl	%eax, -4(%rbp)
	cmpl	$0, -4(%rbp)
	je	.L21
	leave
	ret
.LFE14:
	.size	_ZN8spinlock5lockNEPi, .-_ZN8spinlock5lockNEPi
	.section	.rodata
.LC1:
	.string	"owner"
.LC2:
	.string	"dom thread done"
	.text
.globl _Z3fooP10threaddata
	.type	_Z3fooP10threaddata, @function
_Z3fooP10threaddata:
.LFB963:
	pushq	%rbp
.LCFI21:
	movq	%rsp, %rbp
.LCFI22:
	pushq	%rbx
.LCFI23:
	subq	$56, %rsp
.LCFI24:
	movq	%rdi, -64(%rbp)
	movq	-64(%rbp), %rax
	movq	(%rax), %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	jne	.L24
	movq	-64(%rbp), %rax
	movq	(%rax), %rax
	movl	(%rax), %ebx
	movl	$.LC1, %esi
	movl	$_ZSt4cout, %edi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movq	%rax, %rdi
	movl	%ebx, %esi
	call	_ZNSolsEi
	movq	%rax, %rdi
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	call	_ZNSolsEPFRSoS_E
	movl	$0, -12(%rbp)
	jmp	.L25
.L27:
	movq	-64(%rbp), %rax
	movq	8(%rax), %rdx
	movq	-64(%rbp), %rax
	movq	8(%rax), %rax
	movl	(%rax), %eax
	addl	$1, %eax
	movl	%eax, (%rdx)
	movq	-64(%rbp), %rax
	movq	24(%rax), %rax
	movq	8(%rax), %rax
	testq	%rax, %rax
	je	.L26
	movq	-64(%rbp), %rax
	movq	24(%rax), %rax
	movq	8(%rax), %rdx
	movq	-64(%rbp), %rax
	movq	24(%rax), %rsi
	movq	-64(%rbp), %rax
	movq	8(%rax), %rdi
	call	*%rdx
.L26:
	addl	$1, -12(%rbp)
.L25:
	cmpl	$999999999, -12(%rbp)
	jle	.L27
	movl	$.LC2, %esi
	movl	$_ZSt4cout, %edi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movq	%rax, %rdi
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	call	_ZNSolsEPFRSoS_E
	call	_Z8get_timev
	movq	%rax, %rdx
	movq	start(%rip), %rax
	movq	%rdx, %rbx
	subq	%rax, %rbx
	movl	$.LC0, %esi
	movl	$_ZSt4cout, %edi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movq	%rax, %rdi
	movq	%rbx, %rsi
	call	_ZNSolsEy
	movq	%rax, %rdi
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	call	_ZNSolsEPFRSoS_E
	movq	-64(%rbp), %rax
	movq	8(%rax), %rax
	movl	(%rax), %esi
	movl	$_ZSt4cout, %edi
	call	_ZNSolsEi
	movq	%rax, %rdi
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	call	_ZNSolsEPFRSoS_E
	jmp	.L33
.L24:
	movl	$16, %edi
	call	_Znwm
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	$1, 8(%rax)
	movl	$0, -16(%rbp)
	jmp	.L29
.L32:
	movq	-64(%rbp), %rax
	movq	(%rax), %rdx
	movq	-64(%rbp), %rax
	movq	24(%rax), %rax
	movq	%rax, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movq	-32(%rbp), %rdi
	call	_ZN8spinlock5lockNEPi
	movq	-64(%rbp), %rax
	movq	24(%rax), %rax
	movl	$0, 4(%rax)
	movq	-64(%rbp), %rax
	movq	24(%rax), %rax
	movq	$_Z4incyPiP3lll, 8(%rax)
#APP
# 100 "biasedlock.cpp" 1
	mfence
# 0 "" 2
#NO_APP
	jmp	.L30
.L31:
#APP
# 101 "biasedlock.cpp" 1
	pause
# 0 "" 2
#NO_APP
.L30:
	movq	-64(%rbp), %rax
	movq	24(%rax), %rax
	movl	4(%rax), %eax
	testl	%eax, %eax
	je	.L31
	movq	-64(%rbp), %rax
	movq	(%rax), %rdx
	movq	-64(%rbp), %rax
	movq	24(%rax), %rax
	movq	%rax, -48(%rbp)
	movq	%rdx, -56(%rbp)
	movq	-48(%rbp), %rdi
	call	_ZN8spinlock7unlockNEPi
	addl	$1, -16(%rbp)
.L29:
	cmpl	$0, -16(%rbp)
	js	.L32
.L33:
	addq	$56, %rsp
	popq	%rbx
	leave
	ret
.LFE963:
	.size	_Z3fooP10threaddata, .-_Z3fooP10threaddata
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
	.long	.LFB4
	.long	.LFE4-.LFB4
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI0-.LFB4
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI1-.LCFI0
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE1:
.LSFDE3:
	.long	.LEFDE3-.LASFDE3
.LASFDE3:
	.long	.LASFDE3-.Lframe1
	.long	.LFB15
	.long	.LFE15-.LFB15
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI2-.LFB15
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI3-.LCFI2
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE3:
.LSFDE5:
	.long	.LEFDE5-.LASFDE5
.LASFDE5:
	.long	.LASFDE5-.Lframe1
	.long	.LFB957
	.long	.LFE957-.LFB957
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI4-.LFB957
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI5-.LCFI4
	.byte	0xd
	.uleb128 0x6
	.byte	0x4
	.long	.LCFI6-.LCFI5
	.byte	0x83
	.uleb128 0x3
	.align 8
.LEFDE5:
.LSFDE7:
	.long	.LEFDE7-.LASFDE7
.LASFDE7:
	.long	.LASFDE7-.Lframe1
	.long	.LFB960
	.long	.LFE960-.LFB960
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI7-.LFB960
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI8-.LCFI7
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE7:
.LSFDE9:
	.long	.LEFDE9-.LASFDE9
.LASFDE9:
	.long	.LASFDE9-.Lframe1
	.long	.LFB974
	.long	.LFE974-.LFB974
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI9-.LFB974
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI10-.LCFI9
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE9:
.LSFDE11:
	.long	.LEFDE11-.LASFDE11
.LASFDE11:
	.long	.LASFDE11-.Lframe1
	.long	.LFB975
	.long	.LFE975-.LFB975
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI12-.LFB975
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI13-.LCFI12
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE11:
.LSFDE13:
	.long	.LEFDE13-.LASFDE13
.LASFDE13:
	.long	.LASFDE13-.Lframe1
	.long	.LFB964
	.long	.LFE964-.LFB964
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI14-.LFB964
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI15-.LCFI14
	.byte	0xd
	.uleb128 0x6
	.byte	0x4
	.long	.LCFI18-.LCFI15
	.byte	0x83
	.uleb128 0x4
	.byte	0x8c
	.uleb128 0x3
	.align 8
.LEFDE13:
.LSFDE15:
	.long	.LEFDE15-.LASFDE15
.LASFDE15:
	.long	.LASFDE15-.Lframe1
	.long	.LFB14
	.long	.LFE14-.LFB14
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI19-.LFB14
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI20-.LCFI19
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE15:
.LSFDE17:
	.long	.LEFDE17-.LASFDE17
.LASFDE17:
	.long	.LASFDE17-.Lframe1
	.long	.LFB963
	.long	.LFE963-.LFB963
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI21-.LFB963
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI22-.LCFI21
	.byte	0xd
	.uleb128 0x6
	.byte	0x4
	.long	.LCFI24-.LCFI22
	.byte	0x83
	.uleb128 0x3
	.align 8
.LEFDE17:
	.ident	"GCC: (Ubuntu 4.3.3-5ubuntu4) 4.3.3"
	.section	.note.GNU-stack,"",@progbits
