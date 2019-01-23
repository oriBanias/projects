#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 500
#endif

#include "cdr.h"
#include "aggregator.h"
#include "HashMap.h"
#include "dssO.h"
#include "query.h"
#include "common.h"

#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/stat.h> 

#define UI_TO_MANAGER 1
#define MANAGER_TO_UI_REPORT 2
#define MANAGER_TO_UI_QUERY 3


/*static functions declarations*/
static int InitUIProtocol(const char* _pathname, int _proj_id);
static HashMap* InitManagerHashMap(void);
static int HandleUIRequest(int msgid, HashMap* subHash);
static int HandleReport(int msgid, HashMap* subHash);
static int HandleQuery(int msgid, HashMap* subHash, char* _msisdn);

static int InitUIProtocol(const char* _pathname, int _proj_id)
{
	int msgid = 0;
	key_t key;
	
	if (_pathname != NULL)
	{
		if ((key = ftok(_pathname, _proj_id)) == -1) 
		{
			perror("ftok");
			return -1;
		}
		msgid = msgget(key, 0666 | IPC_CREAT);
	}
	return msgid;	
}

static HashMap* InitManagerHashMap(void)
{
	/* hash params */
	HashMap* subHash = NULL;
	const size_t hashCapacity = 2;
	const double hashLoadFactor = 0.75;
	subHash = HashMap_Create(hashCapacity, HashFunc, EqualFunc, hashLoadFactor);
	return subHash;	
}

static int HandleUIRequest(int msgid, HashMap* subHash)
{
	int status = 0;
	Msg recieveMsg = {0};
	if (subHash == NULL)
	{
		perror(" NULL pointer refrence");
		return errno;
	}
	
	if (msgrcv(msgid, &recieveMsg, g_msgTextLength, UI_TO_MANAGER , 0) == -1) 
	{
		perror("mmmmmmsgrcv");
		return errno;
	}
	
	if(strcmp(recieveMsg.m_text, "report") == 0) /* report */
	{
		status = HandleReport(msgid, subHash);
	}
	else /* query */
	{
		status = HandleQuery(msgid, subHash, recieveMsg.m_text);
	}
	return status;
}

static int HandleReport(int msgid, HashMap* subHash)
{
	Msg sendMsg = {0};
	FILE* fp = NULL;
	const char* inProgressStatus = "working on report";
	const char* finishStatus = "work is done";
	const char* reportPath = "../reportFiles/report.txt";
	
	if (subHash == NULL)
	{
		perror(" NULL pointer refrence");
		return errno;
	}
	sendMsg.m_type = MANAGER_TO_UI_REPORT;
	strcpy(sendMsg.m_text, inProgressStatus);
	
	if (msgsnd(msgid, &sendMsg, g_msgTextLength, 0) == -1)
	{
		perror("msgsend failed");
		return errno;
	}
	
	fp = fopen(reportPath, "r+");
	if (fp != NULL)
	{
		CreateReport(subHash, ActionFunc, fp);
		fclose(fp);
		
		strcpy(sendMsg.m_text, finishStatus);
		if (msgsnd(msgid, &sendMsg, g_msgTextLength, 0) == -1)
		{
			perror("msgsend failed");
			return errno;
		}
	}
	else
	{
		perror("report file open failed");
		return errno;
	}
	return 0;
}

static int HandleQuery(int msgid, HashMap* subHash, char* _msisdn)
{
	Msg sendMsg = {0};
	Subscriber* sub = NULL;
	const char* inProgressStatus = "working on query";
	
	if (subHash == NULL)
	{
		perror(" NULL pointer refrence");
		return errno;
	}
	sendMsg.m_type = MANAGER_TO_UI_QUERY;
	strcpy(sendMsg.m_text, inProgressStatus);
	
	if (msgsnd(msgid, &sendMsg, g_msgTextLength, 0) == -1)
	{
		perror("msgsend failed");
		return errno;
	}
	sub = (Subscriber*)RetrieveSubscriptor(_msisdn, subHash);
	if(sub == NULL)
	{
		strcpy(sendMsg.m_text, "ERROR!!!");
		if (msgsnd(msgid, &sendMsg, g_msgTextLength, 0) == -1)
		{
			perror("msgsend failed");
			return errno;
		}
	}
	else
	{
		PrintSubscriber(sub);
		memcpy(sendMsg.m_text, sub, SubscriberSize());
		
		if (msgsnd(msgid, &sendMsg, g_msgTextLength, 0) == -1)
		{
			perror("msgsend failed");
			return errno;
		}
	}
	return 0;
} 

int main()
{ 
	int status = 0;
	int msgid = 0; 
	HashMap* subHash = NULL;		  /* Hash */
	pthread_t* threadArr = NULL; 	  /* Aggergator */
	const char* uiPath = "../ui.txt"; /* UI */
	const int uiProjId = 'Q';		  /* UI */
	
	subHash = InitManagerHashMap();
	if (subHash  == NULL)
	{
		perror("hashMap create failure");
		return -1;
	}
	threadArr = Start_Aggergator(THREAD_NUM, subHash); /*aggregaor*/
	if (threadArr == NULL)
	{
		perror("start aggergator failure");
		return -1;
	}
	msgid = InitUIProtocol(uiPath, uiProjId);

	while(1)
	{	
		status = HandleUIRequest(msgid, subHash);
		if (status != 0) /*in case of failure*/
		{
			break;
		}
	}
	Aggregator_Stop(threadArr, THREAD_NUM);
	HashMap_Destroy(&subHash, NULL, NULL);
	return status;

}
