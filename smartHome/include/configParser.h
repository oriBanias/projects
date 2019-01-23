#ifndef __CONFIGPARSER_H__
#define __CONFIGPARSER_H__

#include <cstring>
#include <cstdio>
#include <iostream>
#include "IParser.h"
#include "uncopy.h"
//#include "deviceFactory.h"
#include <string>
#include <vector>
//#include "deviceManager.h"

class ConfigParser : public IParser, private UnCopyable
{
public:
	ConfigParser();
	~ConfigParser();

	virtual void Parsing(std::vector<DeviceMembers>& vec);
	void UpdateMembers(char* token, const char* delim, DeviceMembers* device);
	
private:
    
	std::string m_pathName;	
    DeviceMembers m_deviceMem;	
};

#endif
