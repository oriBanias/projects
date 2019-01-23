#ifndef __CONTROLLERBASE_H__
#define __CONTROLLERBASE_H__

#include "event.h"
#include "subscriber.h"
#include "sharedMem.h"
#include "IDevice.h"

class ControllerBase : public IDevice, public SubscriberManager
{
public:
	
	explicit ControllerBase(DeviceMembers& deviceMem);
	
	bool Init(Event::E_EventType eventType);
	void start();
	virtual void GetEvent(shared_ptr<Event> event) = 0;
	virtual int GetMEvent() = 0;
	virtual ~ControllerBase();
private:
	IRegister* m_registerInterfacePtr;
};

#endif
