#ifndef __LOCKGUARD_H__
#define __LOCKGUARD_H__

#include "uncopy.h"

class LockGuard : private UnCopyable
{
public:
	LockGuard(Mutex& mut) : m_mutex(mut)
	{
		m_mutex.MutexLock();
	}
	
	~LockGuard()
	{
		m_mutex.MutexUnLock();
	}
	
private:
	Mutex& m_mutex;
};

#endif
