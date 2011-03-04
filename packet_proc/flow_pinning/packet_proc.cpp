#include <iostream>
#include <fstream>
#include <sstream>
#include <pthread.h>
#include <map>

#include "spinlock.h"
#include "myqueue.h"
#include "packet.h"

class threaddata
{
	public:
	myqueue<std::string*> * q;
};


void foo(threaddata * td)
{
	std::map<int, Fragment **> * f = new std::map<int, Fragment **>;
	std::string * str;
	std::stringstream ss;

	while(true)	
	{
		if(td->q->popElement(&str))
		{
			ss.str(*str);
			int s,d,id,fn,n;
			std::string c;
			
			s = d = id = fn = n = 0;
			
			ss >> s >> d >> id >> fn >> n >> c;

		//	std::cout << s << " " << d << " " << id << " " << fn << " " << n << " " << c << std::endl;

			if(n == 0) break;	
			
			if((*f)[id] == NULL)
			{
				(*f)[id] = new Fragment*[n];
				for(int i=0;i<n;i++)
					(*f)[id][i] = NULL;
			}
			
			(*f)[id][fn-1] = new Fragment(s,d,id,c,fn,n);

			bool complete = true;
			for(int i = 0; i < n; i++)
				if((*f)[id][i] == NULL)
					complete = false;

			if(complete)
			{
				Packet * p = new Packet((*f)[id]);
			//	std::cout << *p->contents << std::endl;
			}
		}
	}
}


#define NUM_THREADS 3 
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
			td[i].q = new myqueue<std::string*>;
				
		for(int i = 0; i < NUM_THREADS; i++)	
			pthread_create(&threads[i], NULL, (void* (*)(void*)) foo, &td[i]);

		std::ifstream input(argv[1]);
		std::string str;
		std::stringstream ss;	

		if(input.is_open())	
		{
			while(!input.eof())
 			{
				getline(input, str);
				ss.str(str);
				int s,d,id,fn,n;
				std::string c;
				
				s = d = id = fn = n = 0;
				
				ss >> s >> d >> id >> fn >> n >> c;

			//	std::cout << s << " " << d << " " << id << " " << fn << " " << n << " " << c << std::endl;

				std::string * kk = new std::string(str);
				if(n == 0)
				{
					while(!td[0].q->pushElement(&kk));
					while(!td[1].q->pushElement(&kk));
					while(!td[2].q->pushElement(&kk));
					break;	
				}
				
				if(id < 2000)
					while(!td[0].q->pushElement(&kk));
				else if(id < 4000)
					while(!td[1].q->pushElement(&kk));
				else 
					while(!td[2].q->pushElement(&kk));
			}
		}
		else 
		{
			std::cout << "error" << std::endl;
		}
	}
	std::cout << "END" << std::endl;
	
}
