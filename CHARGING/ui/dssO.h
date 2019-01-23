#ifndef __DSSO_H__
#define __DSSO_H__

#include "cdr.h"
#include <stddef.h>  /* size_t */

typedef struct Subscriber Subscriber;


Subscriber* SubscriberCreate(void);

size_t SubscriberSize(void);

void SubscriberDestroy(void* _sub);

size_t HashFunc(const void* _key);

int	ActionFunc(const void* _key, void* _value, void* _context);

int EqualFunc(const void* _sub1, const void* _sub2);

void* UpdateValFunc(void* _originalValue, const void* _updateValue);

void PrintSubscriber(Subscriber* _subscriber);

char* GetImsiObject(Subscriber* _subscriber);

void SetImsi(Subscriber* _subscriber, Cdr* _newCdr);

size_t GetOutCallIn(Subscriber* _subscriber);

void SetOutCallIn(Subscriber* _subscriber, size_t _addVal);

size_t GetOutCallOut(Subscriber* _subscriber);

void SetOutCallOut(Subscriber* _subscriber, size_t _addVal);

size_t GetInCallIn(Subscriber* _subscriber);

void SetInCallIn(Subscriber* _subscriber, size_t _addVal);

size_t GetInCallOut(Subscriber* _subscriber);

void SetInCallOut(Subscriber* _subscriber, size_t _addVal);

size_t GetOutSmsIn(Subscriber* _subscriber);

void SetOutSmsIn(Subscriber* _subscriber);

size_t GetOutSmsOut(Subscriber* _subscriber);

void SetOutSmsOut(Subscriber* _subscriber);

size_t GetInSmsIn(Subscriber* _subscriber);

void SetInSmsIn(Subscriber* _subscriber);

size_t GetInSmsOut(Subscriber* _subscriber);

void SetInSmsOut(Subscriber* _subscriber);

size_t GetDownloadObject(Subscriber* _subscriber);

void SetDownload(Subscriber* _subscriber, size_t _addVal);

size_t GetUploadObject(Subscriber* _subscriber);

void SetUpload(Subscriber* _subscriber, size_t _addVal);






#endif /* __DSSO_H__ */
