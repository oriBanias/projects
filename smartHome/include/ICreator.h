#ifndef __ICREATOR_H__
#define __ICREATOR_H__

#include "deviceMembers.h"
#include "IDevice.h"
//#include "deviceCreator.h"


typedef void (*destroy_Device)(IDevice*);
typedef IDevice*(*create_Device)(DeviceMembers& deviceMem);

class ICreator
{
public:
	virtual create_Device GetDeviceCreatePtr(DeviceMembers& deviceMem) = 0;
	virtual ~ICreator();
};

#endif
