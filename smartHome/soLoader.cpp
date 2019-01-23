#include "soLoader.h"
#include "sensorBase.h"
#include "controllerBase.h"
#include <utility>
#include <dlfcn.h>
#include <iostream>
#include "stdio.h"
#include <stdio.h>
#include <stdlib.h>

std::pair<destroy_Device, create_Device> SoLoader::LoadSoFile(std::string fileName)
{
	std::cout << "\nwill load " << fileName.c_str() << std::endl;
	void *handle = dlopen(fileName.c_str(), RTLD_LAZY);
	if (!handle) 
	{
		fprintf(stderr, "error loading so[%s] %s\n", fileName.c_str(), dlerror());
		exit(EXIT_FAILURE);
	}

	
	create_Device create = (create_Device) dlsym(handle, "create_device");	
	if(create == NULL)
	{
		printf("null error in function create");
	}
	
	destroy_Device destroy = (void (*)(IDevice*))dlsym(handle, "destroy_device");
	
	if(destroy == NULL)
	{
		printf("null error in function destroy");
	}
	
	return std::make_pair (destroy,create);
}
