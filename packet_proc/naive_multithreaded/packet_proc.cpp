#include <iostream>
#include <fstream>
#include <pthread.h>
#include <map>

#include "spinlock.h"

#include "packet.h"

class threaddata
{
	public:
	std::map<int, Fragment **> * f;
	std::string filename;
	int * l;
};


void foo(threaddata * td)
{
	std::cout << td->filename << std::endl;
	std::ifstream input(td->filename.c_str());

	if(input.is_open())	
	{
		while(!input.eof())
		{
			int s,d,id,fn,n;
			std::string c;
			
			s = d = id = fn = n = 0;
			
			input >> s >> d >> id >> fn >> n >> c;

		//	std::cout << s << " " << d << " " << id << " " << fn << " " << n << " " << c << std::endl;

			if(n == 0) break;	
			
			spinlock::lockN(td->l);
			if((*td->f)[id] == NULL)
			{
				(*td->f)[id] = new Fragment*[n];
				for(int i=0;i<n;i++)
					(*td->f)[id][i] = NULL;
			}
			
			(*td->f)[id][fn-1] = new Fragment(s,d,id,c,fn,n);

			bool complete = true;
			for(int i = 0; i < n; i++)
				if((*td->f)[id][i] == NULL)
					complete = false;

			if(complete)
			{
				Packet * p = new Packet((*td->f)[id]);
//				std::cout << *p->contents << std::endl;
			}
			spinlock::unlockN(td->l);
		}
	}
	else 
	{
		std::cout << "error" << std::endl;
	}
}


#define NUM_THREADS 4
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


	pthread_t threads[NUM_THREADS];
	
	std::map<int, Fragment **> * f = new std::map<int, Fragment **>;
	int * l = new int(0);
	threaddata td[NUM_THREADS];
	
	for(int i =0 ;i < NUM_THREADS; i++)
	{
		td[i].f =f;
		td[i].l = l;
	}
	td[0].filename = "pkts1";
	td[1].filename = "pkts2";
	td[2].filename = "pkts3";
	td[3].filename = "pkts4";
			
	for(int i = 0; i < NUM_THREADS; i++)	
		pthread_create(&threads[i], NULL, (void* (*)(void*)) foo, &td[i]);

	for(int i = 0; i < NUM_THREADS; i++)
		pthread_join(threads[i], NULL);	
	
}
