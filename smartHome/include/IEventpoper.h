#ifndef __IEVENTPOPER_H__
#define __IEVENTPOPER_H__

#include "event.h"
#include "sharedMem.h"

class IEventPoper
{
public:
	
	virtual void PopEvent(shared_ptr<Event>& event) = 0;
	virtual ~IEventPoper();
};

#endif
