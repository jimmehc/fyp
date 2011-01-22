#include <pthread.h>
#include <boost/interprocess/detail/atomic.hpp>
#include <unistd.h>
#include "spinlock.h"

void spinlock::lockN (boost::uint32_t * lck)
{
	int success = 0;
	do
	{
		while (*lck != 0);
		success = !(boost::interprocess::detail::atomic_cas32(lck, 1, 0));
	}while(!success);
}

void spinlock::unlockN (boost::uint32_t * lck)
{
	*lck = 0;
}

