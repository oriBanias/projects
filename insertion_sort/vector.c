#include "vector.h"


static error_e Resize(Vector_int* _vector, size_t _newSize)  
{
	int* resizeVector = NULL; /* temperory pointer */
	 
	if(_vector->mBlockSize == 0)
	{
		return ERR_OVER_FLOW; 
	}

    resizeVector=(int*)realloc(_vector->mVec, _newSize);

	if(resizeVector == NULL)
	{
		return ERR_ALLOCATION;
	}

	_vector->mVec=resizeVector;
	_vector->mCurrentSize = _newSize;
	
	return ERR_OK;
	
}

Vector_int* VectorCreate(size_t _initSize, size_t _blockSize)
{
	Vector_int* vector = NULL;

	vector = (Vector_int*)malloc(sizeof(Vector_int));
	if(NULL == vector)
	{
		printf("memory cannot be allocated\n");
		return NULL;
	}
	
	vector->mVec = (int*)calloc(_initSize+1, sizeof(int));/* maarah shel mazbiim*/
	if(NULL == vector -> mVec)
	{
		free(vector);
		return NULL;
	}	

	vector->mItemNum = 0;
	vector->mBlockSize = _blockSize;
	vector->mInitSize = _initSize;
	vector->mCurrentSize= vector->mInitSize;	
	
	return vector;	
}

void VectorDestroy(Vector_int* _vector)
{
	if (_vector == NULL)
	{
		return ;	
	}

	free(_vector->mVec);
	free(_vector);
	
	return ;
}

error_e VectorAdd(Vector_int* _vector, int _item)
{ 
	if (_vector == NULL)
	{
		return ERR_ILLIGAL_INPUT;	
	}

	if(_vector->mItemNum >= _vector->mCurrentSize )
	{
		if(ERR_OK != Resize(_vector, _vector->mCurrentSize + _vector->mBlockSize))
		{
			return ERR_ALLOCATION;
		}
	}

	_vector->mVec[++_vector->mItemNum] = _item;
	

	return ERR_OK;
}

error_e VectorDelete(Vector_int* _vector, int* _item)
{

	if (NULL == _vector)
	{	
		return ERR_ALLOCATION; 
	}
	
	*_item = _vector->mVec[_vector->mItemNum];
	
	if((_vector->mCurrentSize - _vector->mItemNum) >= (2*_vector->mBlockSize)
		&& (_vector->mCurrentSize != _vector->mInitSize)) 
		{
			Resize(_vector, (_vector->mCurrentSize) - (_vector->mBlockSize));
		}
	
	--_vector->mItemNum;
		
	return ERR_OK;
	
}



error_e VectorSet(Vector_int* _vector, size_t _indx, int _item)
{ 
	if (_vector == NULL)
	{
		return ERR_ILLIGAL_INPUT;	
	}

	if(_indx > _vector->mItemNum || _indx==0)
	{
		{
			return ERR_OUT_OF_RANGE;
		}
	}

	_vector->mVec[_indx] = _item;

	return ERR_OK;
}

error_e VectorGet(Vector_int* _vector, size_t _indx, int* _item)
{ 
	if (_vector == NULL)
	{
		return ERR_ILLIGAL_INPUT;	
	}

	if(_indx > _vector->mItemNum || _indx==0)
	{
		{
			return ERR_OUT_OF_RANGE;
		}
	}

	*_item = _vector->mVec[_indx];

	return ERR_OK;
}
	
error_e VectorGetItemsNum(Vector_int* _vector, size_t* _numOfItms)
{
	if (_vector == NULL)
	{
		return ERR_ILLIGAL_INPUT;	
	}
	
	else
	{	
		*_numOfItms = _vector->mItemNum;
	}	
	return ERR_OK;
}




void VectorPrint(Vector_int* _vector)
{
	size_t index = 1;

	if (_vector == NULL)
	{
		return;	
	}

	printf("\nthe updated struct members are:\n");
	printf("current size:%lu, init size:%lu, blocksize:%lu, number of items:%lu", _vector->mCurrentSize, _vector->mInitSize, _vector->mBlockSize, _vector->mItemNum );

	if(&_vector->mVec[index] == NULL)
	{
		return;
	}
	
	printf("\nthe updated array of ints is:\n");

	while(index <= _vector->mItemNum)
	{		
		
		printf("%d ", _vector->mVec[index]);
		++index;	
	}	

}



int VectorForEach(Vector_int*_vector, int(*_action)(int* _item, void* _content), void* _content)
{
	size_t max;
	int index = 0;
	max = _vector->mItemNum;

	if (_action ==NULL || NULL == _vector || NULL == _content)
	{
		return ERR_ALLOCATION;
	}

	for(index=0; index<=max; ++index)
	{
		if(0 != _action(&_vector->mVec[index], _content))
		{
			return index;
		}
	}
	
	return 0;
}
