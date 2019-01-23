#include "dssO.h"
#include "dssU.h"
#include "cdr.h"
#include "HashMap.h"
#include "query.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void* updateSubscriber(Cdr* _newCdr, HashMap* _hash)
{	
	Subscriber* newSub = NULL;
	size_t callType;
	int res = 0;

	if (_newCdr==NULL || _hash == NULL)
	{
		return NULL;
	}

	newSub = SubscriberCreate();
	if (newSub == NULL)
	{
		perror("subscriber allocation error");
		free(newSub);
		return NULL;
	}
	
	SetImsi(newSub, _newCdr);	
	callType = GetCallType(_newCdr);

	switch (callType)
	{
	  case MOC:
	  		if (strcmp(GetOperatorBrandName(_newCdr), GetPartyOperator(_newCdr)) == 0)
	  		{
	  			SetOutCallIn(newSub, GetDuration(_newCdr));	
	  			break;	  
	  		}
	  		else
	  		{
	  			SetOutCallOut(newSub, GetDuration(_newCdr));
	  			break;
	  		}
	
   	  case MTC:
  			if (strcmp(GetOperatorBrandName(_newCdr), GetPartyOperator(_newCdr)) == 0)
	  		{
	  			SetInCallIn(newSub, GetDuration(_newCdr)); 	  	
	  			break;	  
	  		}
	  		else
	  		{
	  			SetInCallOut(newSub, GetDuration(_newCdr));
	  			break;
	  		}
		  
	 case SMS_MO:
	 		if (strcmp(GetOperatorBrandName(_newCdr), GetPartyOperator(_newCdr)) == 0)
	  		{
	  			SetOutSmsIn(newSub); 	  	
	  			break;	  
	  		}
	  		else
	  		{
	  			SetOutSmsOut(newSub);
	  			break;
	  		}

     case SMS_MT:
 			if (strcmp(GetOperatorBrandName(_newCdr), GetPartyOperator(_newCdr)) == 0)
	  		{
	  			SetInSmsIn(newSub); 	  	
	  			break;	  
	  		}
	  		else
	  		{
	  			SetInSmsOut(newSub);
	  			break;
	  		}

     case GPRS:
		  SetDownload(newSub, GetDownload(_newCdr));
		  SetUpload(newSub, GetUpload(_newCdr));
		  break; 
	
	 default:  
	 		free(newSub);  			
   			return NULL;	
	}
	
	res = HashMap_Upsert(_hash, GetMsisdn(_newCdr), newSub, UpdateValFunc);
	
	if (res != MAP_SUCCESS)
	{
		free(newSub);
	}
	
	return newSub;
}



