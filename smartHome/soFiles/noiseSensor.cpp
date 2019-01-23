#include "sensorBase.h"
#include "IEventpusher.h"
#include "server.h"
#include "stdio.h"
#include "event.h"
#include "deviceMembers.h"
#include <iostream>
#include <unistd.h>


class NoiseLevelSensor : public SensorBase
{
private:
	Event::E_EventType eventType;
public:
	NoiseLevelSensor(DeviceMembers& deviceMem)
	:
	SensorBase(deviceMem)
	,
	eventType(Event::NOISE_LEVEL)
	{	
		
	}

	virtual void run()
	{
		int n = 10;
		while(n--){
			shared_ptr<Event> p(new Event(eventType));
			GetEventPusherPtr()->PushEvent(p);
			std::cout << "hi guy" << std::endl; 
		}
	}
};	

extern "C" IDevice* create_device(DeviceMembers& deviceMem)
{    
	IDevice* p = new NoiseLevelSensor(deviceMem); 
    return p; 
}

extern "C" void destroy_device( IDevice* object )
{
	delete object;
}

