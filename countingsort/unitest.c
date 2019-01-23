#include "mu_test.h"
#include "../../../DS/vector/vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

error_e CountingSort(int* _arr, size_t _size);
/********* COUNTING SORT ***********/
UNIT(check_counting_sort)
	size_t i;
	int arr[] = {254, 22,925,625626,257,55,22,588,6594,56125181};
	size_t size = sizeof(arr)/sizeof(int);
	
	printf("before sorting:\n");
	for(i = 0; i < sizeof(arr)/sizeof(int); ++i)
	{
		printf("%d\t", arr[i]);
	}
	
	ASSERT_THAT(ERR_OK == CountingSort(arr, size));
	
	printf("after sorting:\n");
	for(i = 0; i < sizeof(arr)/sizeof(int); ++i)
	{
		printf("%d\t", arr[i]);
	}
	
END_UNIT

TEST_SUITE(hash)

TEST(check_counting_sort)

END_SUITE
