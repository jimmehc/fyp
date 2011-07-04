	.file	"overhead_to_sequential.cpp"
	.text
	.p2align 4,,15
.globl _Z3fooP10threaddataIiE
	.type	_Z3fooP10threaddataIiE, @function
_Z3fooP10threaddataIiE:
.LFB1026:
	.cfi_startproc
	movq	8(%rdi), %rdx
	movl	$100000000, %eax
	.p2align 4,,10
	.p2align 3
.L2:
.L9999:
	movl	32(%rdx), %ecx
	addl	$1, %ecx
	subl	$1, %eax
	movl	%ecx, 32(%rdx)
	jne	.L9999
	rep
	ret
	.cfi_endproc
.LFE1026:
	.size	_Z3fooP10threaddataIiE, .-_Z3fooP10threaddataIiE
	.p2align 4,,15
.globl _Z8get_timev
	.type	_Z8get_timev, @function
_Z8get_timev:
.LFB1024:
	.cfi_startproc
	pushq	%rbx
	.cfi_def_cfa_offset 16
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
	.cfi_offset 3, -16
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE1024:
	.size	_Z8get_timev, .-_Z8get_timev
	.p2align 4,,15
.globl _Z3incPV11shared_dataIiEPv
	.type	_Z3incPV11shared_dataIiEPv, @function
_Z3incPV11shared_dataIiEPv:
.LFB1025:
	.cfi_startproc
	movl	32(%rdi), %eax
	addl	$1, %eax
	movl	%eax, 32(%rdi)
	ret
	.cfi_endproc
.LFE1025:
	.size	_Z3incPV11shared_dataIiEPv, .-_Z3incPV11shared_dataIiEPv
	.p2align 4,,15
	.type	_GLOBAL__I__Z8get_timev, @function
_GLOBAL__I__Z8get_timev:
.LFB1044:
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
.LFE1044:
	.size	_GLOBAL__I__Z8get_timev, .-_GLOBAL__I__Z8get_timev
	.section	.ctors,"aw",@progbits
	.align 8
	.quad	_GLOBAL__I__Z8get_timev
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"time: "
.LC1:
	.string	"x: "
	.text
	.p2align 4,,15
.globl main
	.type	main, @function
main:
.LFB1027:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA1027
	pushq	%r12
	.cfi_def_cfa_offset 16
	movl	$4, %edi
	pushq	%rbp
	.cfi_def_cfa_offset 24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	subq	$48, %rsp
	.cfi_def_cfa_offset 80
.LEHB0:
	.cfi_offset 3, -32
	.cfi_offset 6, -24
	.cfi_offset 12, -16
	call	_Znwm
	movl	$40, %edi
	movl	$0, (%rax)
	call	_Znwm
.LEHE0:
	movl	$4, %edi
	movl	$0, (%rax)
	movq	%rax, %rbp
.LEHB1:
	call	_Znwm
.LEHE1:
	movl	$0, (%rax)
	movl	$80, %edi
	movq	%rax, 8(%rbp)
	movq	$0, 16(%rbp)
	movq	$0, 24(%rbp)
	call	malloc
	movq	%rbp, 8(%rsp)
	movq	%rax, 24(%rbp)
	movl	$0, (%rsp)
#APP
# 7 "../../lib/timing.h" 1
	xorl %eax,%eax
cpuid
rdtsc
# 0 "" 2
#NO_APP
	salq	$32, %rdx
	leaq	40(%rsp), %rdi
	movq	%rsp, %rcx
	leaq	(%rdx,%rax), %rax
	xorl	%esi, %esi
	movl	$_Z3fooP10threaddataIiE, %edx
	movq	%rax, start(%rip)
	call	pthread_create
	movq	40(%rsp), %rdi
	xorl	%esi, %esi
.LEHB2:
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
	leaq	(%rdx,%rax), %rax
	movl	$6, %edx
	movq	%rax, 32(%rsp)
	movq	32(%rsp), %r12
	movq	start(%rip), %rbx
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	movq	%r12, %rsi
	movl	$_ZSt4cout, %edi
	subq	%rbx, %rsi
	call	_ZNSo9_M_insertIyEERSoT_
	movq	%rax, %rbx
	movq	(%rax), %rax
	movq	-24(%rax), %rax
	movq	240(%rbx,%rax), %r12
	testq	%r12, %r12
	je	.L17
	cmpb	$0, 56(%r12)
	je	.L10
	movzbl	67(%r12), %eax
.L11:
	movsbl	%al, %esi
	movq	%rbx, %rdi
	call	_ZNSo3putEc
	movq	%rax, %rdi
	call	_ZNSo5flushEv
	movl	32(%rbp), %ebx
	movl	$3, %edx
	movl	$.LC1, %esi
	movl	$_ZSt4cout, %edi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l
	movl	%ebx, %esi
	movl	$_ZSt4cout, %edi
	call	_ZNSolsEi
	movq	%rax, %rbx
	movq	(%rax), %rax
	movq	-24(%rax), %rax
	movq	240(%rbx,%rax), %rbp
	testq	%rbp, %rbp
	je	.L17
	cmpb	$0, 56(%rbp)
	je	.L13
	movzbl	67(%rbp), %eax
.L14:
	movq	%rbx, %rdi
	movsbl	%al, %esi
	call	_ZNSo3putEc
	movq	%rax, %rdi
	call	_ZNSo5flushEv
	addq	$48, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 32
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L10:
	.cfi_restore_state
	movq	%r12, %rdi
	call	_ZNKSt5ctypeIcE13_M_widen_initEv
	movq	(%r12), %rax
	movl	$10, %esi
	movq	%r12, %rdi
	call	*48(%rax)
	jmp	.L11
	.p2align 4,,10
	.p2align 3
.L13:
	movq	%rbp, %rdi
	call	_ZNKSt5ctypeIcE13_M_widen_initEv
	movq	0(%rbp), %rax
	movl	$10, %esi
	movq	%rbp, %rdi
	call	*48(%rax)
	jmp	.L14
.L17:
	call	_ZSt16__throw_bad_castv
.L16:
	movq	%rax, %rbx
	movq	%rbp, %rdi
	call	_ZdlPv
	movq	%rbx, %rdi
	call	_Unwind_Resume
.LEHE2:
	.cfi_endproc
.LFE1027:
	.size	main, .-main
.globl __gxx_personality_v0
	.section	.gcc_except_table,"a",@progbits
.LLSDA1027:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE1027-.LLSDACSB1027
.LLSDACSB1027:
	.uleb128 .LEHB0-.LFB1027
	.uleb128 .LEHE0-.LEHB0
	.uleb128 0x0
	.uleb128 0x0
	.uleb128 .LEHB1-.LFB1027
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L16-.LFB1027
	.uleb128 0x0
	.uleb128 .LEHB2-.LFB1027
	.uleb128 .LEHE2-.LEHB2
	.uleb128 0x0
	.uleb128 0x0
.LLSDACSE1027:
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
