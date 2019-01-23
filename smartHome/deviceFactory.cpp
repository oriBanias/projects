#include "deviceFactory.h"

DeviceFactory::DeviceFactory(ICreator* creator)
:
m_creator(creator)
{

}

DeviceFactory::~DeviceFactory()
{

}

IDevice* DeviceFactory::DeviceCreate(DeviceMembers& deviceMem)
{
	create_Device newPtr = m_creator->GetDeviceCreatePtr(deviceMem);
	IDevice* newDevice =  newPtr(deviceMem);
	return newDevice;

}
