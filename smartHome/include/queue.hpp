#include "queue.h"
#include "exceptions.h"
#include "lockGuard.h"
#include <exception>
#include <deque>
#include <queue>

template <typename T>
void WaitableQueue<T>::push (const T& val) 
{
	LockGuard guard(m_mut);
	
	try
	{
		m_queue.push(val);
	}
	catch(std::exception& ba)
	{
		throw;
	}
		
	try
	{	
		m_sem.SemaphoreIncrement();	
	}
	catch(SemaphoreException& x)
	{
		throw;
	}

}

template <typename T>
void WaitableQueue<T>::pop (T& val)
{
	
	try
	{
		m_sem.SemaphoreDecrement();
	}	
	catch(SemaphoreException& x)
	{
		throw;
	}
	
	LockGuard guard(m_mut);
	
	val = Front();
	try
	{
		m_queue.pop();
	}
	catch(std::exception& ba)
	{
		throw;
	}
	
}

template <typename T>
void WaitableQueue<T>::run()
{
	std::cout<<"ori is smart"<<std::endl;
}

template <typename T>
const T& WaitableQueue<T>::Front() const
{
	return m_queue.front();
}

template <typename T>
bool WaitableQueue<T>::IsEmpty() const
{
	return m_queue.empty();
}

template <typename T>
size_t WaitableQueue<T>::Size() const
{
	return m_queue.size();
}



