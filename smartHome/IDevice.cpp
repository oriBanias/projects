#include "IDevice.h"

IDevice::IDevice(DeviceMembers& deviceMem)
:
m_deviceId(deviceMem.m_deviceId)
,
m_type(deviceMem.m_type)
,
m_room(deviceMem.m_room)
,
m_floor(deviceMem.m_floor)
,
m_config(deviceMem.m_config)
{

}

IDevice::~IDevice()
{

}
