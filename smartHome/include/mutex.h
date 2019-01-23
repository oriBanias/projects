#ifndef __MUTEX_H__
#define __MUTEX_H__
#include <iostream>
#include <stddef.h>
#include <pthread.h>
#include "uncopy.h"
#include "FancyException.h"

class Mutex : private UnCopyable
{
public:
	Mutex(); 
	~Mutex();
	
	void MutexLock(); 
	void MutexUnLock();
       	
private:
	pthread_mutex_t m_mutex;
};

#endif

		
