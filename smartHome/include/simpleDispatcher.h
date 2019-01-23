#ifndef __SIMPLEDISPATCHER_H__
#define __SIMPLEDISPATCHER_H__

#include "IDispatcher.h"
#include "controllerBase.h"
#include "sharedMem.h"
#include <vector>

class SimpleDispatcher : public IDispatcher
{
public:
	IDispatcher* GetDispatcher();
private:
	void Dispatch(shared_ptr<Event> newEvent, std::vector<ControllerBase*>& vec);
};

#endif
