#ifndef __IDISPATCHER_H__
#define __IDISPATCHER_H__

#include "controllerBase.h"
#include "sharedMem.h"
#include <vector>

class IDispatcher
{
public:
	virtual void Dispatch(shared_ptr<Event> newEvent, std::vector<ControllerBase*>& vec) = 0;
	virtual ~IDispatcher();
};

#endif
