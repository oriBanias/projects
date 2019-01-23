#include "cdr.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct Cdr
{
	char m_imsi[20];
	char msisdn[15];
	size_t imei;
	char OperatorBrandName[64];
	char mcc_mnc[6];
	callType type;
	char callDate[20];
	char callTime[20];
	size_t duration;
	size_t download;
	size_t upload;
	char partyMsisdn[15];
	char partyOperator[64];

};

Cdr* CreateCdr(void)
{
	
	Cdr* _newCdr = (Cdr*)malloc(sizeof(Cdr));
	
	if (_newCdr == NULL)
	{
		free(_newCdr);
		return NULL;
	}
	
	return _newCdr;
	
}

void DestroyCdr(Cdr* _cdr)
{
	free(_cdr);

	_cdr = NULL;
	
	return;
}

int parsing(char* _str, Cdr* _newCdr, char* _delim)
{
	char* token = NULL;

	if (_str == NULL || _newCdr == NULL || _delim == NULL)
	{
		return -1;
	}
	
	token = strtok(_str, _delim);
	strcpy(_newCdr->m_imsi, token);

	
	token = strtok(NULL, _delim);
	strcpy(_newCdr->msisdn, token);

	
	token = strtok(NULL, _delim);
	_newCdr->imei = (size_t)atoi(token);

	
	token = strtok(NULL, _delim);
	strcpy(_newCdr->OperatorBrandName, token);

	
	token = strtok(NULL, _delim);
	strcpy(_newCdr->mcc_mnc, token);

	
	token = strtok(NULL, _delim);
	
	if(strcmp(token, "MOC")== 0)
	{
		_newCdr->type = MOC;
	}

	else if (strcmp(token, "MTC")== 0)
	{
		_newCdr->type = MTC;
	}
	
	else if (strcmp(token, "SMS_MO")== 0)
	{
		_newCdr->type = SMS_MO;
	}
	
	else if (strcmp(token, "SMS_MT")== 0)
	{
		_newCdr->type = SMS_MT;
	}
	
	else if (strcmp(token, "GPRS")== 0)
	{
		_newCdr->type = GPRS;
	}
		
	token = strtok(NULL, _delim);
	strcpy(_newCdr->callDate, token);

	
	token = strtok(NULL, _delim);
	strcpy(_newCdr->callTime, token);

	
	token = strtok(NULL, _delim);
	_newCdr->duration = (size_t)atoi(token);

	
	token = strtok(NULL, _delim);
	_newCdr->download = (size_t)atoi(token);

	
	
	token = strtok(NULL, _delim);
	_newCdr->upload = (size_t)atoi(token);

	
	token = strtok(NULL, _delim);
	strcpy(_newCdr->partyMsisdn, token);

	
	token = strtok(NULL, _delim);
	strcpy(_newCdr->partyOperator, token);
	
	return 0;
}

size_t CdrSize()
{
	return sizeof(Cdr);
}

void PrintCdr(Cdr* _cdr)
{
			printf("\n%s %s %lu %s %s %d %s %s %lu %lu %lu %s %s\n", _cdr->m_imsi, _cdr->msisdn, _cdr->imei, _cdr->OperatorBrandName, _cdr->mcc_mnc, _cdr->type, _cdr->callDate, _cdr->callTime, _cdr->duration, _cdr->download, _cdr->upload, _cdr->partyMsisdn, _cdr->partyOperator);
}


char* GetImsi(Cdr* _cdr)
{
	return _cdr->m_imsi;
}

char* GetMsisdn(Cdr* _cdr)
{
	return _cdr->msisdn;
}

size_t GetImei(Cdr* _cdr)
{
	return _cdr->imei;
}

char* GetOperatorBrandName(Cdr* _cdr)
{
	return _cdr->OperatorBrandName;
}

char* GetMccMnc(Cdr* _cdr)
{
	return _cdr->mcc_mnc;
}

callType GetCallType(Cdr* _cdr)
{
	return _cdr->type;
}

size_t GetDuration(Cdr* _cdr)
{
	return _cdr->duration;
}

size_t GetDownload(Cdr* _cdr)
{
	return _cdr->download;
}

size_t GetUpload(Cdr* _cdr)
{
	return _cdr->upload;
}

char* GetPartyMsisdn(Cdr* _cdr)
{
	return _cdr->partyMsisdn;
}

char* GetPartyOperator(Cdr* _cdr)
{
	return _cdr->partyOperator;
}

	
	

