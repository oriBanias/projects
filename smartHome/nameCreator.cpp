#include "nameCreator.h"
#include <iostream>
#include <string>

std::string& NameCreator::CreateName(std::string& type)
{
	std::cout  << "name tx: " << type << std::endl;
	std::string path = "./";
	path += type;
	path += ".so";
	type = path;
	std::cout  << "name tx: " << path << std::endl;
	return type;
}
