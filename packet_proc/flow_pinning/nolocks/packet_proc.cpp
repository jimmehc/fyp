#include <iostream>
#include <fstream>
#include <sstream>
#include <pthread.h>
#include <map>
#include <stdlib.h>

#include "../../../../lib/spinlock.h"
#include "myqueue.h"
#include "packet.h"

/* timing code */
unsigned long long get_time()
{
 unsigned long lo,hi;
 __asm__ __volatile__("xorl %%eax,%%eax\n\
cpuid\n\
rdtsc" : "=a" (lo), "=d" (hi) : : "ebx", "ecx" );
 return ((unsigned long long)lo) + (unsigned long long)(hi<<32ULL);
}

unsigned long long start;

class threaddata
{
	public:
	myqueue<Fragment*> * q;
};


void foo(threaddata * td)
{
	std::map<int, Fragment **> * f = new std::map<int, Fragment **>;
	Fragment * frag;
	std::stringstream ss;

	while(true)	
	{
		if(td->q->popElement(&frag))
		{
			if(frag->id == 0) break;	
			
			if((*f)[frag->id] == NULL)
			{
				(*f)[frag->id] = new Fragment*[frag->numfrags];
				for(int i=0;i < frag->numfrags;i++)
					(*f)[frag->id][i] = NULL;
			}
			
			(*f)[frag->id][frag->fragnum-1] = frag;

			bool complete = true;
			for(int i = 0; i < frag->numfrags; i++)
				if((*f)[frag->id][i] == NULL)
					complete = false;

			if(complete)
			{
				Packet * p = new Packet((*f)[frag->id]);
			//	std::cout << *p->contents << std::endl;
			}
		}
	}
}


#define NUM_THREADS 3 
#define LINES 10000000 
int main(int argc, char* argv[])
{
	//allocate mem for NUM_THREADS-1 ring queues for packets(how big?)
	//allocate mem for NUM_THREADS-1 reassembly data structs for packets
	//start NUM_THREADS-1 threads, pass addrs for above to them

	//begin reading packet file
	//populate packet struct with data
	//do hash
	//put in appropriate queue
	//repeat until file is fully read
	
	if(argc > 1)
	{
		pthread_t threads[NUM_THREADS];
		
		threaddata td[NUM_THREADS];
		
		for(int i =0 ;i < NUM_THREADS; i++)
			td[i].q = new myqueue<Fragment*>;
				
		for(int i = 0; i < NUM_THREADS; i++)	
			pthread_create(&threads[i], NULL, (void* (*)(void*)) foo, &td[i]);

		std::ifstream input(argv[1]);
		std::string str;
		std::stringstream ss;	
		
		std::string ** lines =  (std::string**) malloc(sizeof(std::string*)*LINES);
	
		if(input.is_open())	
		{
		//	std::cout << "kk" << std::endl;
			start = get_time();
			while(!input.eof())
			{

				int s,d,id,fn,n;
				std::string c;
				
				s = d = id = fn = n = 0;
				
				input >> s >> d >> id >> fn >> n >> c;

				if(n == 0) break;

			//	std::cout << s << " " << d << " " << id << " " << fn << " " << n << " " << c << std::endl;

				Fragment * kk = new Fragment (s,d,id,c,fn,n);
				
				if(id < 666666)
					while(!td[0].q->pushElement(&kk));
				else if(id < 1200000)
					while(!td[1].q->pushElement(&kk));
				else 
					while(!td[2].q->pushElement(&kk));
			}
			Fragment * end = new Fragment(0,0,0,"",0,0);
			while(!td[0].q->pushElement(&end));
			while(!td[1].q->pushElement(&end));
			while(!td[2].q->pushElement(&end));
		}
		else 
		{
			std::cout << "error" << std::endl;
		}

		//std::cout << "END" << std::endl;
		for(int j = 0; j < NUM_THREADS; j++)	
			pthread_join(threads[j], NULL);
		
		unsigned long long end = get_time();
		std::cout << "TIME: " << end - start << std::endl;
		input.close();
	}
}
