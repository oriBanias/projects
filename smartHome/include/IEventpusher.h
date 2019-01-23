#ifndef __IEVENTPUSHER_H__
#define __IEVENTPUSHER_H__

#include "event.h"
#include "sharedMem.h"

class IEventPusher
{
public:
	
	virtual void PushEvent(shared_ptr<Event>& event) = 0;
	virtual ~IEventPusher();
};

#endif
