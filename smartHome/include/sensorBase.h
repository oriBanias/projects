#ifndef __SENSORBASE_H__
#define __SENSORBASE_H__

#include "runnable.h"
#include "eventstorage.h"
#include "thread.h"
#include "IDevice.h"

class SensorBase : public Runnable, public EventStorage, public IDevice
{
public:
	explicit SensorBase(DeviceMembers& deviceMem);
	virtual ~SensorBase();
	bool Init();
	IEventPusher* GetEventPusherPtr();
	void start();
	void Finish();	
	virtual void run() = 0;
private:
	IEventPusher* m_eventPusher;
	Thread* m_thread;
};

inline IEventPusher* SensorBase::GetEventPusherPtr()
{
	return m_eventPusher;
}

#endif
