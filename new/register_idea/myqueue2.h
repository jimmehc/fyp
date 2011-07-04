#ifndef MYQUEUE
#define MYQUEUE
#include <iostream>
#include "../lib/volatile_functions.h"

/*

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
	fence();
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
		fence();
                return true;
        }
        else
                return false;
}*/

template <typename T>
struct node 
{ 
    node * volatile  next; 
    T                state; 
}; 

template <typename T>
struct myqueue
{ 
    node<T> * volatile  head; 
    node<T> *           tail; 
    myqueue();
    bool popElement(T * el);
    bool pushElement(T * el);
}; 

template <typename T>
myqueue<T>::myqueue() 
{ 
    node<T> * stub = new node<T>;
    stub->next = 0; 
    head = stub; 
    tail = stub; 
} 

template <typename T>
bool myqueue<T>::pushElement(T * el) 
{ 
/*    node<T> * n = new node<T>;
    n->state = *el;
    n->next = 0; 
    std::cout << "HI" << std::endl;
    node<T> * prev = __sync_lock_test_and_set (&head, n); // serialization-point wrt producers
    fence(); 
    prev->next = n; // serialization-point wrt consumer 
    fence(); */
    return true;
} 

template <typename T>
bool myqueue<T>::popElement(T * el) 
{ 
    node<T> * next = tail->next; // serialization-point wrt producers 
    if (next) 
    { 
        tail = next; 
	*el = next->state;
	delete next;
        return true; 
    } 
    return false; 
} 

#endif
