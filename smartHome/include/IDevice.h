#ifndef __IDEVICE_H__
#define __IDEVICE_H__

#include "deviceMembers.h"
class DeviceMembers;
class IDevice
{
public:
	explicit IDevice(DeviceMembers& deviceMem);
	virtual void start() = 0;
	virtual ~IDevice();

	std::string m_deviceId;
	std::string m_type;
	std::string m_room;
	std::string m_floor;
	std::string m_config;

};

#endif
