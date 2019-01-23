#include "configurationManager.h"
#include "configParser.h"

ConfigManager::ConfigManager()
:
m_creator(new DeviceCreator)
,
m_factory(m_creator)
,
m_manager(m_vecDevice)
{
	m_parser = new ConfigParser;
}

ConfigManager::~ConfigManager()
{
	delete m_creator;
}

void ConfigManager::GetDeviceMembers()
{
	m_parser->Parsing(m_vecDeviceMem);
}

void ConfigManager::CreateDevice() 
{
	std::vector<DeviceMembers>::iterator it = m_vecDeviceMem.begin();
	while (it != m_vecDeviceMem.end())
	{
		m_vecDevice.push_back(m_factory.DeviceCreate(*it));
		++it;	
	}
}

