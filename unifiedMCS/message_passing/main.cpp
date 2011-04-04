#include "../../lib/myqueue.h"
#include <iostream>

int main()
{
	myqueue<int> * m = new myqueue<int>;

	int y = 8;

	m->pushElement(y);

	int x;
	
	m->popElement(x);

	std::cout << x << std::endl;
}
