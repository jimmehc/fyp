#define NUM_THREADS 8 

#define DOM_ACCESSES 100000000

#if NNPNNN
#define NON_DOM_ACCESSES 1000/(NUM_THREADS - 1)
#elif NNPNN
#define NON_DOM_ACCESSES 10000/(NUM_THREADS - 1)
#elif NNPN
#define NON_DOM_ACCESSES 100000/(NUM_THREADS - 1)
#elif NN
#define NON_DOM_ACCESSES 1000000/(NUM_THREADS -1)
#elif NF
#define NON_DOM_ACCESSES 5263100/(NUM_THREADS - 1)
#elif N
#define NON_DOM_ACCESSES 10000000/(NUM_THREADS - 1)
/*
#elif EF
#define NON_DOM_ACCESSES 58823529
#elif E
#define NON_DOM_ACCESSES 83333333
#elif SF
#define NON_DOM_ACCESSES 111111111 
#elif S
#define NON_DOM_ACCESSES 142857142 
#elif SI
#define NON_DOM_ACCESSES 222222222
#elif F
#define NON_DOM_ACCESSES 333333333 */
#else
#define NON_DOM_ACCESSES 0
#endif
