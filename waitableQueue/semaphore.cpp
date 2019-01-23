#include "semaphoreQueue.h"
#include "exceptions.h"
#include <assert.h>
#include <cstdio>
#include <cerrno>

Semaphore::Semaphore()
{
	int check = sem_init(&m_sem, 0, 0);
	
	if (check)
	{
		throw SemaphoreException(strerror(errno), __FILE__, __LINE__);
	} 
}

Semaphore::~Semaphore()
{
	if(sem_destroy(&m_sem))
	{
		std::perror("sem_destroy function error");
	}
}

void Semaphore::SemaphoreIncrement()
{
	int check = sem_post(&m_sem);
	
	if (check)
	{
		throw SemaphoreException(strerror(errno), __FILE__, __LINE__);
	}
}

void Semaphore::SemaphoreDecrement()
{
	int check = sem_wait(&m_sem);
	
	if (check)
	{
		throw SemaphoreException(strerror(errno), __FILE__, __LINE__);
	}
}
