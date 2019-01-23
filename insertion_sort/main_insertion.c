
#include "mu_test.h"
#include "insertion.h"


/********* INSERTION CHECK ***********/
UNIT(check_sorting_vector_by_insertion)
	Vector_int* vec;
	vec = VectorCreate(5, 5);
	VectorAdd(vec, 2);
	VectorAdd(vec, 4);
	VectorAdd(vec, 5);
	VectorAdd(vec, 3);
	VectorAdd(vec, 6);
	VectorPrint(vec);
	ASSERT_THAT(ERR_OK == InsertionSort(vec));
	VectorPrint(vec);
	VectorDestroy(vec);
END_UNIT

TEST_SUITE(insertion)

TEST(check_sorting_vector_by_insertion)

END_SUITE
