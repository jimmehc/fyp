#define vol_inc(x) asm volatile ("addl $1,%0":"=r"(x):"0"(x));
#define fence() asm volatile ("sync")
#define pause() asm volatile ("or 31,31,31")
#define restorepr() asm volatile ("or 2,2,2");
