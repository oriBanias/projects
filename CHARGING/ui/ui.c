#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 500
#endif

/*#include "ui.h"*/
#include "dssO.h"
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

static int HandleUserRequest(void);
static int GetQuery(const char* _msisdn);
static int GetReport(void);

int HandleUserRequest(void)
{
	size_t choice = 0;
	char msisdn[20] = {0};
	int status = 0;
	
	printf("please enter your request: enter 1 for query or 2 for report:\n");
	scanf("%lu", &choice);
	
	if (choice == 1)
	{
		printf("please enter the msisdn number:\n");
		scanf("%s", msisdn);
		status = GetQuery(msisdn);
	}
	
	else if (choice == 2)
	{
		status = GetReport();
	}	
	
	else
	{
		printf("invalid choice, try again\n");
	}
	return status;
}

static int GetQuery(const char* _msisdn)
{
	key_t key; 
	int msgid = 0; 
	Msg sendMsg = {0};
	Msg recieveMsg = {0};
	
	if (_msisdn == NULL)
	{
		perror("msisdn is NULL");
		return -1;
	}
	
	if ((key = ftok("../ui.txt", 'Q')) == -1) 
	{
		perror("ftok");
		return errno;
	}
	
	msgid = msgget(key, 0666 | IPC_CREAT);

	sendMsg.m_type = UI_TO_MANAGER;
	strcpy(sendMsg.m_text, _msisdn);
	
	if (msgsnd(msgid, &sendMsg, g_msgTextLength, 0) == -1)
	{
		perror("msgsend failed");
		return errno;
	}
	
	if (msgrcv(msgid, &recieveMsg, g_msgTextLength, MANAGER_TO_UI_QUERY , 0) == -1) 
	{
		perror("msgrcv");
		return errno;
	}
	
	/*printing the string we got - "working on query" */
	printf("%s\n", recieveMsg.m_text);
	
	if (msgrcv(msgid, &recieveMsg, g_msgTextLength, MANAGER_TO_UI_QUERY , 0) == -1) 
	{
		perror("msgrcv");
		return errno;
	}
	
	/*printing the query*/
	PrintSubscriber((Subscriber*)recieveMsg.m_text);

	return 0; /*success*/
}

static int GetReport(void)
{
	key_t key; 
	int msgid = 0; 
	Msg sendMsg = {0};
	Msg recieveMsg = {0};

	if ((key = ftok("../ui.txt", 'Q')) == -1) 
	{
		perror("ftok");
		return errno;
	}
	
	msgid = msgget(key, 0666);

	sendMsg.m_type = UI_TO_MANAGER;
	strcpy(sendMsg.m_text, "report");
	
	if (msgsnd(msgid, &sendMsg, g_msgTextLength, 0) == -1)
	{
		perror("msgsend failed");
		return errno;
	}
	
	if (msgrcv(msgid, &recieveMsg, g_msgTextLength, MANAGER_TO_UI_REPORT , 0) == -1) 
	{
		perror("msgrcv");
		return errno;
	}
	
	/*printing the string we got - "working on report"*/
	printf("%s\n", recieveMsg.m_text);
	
	if (msgrcv(msgid, &recieveMsg, g_msgTextLength, MANAGER_TO_UI_REPORT , 0) == -1) 
	{
		perror("msgrcv");
		return errno;
	}
	
	/*printing THE STRING WE GOT - "WORK IS DONE"*/
	printf("%s\n", recieveMsg.m_text);
	
	return 0; /*success*/
}

int main()
{	
	int status;
	
	while(1)
	{
		status = HandleUserRequest();
	}	

	if (status != 0)
	{
		perror("ui status failure");
	}		
	return status;
}

    
