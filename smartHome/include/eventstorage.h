#ifndef __EVENTSTORAGE_H__
#define __EVENTSTORAGE_H__

#include "queue.h"
#include "event.h"
#include "IEventpoper.h"
#include "IEventpusher.h"
#include "sharedMem.h"
#include <string>



class EventStorage : public IEventPoper, public IEventPusher
{
public:
	IEventPusher* GetEventPusher();
	IEventPoper* GetEventPoper();
	
private:
	WaitableQueue<shared_ptr<Event> > m_eventQueue;
	void PopEvent(shared_ptr<Event>& event);
	void PushEvent(shared_ptr<Event>& event);
	
};


	
#endif
