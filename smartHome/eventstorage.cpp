#include "eventstorage.h"

void EventStorage::PopEvent(shared_ptr<Event>& event)
{	
	m_eventQueue.pop(event);
}

void EventStorage::PushEvent(shared_ptr<Event>& event)
{
	m_eventQueue.push(event);
	std::cout << "soso" << std::endl;
}

IEventPusher* EventStorage::GetEventPusher()
{
	return	this;
}

IEventPoper* EventStorage::GetEventPoper()
{
	return	this;
}

