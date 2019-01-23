#ifndef __SOLOADER_H__
#define __SOLOADER_H__

#include <string>
#include "ILoader.h"
#include "deviceCreator.h"

class SoLoader : public ILoader
{
public:
	std::pair<destroy_Device, create_Device> LoadSoFile(std::string fileName);

private:

};


#endif
