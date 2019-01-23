#ifndef __CDR_H__
#define __CDR_H__

#include <stddef.h>
/*#include <time.h>*/

typedef enum {MOC, MTC, SMS_MO, SMS_MT, GPRS} callType;

typedef struct Cdr Cdr;

Cdr* CreateCdr(void);

void DestroyCdr(Cdr* _cdr);

int parsing(char* _str, Cdr* _newCdr, char* _delim);

size_t CdrSize();

void PrintCdr(Cdr* _cdr);

char* GetImsi(Cdr* _cdr);

char* GetMsisdn(Cdr* _cdr);

size_t GetImei(Cdr* _cdr);

char* GetOperatorBrandName(Cdr* _cdr);

char* GetMccMnc(Cdr* _cdr);

callType GetCallType(Cdr* _cdr);

size_t GetDuration(Cdr* _cdr);

size_t GetDownload(Cdr* _cdr);

size_t GetUpload(Cdr* _cdr);

char* GetPartyMsisdn(Cdr* _cdr);

char* GetPartyOperator(Cdr* _cdr);


#endif
