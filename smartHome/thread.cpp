#include "thread.h"
#include "runnable.h"
#include "exceptions.h"
#include <exception>
#include <iostream>
#include <errno.h>
#include <cstring>
#include <stdio.h>

Thread::Thread(Runnable& runnable):
	    m_joinFlag(false)
{
	if (pthread_create(&m_thread, NULL, Routine, &runnable))
	{
		throw ThreadException(strerror(errno), __FILE__, __LINE__);
	}        
}

Thread::~Thread()
{
	if (!m_joinFlag)
	{
		try
		{
			join();		
		}
		catch(ThreadException& e)
		{
			std::cerr<<e.what()<<std::endl;
		}
		catch(const std::exception& e)
		{
			std::cerr<<e.what()<<std::endl;
		}
		catch(...)
		{
			perror("Thread exception occured");
		}
		
	}
}

int Thread::join()
{
	int check = 0;
	if (!m_joinFlag)
	{
		check = pthread_join(m_thread, NULL);			
		if (!check)
		{
			m_joinFlag = true;
		}
		else
		{
			throw ThreadException("join function has failed\n", __FILE__, __LINE__); 
		}
	}
	return check;
}

void* Thread::Routine(void* arg)
{
	Runnable* p = (Runnable*)arg;
	try
	{
		p->run();
	}
	catch(...)
	{
		perror("function routin has failed");
	}
	return 0;
}
