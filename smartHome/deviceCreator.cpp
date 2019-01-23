#include "deviceCreator.h"
#include "soLoader.h"

DeviceCreator::DeviceCreator()
{
	m_loader = new SoLoader; // need to delete in distructor 
}

#include <stdio.h>
create_Device DeviceCreator::GetDeviceCreatePtr(DeviceMembers& deviceMem)
{
	std::map< std::string, std::pair<destroy_Device, create_Device> >::iterator it;
	
	if (DeviceCreator::CheckIfDeviceExist(deviceMem.m_type, it))
	{
		return ((*it).second.second);
	}	
	else
	{
		//std::string so(".so");
		//std::string dir("./"); 
		//std::string t("noiseSensor");//deviceMem.m_type);
		std::string n;
		//n = dir +  t + so;		
		//printf("will try load %s\n", n.c_str());
		n = m_nameCreator.CreateName(deviceMem.m_type);
		printf("will try load %s\n", n.c_str());

		m_map[n] = m_loader->LoadSoFile(n);
		return (m_map[n].second);
	}
}

bool DeviceCreator::CheckIfDeviceExist(std::string type, std::map< std::string, std::pair<destroy_Device, create_Device> >::iterator& it)
{
    it = m_map.find(type);
    
    if (it != m_map.end())
    {
    	return true;
    }
    return false;
}

std::string DeviceCreator::GetNameToLookUp(std::string type)
{
	return m_nameCreator.CreateName(type);
}
