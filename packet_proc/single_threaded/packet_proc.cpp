#include <iostream>
#include <fstream>
#include <sstream>

#include <map>

#include "packet.h"

#define NUM_THREADS 4
#define LINES 1000000
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
		std::string lines[LINES];
		std::map <int, Fragment **> * f = new std::map<int, Fragment **>();
		std::ifstream input(argv[1]);
	
		if(input.is_open())	
		{
			for (int j = 0; j < LINES; j++)
 			{
				getline(input, lines[j]);
			}

			//start timing here
			for (int j = 0; j < LINES; j++)
			{
				std::stringstream ss;
				ss.clear();
				ss.str(lines[j]);

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
