#include "controllerBase.h"
//#include "configParser.h"
#include "eventstorage.h"
#include "sensorBase.h"
#include "server.h"
#include "mu_test.h"
#include "stdio.h"
#include "thread.h"
#include "configurationManager.h"
#include "deviceMembers.h"
#include <dlfcn.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


/*

//class ControllerBase; 
class NoiseController : public ControllerBase
{ 
public:
	NoiseController(IRegister* pr)
	: ControllerBase(pr)
	,m_event(0)
	{		
	}

	void GetEvent(shared_ptr<Event> event)
	{
	//	std::cout<< event->GetEventType() <<" has been recieved"<<std::endl;
		__sync_add_and_fetch (&m_event, 1);
	}
	
	int GetMEvent()
	{
		return m_event;
	}
private:
	int m_event;
};


class NoiseLevelSensor : public SensorBase
{
private:
	Event::E_EventType eventType;
public:
	NoiseLevelSensor(IEventPusher* pusherPtr, Event::E_EventType et)
	:
	SensorBase(pusherPtr)
	,eventType(et)
	{	
		
	}

	void run()
	{
		int n = 10;
		while(n--){
			shared_ptr<Event> p(new Event(eventType));
	//		std::cout << "sending " << n << " " << eventType << '\n';
			GetEventPusherPtr()->PushEvent(p); 
		}
	}
};

UNIT(test_simple_server_setup)

    Server srv(10);
	NoiseController ctl(srv.GetSubscriptionManager()->GetIRegister());
	ctl.Init(Event::NOISE_LEVEL);

	NoiseLevelSensor sensor(srv.GetEventStorage()->GetEventPusher(), Event::NOISE_LEVEL); 	

	
	sensor.Start();	
	srv.Start();
	sleep(1);
	sensor.Finish();

	srv.Shutdown();

	srv.Finish();
	
	ASSERT_THAT(ctl.GetMEvent() == 10);	
END_UNIT

UNIT(test_simple_server_2Sensors)

    Server srv(10);
	NoiseController ctl(srv.GetSubscriptionManager()->GetIRegister());
	ctl.Init(Event::NOISE_LEVEL);

	NoiseLevelSensor sensor1(srv.GetEventStorage()->GetEventPusher(), Event::NOISE_LEVEL); 	
	NoiseLevelSensor sensor2(srv.GetEventStorage()->GetEventPusher(), Event::NOISE_LEVEL); 	

	
	sensor1.Start();	
	sensor2.Start();	
	
	srv.Start();
	sleep(1);
	sensor1.Finish();	
	sensor2.Finish();

	srv.Shutdown();

	srv.Finish();
	
	ASSERT_THAT(ctl.GetMEvent() == 20);
	
END_UNIT

UNIT(test_simple_server_2Sensors_halfEvents)

    Server srv(10);
	NoiseController ctl(srv.GetSubscriptionManager()->GetIRegister());
	ctl.Init(Event::NOISE_LEVEL);

	NoiseLevelSensor sensor1(srv.GetEventStorage()->GetEventPusher(), Event::NOISE_LEVEL); 	
	NoiseLevelSensor sensor2(srv.GetEventStorage()->GetEventPusher(), Event::ENTRANCE_REQUEST); 	

	
	sensor1.Start();	
	sensor2.Start();	
	
	srv.Start();
	sleep(1);
	
	sensor1.Finish();	
	sensor2.Finish();

	srv.Shutdown();

	srv.Finish();
	
	ASSERT_THAT(ctl.GetMEvent() == 10);
	
END_UNIT

UNIT(test_with_two_events)

    Server srv(10);
	NoiseController ctl1(srv.GetSubscriptionManager()->GetIRegister());
	ctl1.Init(Event::NOISE_LEVEL);
	
	NoiseController ctl2(srv.GetSubscriptionManager()->GetIRegister());
	ctl2.Init(Event::ENTRANCE_REQUEST);
	
	NoiseLevelSensor sensor1(srv.GetEventStorage()->GetEventPusher(), Event::NOISE_LEVEL); 	
	NoiseLevelSensor sensor2(srv.GetEventStorage()->GetEventPusher(), Event::ENTRANCE_REQUEST); 
	
	sensor1.Start();	
	sensor2.Start();
	
	srv.Start();
	
	
	sleep(1);
	sensor1.Finish();	
	sensor2.Finish();
	
	srv.Shutdown();
	srv.Finish();
	
	ASSERT_THAT(ctl1.GetMEvent() == 10);
	ASSERT_THAT(ctl2.GetMEvent() == 10);
	
	
END_UNIT

UNIT(test_with_so_files)
	
	Server srv(10);
   //SENSOR
	void *handleSensor = NULL;

	handleSensor = dlopen("./libnoiseSensor.so", RTLD_LAZY);
	if (!handleSensor) 
	{
		fprintf(stderr, "%s\n", dlerror());
		exit(EXIT_FAILURE);
	}

	SensorBase* (*createSensor)(IEventPusher* pusherPtr, Event::E_EventType type);
	void (*destroySensor)(SensorBase*);

	createSensor = (SensorBase* (*)(IEventPusher*, Event::E_EventType))dlsym(handleSensor, "create_sensor");
	
	if(createSensor == NULL)
	{
		printf("null error in function create");
	}
	
	destroySensor = (void (*)(SensorBase*))dlsym(handleSensor, "destroy_sensor");
	
	if(destroySensor == NULL)
	{
		printf("null error in function destroy");
	}

	SensorBase* mySensor = (SensorBase*)createSensor(srv.GetEventStorage()->GetEventPusher(), Event::NOISE_LEVEL);
	
	
	//CONTROLLER
	void *handleController = NULL;

	handleController = dlopen("./libnoiseController.so", RTLD_LAZY);
	if (!handleController) 
	{
		fprintf(stderr, "%s\n", dlerror());
		exit(EXIT_FAILURE);
	}

	ControllerBase* (*createController)(IRegister* pr);
	void (*destroyController)(ControllerBase*);

	createController = (ControllerBase* (*)(IRegister*))dlsym(handleController, "create_controller");
	
	if(createController == NULL)
	{
		printf("null error in function create");
	}
	
	destroyController = (void (*)(ControllerBase*))dlsym(handleController, "destroy_controller");
	
	if(destroyController == NULL)
	{
		printf("null error in function destroy");
	}

	ControllerBase* myController = (ControllerBase*)createController(srv.GetSubscriptionManager()->GetIRegister());	
	myController->Init(Event::NOISE_LEVEL);	

	mySensor->Start();

	srv.Start();
	sleep(4);
	
	mySensor->Finish();

	srv.Shutdown();
	srv.Finish();

	ASSERT_THAT(myController->GetMEvent() == 1000);	
	
	destroyController(myController);
	destroySensor( mySensor );
END_UNIT

UNIT(test_with_so_fileswith_two_events)

	Server srv(10);
	
	//CONTROLLER1
	void *handleController1 = NULL;

	handleController1 = dlopen("./libnoiseController.so", RTLD_LAZY);
	if (!handleController1) 
	{
		fprintf(stderr, "%s\n", dlerror());
		exit(EXIT_FAILURE);
	}

	ControllerBase* (*createController)(IRegister* pr);
	void (*destroyController)(ControllerBase*);

	createController = (ControllerBase* (*)(IRegister*))dlsym(handleController1, "create_controller");
	
	if(createController == NULL)
	{
		printf("null error in function create");
	}
	
	destroyController = (void (*)(ControllerBase*))dlsym(handleController1, "destroy_controller");
	
	if(destroyController == NULL)
	{
		printf("null error in function destroy");
	}

	ControllerBase* myController1 = (ControllerBase*)createController(srv.GetSubscriptionManager()->GetIRegister());
	
	//CONTROLLER2
	void *handleController2 = NULL;

	handleController2 = dlopen("./libnoiseController.so", RTLD_LAZY);
	if (!handleController2) 
	{
		fprintf(stderr, "%s\n", dlerror());
		exit(EXIT_FAILURE);
	}

	ControllerBase* (*createController2)(IRegister* pr);
	void (*destroyController2)(ControllerBase*);

	createController2 = (ControllerBase* (*)(IRegister*))dlsym(handleController2, "create_controller");
	
	if(createController2 == NULL)
	{
		printf("null error in function create");
	}
	
	destroyController2 = (void (*)(ControllerBase*))dlsym(handleController2, "destroy_controller");
	
	if(destroyController2 == NULL)
	{
		printf("null error in function destroy");
	}

	ControllerBase* myController2 = (ControllerBase*)createController2(srv.GetSubscriptionManager()->GetIRegister());
	
	
	
   //SENSOR1
	void *handleSensor1 = NULL;

	handleSensor1 = dlopen("./libnoiseSensor.so", RTLD_LAZY);
	if (!handleSensor1) 
	{
		fprintf(stderr, "%s\n", dlerror());
		exit(EXIT_FAILURE);
	}

	SensorBase* (*createSensor)(IEventPusher* pusherPtr, Event::E_EventType type);
	void (*destroySensor)(SensorBase*);

	createSensor = (SensorBase* (*)(IEventPusher*, Event::E_EventType))dlsym(handleSensor1, "create_sensor");
	
	if(createSensor == NULL)
	{
		printf("null error in function create");
	}
	
	destroySensor = (void (*)(SensorBase*))dlsym(handleSensor1, "destroy_sensor");
	
	if(destroySensor == NULL)
	{
		printf("null error in function destroy");
	}

	SensorBase* mySensor1 = (SensorBase*)createSensor(srv.GetEventStorage()->GetEventPusher(), Event::NOISE_LEVEL);
	

	//SENSOR2
	void *handleSensor2 = NULL;

	handleSensor2 = dlopen("./libnoiseSensor.so", RTLD_LAZY);
	if (!handleSensor2) 
	{
		fprintf(stderr, "%s\n", dlerror());
		exit(EXIT_FAILURE);
	}

	SensorBase* (*createSensor2)(IEventPusher* pusherPtr, Event::E_EventType type);
	void (*destroySensor2)(SensorBase*);

	createSensor2 = (SensorBase* (*)(IEventPusher*, Event::E_EventType))dlsym(handleSensor2, "create_sensor");
	
	if(createSensor2 == NULL)
	{
		printf("null error in function create");
	}
	
	destroySensor2 = (void (*)(SensorBase*))dlsym(handleSensor2, "destroy_sensor");
	
	if(destroySensor2 == NULL)
	{
		printf("null error in function destroy");
	}

	SensorBase* mySensor2 = (SensorBase*)createSensor2(srv.GetEventStorage()->GetEventPusher(), Event::ENTRANCE_REQUEST);
	
	
	
	myController1->Init(Event::NOISE_LEVEL);
	myController2->Init(Event::ENTRANCE_REQUEST);
	
	mySensor1->Start();
	mySensor2->Start();
	
	srv.Start();
	
	sleep(1);
	
	mySensor1->Finish();
	mySensor2->Finish();

	srv.Shutdown();
	srv.Finish();
	
	ASSERT_THAT(myController1->GetMEvent() == 1000);
	ASSERT_THAT(myController2->GetMEvent() == 1000);
	
	destroyController(myController1);
	destroyController(myController2);
	destroySensor( mySensor1 );
	destroySensor( mySensor2 );
		
END_UNIT*/

/*UNIT(test_parsing)

    ConfigParser pars;
    int check = pars.ParsingConfiguration();	
    ASSERT_THAT(check == 0);
END_UNIT*/



UNIT(first_test)

    ConfigManager manager;
    manager.GetDeviceMembers();
    manager.CreateDevice();	
    std::vector<IDevice*> vec = manager.GetDeviceVec();
    ASSERT_THAT(vec.size() == 2);
  	ASSERT_THAT(vec[0]->m_config == "sensor");
   // std::cout << vec[0]->m_deviceId << std::endl;
    ASSERT_THAT(vec[0]->m_deviceId == "room-1-a-noise-sensor");
    ASSERT_THAT(vec[1]->m_deviceId == "room-1-a-noise-controller");
END_UNIT

UNIT(final_test)
	
	Server srv(10);
	srv.Start();
	sleep(1);
	srv.Shutdown();
	srv.Finish();
	
    
END_UNIT


TEST_SUITE(SmartHub_test)

	IGNORE_TEST(first_test)
	TEST(final_test)
	IGNORE_TEST(test_simple_server_setup)
	IGNORE_TEST(test_simple_server_2Sensors)
	IGNORE_TEST(test_simple_server_2Sensors_halfEvents)
	IGNORE_TEST(test_with_two_events)
	IGNORE_TEST(test_with_so_files)
	IGNORE_TEST(test_with_so_fileswith_two_events)
	IGNORE_TEST(test_parsing)	
	
END_SUITE

