#ifndef __IPARSER_H__
#define __IPARSER_H__

#include <vector>
#include "deviceMembers.h"
class IParser
{
public:
	virtual void Parsing(std::vector<DeviceMembers>& vec) = 0;
	virtual ~IParser();
};

#endif
