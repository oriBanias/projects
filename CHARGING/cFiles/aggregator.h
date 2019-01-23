#ifndef __AGGREGATOR_H__
#define __AGGREGATOR_H__

#include "HashMap.h"
#include <stddef.h>  /* size_t */
#include <pthread.h>

void* GetCdrFile(void* _msqid);

pthread_t* Start_Aggergator(size_t _threadNum, HashMap* _newHash);

void Aggregator_Stop(pthread_t* _threadArr, int _threadNum);

#endif /* __AGGREGATOR_H__ */
