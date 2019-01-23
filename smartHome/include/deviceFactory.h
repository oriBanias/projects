#ifndef __DEVICEFACTORY_H__
#define __DEVICEFACTORY_H__

#include "uncopy.h"
#include "deviceMembers.h"
#include "soLoader.h"

class DeviceFactory : private UnCopyable
{
public:
	explicit DeviceFactory(ICreator* creator);
	~DeviceFactory();
	
	IDevice* DeviceCreate(DeviceMembers& deviceMem);
	
private:
	ICreator* m_creator;	
};

#endif
