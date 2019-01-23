#ifndef __SUBSCRIBER_H__
#define __SUBSCRIBER_H__

#include "uncopy.h"
#include "iregister.h"
#include "ihandleregistration.h"
#include "event.h"
#include <map>
#include <vector>


class ControllerBase;
class SubscriberManager : private UnCopyable, public IRegister, public IHandleRegistration
{
public:
	IRegister* GetIRegister();
	IHandleRegistration* GetIHandleRegistration();
	~SubscriberManager();
private:
	std::map< Event::E_EventType, std::vector<ControllerBase*> > m_controllerMap;
	void Subscribe(Event::E_EventType eventType, ControllerBase* ctl);
	std::vector<ControllerBase*> GetRegisterControllers(Event::E_EventType eventType);
};

#endif
