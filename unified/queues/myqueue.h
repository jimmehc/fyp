#ifndef MYQUEUE
#define MYQUEUE

//taken from http://msmvps.com/blogs/vandooren/archive/2007/01/05/creating-a-thread-safe-producer-consumer-queue-in-c-without-using-locks.aspx

template <class T>
class myqueue
{
	public:
	volatile int m_Write;
	static const int Size = 10;
	volatile T m_Data[Size];
	bool popElement(T * Element);
	bool pushElement(T * Element);
	volatile int padding[64];
	volatile int m_Read;
};

template <class T>
bool myqueue<T>::popElement(T * Element)
{
        if(m_Read == m_Write)
                return false;

        int nextElement = (m_Read + 1) % Size;
        *Element = m_Data[m_Read];
        m_Read = nextElement;
	asm volatile ("mfence");
        return true;
}

template <class T>
bool myqueue<T>::pushElement(T * Element)
{
        int nextElement = (m_Write + 1) % Size;
        if(nextElement != m_Read)
        {
                m_Data[m_Write] = *Element;
                m_Write = nextElement;
		asm volatile ("mfence");
                return true;
        }
        else
                return false;
}

#endif
