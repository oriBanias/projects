
#include "aggregator.h"
#include "cdr.h"
#include "common.h"
#include "HashMap.h"
#include "dssO.h"
#include "dssU.h"
#include "query.h"
#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define PARSER_TO_AGGREGATOR 2 /*channel sending struct to aggregator*/
#define MODE 0644
#define AGG_MEM_SIZE 13 /*number of members of struct Cdr*/


pthread_t* Start_Aggergator(size_t _threadNum, HashMap* _newHash)
{
	pthread_t* threadArr;
	size_t i, res;
	
	threadArr=(pthread_t*)calloc(_threadNum, sizeof(pthread_t));
	
	for (i=0 ; i < _threadNum ; ++i)
	{   
		sleep(1);
	    res = pthread_create(&threadArr[i], NULL, &GetCdrFile, _newHash);
        if (res != 0)
        {
            printf("\nfail to create Thread\n");
            return NULL;
		}
	}
	
	return threadArr;
}
	
void Aggregator_Stop(pthread_t* _threadArr, int _threadNum)
{
	int i = 0;
	
	while(i < _threadNum)
	{
		pthread_cancel(_threadArr[i]);
		pthread_join(_threadArr[i], NULL);
    	++i;
	}
	free(_threadArr);
}

static int InitAggregatorProtocol(const char* _pathname, int _proj_id)
{
	key_t key;
	int msqid;
	
	if (_pathname == NULL)
	{
		perror("_pathname is NULL");
		return -1;
	}
	if ((key = ftok(_pathname, _proj_id)) == -1) 
 	{
		perror("ftok");
		return -1;
	}

	if ((msqid = msgget(key,0666 | IPC_CREAT)) == -1) 
	{
		perror("msgget");
		return -1;
	}
	
	return msqid; /*success*/
}	

static int HandleReaderRequest(int _msqid, HashMap* _newHash)
{
	Cdr* newCdr = NULL;
	Msg recieveMsg = {0};
	const char* terminateMsg = "terminate";
	void* res = NULL;
	
	newCdr = CreateCdr(); 
	if (newCdr == NULL)
	{
		perror("cdr allocation failed");
		DestroyCdr(newCdr);
		return -1;
	}
	
	if(msgrcv(_msqid, &recieveMsg, g_msgTextLength, PARSER_TO_AGGREGATOR, 0) == -1)
	{
		perror("msgrcv failed");
		DestroyCdr(newCdr);
		return -1;
	}

	if (strcmp(recieveMsg.m_text, terminateMsg) == 0)
	{
		DestroyCdr(newCdr);
		return 0; /*getting out off the loop*/
	}
	
	memcpy(newCdr, (Cdr*)recieveMsg.m_text, CdrSize());
	PrintCdr(newCdr);
	res = updateSubscriber(newCdr, _newHash);
	if (res == NULL)
	{
		perror("updateSubscriber function error");
		DestroyCdr(newCdr);
		return -1;
	}
	return 1; /*success*/
}

void* GetCdrFile(void* _newHash)
{
	int msqid = 0;
	int status = 0;
	int proj_id = 'B';
	const char* cdrPath = "../cdrfiles/cdr.ini";
	
	msqid = InitAggregatorProtocol(cdrPath, proj_id);
	
	if(msqid == -1)
	{
		perror("InitAggregatorProtocol function error");
		return NULL;
	}
	
	for(;;) 
	{ 
		status = HandleReaderRequest(msqid, _newHash);
		
		if(status == 0)
		{
			perror("terminate massege recieved");
			break;
		}
		
		if(status == -1)
		{
			perror("HandleReaderRequest function error");
			break;
		}
	}
	
	return NULL;	
}



