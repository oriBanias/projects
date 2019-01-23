#include "threadPool.h"
#include "emptyApple.h"
#include "lockGuard.h"
 #include <stdio.h>
 #include <pthread.h>
#include <exception>
#include <sys/sysinfo.h>
#include <algorithm>


ThreadPool::ThreadPool(int n)
	:
	m_numOfThreads(n)
	,m_shrinkFlg(0)
	,m_minNumOfThreads(2)	
{
	__sync_lock_test_and_set(&m_shutdownFlag, 0);
	Grow(m_numOfThreads);
}

ThreadPool::~ThreadPool()
{
	if (__sync_add_and_fetch (&m_shutdownFlag, 0) == 0)
	{		
		std::terminate();		
	}	
}


EmptyApple g_emptyApple;

void ThreadPool::GracefulShutdown()
{
	std::cout << "Shutdown" << std::endl;
	__sync_lock_test_and_set(&m_shutdownFlag, 1);
	
	size_t size =  m_vec.size();
	
	for(size_t i = 0 ; i < size; ++i)
	{		
		m_queue.push(&g_emptyApple);
	}		
	
}

void ThreadPool::SubmitWork(Runnable* runnable)
{
	m_queue.push(runnable); 
}

void ThreadPool::Grow(int numToGrow) 
{
	for (int i = 0; i < numToGrow; ++i)
	{
		m_vec.push_back (shared_ptr<Thread>(new Thread(*this)));  
	}
}

size_t ThreadPool::GetVectorSize()
{
	LockGuard guard(m_mut);
	return m_vec.size();
}


void ThreadPool::Shrink(int numToShrink) 
{
	LockGuard guard(m_mut);
	
	for(int i = 0 ; i < numToShrink; ++i)
	{		
		m_queue.push(&g_emptyApple);
	}
		
	
	if ((static_cast<int>(m_vec.size()) - numToShrink) < m_minNumOfThreads)
	{
		__sync_add_and_fetch (&m_shrinkFlg, (m_vec.size() - m_minNumOfThreads));
	}
	else
	{
		__sync_add_and_fetch (&m_shrinkFlg, numToShrink);
	}
}

bool CheckPthreadT(shared_ptr<Thread> thread)
{
	return thread->GetPthreadT() == pthread_self();
}

void ThreadPool::run() 
{
	pthread_detach(pthread_self());
	while (!(__sync_add_and_fetch (&m_shutdownFlag, 0)))
	{
		Runnable* t = 0;
		m_queue.pop(t);
		t->run();
		
		{
			
			if ((__sync_add_and_fetch (&m_shrinkFlg, 0)) > 0)
			{		
				LockGuard guard(m_mut);				

				std::cout << "x" ;
				std::vector<shared_ptr<Thread> >::iterator it = std::find_if (m_vec.begin(), m_vec.end(), CheckPthreadT);
				m_vec.erase (it);
				__sync_sub_and_fetch (&m_shrinkFlg, 1);
				std::cout << "b" << std::endl;
				
				size_t size = m_vecToKill.size();
				for (size_t i = 0; i < size; ++i)
				{
					m_vecToKill.push_back (*it);
				}
				break;
			}
		}
	} 

}

