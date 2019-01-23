#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "semaphoreQueue.h"
#include "mutex.h"
#include "runnable.h"
#include <queue>

template <typename T>
class WaitableQueue : public Runnable 
{
public:
	void push (const T& val);
	void pop(T& val);
	const T& Front() const;
	bool IsEmpty() const;
	size_t Size() const; 
	virtual void run();
	
private:
	Semaphore m_sem;
	Mutex m_mut;
	std::queue<T> m_queue;
};

#include "queue.hpp"

#endif
