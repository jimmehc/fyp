#define vol_inc(x) asm volatile ("addl $1,%0":"=r"(x):"0"(x));
#define fence() asm volatile ("mfence")
#define pause() asm volatile ("pause")
#define restorepr()
