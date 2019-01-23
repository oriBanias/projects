#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef enum { ERR_OK, ERR_ALLOCATION , ERR_ILLIGAL_INPUT, ERR_OVER_FLOW, ERR_DOWN_FLOW, ERR_OUT_OF_RANGE  }error_e;

typedef struct
{
	int* mVec ;
	size_t mCurrentSize;
	size_t mInitSize ;
	size_t mBlockSize ; 
	size_t mItemNum ;      
}Vector_int;

/*
	description: creates a new vector struct and initilized the struct members, and also the array of ints in the size of init size that we got from the user.
	input: initsize and block size
		   
	 
	return value: pointer to the new vector that we created	
			return NULL in case it did not work.			
*/
Vector_int* VectorCreate(size_t _initSize, size_t _blockSize);

/*
	description:erase the vectore we created 
	input: pointer to the vector we wish to erase
		   
	output:clean memory in the place we use to have the vector
	return value: void			
*/
void VectorDestroy(Vector_int* _vector);


/*
	description: we need to add an int element into the array of ints we created 
			O(1). in case of resizing occasionally   of container, O(n)!!!
	input: pointer to vector
		   
	output:the array with additional element in  the last place of the array
	return value: 	-ERR_ILLIGAL_INPUT (ADDRESS IS NULL)
			-ERR_OVER_FLOW  (BLOCK SIZE IS 0)			
*/
error_e VectorAdd(Vector_int* _vector, int _item); 


/*
	description: delete the last element in an array. O(1).
			
	input: pointer to vector and pointer to element
		   
	output:the array without the element we erased. in this element we now have 0
	return value: -ERR_ILLIGAL_INPUT (ADDRESS or item IS NULL)
			-ERR_DOWN_FLOW	
			in case it is ok, we return the item!		
*/
error_e VectorDelete(Vector_int* _vector, int* _item);



/*
	description: the function get to the user the value of an element he wish to see by the index he sent
	input: pointer to vector, index from the user and point to the item we wish to see
		   
	return value: 	- ERR_OUT_OF_RANGE
			- ERR_ILLIGAL_INPUT
			- ERR_OK			
*/
error_e VectorGet(Vector_int* _vector, size_t _index, int* _item ); 

/*
	description: set  new element in the array of vectors in one of the indexes that the user ask for
	input: pointer to vector, index from the user and the item we wish to set
		   
	output: an array of vectors with the new item we set in a specific index
	return value: 	-ERR_ILLIGAL_INPUT
			-ERR_OUT_OF_RANGE*/
error_e VectorSet(Vector_int* _userVector, size_t _index,int _item ); 

/*
	description: get for the user the number of items thare are in the array
	input: pointer to vector, num of items
		 
	return value: -  				
*/
error_e VectorGetItemsNum(Vector_int* _vector,size_t* _numOfItms);


/*-
	description: print the array of ints and the members of the struct vector_int
	input: pointer to vector struct
		   
	output:none
	return value: none				
*/
void VectorPrint(Vector_int* _vector);

/*-
	description: let the user choose an action out of three to preform on each one of the vector members
	input: pointer to vector struct, pointer to function
		   
	return value: 0 for failed,  1 for success				
*/
int VectorForEach(Vector_int*_vector, int(*_action)(int* _item, void* _content), void* _content);



#endif
