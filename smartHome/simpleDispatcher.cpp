#include "simpleDispatcher.h"
#include <cstddef>
#include <iostream>

IDispatcher* SimpleDispatcher::GetDispatcher()
{
	return	this;
}

void SimpleDispatcher::Dispatch(shared_ptr<Event> newEvent, std::vector<ControllerBase*>& vec)
{
	for (std::vector<ControllerBase*>::iterator it = vec.begin(); it != vec.end(); 
		++it)                               
	{
 	 	ControllerBase* ctl = *it;
 	 	if (ctl != NULL)
 	 	{
 	 		ctl->GetEvent(newEvent);
 	 	}
 	 	
	}
	
}
