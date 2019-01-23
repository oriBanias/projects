#ifndef __SERVER_H__
#define __SERVER_H__

#include "queue.h"

#include "eventstorage.h"
#include "subscriber.h"
#include "publisher.h"
#include "thread.h"
#include "sharedMem.h"
#include "configurationManager.h"



class Server
{
public:
	Server(int n = 10);
	
	virtual ~Server(); 
	EventStorage* GetEventStorage();
	SubscriberManager* GetSubscriptionManager();
	
	void Start();
	void Finish();
	void Shutdown();
	
private:
	
	SubscriberManager m_subManager;
	EventStorage* m_eventStorage;
	PublisherManager m_pubManager;
	ConfigManager m_config;
	int m_numOfIterations;
	Thread* m_thread;
};

inline EventStorage* Server::GetEventStorage()
{
	return m_eventStorage;
}

inline SubscriberManager* Server::GetSubscriptionManager()
{
	return &m_subManager;
}

#endif
