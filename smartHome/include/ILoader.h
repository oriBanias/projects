#ifndef __ILOADER_H__
#define __ILOADER_H__

#include "deviceCreator.h"
#include <string>
#include <utility>

class ILoader
{
public:
	virtual std::pair<destroy_Device, create_Device> LoadSoFile(std::string fileName) = 0;
	virtual ~ILoader();
};


#endif

