#ifndef __EVENT_H__
#define __EVENT_H__

class Event
{
public:
	enum E_EventType 
	{
		NOISE_LEVEL = 0, 
		ENTRANCE_REQUEST,
		SHUTDOWN
	};
	Event();
	explicit Event(E_EventType eventType);
	E_EventType GetEventType();
	
private:
	E_EventType m_eventType;
};

inline Event::E_EventType Event::GetEventType()
{
	return m_eventType;
}

#endif

