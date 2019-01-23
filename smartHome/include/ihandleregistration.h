#ifndef __IHANDLEREGISTRATION_H__
#define __IHANDLEREGISTRATION_H__

#include <vector>
#include "event.h"

class ControllerBase;
class IHandleRegistration
{
public:
	virtual std::vector<ControllerBase*> GetRegisterControllers(Event::E_EventType eventType) = 0;
	virtual ~IHandleRegistration();
};
#endif
