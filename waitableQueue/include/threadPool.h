#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include <vector>
#include <iterator>
#include <memory>
#include "uncopy.h"
#include "thread.h"
#include "queue.h"
#include "runnable.h"
#include "mutex.h"
#include "sharedMem.h"


class ThreadPool : public Runnable, private UnCopyable
{
public:
	explicit ThreadPool(int n);
	
	~ThreadPool(); // i will do std::terminate if shutdown hasnt been called already
	
	//submit work function will be responsible to submit an object function to the queue so a thread will be
	//able to run it. it will happen by using push function!!! need to check if the flag of shutdown is up.
	//arguments: runnable object function
	void SubmitWork(Runnable* runnable);
	
	
	//the shutdown function will be responsible to kill all existing threads. turn on the flag, make sure all the running threads are finish and only then- shutdown - this is shutdown gracefull
	
	//hard shutdown - returnning vector of all  the tasks that did not  run yet!!! not to implement yet - only think about it!!! vector<thread*> HardShutdown(timeOut)
	void GracefulShutdown();
	
	//the grow function will be responsible to grow num of threads when needed
	void Grow(int numToGrow);
	
	//the shrink function will be responsible to shrink num of threads when needed, get thread out of the vector of threads , need to notice that the thread is not in the middle of a task, and of course to kill the thread we took out
	void Shrink(int numToShrink);
	
	virtual void run();
	
	int RaiseTaskFlag(int index);
	
	size_t GetVectorSize();

	
private:
	int m_numOfThreads; 
	int m_shutdownFlag;
	int m_shrinkFlg;
	int m_minNumOfThreads;
	Mutex m_mut;
	std::vector<shared_ptr<Thread> > m_vec;
	std::vector<shared_ptr<Thread> > m_vecToKill;
	WaitableQueue<Runnable*> m_queue;
	
};


#endif
