	.file	"biasedlock.cpp"
	.text
	.type	_Z41__static_initialization_and_destruction_0ii, @function
_Z41__static_initialization_and_destruction_0ii:
.LFB980:
	pushq	%rbp
.LCFI0:
	movq	%rsp, %rbp
.LCFI1:
	subq	$16, %rsp
.LCFI2:
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	cmpl	$1, -4(%rbp)
	jne	.L3
	cmpl	$65535, -8(%rbp)
	jne	.L3
	movl	$_ZStL8__ioinit, %edi
	call	_ZNSt8ios_base4InitC1Ev
	movl	$_ZNSt8ios_base4InitD1Ev, %edi
	movl	$__dso_handle, %edx
	movl	$_ZStL8__ioinit, %esi
	call	__cxa_atexit
.L3:
	leave
	ret
.LFE980:
	.size	_Z41__static_initialization_and_destruction_0ii, .-_Z41__static_initialization_and_destruction_0ii
	.type	_GLOBAL__I__Z13biased_unlockP4LockPi, @function
_GLOBAL__I__Z13biased_unlockP4LockPi:
.LFB981:
	pushq	%rbp
.LCFI3:
	movq	%rsp, %rbp
.LCFI4:
	movl	$65535, %esi
	movl	$1, %edi
	call	_Z41__static_initialization_and_destruction_0ii
	leave
	ret
.LFE981:
	.size	_GLOBAL__I__Z13biased_unlockP4LockPi, .-_GLOBAL__I__Z13biased_unlockP4LockPi
	.section	.ctors,"aw",@progbits
	.align 8
	.quad	_GLOBAL__I__Z13biased_unlockP4LockPi
	.section	.rodata
.LC0:
	.string	"x: "
.LC1:
	.string	" y: "
	.text
.globl main
	.type	main, @function
main:
.LFB971:
	pushq	%rbp
.LCFI5:
	movq	%rsp, %rbp
.LCFI6:
	pushq	%r12
.LCFI7:
	pushq	%rbx
.LCFI8:
	subq	$688, %rsp
.LCFI9:
	movl	$8, %edi
	call	malloc
	movq	%rax, -40(%rbp)
	movq	-40(%rbp), %rax
	addq	$4, %rax
	movl	$0, (%rax)
	movl	(%rax), %edx
	movq	-40(%rbp), %rax
	movl	%edx, (%rax)
	movl	$32, %edi
	call	_Znwm
	movq	%rax, -48(%rbp)
	movq	-48(%rbp), %rax
	movb	$0, 28(%rax)
	movq	-48(%rbp), %rax
	movb	$0, 29(%rax)
	movl	$4, %edi
	call	_Znwm
	movl	$0, (%rax)
	movq	%rax, -56(%rbp)
	movl	$4, %edi
	call	_Znwm
	movl	$0, (%rax)
	movq	%rax, -64(%rbp)
	movl	$0, -24(%rbp)
	jmp	.L7
.L8:
	movl	-24(%rbp), %eax
	cltq
	addq	%rax, %rax
	addq	$1, %rax
	salq	$4, %rax
	leaq	-16(%rbp), %rdx
	leaq	(%rdx,%rax), %rax
	leaq	-688(%rax), %rdx
	movq	-56(%rbp), %rax
	movq	%rax, (%rdx)
	movl	-24(%rbp), %eax
	cltq
	addq	%rax, %rax
	addq	$1, %rax
	salq	$4, %rax
	leaq	-16(%rbp), %rcx
	leaq	(%rcx,%rax), %rax
	leaq	-680(%rax), %rdx
	movq	-64(%rbp), %rax
	movq	%rax, (%rdx)
	movl	-24(%rbp), %eax
	cltq
	salq	$5, %rax
	leaq	-16(%rbp), %rdx
	leaq	(%rdx,%rax), %rax
	leaq	-680(%rax), %rdx
	movq	-48(%rbp), %rax
	movq	%rax, (%rdx)
	movl	-24(%rbp), %ebx
	movl	$4, %edi
	call	_Znwm
	movq	%rax, %rdx
	movl	-24(%rbp), %eax
	movl	%eax, (%rdx)
	movslq	%ebx,%rax
	salq	$5, %rax
	leaq	-16(%rbp), %rcx
	leaq	(%rcx,%rax), %rax
	subq	$688, %rax
	movq	%rdx, (%rax)
	movl	-24(%rbp), %eax
	leaq	-704(%rbp), %rdx
	cltq
	salq	$5, %rax
	leaq	(%rdx,%rax), %rcx
	movl	$_Z3fooP10threaddata, %esi
	movl	-24(%rbp), %eax
	leaq	-192(%rbp), %rdx
	cltq
	salq	$3, %rax
	leaq	(%rdx,%rax), %rdi
	movq	%rsi, %rdx
	movl	$0, %esi
	call	pthread_create
	addl	$1, -24(%rbp)
.L7:
	cmpl	$15, -24(%rbp)
	jle	.L8
	movl	$0, -28(%rbp)
	jmp	.L9
.L10:
	movl	-28(%rbp), %eax
	cltq
	movq	-192(%rbp,%rax,8), %rdi
	movl	$0, %esi
	call	pthread_join
	addl	$1, -28(%rbp)
.L9:
	cmpl	$15, -28(%rbp)
	jle	.L10
	movq	-64(%rbp), %rax
	movl	(%rax), %r12d
	movq	-56(%rbp), %rax
	movl	(%rax), %ebx
	movl	$.LC0, %esi
	movl	$_ZSt4cout, %edi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movq	%rax, %rdi
	movl	%ebx, %esi
	call	_ZNSolsEi
	movq	%rax, %rdi
	movl	$.LC1, %esi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movq	%rax, %rdi
	movl	%r12d, %esi
	call	_ZNSolsEi
	movq	%rax, %rdi
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	call	_ZNSolsEPFRSoS_E
	movl	$0, %eax
	addq	$688, %rsp
	popq	%rbx
	popq	%r12
	leave
	ret
.LFE971:
	.size	main, .-main
	.section	.text._Z11biased_lockP4LockPi,"axG",@progbits,_Z11biased_lockP4LockPi,comdat
	.weak	_Z11biased_lockP4LockPi
	.type	_Z11biased_lockP4LockPi, @function
_Z11biased_lockP4LockPi:
.LFB968:
	pushq	%rbp
.LCFI10:
	movq	%rsp, %rbp
.LCFI11:
	subq	$16, %rsp
.LCFI12:
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-8(%rbp), %rax
	leaq	24(%rax), %rdi
	call	_ZN8spinlock5lockNEPi
	movq	-8(%rbp), %rax
	movb	$1, 28(%rax)
.L13:
	movq	-8(%rbp), %rax
	movzbl	29(%rax), %eax
	xorl	$1, %eax
	testb	%al, %al
	jne	.L13
	leave
	ret
.LFE968:
	.size	_Z11biased_lockP4LockPi, .-_Z11biased_lockP4LockPi
	.text
.globl _Z13biased_unlockP4LockPi
	.type	_Z13biased_unlockP4LockPi, @function
_Z13biased_unlockP4LockPi:
.LFB969:
	pushq	%rbp
.LCFI13:
	movq	%rsp, %rbp
.LCFI14:
	subq	$16, %rsp
.LCFI15:
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
#APP
# 33 "biasedlock.cpp" 1
	mfence
# 0 "" 2
#NO_APP
	movq	-8(%rbp), %rax
	movb	$0, 29(%rax)
	movq	-8(%rbp), %rax
	leaq	24(%rax), %rdi
	call	_ZN8spinlock7unlockNEPi
	leave
	ret
.LFE969:
	.size	_Z13biased_unlockP4LockPi, .-_Z13biased_unlockP4LockPi
	.section	.rodata
.LC2:
	.string	"owner"
.LC3:
	.string	"dom thread done"
.LC4:
	.string	"thread "
.LC5:
	.string	" done"
	.text
.globl _Z3fooP10threaddata
	.type	_Z3fooP10threaddata, @function
_Z3fooP10threaddata:
.LFB970:
	pushq	%rbp
.LCFI16:
	movq	%rsp, %rbp
.LCFI17:
	pushq	%rbx
.LCFI18:
	subq	$24, %rsp
.LCFI19:
	movq	%rdi, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	jne	.L18
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	movl	(%rax), %ebx
	movl	$.LC2, %esi
	movl	$_ZSt4cout, %edi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movq	%rax, %rdi
	movl	%ebx, %esi
	call	_ZNSolsEi
	movq	%rax, %rdi
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	call	_ZNSolsEPFRSoS_E
	movl	$0, -12(%rbp)
	jmp	.L19
.L20:
	movq	-32(%rbp), %rax
	movq	8(%rax), %rax
	movzbl	29(%rax), %eax
	testb	%al, %al
	jne	.L20
	movq	-32(%rbp), %rax
	movq	16(%rax), %rdx
	movq	-32(%rbp), %rax
	movq	16(%rax), %rax
	movl	(%rax), %eax
	addl	$1, %eax
	movl	%eax, (%rdx)
	movq	-32(%rbp), %rax
	movq	8(%rax), %rax
	movzbl	28(%rax), %eax
	testb	%al, %al
	je	.L21
	movq	-32(%rbp), %rax
	movq	8(%rax), %rax
	movb	$0, 28(%rax)
#APP
# 54 "biasedlock.cpp" 1
	mfence
# 0 "" 2
#NO_APP
	movq	-32(%rbp), %rax
	movq	8(%rax), %rax
	movb	$1, 29(%rax)
.L21:
	addl	$1, -12(%rbp)
.L19:
	cmpl	$119999999, -12(%rbp)
	jle	.L20
	movl	$.LC3, %esi
	movl	$_ZSt4cout, %edi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movq	%rax, %rdi
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	call	_ZNSolsEPFRSoS_E
	jmp	.L25
.L18:
	movl	$0, -16(%rbp)
	jmp	.L23
.L24:
	movq	-32(%rbp), %rax
	movq	(%rax), %rsi
	movq	-32(%rbp), %rax
	movq	8(%rax), %rdi
	call	_Z11biased_lockP4LockPi
	movq	-32(%rbp), %rax
	movq	24(%rax), %rdx
	movq	-32(%rbp), %rax
	movq	24(%rax), %rax
	movl	(%rax), %eax
	addl	$1, %eax
	movl	%eax, (%rdx)
	movq	-32(%rbp), %rax
	movq	(%rax), %rsi
	movq	-32(%rbp), %rax
	movq	8(%rax), %rdi
	call	_Z13biased_unlockP4LockPi
	addl	$1, -16(%rbp)
.L23:
	cmpl	$19, -16(%rbp)
	jle	.L24
	movq	-32(%rbp), %rax
	movq	(%rax), %rax
	movl	(%rax), %ebx
	movl	$.LC4, %esi
	movl	$_ZSt4cout, %edi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movq	%rax, %rdi
	movl	%ebx, %esi
	call	_ZNSolsEi
	movq	%rax, %rdi
	movl	$.LC5, %esi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movq	%rax, %rdi
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	call	_ZNSolsEPFRSoS_E
.L25:
	addq	$24, %rsp
	popq	%rbx
	leave
	ret
.LFE970:
	.size	_Z3fooP10threaddata, .-_Z3fooP10threaddata
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
	.long	.LFB980
	.long	.LFE980-.LFB980
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI0-.LFB980
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
	.long	.LFB981
	.long	.LFE981-.LFB981
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI3-.LFB981
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI4-.LCFI3
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE3:
.LSFDE5:
	.long	.LEFDE5-.LASFDE5
.LASFDE5:
	.long	.LASFDE5-.Lframe1
	.long	.LFB971
	.long	.LFE971-.LFB971
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI5-.LFB971
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI6-.LCFI5
	.byte	0xd
	.uleb128 0x6
	.byte	0x4
	.long	.LCFI9-.LCFI6
	.byte	0x83
	.uleb128 0x4
	.byte	0x8c
	.uleb128 0x3
	.align 8
.LEFDE5:
.LSFDE7:
	.long	.LEFDE7-.LASFDE7
.LASFDE7:
	.long	.LASFDE7-.Lframe1
	.long	.LFB968
	.long	.LFE968-.LFB968
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI10-.LFB968
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI11-.LCFI10
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE7:
.LSFDE9:
	.long	.LEFDE9-.LASFDE9
.LASFDE9:
	.long	.LASFDE9-.Lframe1
	.long	.LFB969
	.long	.LFE969-.LFB969
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI13-.LFB969
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI14-.LCFI13
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE9:
.LSFDE11:
	.long	.LEFDE11-.LASFDE11
.LASFDE11:
	.long	.LASFDE11-.Lframe1
	.long	.LFB970
	.long	.LFE970-.LFB970
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI16-.LFB970
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI17-.LCFI16
	.byte	0xd
	.uleb128 0x6
	.byte	0x4
	.long	.LCFI19-.LCFI17
	.byte	0x83
	.uleb128 0x3
	.align 8
.LEFDE11:
	.ident	"GCC: (Ubuntu 4.3.3-5ubuntu4) 4.3.3"
	.section	.note.GNU-stack,"",@progbits
