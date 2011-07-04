#define vol_inc(x) asm volatile ("addi %1,%1,1":"=r"(x):"r"(x));
#define fence() asm volatile ("sync")
#define pause() asm volatile ("or 31,31,31")
#define restorepr() asm volatile ("or 2,2,2");
