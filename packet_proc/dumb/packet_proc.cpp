#include <iostream>

#define NUM_THREADS 4
int main()
{
	//allocate mem for NUM_THREADS-1 ring queues for packets(how big?)
	//allocate mem for NUM_THREADS-1 reassembly data structs for packets
	//start NUM_THREADS-1 threads, pass addrs for above to them

	//begin reading packet file
	//populate packet struct with data
	//do hash
	//put in appropriate queue
	//repeat until file is fully read
}
