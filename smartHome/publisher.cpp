#include "publisher.h"
#include "event.h"
#include "subscriber.h"
#include "eventstorage.h"
#include "controllerBase.h"
#include "server.h"
#include "simpleDispatcher.h"
#include "sharedMem.h"
#include <vector>

PublisherManager::PublisherManager(IEventPoper* ptrInterface, IHandleRegistration* ptrRegInterface)
:
m_eventPoperInterface(ptrInterface)
,m_handleRegInterface(ptrRegInterface)
,m_shutdownFlag(1)
{
	m_dispatch = new SimpleDispatcher;
}

PublisherManager::~PublisherManager()
{
	delete m_dispatch;
}

void PublisherManager::run()
{	
	while(m_flag.isUp()) 
	{
		shared_ptr<Event> newEvent;	
		m_eventPoperInterface->PopEvent(newEvent); 
		if (newEvent)
		{
		
			Event::E_EventType eventType = newEvent->GetEventType() ;
			if(eventType == Event::SHUTDOWN){
				//std::cout << " pub got event: " << eventType << std::endl;
				continue;				
			}
			//std::cout << " pub got event: " << eventType << std::endl;			
			std::cout << "whats up baby goomi " << newEvent->GetEventType() << std::endl;
			if (m_handleRegInterface != NULL)
			{
				
				std::vector<ControllerBase*> registerControllers =
							 m_handleRegInterface->GetRegisterControllers(eventType);  				
				
				m_dispatch->Dispatch(newEvent, registerControllers); 
			}		
		}
		
		else
		{
			std::cout << "got null shared ptr\n";
		}
	}
}				

