#include "controllerBase.h"
#include "server.h"


ControllerBase::ControllerBase(DeviceMembers& deviceMem)
:
IDevice(deviceMem)
{
	m_registerInterfacePtr = GetIRegister();
}

ControllerBase::~ControllerBase()
{

}

void ControllerBase::start()
{
	ControllerBase::Init(Event::NOISE_LEVEL);
}
bool ControllerBase::Init(Event::E_EventType eventType)
{
	bool initOk = false;
	if (m_registerInterfacePtr != NULL)
	{
		std::cout << "fuckkkkkkYouBeach" << std::endl;
		m_registerInterfacePtr->Subscribe(eventType, this);
		initOk = true;
	}
	return initOk;
}


