int fibs(int n, threaddata * td)
{
	spinlock::lockN(&td->lock->n);
	if(n == 0)
	{
		spinlock::unlockN(&td->lock->n);
		return 0;
	}
	
	if(n == 1)
	{
		spinlock::unlockN(&td->lock->n);
		return 1;
	}

	spinlock::unlockN(&td->lock->n);
	return fibs(n-1,td) + fibs(n-2,td);
}
