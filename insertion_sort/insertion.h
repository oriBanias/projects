#ifndef __INSERTION_H__
#define __INSERTION_H__
#include "vector.h"
#include <stdio.h>
#include <stdlib.h>

/*
	description:sort the vector by insertion
	input: pointer to the vector we created
	return value: -ERR_OK
					-ERR_ILLIGAL_INPUT			
*/
error_e InsertionSort(Vector_int* _vec);

#endif
