
#include "insertion.h"

static void InsertionDown(Vector_int* _vec, size_t _index)
{
	int current = 0;
	int insertItem = 0;
	
	if(_index == 0)
	{
		return;
	}

	VectorGet(_vec, _index, &current);
	VectorGet(_vec, _index-1, &insertItem);

	while(_index > 1 && current < insertItem )
	{
		VectorSet(_vec, _index, insertItem);
		VectorGet(_vec, --_index-1, &insertItem);
	}	
	
	if(_index == 1)
	{
		VectorSet(_vec, 1, current);
	} 
	else
	{
		VectorSet(_vec, _index, current);
	}
}

error_e InsertionSort(Vector_int* _vec)
{	
	size_t i;
	size_t itemNum;
	if(_vec == NULL)
	{
		return ERR_ILLIGAL_INPUT;
	}
	VectorGetItemsNum(_vec, &itemNum);
	for(i = 1; i < itemNum; ++i )
	{
		InsertionDown(_vec, i+1);
	}
	
	return ERR_OK;




}
