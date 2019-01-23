#include <stdio.h>
#include <stdlib.h>
#include "../../../DS/vector/vector.h"

static int MaxItem(int* _arr, size_t _size)
{
	size_t i;
	int max = 0;
	for(i=0; i<_size; ++i)
	{
		if (_arr[i] > max)
		{
			max = _arr[i];
		}
		
	}
	return max;
}

error_e CountingSort(int* _arr, size_t _size)
{
	size_t i;
	int* newArr;
	int* countArr;
	int max = MaxItem(_arr, _size);
	countArr = (int*)calloc((size_t)max+1, sizeof(int));
	
	if(countArr == NULL)
	{
		return ERR_ALLOCATION;
	}
	
	for(i=0; i<_size; ++i)
	{
		++countArr[_arr[i]];
	}
	
	for(i = 1; i<max+1; ++i)
	{
		countArr[i] = countArr[i] + countArr[i-1];
	}
		
	newArr = (int*)malloc(sizeof(int)*_size);
	
	for(i=_size-1; (int)i>=0; --i)
	{
		newArr[countArr[_arr[i]]-1] = _arr[i];
		--countArr[_arr[i]];
	}
	
	memcpy(_arr, newArr, (_size)*sizeof(int));
	
	free(countArr);
	free(newArr);
	
	return ERR_OK;
	
}


/*

int main()
{
	size_t i;
	int arr[] = {1,3,2,1,5,7,5};
	size_t size = sizeof(arr)/sizeof(int);
	
	printf("before sorting:\n");
	for(i = 0; i < 7; ++i)
	{
		printf("%d\t", arr[i]);
	}
	
	CountingSort(arr, size);
	
	printf("after sorting:\n");
	for(i = 0; i < 7; ++i)
	{
		printf("%d\t", arr[i]);
	}
	return 0;
}*/
