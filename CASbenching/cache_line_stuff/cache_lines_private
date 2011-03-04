	.file	"cache_lines_private.cpp"
	.text
.globl _Z6writexP10threaddata
	.type	_Z6writexP10threaddata, @function
_Z6writexP10threaddata:
.LFB952:
	pushq	%rbp
.LCFI0:
	movq	%rsp, %rbp
.LCFI1:
	movq	%rdi, -24(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L2
.L3:
	movq	-24(%rbp), %rdx
	movl	-4(%rbp), %eax
	movl	%eax, 260(%rdx)
	addl	$1, -4(%rbp)
.L2:
	cmpl	$999999999, -4(%rbp)
	jle	.L3
	leave
	ret
.LFE952:
	.size	_Z6writexP10threaddata, .-_Z6writexP10threaddata
.globl _Z6writeyP10threaddata
	.type	_Z6writeyP10threaddata, @function
_Z6writeyP10threaddata:
.LFB953:
	pushq	%rbp
.LCFI2:
	movq	%rsp, %rbp
.LCFI3:
	movq	%rdi, -24(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L6
.L7:
	movq	-24(%rbp), %rdx
	movl	-4(%rbp), %eax
	movl	%eax, 520(%rdx)
	addl	$1, -4(%rbp)
.L6:
	cmpl	$999999999, -4(%rbp)
	jle	.L7
	leave
	ret
.LFE953:
	.size	_Z6writeyP10threaddata, .-_Z6writeyP10threaddata
.globl _Z6writezP10threaddata
	.type	_Z6writezP10threaddata, @function
_Z6writezP10threaddata:
.LFB954:
	pushq	%rbp
.LCFI4:
	movq	%rsp, %rbp
.LCFI5:
	movq	%rdi, -24(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L10
.L11:
	movq	-24(%rbp), %rdx
	movl	-4(%rbp), %eax
	movl	%eax, 780(%rdx)
	addl	$1, -4(%rbp)
.L10:
	cmpl	$999999999, -4(%rbp)
	jle	.L11
	leave
	ret
.LFE954:
	.size	_Z6writezP10threaddata, .-_Z6writezP10threaddata
.globl _Z6writewP10threaddata
	.type	_Z6writewP10threaddata, @function
_Z6writewP10threaddata:
.LFB955:
	pushq	%rbp
.LCFI6:
	movq	%rsp, %rbp
.LCFI7:
	movq	%rdi, -24(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L14
.L15:
	movq	-24(%rbp), %rdx
	movl	-4(%rbp), %eax
	movl	%eax, (%rdx)
	addl	$1, -4(%rbp)
.L14:
	cmpl	$999999999, -4(%rbp)
	jle	.L15
	leave
	ret
.LFE955:
	.size	_Z6writewP10threaddata, .-_Z6writewP10threaddata
	.type	_Z41__static_initialization_and_destruction_0ii, @function
_Z41__static_initialization_and_destruction_0ii:
.LFB966:
	pushq	%rbp
.LCFI8:
	movq	%rsp, %rbp
.LCFI9:
	subq	$16, %rsp
.LCFI10:
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	cmpl	$1, -4(%rbp)
	jne	.L19
	cmpl	$65535, -8(%rbp)
	jne	.L19
	movl	$_ZStL8__ioinit, %edi
	call	_ZNSt8ios_base4InitC1Ev
	movl	$_ZNSt8ios_base4InitD1Ev, %edi
	movl	$__dso_handle, %edx
	movl	$_ZStL8__ioinit, %esi
	call	__cxa_atexit
.L19:
	leave
	ret
.LFE966:
	.size	_Z41__static_initialization_and_destruction_0ii, .-_Z41__static_initialization_and_destruction_0ii
	.type	_GLOBAL__I__Z6writexP10threaddata, @function
_GLOBAL__I__Z6writexP10threaddata:
.LFB967:
	pushq	%rbp
.LCFI11:
	movq	%rsp, %rbp
.LCFI12:
	movl	$65535, %esi
	movl	$1, %edi
	call	_Z41__static_initialization_and_destruction_0ii
	leave
	ret
.LFE967:
	.size	_GLOBAL__I__Z6writexP10threaddata, .-_GLOBAL__I__Z6writexP10threaddata
	.section	.ctors,"aw",@progbits
	.align 8
	.quad	_GLOBAL__I__Z6writexP10threaddata
	.section	.rodata
.LC0:
	.string	"w: "
.LC1:
	.string	"x: "
.LC2:
	.string	"y: "
.LC3:
	.string	"z: "
	.text
.globl main
	.type	main, @function
main:
.LFB956:
	pushq	%rbp
.LCFI13:
	movq	%rsp, %rbp
.LCFI14:
	pushq	%rbx
.LCFI15:
	subq	$56, %rsp
.LCFI16:
	movl	$784, %edi
	call	_Znwm
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rbx
	movl	$.LC0, %esi
	movl	$_ZSt4cout, %edi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movq	%rax, %rdi
	movq	%rbx, %rsi
	call	_ZNSolsEPKv
	movq	%rax, %rdi
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	call	_ZNSolsEPFRSoS_E
	movq	-32(%rbp), %rax
	leaq	260(%rax), %rbx
	movl	$.LC1, %esi
	movl	$_ZSt4cout, %edi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movq	%rax, %rdi
	movq	%rbx, %rsi
	call	_ZNSolsEPKv
	movq	%rax, %rdi
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	call	_ZNSolsEPFRSoS_E
	movq	-32(%rbp), %rax
	leaq	520(%rax), %rbx
	movl	$.LC2, %esi
	movl	$_ZSt4cout, %edi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movq	%rax, %rdi
	movq	%rbx, %rsi
	call	_ZNSolsEPKv
	movq	%rax, %rdi
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	call	_ZNSolsEPFRSoS_E
	movq	-32(%rbp), %rax
	leaq	780(%rax), %rbx
	movl	$.LC3, %esi
	movl	$_ZSt4cout, %edi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movq	%rax, %rdi
	movq	%rbx, %rsi
	call	_ZNSolsEPKv
	movq	%rax, %rdi
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	call	_ZNSolsEPFRSoS_E
	movq	-32(%rbp), %rax
	movl	$0, 780(%rax)
	movq	-32(%rbp), %rax
	movl	780(%rax), %edx
	movq	-32(%rbp), %rax
	movl	%edx, 520(%rax)
	movq	-32(%rbp), %rax
	movl	520(%rax), %edx
	movq	-32(%rbp), %rax
	movl	%edx, 260(%rax)
	movq	-32(%rbp), %rax
	movl	260(%rax), %edx
	movq	-32(%rbp), %rax
	movl	%edx, (%rax)
	movl	$_Z6writewP10threaddata, %edx
	movq	-32(%rbp), %rcx
	leaq	-64(%rbp), %rdi
	movl	$0, %esi
	call	pthread_create
	movl	$_Z6writexP10threaddata, %edx
	movq	-32(%rbp), %rcx
	leaq	-64(%rbp), %rax
	leaq	8(%rax), %rdi
	movl	$0, %esi
	call	pthread_create
	movl	$_Z6writeyP10threaddata, %edx
	movq	-32(%rbp), %rcx
	leaq	-64(%rbp), %rax
	leaq	16(%rax), %rdi
	movl	$0, %esi
	call	pthread_create
	movl	$_Z6writezP10threaddata, %edx
	movq	-32(%rbp), %rcx
	leaq	-64(%rbp), %rax
	leaq	24(%rax), %rdi
	movl	$0, %esi
	call	pthread_create
	movl	$0, -20(%rbp)
	jmp	.L23
.L24:
	movl	-20(%rbp), %eax
	cltq
	movq	-64(%rbp,%rax,8), %rdi
	movl	$0, %esi
	call	pthread_join
	addl	$1, -20(%rbp)
.L23:
	cmpl	$3, -20(%rbp)
	jle	.L24
	movl	$0, %eax
	addq	$56, %rsp
	popq	%rbx
	leave
	ret
.LFE956:
	.size	main, .-main
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
	.long	.LFB952
	.long	.LFE952-.LFB952
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI0-.LFB952
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
	.long	.LFB953
	.long	.LFE953-.LFB953
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI2-.LFB953
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
	.long	.LFB954
	.long	.LFE954-.LFB954
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI4-.LFB954
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI5-.LCFI4
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE5:
.LSFDE7:
	.long	.LEFDE7-.LASFDE7
.LASFDE7:
	.long	.LASFDE7-.Lframe1
	.long	.LFB955
	.long	.LFE955-.LFB955
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI6-.LFB955
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI7-.LCFI6
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE7:
.LSFDE9:
	.long	.LEFDE9-.LASFDE9
.LASFDE9:
	.long	.LASFDE9-.Lframe1
	.long	.LFB966
	.long	.LFE966-.LFB966
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI8-.LFB966
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI9-.LCFI8
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE9:
.LSFDE11:
	.long	.LEFDE11-.LASFDE11
.LASFDE11:
	.long	.LASFDE11-.Lframe1
	.long	.LFB967
	.long	.LFE967-.LFB967
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI11-.LFB967
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI12-.LCFI11
	.byte	0xd
	.uleb128 0x6
	.align 8
.LEFDE11:
.LSFDE13:
	.long	.LEFDE13-.LASFDE13
.LASFDE13:
	.long	.LASFDE13-.Lframe1
	.long	.LFB956
	.long	.LFE956-.LFB956
	.uleb128 0x0
	.byte	0x4
	.long	.LCFI13-.LFB956
	.byte	0xe
	.uleb128 0x10
	.byte	0x86
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI14-.LCFI13
	.byte	0xd
	.uleb128 0x6
	.byte	0x4
	.long	.LCFI16-.LCFI14
	.byte	0x83
	.uleb128 0x3
	.align 8
.LEFDE13:
	.ident	"GCC: (Ubuntu 4.3.3-5ubuntu4) 4.3.3"
	.section	.note.GNU-stack,"",@progbits
