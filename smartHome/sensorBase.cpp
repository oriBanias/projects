#include "sensorBase.h"
#include "server.h"

SensorBase::SensorBase(DeviceMembers& deviceMem)
:
IDevice(deviceMem)
,
m_eventPusher(GetEventPusher())
,
m_thread(NULL)

{
	
}	

	
SensorBase::~SensorBase()
{
	m_eventPusher = NULL;
}
				
bool SensorBase::Init()			
{
	bool initOk = true;
	
	if (m_eventPusher == NULL)
	{
		initOk = false;
	}
	return initOk;
}

void SensorBase::start()
{
	m_thread = new Thread(*this);
}

void SensorBase::Finish()
{
	m_thread->join();
	delete m_thread;
}
