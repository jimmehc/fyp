#include <iostream>
#include <fstream>

#include <map>

#include "packet.h"

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

	
	if(argc > 1)
	{
		std::map <int, Fragment **> * f = new std::map<int, Fragment **>();
		std::ifstream input(argv[1]);
	
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
			//		std::cout << *p->contents << std::endl;
				}
			}
		}
		else 
		{
			std::cout << "error" << std::endl;
		}
	}
	
}
