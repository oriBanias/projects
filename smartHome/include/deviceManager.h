#ifndef __DEVICEMANAGER_H__
#define __DEVICEMANAGER_H__

#include <vector>
#include "IDevice.h"
class DeviceManager
{
public:
	DeviceManager(std::vector<IDevice*>& vector);
	void DestroyDevices();
	void PushDevices();

private:
	std::vector<IDevice*> m_vec;
};

#endif

