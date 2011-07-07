#ifndef ALGS
#define ALGS

#include <iostream>
#include "volatile_functions.h"
#include "biased_sync.h"
#include "myspinlock.h"
#include "../constants.h"
#define atstart() 

template <typename T>
struct shared_data;

template <typename T>
struct func_struct;
template <typename T>
struct msg_struct;

#if defined SPL
template <typename T>
struct Lock{
	int owner;
	volatile int * n;
	Lock();
};	

template <typename T>
Lock<T>::Lock(){
	owner = -1;
	n = new int(0);
}

template <typename T>
void poll(shared_data<T> * sd, void * params){
}
template <typename T>
void push_work(void (*work)(shared_data<T> *, void *), shared_data<T> * sd, void * params, int threadid, shared_data<T> * mysd){
	spinlock::lockN(sd->l.n);
	work (sd, params);
	spinlock::unlockN(sd->l.n);
}

#endif



#if defined(FP) || defined(AFP)
template <typename T>
struct Lock{
	int owner;
	volatile int * n;
	void (*func)(shared_data<T> *, void *);
	void * params;
	Lock();
};	

template <typename T>
Lock<T>::Lock(){
	owner = 0;
	n = new int(0);
	func = NULL;
	params = NULL;
	params = malloc(10*sizeof(void*));
}

template <typename T>
void poll(shared_data<T> * sd, void * params){
	if(sd->l.func != NULL) 	
	{	
		sd->l.func (sd,sd->l.params );
		sd->l.func = NULL;
		fence();
	}
}
#endif

#if defined(FP)
template <typename T>
void push_work(void (*work)(shared_data<T> *, void *), shared_data<T> * sd, void * params, int threadid, shared_data<T> * mysd = NULL){
	spinlock::lockN(sd->l.n);
	sd->l.params = params;
	fence();
	sd->l.func = work;
	while (sd->l.func != NULL){ 
		pause(); 
#ifdef MULTIPLE 
		poll(mysd, NULL); 
#endif
	}
	restorepr();
	spinlock::unlockN(sd->l.n);
}
#endif

#if defined(AFP)
template <typename T>
void push_work(void (*work)(shared_data<T> *, void *), shared_data<T> * sd, void * params, int threadid, shared_data<T> * mysd = NULL){
	spinlock::lockN(sd->l.n);
	while (sd->l.func != NULL){ 
	pause(); 
#ifdef MULTIPLE 
		poll(mysd, NULL); 
#endif
	}
	restorepr();
	sd->l.params = params;
	fence();
	sd->l.func = work;
	spinlock::unlockN (sd->l.n);
}
#endif

#ifdef ISPL
#define CAS __sync_bool_compare_and_swap

template <typename T>
struct Lock{
	int owner;
	volatile int * n;
	func_struct<T> * fs;
	Lock();
};	

template <typename T>
Lock<T>::Lock(){
	owner = 0;
	n = new int(0);
	fs = NULL;
}

template <typename T>
void push_work(void (*work)(shared_data<T> *, void *), shared_data<T> * sd, void * params, int threadid, shared_data<T> * mysd = NULL){
	static func_struct<T> fss[NUM_THREADS];
	fss[threadid].func = work;
	fss[threadid].params = params;

	int success = 0;
	success = CAS(&sd->l.fs, NULL, &fss[threadid]);
	while(!success)	
	{
		for (int i = 0; i < 400; i++) {
#ifdef MULTIPLE
			poll(mysd, NULL); 
#endif
			pause();
		} 
		restorepr(); 
		success = CAS(&sd->l.fs, NULL,&fss[threadid]);
	}
}

template <typename T>
void poll(shared_data<T> * sd, void * params){
	if(sd->l.fs != NULL) 	
	{	
		sd->l.fs->func (sd,sd->l.fs->params );
		sd->l.fs = NULL;
		fence();
	}
}

#endif

#ifdef FPQ
	
#include "myqueue.h"

template <typename T>
struct Lock{
	int owner;
	volatile int * n;
	myqueue< func_struct<T> > * q;
	Lock();
};	

template <typename T>
Lock<T>::Lock(){
	owner = 0;
	n = new int(0);
	q = new myqueue< func_struct<T> >;
	q->m_Read = q->m_Write = 0;
}

template <typename T>
void poll(shared_data<T> * sd, void * params){
	func_struct<T> fs;
	while(sd->l.q->popElement(&fs))
		fs.func (sd,fs.params );
}
 
template <typename T>
void push_work(void (*work)(shared_data<T> *, void *), shared_data<T> * sd, void * params, int threadid, shared_data<T> * mysd = NULL){
	spinlock::lockN(sd->l.n);
	func_struct<T> fs;
	fs.func = work;
	fs.params = params;
	while(!sd->l.q->pushElement(&fs)) {
#ifdef MULTIPLE	
		poll(mysd, NULL);
#endif
		pause();
	} restorepr(); 
	spinlock::unlockN(sd->l.n);
}

#endif

#ifdef VAS
template <typename T>
struct Lock{
	int owner;
	volatile int * n;
	bool request;
	bool grant;
	Lock();
};	

template <typename T>
Lock<T>::Lock(){
	owner = 0;
	n = new int(0);
	request = false;
	grant = false;
}

#undef atstart
#define atstart() while(sd->l.grant){pause();} restorepr(); 

template <typename T>
void poll(shared_data<T> * sd, void * params)
{
	if(sd->l.request) 
	{	
		sd->l.request = false; 
		fence();
		sd->l.grant = true;
	}
}
template <typename T>
void push_work(void (*work)(shared_data<T> *, void *), shared_data<T> * sd, void * params, int threadid, shared_data<T> *mysd = NULL){
	spinlock::lockN(sd->l.n); 
	sd->l.request = true; 
	while(!sd->l.grant){ 
#ifdef MULTIPLE
		poll(mysd, NULL);
#endif
		pause(); 
	}
	restorepr();
	work(sd, params);
	fence(); 
	sd->l.grant = false; 
	spinlock::unlockN(sd->l.n);
}

#endif

#ifdef BQ

#include "myqueue.h"

template <typename T>
struct Lock{
	int owner;
	volatile int * n;
	void * params;
	bool done[NUM_THREADS];
	myqueue< func_struct<T> > * q;
	Lock();
};	

template <typename T>
Lock<T>::Lock(){
	owner = 0;
	n = new int(0);
	q = new myqueue< func_struct<T> >;
	q->m_Read = q->m_Write = 0;
	params = malloc(10*sizeof(void*));
	for(int i = 0;i < NUM_THREADS; i++) done[i] = true;
}

template <typename T>
void poll(shared_data<T> * sd, void * params){
	func_struct<T> fs;
	while(sd->l.q->popElement(&fs))
	{
		fs.func (sd,sd->l.params );
		sd->l.done[fs.creatorid] = true;
	}	
}

template <typename T>
void push_work(void (*work)(shared_data<T> *, void *), shared_data<T> * sd, void * params, int threadid, shared_data<T> * mysd = NULL){
	spinlock::lockN(sd->l.n);
	func_struct<T> fs;
	fs.func = work;
	fs.params = params;
	fs.creatorid = threadid;
	sd->l.done[threadid] = false;
	fence();
	while(!sd->l.q->pushElement(&fs)) {
#ifdef MULTIPLE
		poll(mysd, NULL); 
#endif
		pause();
	} restorepr();
	spinlock::unlockN(sd->l.n);
	while(!sd->l.done[threadid]) { 
#ifdef MULTIPLE
		poll(mysd, NULL); 
#endif
		pause(); 
	}
	restorepr();
}

#endif

#endif

#if defined(MP) || defined(AMP)
template <typename T>
struct Lock{
	int owner;
	volatile int * n;
	int token;
	void * params;
	Lock();
};	

template <typename T>
Lock<T>::Lock(){
	owner = 0;
	n = new int(0);
	token = 0;
	params = NULL;
	params = malloc(10*sizeof(void*));
}

template <typename T>
void poll(shared_data<T> * sd, void * params){
	if(sd->l.token != 0) 	
	{	
		message_handler(sd->l.token, sd, sd->l.params);
		sd->l.token = 0;
		fence();
	}
}
#endif

#if defined(MP)
template <typename T>
void push_work(int msg, shared_data<T> * sd, void * params, int threadid, shared_data<T> * mysd = NULL){
	spinlock::lockN(sd->l.n);
	sd->l.params = params;
	fence();
	sd->l.token = msg;
	while (sd->l.token != 0){ 
		pause(); 
#ifdef MULTIPLE 
		poll(mysd, NULL); 
#endif
	}
	restorepr();
	spinlock::unlockN(sd->l.n);
}
#endif

#if defined(AMP)
template <typename T>
void push_work(int msg, shared_data<T> * sd, void * params, int threadid, shared_data<T> * mysd = NULL){
	spinlock::lockN(sd->l.n);
	while (sd->l.token != 0){ 
	pause(); 
#ifdef MULTIPLE 
		poll(mysd, NULL); 
#endif
	}
	restorepr();
	sd->l.params = params;
	fence();
	sd->l.token = msg;
	spinlock::unlockN (sd->l.n);
}
#endif

#ifdef MPQ
	
#include "myqueue.h"

template <typename T>
struct Lock{
	int owner;
	volatile int * n;
	myqueue<msg_struct<T> > * q;
	Lock();
};	

template <typename T>
Lock<T>::Lock(){
	owner = 0;
	n = new int(0);
	q = new myqueue< msg_struct<T> >;
	q->m_Read = q->m_Write = 0;
}

template <typename T>
void poll(shared_data<T> * sd, void * params){
	msg_struct<T> ms;
	while(sd->l.q->popElement(&ms))
		message_handler(ms.msg, sd, ms.params );
}
 
template <typename T>
void push_work(int msg, shared_data<T> * sd, void * params, int threadid, shared_data<T> * mysd = NULL){
	spinlock::lockN(sd->l.n);
	msg_struct<T> ms;
	ms.msg = msg;
	ms.params = params;
	while(!sd->l.q->pushElement(&ms)) {
#ifdef MULTIPLE
		poll(mysd, NULL);
#endif
		pause();
	} 
	restorepr(); 
	spinlock::unlockN(sd->l.n);
}

#endif
#ifdef ISPLMP
#define CAS __sync_bool_compare_and_swap

template <typename T>
struct Lock{
	int owner;
	volatile int * n;
	msg_struct<T> * ms;
	Lock();
};	

template <typename T>
Lock<T>::Lock(){
	owner = 0;
	n = new int(0);
	ms = 0;
}

template <typename T>
void push_work(int msg, shared_data<T> * sd, void * params, int threadid, shared_data<T> * mysd = NULL){
	static msg_struct<T> mss[NUM_THREADS];

	mss[threadid].msg = msg;
	mss[threadid].params = params;

	int success = 0;
	success = CAS(&sd->l.ms, NULL, &mss[threadid]);
	while(!success)	
	{
		for (int i = 0; i < 400; i++) {
#ifdef MULTIPLE
			poll(mysd, NULL); 
#endif
			pause();
		} restorepr(); 
		success = CAS(&sd->l.ms, NULL, &mss[threadid]);
	}
}

template <typename T>
void poll(shared_data<T> * sd, void * params){
	if(sd->l.ms != NULL) 	
	{	
		message_handler(sd->l.ms->msg, sd, sd->l.ms->params);
		sd->l.ms = NULL;
		fence();
	}
}

#endif

