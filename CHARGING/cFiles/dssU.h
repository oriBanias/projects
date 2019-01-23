#ifndef __UPDATES_H__
#define __UPDATES_H__

#include "aggregator.h" 
#include "HashMap.h"
#include <stddef.h>  /* size_t */


void* updateSubscriber(Cdr* _newCdr, HashMap* _hash);



/* size_t HashFun(const void* _key);*/
/*
CDR_Result updateQuery(char* _imsi, HashMap* _HashMap);

CDR_Result updateExtract(char* _imsi, HashMap* _HashMap);
*/


#endif 
