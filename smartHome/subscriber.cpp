#include "subscriber.h"
#include <iostream>
#include <cstddef>

SubscriberManager::~SubscriberManager()
{   
	
}

IRegister* SubscriberManager::GetIRegister()
{
	return this;
}

IHandleRegistration* SubscriberManager::GetIHandleRegistration()
{
	return this;
}
	
void SubscriberManager::Subscribe(Event::E_EventType eventType, ControllerBase* ctl)
{
	std::vector<ControllerBase*>& v =  m_controllerMap[eventType];
	v.push_back(ctl);
}   

std::vector<ControllerBase*> SubscriberManager::GetRegisterControllers(Event::E_EventType eventType)
{
	return m_controllerMap[eventType];
}
