#ifndef SPINLOCK
#define SPINLOCK

namespace spinlock
{
	void lockN (boost::uint32_t * lck);
	void unlockN (boost::uint32_t * lck);
}
#endif
