#include "deviceManager.h"
#include "deviceCreator.h"

DeviceManager::DeviceManager(std::vector<IDevice*>& vector)
:
m_vec(vector)
{

}

void DeviceManager::DestroyDevices()
{
	std::vector<IDevice*>::iterator it = m_vec.begin();
	
	while (it != m_vec.end())
	{
		destroy_Device(*it);
		++it;
	}
}
