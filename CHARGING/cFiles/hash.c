#include "HashMap.h"
#include "list.h"
#include "list_itr.h" 
#include "list_functions.h" 
#include "dssO.h"
/*#include "../../PROJECTS/ZLOG/logger/logger.h" */
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <math.h>
#define TRUE 1
#define FALSE 0

struct HashMap
{
	List** keyArr;
	pthread_mutex_t* m_mutArr;
	HashFunction m_hashFunc;
	EqualityFunction m_keysEqualFunc;
	size_t m_mutexNum;
	size_t m_capacity;
};

typedef struct Pair
{
	void* m_value;
	void* m_key;
}Pair;

static void FindMutexNum(void* _key, HashMap* _map, pthread_mutex_t* _mutex)
{
	*_mutex = _map->m_mutArr[((_map->m_hashFunc(_key) % (_map->m_capacity)) % (_map->m_mutexNum))];
} 

static size_t getPrime(size_t _capacity)
{
	size_t i, j;
	if (_capacity < 4)
	{
		return _capacity;
	}
	for (i=_capacity+1 ; ; ++i)
	{	
		for (j=2 ;j<i/2 ; ++j)
		{
			if (i%j==0)
			{
				break;
			}		
		}
		if(j == i/2)
		{
			return i;
		}
	}
	
	return _capacity;
	  
}

static size_t MakeHash(const HashMap* _map, const void* _key)
{
	return (_map->m_hashFunc(_key)) % (_map->m_capacity);
}

static void PairDestroy(Pair* _pair, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value))
{
	if (_keyDestroy != NULL)
	{
		_keyDestroy(_pair->m_key);
	} 

	if (_valDestroy != NULL)
	{
		 _valDestroy(_pair->m_value); 
	}
	
	free(_pair);
}

static Pair* PairCreate(void* _key, void* _value)
{
	Pair* pair = (Pair*)malloc(sizeof(Pair));  
	
	if (pair == NULL)
	{
		free(pair);
		return NULL;
	}

	pair->m_value = _value;

	pair->m_key = _key;
	
	return pair;
}

HashMap* HashMap_Create(size_t _capacity, HashFunction _hashFunc, EqualityFunction _keysEqualFunc, double loadFactor)
{
	size_t realSize = 0;
	size_t i = 0;
	HashMap* newMap = NULL;
	size_t mutexNum = 0;
	
	if (NULL == _hashFunc || NULL == _keysEqualFunc || _capacity < 1)
	{
		return NULL;
	}

	newMap = (HashMap*)malloc(sizeof(HashMap));
	
	if (newMap == NULL)
	{
		return NULL;
	}
	
	realSize = getPrime(_capacity);

/*	LOG(T, "hash", "error hash is possible");*/

	newMap->keyArr = (List**)calloc(realSize, sizeof(List*));
	
	if (newMap->keyArr == NULL)
	{
		free(newMap);
		return NULL;
	}

	newMap->m_capacity = realSize;
	newMap->m_keysEqualFunc = _keysEqualFunc;
	newMap->m_hashFunc = _hashFunc;
	if (loadFactor > 1.0 || loadFactor <= 0.0)
	{
		mutexNum = newMap->m_capacity;
	}
	else
	{
		mutexNum = newMap->m_capacity * loadFactor;
		if (mutexNum == 0)
		{
			mutexNum = 1;
		}
	}
	newMap->m_mutexNum = mutexNum;
	newMap->m_mutArr=(pthread_mutex_t*)calloc(newMap->m_mutexNum, sizeof(pthread_mutex_t));
	if (newMap->m_mutArr == NULL)
	{
		free(newMap->keyArr);
		free(newMap);
		perror("allocate mutArr error");
		return NULL;
	}
	
	for(i=0 ; i < newMap->m_mutexNum ; ++i)
	{
		if (pthread_mutex_init(&newMap->m_mutArr[i],NULL) !=0)
		{
			free(newMap->keyArr);
			free(newMap);
			perror("mutex init error");
			return NULL;
		}
	}
	
	return newMap;	
}

void HashMap_Destroy(HashMap** _map, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value))
{
	ListItr begin;
	ListItr end;
	Pair* pair;
	size_t i;
	if (_map == NULL || *_map == NULL)
	{
		return;
	}

	
	else
	{
		for (i = 0; i < (*_map)->m_capacity; ++i)
		{
			if ((*_map)->keyArr[i] != NULL)
			{
				begin = ListItr_Begin((*_map)->keyArr[i]);

				end = ListItr_End((*_map)->keyArr[i]);

				while (!ListItr_Equals(begin, end))
				{
					pair = (Pair*)ListItr_Get(begin);  

					PairDestroy(pair, _keyDestroy, _valDestroy);
					
					begin = ListItr_Next(begin);

					ListItr_Remove(ListItr_Prev(begin));
				}
			}
		}
		
		free((*_map)->keyArr);
		
		for (i = 0; i < (*_map)->m_mutexNum; ++i)
		{
			pthread_mutex_destroy(&(*_map)->m_mutArr[i]);
		}
		free ((*_map)->m_mutArr);		
	}

	free(*_map);
	*_map = NULL;	
}

Map_Result HashMap_Insert(HashMap* _map, void* _key, void* _value)
{
	Pair* pair;
	size_t index;

	if (_map == NULL)
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	
	if(_key == NULL || _value == NULL)
	{
		return MAP_KEY_NULL_ERROR;
	}

	if (HashMap_Find(_map, _key, &_value) != MAP_KEY_NOT_FOUND_ERROR )
	{
		return MAP_KEY_DUPLICATE_ERROR;
	}
	
	index = MakeHash(_map, _key); 

	pair = PairCreate(_key, _value);	
	if (pair == NULL)
	{
		return MAP_ALLOCATION_ERROR;
	}
	
	if (List_PushHead(_map->keyArr[index], pair) != LIST_SUCCESS)
	{
		_map->keyArr[index] = List_Create();

		if (List_PushHead(_map->keyArr[index], pair) != LIST_SUCCESS)
		{
			free(pair);

			free(_map->keyArr[index]);

			pair = NULL;

			_map->keyArr[index] = NULL;

			return MAP_ALLOCATION_ERROR;
		}
	
	}
	return MAP_SUCCESS;
}

Map_Result HashMap_Rehash(HashMap *_map, size_t newCapacity)
{
	ListItr begin = NULL;
	ListItr end = NULL;
	HashMap* newMap = NULL;
	size_t index = 0;
	size_t realSize = 0;

	if (_map == NULL)
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	
	newMap = (HashMap*)malloc(sizeof(HashMap));
	
	if (newMap == NULL)
	{
		return MAP_ALLOCATION_ERROR;
	}
	
	realSize = getPrime(newCapacity);
	
	newMap->keyArr = (List**)calloc(realSize, sizeof(List*));
	
	if (newMap->keyArr == NULL)
	{
		free(newMap->keyArr);
		return MAP_ALLOCATION_ERROR;
	}
		
	newMap->m_capacity = realSize;

	newMap->m_keysEqualFunc = _map->m_keysEqualFunc;

	newMap->m_hashFunc = _map->m_hashFunc;
	
	
	while (index < _map->m_capacity)
	{
		while (_map->keyArr[index] == NULL)
		{
			++index;
		}
		if (index == _map->m_capacity)
		{
			break;
		}

		begin = ListItr_Begin(_map->keyArr[index]);

		end = ListItr_End(_map->keyArr[index]);

		newMap->keyArr[index] = ListItr_Cut(begin, end);
		
		++index;
	
	}	
	
	_map->keyArr = newMap->keyArr;
	
	free(newMap);
	newMap = NULL;
	
	return MAP_SUCCESS;
}	
	

Map_Result HashMap_Upsert(HashMap* _map, void* _key, void* _valueUpdate, UpdateValueFunction _updateValue)
{
	void* _pValue = NULL; 
	Map_Result res; /* insert, update */
	pthread_mutex_t mutex;

	if (_map == NULL)
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	
	if(_key == NULL || _valueUpdate == NULL)
	{
		return MAP_KEY_NULL_ERROR;
	}

	/*locking mutex segment*/
	FindMutexNum(_key, _map, &mutex);
	pthread_mutex_lock(&mutex);
	
	/*finding subscriber*/

	res = HashMap_Find(_map, _key, &_pValue);
	
	if (res == MAP_SUCCESS) /*update*/
	{
		_updateValue(_pValue, _valueUpdate); 
	}
	
	else /*insert*/
	{
		res = HashMap_Insert(_map, _key, _valueUpdate);
	}
	/*unlock mutex*/
	FindMutexNum(_key, _map, &mutex);
	pthread_mutex_unlock(&mutex);
		
	return res;
}

Map_Result HashMap_Remove(HashMap* _map, const void* _searchKey, void** _pKey, void** _pValue)
{
	Pair* pair;
	ListItr begin;
	ListItr end;
	size_t index;

	if(NULL == _map || NULL == _pValue || NULL == _pKey) 
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	
	if(NULL == _searchKey)
	{
		return MAP_KEY_NULL_ERROR;
	}
	
	index = MakeHash(_map, _searchKey);
	
	if(NULL == _map->keyArr[index])
	{
		return MAP_KEY_NOT_FOUND_ERROR;
	}
	
	begin = ListItr_Begin(_map->keyArr[index]);
	end =  ListItr_End(_map->keyArr[index]);

	while(!ListItr_Equals(begin, end))
	{
		pair = (Pair*)ListItr_Get(begin);
		
		if(_map->m_keysEqualFunc(pair->m_key , _searchKey))
		{
			*_pValue = pair->m_value;
			*_pKey = pair->m_key;
			
			ListItr_Remove(begin);
			return MAP_SUCCESS;
		}
		
		begin = ListItr_Next(begin);
	}
			
	return MAP_KEY_NOT_FOUND_ERROR;
}

Map_Result HashMap_Find(const HashMap* _map, const void* _searchKey, void** _pValue)
{
	size_t index = 0;
	ListItr begin;
	ListItr end;
	void* data = NULL;
	Pair* pair = NULL;

	if (_map == NULL)
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	
	if (_searchKey == NULL)
	{
		return MAP_KEY_NULL_ERROR;
	}

	index = MakeHash(_map, _searchKey);

	if(NULL == _map->keyArr[index])
	{
		return MAP_KEY_NOT_FOUND_ERROR;
	}
	
	begin = ListItr_Begin(_map->keyArr[index]);

	end = ListItr_End(_map->keyArr[index]);
	
	while (!ListItr_Equals(begin, end))
	{
		data = ListItr_Get(begin);
		pair = (Pair*)data;
		
		if(_map->m_keysEqualFunc( _searchKey, pair->m_key))
		{
			*_pValue = pair->m_value;
			return MAP_SUCCESS;
		}
		
		begin = ListItr_Next(begin);
	}

	return MAP_KEY_NOT_FOUND_ERROR;
		
}	


size_t HashMap_Size(const HashMap* _map)
{
	size_t sizeArr;
	size_t i;
	size_t counter = 0;

	if (_map == NULL)
	{
		return 0;
	}
	
	sizeArr = _map->m_capacity;
	
	for (i = 0; i < sizeArr; ++i)
	{
		 counter += List_Size(_map->keyArr[i]);
	}
	
	return counter;
}

size_t HashMap_ForEach(const HashMap* _map, KeyValueActionFunction _action, void* _context)
{
	ListItr begin = NULL;
	ListItr end = NULL;
	size_t i;
	size_t counter = 0;
	pthread_mutex_t mutex;
	Pair* pair = NULL;
	
	if (_map == NULL || _action == NULL)
	{
		return counter;
	}
	
	/*locking mutex segment*/
	pthread_mutex_init(&mutex,NULL);
	pthread_mutex_lock(&mutex);
	
	for (i = 0; i < _map->m_capacity; ++i)
	{
		if (_map->keyArr[i] != NULL)
		{
			begin = ListItr_Begin(_map->keyArr[i]);

			end = ListItr_End(_map->keyArr[i]);

			while (!ListItr_Equals(begin, end))
			{
				pair = (Pair*)ListItr_Get(begin);  
				
				_action(NULL, pair->m_value, _context);
				
				begin = ListItr_Next(begin);
				
				++counter;

			}
		}
	}
	
	/*unlock mutex*/
	
	pthread_mutex_unlock(&mutex);
	pthread_mutex_destroy(&mutex);
	
	return counter;		
	
}
