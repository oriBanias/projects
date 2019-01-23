#include "mutex.h"
#include "exceptions.h"
#include <iostream>
#include <cstdio>
#include <cerrno>
#include <stdexcept>
#include <assert.h>
	


Mutex::Mutex()
{
	int r = pthread_mutex_init(&m_mutex, 0);
	if(r != 0)
	{
		throw MutexException(strerror(errno), __FILE__, __LINE__);
	}

}

Mutex::~Mutex()
{
	 if(pthread_mutex_destroy(&m_mutex))
	 {
	 	std::perror("pthread_destroy function error");
	 }
}

void Mutex::MutexLock()
{
	 if(pthread_mutex_lock(&m_mutex))
	 {
	 	throw MutexException(strerror(errno),__FILE__, __LINE__);
	 }
}

void Mutex::MutexUnLock()
{
	if(pthread_mutex_unlock(&m_mutex))
	{
		throw MutexException(strerror(errno),__FILE__, __LINE__);
	}
}
