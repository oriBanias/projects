#ifndef __DEVICECREATOR_H__
#define __DEVICECREATOR_H__

#include <utility>
#include <map>
#include "ICreator.h"
#include "IDevice.h"
//#include "ILoader.h"
#include "nameCreator.h"

class ILoader;
class ICreator;

 
class DeviceCreator : public ICreator
{
public:
	DeviceCreator();
	create_Device GetDeviceCreatePtr(DeviceMembers& deviceMem);
	bool CheckIfDeviceExist(std::string type, std::map< std::string, std::pair<destroy_Device, create_Device> >::iterator& it);
	std::string GetNameToLookUp(std::string type);
	
	
private:
	std::map< std::string, std::pair<destroy_Device, create_Device> > m_map;
	ILoader* m_loader;
	NameCreator m_nameCreator;
};


#endif
