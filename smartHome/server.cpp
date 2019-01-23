#include "server.h"
#include "event.h"


Server::Server(int n)
:
m_eventStorage(new EventStorage)
,m_pubManager(m_eventStorage->GetEventPoper() ,GetSubscriptionManager()->GetIHandleRegistration())
,m_numOfIterations(n)
{
	m_thread = NULL;
}

Server::~Server()
{
	if (m_eventStorage != NULL)
	{
		delete m_eventStorage;
	}	
}


void Server::Shutdown()
{	
	m_pubManager.ShutdownFlg();	

	Event::E_EventType type = Event::SHUTDOWN;
	shared_ptr<Event> emptyEvent(new Event(type));
	m_eventStorage->GetEventPusher()->PushEvent(emptyEvent);
}


void Server::Start()	
{
	m_config.GetDeviceMembers();
	m_config.CreateDevice();
	
	m_thread = new Thread(m_pubManager);	
	for (size_t i = 0; i < (m_config.GetDeviceVec()).size(); ++i)
	{
		(m_config.GetDeviceVec())[i]->start();	
	}

}

void Server::Finish()
{
	m_thread->join();
	delete m_thread;
}
