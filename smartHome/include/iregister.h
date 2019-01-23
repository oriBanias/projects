#ifndef __IREGISTER_H__
#define __IREGISTER_H__

#include "event.h"

class ControllerBase;
class IRegister
{
public:
	virtual void Subscribe(Event::E_EventType eventType, ControllerBase* ctl) = 0;
	virtual ~IRegister();
};
#endif
