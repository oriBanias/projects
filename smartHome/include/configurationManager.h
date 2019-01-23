#ifndef __CONFIGURATIONMANAGER_H__
#define __CONFIGURATIONMANAGER_H__

#include <vector>
#include "IParser.h"
#include "ICreator.h"
#include "deviceMembers.h"
#include "uncopy.h"
#include "IDevice.h"
#include "deviceManager.h"
#include "deviceFactory.h"


class ConfigManager : private UnCopyable
{
public:
	ConfigManager();
	~ConfigManager();
	void GetDeviceMembers();
	void CreateDevice();
	std::vector<IDevice*> GetDeviceVec();

private:
std::vector<DeviceMembers> m_vecDeviceMem;
std::vector<IDevice*> m_vecDevice;
ICreator* m_creator; 
DeviceFactory m_factory;
DeviceManager m_manager; 
IParser* m_parser;
};

inline std::vector<IDevice*> ConfigManager::GetDeviceVec()
{
	return m_vecDevice;
}

#endif
