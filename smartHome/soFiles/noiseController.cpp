#include "eventstorage.h"
#include "controllerBase.h"
#include "stdio.h"
#include "event.h"
#include "iregister.h"
#include "sharedMem.h"
#include "deviceMembers.h"
#include <iostream>
#include <unistd.h>

class Event;
class NoiseController : public ControllerBase
{ 
public:
	NoiseController(DeviceMembers& deviceMem)
	:
	ControllerBase(deviceMem)
	,
	m_event(0)
	{		
	}
	
	void GetEvent(shared_ptr<Event> event)
	{
		__sync_add_and_fetch (&m_event, 1);
		std::cout << m_event << "oriiiiiiiiiiiii" << std::endl;
	}
	
	int GetMEvent()
	{
		return m_event;
	}
private:
	int m_event;
};

extern "C" ControllerBase* create_device(DeviceMembers& deviceMem)
{
  return new NoiseController(deviceMem);
}

extern "C" void destroy_device( ControllerBase* object )
{
  delete object;
}
