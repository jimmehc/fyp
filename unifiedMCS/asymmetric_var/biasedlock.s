	.file	"biasedlock.cpp"
	.section	.text._ZN8spinlock7unlockNEPi,"axG",@progbits,_ZN8spinlock7unlockNEPi,comdat
	.weak	_ZN8spinlock7unlockNEPi
	.type	_ZN8spinlock7unlockNEPi, @function
_ZN8spinlock7unlockNEPi:
.LFB37:
	pushq	%rbp
.LCFI0:
	movq	%rsp, %rbp
.LCFI1:
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	$0, (%rax)
	leave
	ret
.LFE37:
	.size	_ZN8spinlock7unlockNEPi, .-_ZN8spinlock7unlockNEPi
	.text
.globl _Z8get_timev
	.type	_Z8get_timev, @function
_Z8get_timev:
.LFB970:
	pushq	%rbp
.LCFI2:
	movq	%rsp, %rbp
.LCFI3:
	pushq	%rbx
.LCFI4:
#APP
# 19 "biasedlock.cpp" 1
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
.LFE970:
	.size	_Z8get_timev, .-_Z8get_timev
	.type	_Z41__static_initialization_and_destruction_0ii, @function
_Z41__static_initialization_and_destruction_0ii:
.LFB982:
	pushq	%rbp
.LCFI5:
	movq	%rsp, %rbp
.LCFI6:
	subq	$16, %rsp
.LCFI7:
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	cmpl	$1, -4(%rbp)
	jne	.L7
	cmpl	$65535, -8(%rbp)
	jne	.L7
	movl	$_ZStL8__ioinit, %edi
	call	_ZNSt8ios_base4InitC1Ev
	movl	$_ZNSt8ios_base4InitD1Ev, %edi
	movl	$__dso_handle, %edx
	movl	$_ZStL8__ioinit, %esi
	call	__cxa_atexit
.L7:
	leave
	ret
.LFE982:
	.size	_Z41__static_initialization_and_destruction_0ii, .-_Z41__static_initialization_and_destruction_0ii
	.type	_GLOBAL__I__Z12acquire_lockPP6_qnodeS0_, @function
_GLOBAL__I__Z12acquire_lockPP6_qnodeS0_:
.LFB983:
	pushq	%rbp
.LCFI8:
	movq	%rsp, %rbp
.LCFI9:
	movl	$65535, %esi
	movl	$1, %edi
	call	_Z41__static_initialization_and_destruction_0ii
	leave
	ret
.LFE983:
	.size	_GLOBAL__I__Z12acquire_lockPP6_qnodeS0_, .-_GLOBAL__I__Z12acquire_lockPP6_qnodeS0_
	.section	.ctors,"aw",@progbits
	.align 8
	.quad	_GLOBAL__I__Z12acquire_lockPP6_qnodeS0_
	.section	.rodata
.LC0:
	.string	"time: "
	.text
.globl main
	.type	main, @function
main:
.LFB972:
	pushq	%rbp
.LCFI10:
	movq	%rsp, %rbp
.LCFI11:
	pushq	%rbx
.LCFI12:
	subq	$216, %rsp
.LCFI13:
	movl	$24, %edi
	call	_Znwm
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rax
	movb	$0, 20(%rax)
	movq	-32(%rbp), %rax
	movb	$0, 21(%rax)
	movl	$4, %edi
	call	_Znwm
	movl	$0, (%rax)
	movq	%rax, -40(%rbp)
	movl	$4, %edi
	call	_Znwm
	movl	$0, (%rax)
	movq	%rax, -48(%rbp)
	call	_Z8get_timev
	movq	%rax, start(%rip)
	movl	$0, -20(%rbp)
	jmp	.L11
.L12:
	movl	-20(%rbp), %eax
	cltq
	addq	%rax, %rax
	addq	$1, %rax
	salq	$4, %rax
	leaq	-16(%rbp), %rdx
	leaq	(%rdx,%rax), %rax
	leaq	-208(%rax), %rdx
	movq	-40(%rbp), %rax
	movq	%rax, (%rdx)
	movl	-20(%rbp), %eax
	cltq
	addq	%rax, %rax
	addq	$1, %rax
	salq	$4, %rax
	leaq	-16(%rbp), %rcx
	leaq	(%rcx,%rax), %rax
	leaq	-200(%rax), %rdx
	movq	-48(%rbp), %rax
	movq	%rax, (%rdx)
	movl	-20(%rbp), %eax
	cltq
	salq	$5, %rax
	leaq	-16(%rbp), %rdx
	leaq	(%rdx,%rax), %rax
	leaq	-200(%rax), %rdx
	movq	-32(%rbp), %rax
	movq	%rax, (%rdx)
	movl	-20(%rbp), %ebx
	movl	$4, %edi
	call	_Znwm
	movq	%rax, %rdx
	movl	-20(%rbp), %eax
	movl	%eax, (%rdx)
	movslq	%ebx,%rax
	salq	$5, %rax
	leaq	-16(%rbp), %rcx
	leaq	(%rcx,%rax), %rax
	subq	$208, %rax
	movq	%rdx, (%rax)
	movl	-20(%rbp), %eax
	leaq	-224(%rbp), %rdx
	cltq
	salq	$5, %rax
	leaq	(%rdx,%rax), %rcx
	movl	$_Z3fooP10threaddata, %esi
	movl	-20(%rbp), %eax
	leaq	-96(%rbp), %rdx
	cltq
	salq	$3, %rax
	leaq	(%rdx,%rax), %rdi
	movq	%rsi, %rdx
	movl	$0, %esi
	call	pthread_create
	addl	$1, -20(%rbp)
.L11:
	cmpl	$3, -20(%rbp)
	jle	.L12
	movl	$0, -24(%rbp)
	jmp	.L13
.L14:
	movl	-24(%rbp), %eax
	cltq
	movq	-96(%rbp,%rax,8), %rdi
	movl	$0, %esi
	call	pthread_join
	addl	$1, -24(%rbp)
.L13:
	cmpl	$3, -24(%rbp)
	jle	.L14
	call	_Z8get_timev
	movq	%rax, -56(%rbp)
	movq	start(%rip), %rdx
	movq	-56(%rbp), %rax
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
	addq	$216, %rsp
	popq	%rbx
	leave
	ret
.LFE972:
	.size	main, .-main
	.section	.text._ZN8spinlock5lockNEPi,"axG",@progbits,_ZN8spinlock5lockNEPi,comdat
	.weak	_ZN8spinlock5lockNEPi
	.type	_ZN8spinlock5lockNEPi, @function
_ZN8spinlock5lockNEPi:
.LFB36:
	pushq	%rbp
.LCFI14:
	movq	%rsp, %rbp
.LCFI15:
	movq	%rdi, -24(%rbp)
	movl	$0, -4(%rbp)
.L17:
	movq	-24(%rbp), %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	jne	.L17
	movq	-24(%rbp), %rcx
	movl	$0, -36(%rbp)
	movl	$1, %edx
	movl	-36(%rbp), %eax
	lock cmpxchgl	%edx, (%rcx)
	sete	%al
	movzbl	%al, %eax
	movl	%eax, -4(%rbp)
	cmpl	$0, -4(%rbp)
	je	.L17
	leave
	ret
.LFE36:
	.size	_ZN8spinlock5lockNEPi, .-_ZN8spinlock5lockNEPi
	.section	.rodata
.LC1:
	.string	"dom thread done"
	.text
.globl _Z3fooP10threaddata
	.type	_Z3fooP10threaddata, @function
_Z3fooP10threaddata:
.LFB971:
	pushq	%rbp
.LCFI16:
	movq	%rsp, %rbp
.LCFI17:
	subq	$48, %rsp
.LCFI18:
	movq	%rdi, -40(%rbp)
	movq	-40(%rbp), %rax
	movq	(%rax), %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	jne	.L20
	movl	$0, -4(%rbp)
	jmp	.L21
.L25:
	movq	-40(%rbp), %rax
	movq	16(%rax), %rdx
	movq	-40(%rbp), %rax
	movq	16(%rax), %rax
	movl	(%rax), %eax
	addl	$1, %eax
	movl	%eax, (%rdx)
	movq	-40(%rbp), %rax
	movq	8(%rax), %rax
	movzbl	20(%rax), %eax
	testb	%al, %al
	je	.L22
	movq	-40(%rbp), %rax
	movq	8(%rax), %rax
	movb	$0, 20(%rax)
#APP
# 58 "biasedlock.cpp" 1
	mfence
# 0 "" 2
#NO_APP
	movq	-40(%rbp), %rax
	movq	8(%rax), %rax
	movb	$1, 21(%rax)
	jmp	.L23
.L24:
#APP
# 58 "biasedlock.cpp" 1
	pause
# 0 "" 2
#NO_APP
.L23:
	movq	-40(%rbp), %rax
	movq	8(%rax), %rax
	movzbl	21(%rax), %eax
	testb	%al, %al
	jne	.L24
.L22:
	addl	$1, -4(%rbp)
.L21:
	cmpl	$999999999, -4(%rbp)
	jle	.L25
	movl	$.LC1, %esi
	movl	$_ZSt4cout, %edi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movq	%rax, %rdi
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	call	_ZNSolsEPFRSoS_E
	jmp	.L31
.L20:
	movl	$16, %edi
	call	_Znwm
	movq	%rax, -16(%rbp)
	movl	$16, %edi
	call	_Znwm
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	$1, 8(%rax)
	movl	$0, -8(%rbp)
	jmp	.L27
.L30:
	movq	-40(%rbp), %rax
	movq	8(%rax), %rax
	leaq	16(%rax), %rdi
	call	_ZN8spinlock5lockNEPi
	movq	-40(%rbp), %rax
	movq	8(%rax), %rax
	movb	$1, 20(%rax)
	jmp	.L28
.L29:
#APP
# 80 "biasedlock.cpp" 1
	pause
# 0 "" 2
#NO_APP
.L28:
	movq	-40(%rbp), %rax
	movq	8(%rax), %rax
	movzbl	21(%rax), %eax
	xorl	$1, %eax
	testb	%al, %al
	jne	.L29
	movq	-40(%rbp), %rax
	movq	16(%rax), %rdx
	movq	-40(%rbp), %rax
	movq	16(%rax), %rax
	movl	(%rax), %eax
	addl	$1, %eax
	movl	%eax, (%rdx)
#APP
# 84 "biasedlock.cpp" 1
	mfence
# 0 "" 2
#NO_APP
	movq	-40(%rbp), %rax
	movq	8(%rax), %rax
	movb	$0, 21(%rax)
	movq	-40(%rbp), %rax
	movq	8(%rax), %rax
	leaq	16(%rax), %rdi
	call	_ZN8spinlock7unlockNEPi
	addl	$1, -8(%rbp)
.L27:
	cmpl	$0, -8(%rbp)
	js	.L30
.L31:
	leave
	ret
.LFE971:
	.size	_Z3fooP10threaddata, .-_Z3fooP10threaddata
.globl _Z12release_lockPP6_qnodeS0_
	.type	_Z12release_lockPP6_qnodeS0_, @function
_Z12release_lockPP6_qnodeS0_:
.LFB39:
	pushq	%rbp
.LCFI19:
	movq	%rsp, %rbp
.LCFI20:
	pushq	%rbx
.LCFI21:
	movq	%rdi, -16(%rbp)
	movq	%rsi, -24(%rbp)
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	testq	%rax, %rax
	jne	.L33
	movq	-24(%rbp), %rcx
	movq	-16(%rbp), %rax
	movq	%rax, -40(%rbp)
	movl	$0, %edx
	movq	-40(%rbp), %rbx
	movq	%rcx, %rax
	lock cmpxchgq	%rdx, (%rbx)
	sete	%al
	testb	%al, %al
	jne	.L36
.L35:
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	testq	%rax, %rax
	je	.L35
.L33:
	movq	-24(%rbp), %rax
	movq	(%rax), %rax
	movb	$0, 8(%rax)
.L36:
	popq	%rbx
	leave
	ret
.LFE39:
	.size	_Z12release_lockPP6_qnodeS0_, .-_Z12release_lockPP6_qnodeS0_
.globl _Z12acquire_lockPP6_qnodeS0_
	.type	_Z12acquire_lockPP6_qnodeS0_, @function
_Z12acquire_lockPP6_qnodeS0_:
.LFB38:
	pushq	%rbp
.LCFI22:
	movq	%rsp, %rbp
.LCFI23:
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	$0, (%rax)
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	xchgq	(%rax), %rdx
	movq	%rdx, -8(%rbp)
	cmpq	$0, -8(%rbp)
	je	.L40
	movq	-32(%rbp), %rax
	movb	$1, 8(%rax)
	movq	-8(%rbp), %rdx
	movq	-32(%rbp), %rax
	movq	%rax, (%rdx)
.L39:
	movq	-32(%rbp), %rax
	movzbl	8(%rax), %eax
	testb	%al, %al
	jne	.L39
.L40:
	leave
	ret
.LFE38:
	.size	_Z12acquire_lockPP6_qnodeS0_, .-_Z12acquire_lockPP6_qnodeS0_
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
	.long	.LFB37
	.long	.LFE37-.LFB37
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI0-.LFB37
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
	.long	.LFB970
	.long	.LFE970-.LFB970
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI2-.LFB970
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI3-.LCFI2
	.byte	0xd
	.uleb128 0x6
	.byte	0x4
	.long	.LCFI4-.LCFI3
	.byte	0x83
	.uleb128 0x3
	.align 8
.LEFDE3:
.LSFDE5:
	.long	.LEFDE5-.LASFDE5
.LASFDE5:
	.long	.LASFDE5-.Lframe1
	.long	.LFB982
	.long	.LFE982-.LFB982
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI5-.LFB982
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI6-.LCFI5
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE5:
.LSFDE7:
	.long	.LEFDE7-.LASFDE7
.LASFDE7:
	.long	.LASFDE7-.Lframe1
	.long	.LFB983
	.long	.LFE983-.LFB983
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI8-.LFB983
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI9-.LCFI8
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE7:
.LSFDE9:
	.long	.LEFDE9-.LASFDE9
.LASFDE9:
	.long	.LASFDE9-.Lframe1
	.long	.LFB972
	.long	.LFE972-.LFB972
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI10-.LFB972
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI11-.LCFI10
	.byte	0xd
	.uleb128 0x6
	.byte	0x4
	.long	.LCFI13-.LCFI11
	.byte	0x83
	.uleb128 0x3
	.align 8
.LEFDE9:
.LSFDE11:
	.long	.LEFDE11-.LASFDE11
.LASFDE11:
	.long	.LASFDE11-.Lframe1
	.long	.LFB36
	.long	.LFE36-.LFB36
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI14-.LFB36
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI15-.LCFI14
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE11:
.LSFDE13:
	.long	.LEFDE13-.LASFDE13
.LASFDE13:
	.long	.LASFDE13-.Lframe1
	.long	.LFB971
	.long	.LFE971-.LFB971
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI16-.LFB971
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI17-.LCFI16
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE13:
.LSFDE15:
	.long	.LEFDE15-.LASFDE15
.LASFDE15:
	.long	.LASFDE15-.Lframe1
	.long	.LFB39
	.long	.LFE39-.LFB39
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI19-.LFB39
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI20-.LCFI19
	.byte	0xd
	.uleb128 0x6
	.byte	0x4
	.long	.LCFI21-.LCFI20
	.byte	0x83
	.uleb128 0x3
	.align 8
.LEFDE15:
.LSFDE17:
	.long	.LEFDE17-.LASFDE17
.LASFDE17:
	.long	.LASFDE17-.Lframe1
	.long	.LFB38
	.long	.LFE38-.LFB38
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI22-.LFB38
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI23-.LCFI22
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE17:
	.ident	"GCC: (Ubuntu 4.3.3-5ubuntu4) 4.3.3"
	.section	.note.GNU-stack,"",@progbits
