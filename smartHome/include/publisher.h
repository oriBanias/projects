#ifndef __PUBLISHER_H__
#define __PUBLISHER_H__

#include "IDispatcher.h"
#include "runnable.h"
#include "IEventpoper.h"
#include "subscriber.h"
#include "atomicFlag.h"


class PublisherManager : public Runnable
{
public:
	PublisherManager(IEventPoper* ptrInterface, IHandleRegistration* ptrRegInterface);
	~PublisherManager();
	void ShutdownFlg();
	
	virtual void run();

private:	
	IEventPoper* m_eventPoperInterface;	
	IHandleRegistration* m_handleRegInterface;
	int m_shutdownFlag;
	IDispatcher* m_dispatch;
	AtomicFlag m_flag;

};

inline void PublisherManager::ShutdownFlg()
{
	m_flag.down();
}
#endif
