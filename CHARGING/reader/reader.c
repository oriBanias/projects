#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 500
#endif

#include "reader.h"
#include "cdr.h"
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

#define SIZE 2048
#define AGG_MEM_SIZE 13 /*number of members of struct Cdr*/
#define PARSER_TO_AGGREGATOR 2 /*channel sending struct to aggregator*/

/* static reader functions */
static int InitReaderProtocol(const char* _pathname, int _proj_id);
static int HandleCdrFiles(const char* _pathname, FILE** _fp, int _msgid);
static int TerminateCommunication(int _msgid);

static int InitReaderProtocol(const char* _pathname, int _proj_id)
{
	key_t key;
	int msgid = 0; 
	
	if (_pathname == NULL)
	{
		perror("pathname NULL error");
		return -1;
	}
	
	if ((key = ftok(_pathname, _proj_id)) == -1) 
	{
		perror("ftok");
		return -1;
	}
	
	msgid = msgget(key, 0666 | IPC_CREAT);	
	return msgid;
}

static int HandleCdrFiles(const char* _pathname, FILE** _fp, int _msgid)
{
	char delim[2] = "|";
	Msg sendMsg = {0};
	char str[SIZE] = {0};
	int status = 0;
	
	
	if (_pathname == NULL)
	{
		perror(" NULL error");
		return -1;
	}
	
	sendMsg.m_type = PARSER_TO_AGGREGATOR;
	
	*_fp=fopen(_pathname, "r");

	if(*_fp == NULL)
	{
		perror("File Opening Error!!");
		return -1;
	}
	
	while (fgets(str, SIZE, *_fp) != NULL) 
	{
		status = parsing(str, (Cdr*)sendMsg.m_text, delim);
		if (status == -1)
		{
			perror("parsing function error");
			return -1;
		}
	
		if (msgsnd(_msgid, &sendMsg, g_msgTextLength, 0) == -1)
		{
			perror("msgsend failed");
			return errno;
		}
		
	}
	return 0; /*success*/
}

static int TerminateCommunication(int _msgid)
{
	const char* terminateMsg = "terminate";
	int i = 0;
	Msg sendMsg = {0};
	
	strcpy(sendMsg.m_text, terminateMsg);
	sendMsg.m_type = PARSER_TO_AGGREGATOR;

	for(i = 0; i < THREAD_NUM; ++i)
	{
		if (msgsnd(_msgid, &sendMsg, g_msgTextLength, 0) == -1)
		{
			perror("msgsend failed");
			return errno;
		}
	}
	return 0; /*success*/
}

int main()
{
    int msgid = 0;
    int status = 0;
    int proj_id = 'B'; 
    const char* cdrFilePath = "../cdrfiles/cdr.ini";
    FILE* fp = NULL;
    
	msgid = InitReaderProtocol(cdrFilePath, proj_id);
	
	if (msgid == -1 || msgid == 0)
	{
		perror("InitReaderProtocol");
		return -1;
	}
	
	status = HandleCdrFiles(cdrFilePath, &fp, msgid);
	if (status != 0)
	{
		perror("handleCdrFiles function error");
		return -1;
	}
	
	status = TerminateCommunication(msgid);
	if (status != 0)
	{
		perror("TerminateCommunication function error");
		return -1;
	}

	fclose(fp);
	return 0;
} 

