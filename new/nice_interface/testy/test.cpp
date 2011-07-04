#include <iostream>
#include "../lib/volatile_functions.h"
#include <stdlib.h>

template <typename T>
struct func_struct
{
	void * a;
	void * b;
};

int main()
{
	typedef int really_long __attribute__ ((mode (TI)));

	void * a = malloc(1);
	void * b = malloc(1);

	std::cout << a << " " << b << std::endl;

	func_struct<int> fs;
	fs.a = a;
	fs.b = b;

	really_long d = (really_long) a;
	d >>= 64;	
	d += (really_long) b;	

//	std::cout << d << std::endl;
}
