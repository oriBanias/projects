#ifndef __THREAD_H__
#define __THREAD_H__

#include "runnable.h"
#include "uncopy.h"
#include <pthread.h>

class Thread : private UnCopyable
{
public:
	explicit Thread(Runnable& runnable);
	~Thread();
	int join();
	inline pthread_t GetPthreadT();
private:
	pthread_t m_thread;
	bool m_joinFlag;
	static void* Routine(void* arg);
};

pthread_t Thread::GetPthreadT()
{
	return m_thread;
}
/*
void MakeThreads(Runnable& r, int n, std::vector<Thread*>& bunchOfThreads)//TODO
{
	std::vector<bunchOfThreads>
	while(n--)
	{
		bunchOfThreads.push_back(Threads(r));
	}
}

void joinAll(std::vector<Thread*>& threads)//TODO
{
	for(int i = 0; i<threads.size(); ++i)
	{
		threads[i].join();
	}
}

void delAll(std::vector<Thread*>& threads) //TODO
{
	for(int i = 0; i<threads.size(); ++i)
	{
		threads[i].join();
	}
}
*/
#endif
