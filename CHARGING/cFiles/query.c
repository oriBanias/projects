#include "HashMap.h"
#include "dssO.h"
#include <stdio.h>

void* RetrieveSubscriptor(char* _msisdn, HashMap* _map)
{
	Map_Result res;
	Subscriber* newSub = NULL;
	
	if (_msisdn == NULL || _map == NULL)
	{
		return NULL;
	}
	
	res = HashMap_Find(_map, _msisdn, (void**)&newSub);
	
	if (res != MAP_SUCCESS)
	{
		
		printf("not found map: %lu\n", HashMap_Size(_map));
		return NULL;
	}
	
	return newSub;
	
}

void CreateReport(HashMap* _map, KeyValueActionFunction _action, void* _context) 
{
	size_t counter = 0;
	
	if (_map == NULL)
	{
		return;
	}
	
	counter = HashMap_ForEach(_map, _action, _context);
	
	if (counter != HashMap_Size(_map))
	{
		printf("report error\n");
	}
	
}
