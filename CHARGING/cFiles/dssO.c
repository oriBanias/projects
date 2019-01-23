#include "dssO.h"
#include "cdr.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

struct Subscriber 
{
	char m_imsi[20];
	size_t m_outCallIn;
	size_t m_outCallOut;
	size_t m_inCallIn;
	size_t m_inCallOut;
	size_t m_outSmsIn;
	size_t m_outSmsOut;
	size_t m_inSmsIn;
	size_t m_inSmsOut;
	size_t m_dowmload;
	size_t m_upload;
	
};

char* GetImsiObject(Subscriber* _subscriber)
{
	return _subscriber->m_imsi;
}

void SetImsi(Subscriber* _subscriber, Cdr* _newCdr)
{
	strcpy(_subscriber->m_imsi, GetImsi(_newCdr));	
	puts(_subscriber->m_imsi);
}

size_t GetOutCallIn(Subscriber* _subscriber)
{
	return _subscriber->m_outCallIn;
}

void SetOutCallIn(Subscriber* _subscriber, size_t _addVal)
{
	_subscriber->m_outCallIn += _addVal;
}

size_t GetOutCallOut(Subscriber* _subscriber)
{
	return _subscriber->m_outCallOut;
}

void SetOutCallOut(Subscriber* _subscriber, size_t _addVal)
{
	_subscriber->m_outCallOut += _addVal;
}

size_t GetInCallIn(Subscriber* _subscriber)
{
	return _subscriber->m_inCallIn;
}

void SetInCallIn(Subscriber* _subscriber, size_t _addVal)
{
	_subscriber->m_inCallIn += _addVal;
}

size_t GetInCallOut(Subscriber* _subscriber)
{
	return _subscriber->m_inCallOut;
}

void SetInCallOut(Subscriber* _subscriber, size_t _addVal)
{
	_subscriber->m_inCallOut += _addVal;
}

size_t GetOutSmsIn(Subscriber* _subscriber)
{
	return _subscriber->m_outSmsIn;
}

void SetOutSmsIn(Subscriber* _subscriber)
{
	_subscriber->m_outSmsIn++;
}

size_t GetOutSmsOut(Subscriber* _subscriber)
{
	return _subscriber->m_outSmsOut;
}

void SetOutSmsOut(Subscriber* _subscriber)
{
	_subscriber->m_outSmsOut++;
}

size_t GetInSmsIn(Subscriber* _subscriber)
{
	return _subscriber->m_inSmsIn;
}

void SetInSmsIn(Subscriber* _subscriber)
{
	_subscriber->m_inSmsIn++;
}

size_t GetInSmsOut(Subscriber* _subscriber)
{	
	return _subscriber->m_inSmsOut;
}

void SetInSmsOut(Subscriber* _subscriber)
{
	_subscriber->m_inSmsOut++;
}

size_t GetDownloadObject(Subscriber* _subscriber)
{
	return _subscriber->m_dowmload;
}

void SetDownload(Subscriber* _subscriber, size_t _addVal)
{
	_subscriber->m_dowmload += _addVal;
}

size_t GetUploadObject(Subscriber* _subscriber)
{
	return _subscriber->m_upload;
}

void SetUpload(Subscriber* _subscriber, size_t _addVal)
{
	_subscriber->m_upload += _addVal;
}

size_t SubscriberSize(void)
{
	return sizeof(Subscriber);
}
Subscriber* SubscriberCreate(void)
{
	Subscriber* newSub;
	newSub = (Subscriber*)malloc(sizeof(Subscriber));
	
	if (newSub == NULL)
	{
		return NULL;
	}
	
	newSub->m_outCallIn = 0;
	newSub->m_outCallOut = 0;
	newSub->m_inCallIn = 0;
	newSub->m_inCallOut = 0;
	newSub->m_outSmsIn = 0;
	newSub->m_outSmsOut = 0;
	newSub->m_inSmsIn = 0;
	newSub->m_inSmsOut = 0;
	newSub->m_dowmload = 0;
	newSub->m_upload = 0;
	
	return newSub;
}

void SubscriberDestroy(void* _sub)
{
	free(_sub);
	_sub = NULL;
}

int EqualFunc(const void* _key1, const void* _key2)
{
	int res;
	char* key1 = (char*)_key1;
	char* key2 = (char*)_key2;
	
	res = strcmp(key1, key2); /*key is msisdn*/
	
	if (res == 0)
	{
		return 1; /*true*/
	}
	return 0; /*false*/
}

void* UpdateValFunc(void* _originalValue, const void* _updateValue)
{
	Subscriber* originalValue = (Subscriber*)_originalValue;
	
	Subscriber* updateValue = (Subscriber*)_updateValue;
	
	
	originalValue->m_outCallIn  += updateValue->m_outCallIn;
	originalValue->m_outCallOut += updateValue->m_outCallOut;
	originalValue->m_inCallIn   += updateValue->m_inCallIn;
	originalValue->m_inCallOut  += updateValue->m_inCallOut;
	originalValue->m_outSmsIn   += updateValue->m_outSmsIn;
	originalValue->m_outSmsOut  += updateValue->m_outSmsOut;
	originalValue->m_inSmsIn    += updateValue->m_inSmsIn;
	originalValue->m_inSmsOut   += updateValue->m_inSmsOut;
	originalValue->m_dowmload   += updateValue->m_dowmload;
	originalValue->m_upload     += updateValue->m_upload;
	
	return NULL;
}

size_t HashFunc(const void* _key)
{
	size_t res;
	char* key = (char*)_key;
	
	res = (size_t)strtol(key, NULL, 0);
	
	return res;
	
}

int	ActionFunc(const void* _key, void* _value, void* _context)
{
	Subscriber* sub = (Subscriber*)_value;
	FILE* fp = (FILE*)_context;
	
	fprintf(fp, "%s, %lu, %lu, %lu, %lu, %lu, %lu, %lu, %lu, %lu, %lu\n", sub->m_imsi, sub->m_outCallIn, sub->m_outCallOut, sub->m_inCallIn, sub->m_inCallOut, sub->m_outSmsIn, sub->m_outSmsOut, sub->m_inSmsIn, sub->m_inSmsOut, sub->m_dowmload, sub->m_upload);

	
	return 1;
	
}

void PrintSubscriber(Subscriber* _subscriber)
{
	printf("%s %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu\n", _subscriber->m_imsi, _subscriber->m_outCallIn, _subscriber->m_outCallOut, _subscriber->m_inCallIn, _subscriber->m_inCallOut, _subscriber->m_outSmsIn, _subscriber->m_outSmsOut, _subscriber->m_inSmsIn, _subscriber->m_inSmsOut, _subscriber->m_dowmload, _subscriber->m_upload); 
}
