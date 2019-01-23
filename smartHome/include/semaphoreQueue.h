#ifndef __SEMAPHOREQUEUE_H__
#define __SEMAPHOREQUEUE_H__

#include <semaphore.h>
#include "uncopy.h"

class Semaphore : private UnCopyable
{
public:
	Semaphore();
	~Semaphore();
	
	void SemaphoreIncrement();
	void SemaphoreDecrement();
       	
private:
	sem_t m_sem; 	
};

#endif
