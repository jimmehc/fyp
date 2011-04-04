#ifndef MCS
#define MCS
#define CAS __sync_bool_compare_and_swap


typedef struct _qnode
{
	struct _qnode * next;
	bool locked;
} qnode;

inline void acquire_lock(qnode ** L, qnode * I)
{
	I->next = NULL;
	qnode * predecessor = __sync_lock_test_and_set(L, I); //same as atomic fetch and store??

	if (predecessor != NULL)
	{
		I->locked = true;
		predecessor->next = I;
		while(I->locked) { asm volatile("pause"); }
	}
}

inline void release_lock (qnode ** L, qnode * I)
{
	if(I->next == NULL)
	{
		if(CAS(L, I, NULL))
			return;

		while(I->next == NULL) {asm volatile ("pause");}
	}
	I->next->locked = false;
}
#endif
