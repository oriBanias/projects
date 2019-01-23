#include "configParser.h"
#include <string>


#define SIZE 2048

ConfigParser::ConfigParser()
:
m_pathName("./configurator.ini")
{
	
}

ConfigParser::~ConfigParser()
{

}

void ConfigParser::UpdateMembers(char* token, const char* delim, DeviceMembers* device)
{
	if (strcmp(token,"type") == 0)
	{
		device->m_type = strtok(NULL, "\n");
        
	}
	if (strcmp(token,"room") == 0)
	{
		device->m_room = strtok(NULL, "\n");
	}
	if (strcmp(token,"floor") == 0)
	{
		device->m_floor = strtok(NULL, "\n");
	}
	if (strcmp(token,"config") == 0)
	{
		device->m_config = strtok(NULL, "\n");
		
	}
}

void ConfigParser::Parsing(std::vector<DeviceMembers>& vec)
{

	// read
	// if []
    //   id
	//   read field
	//   while field != []
	//   add to vector []+fileds
	//   g
	
	char str[255];
	const char delim[2] = {'='};
	char* token;
	FILE* fp; 
	int counter = 0;
	
	fp = fopen(m_pathName.c_str(), "r+");

	if(fp == NULL)
	{
		perror("File Opening Error!!");
		return;
	}
	
	while (fgets(str, SIZE, fp) != NULL) 	
	{
			++counter;
			if (str[0] == '[')
			{
				strtok(str, "]");
				m_deviceMem.m_deviceId = str+1;
				continue;
			}
				
			token = strtok(str, delim);
			
			ConfigParser::UpdateMembers(token, delim, &m_deviceMem);
			
			if (counter % 5 == 0)
			{
				vec.push_back(m_deviceMem);					
			}
	}
	
	fclose(fp);		
}
