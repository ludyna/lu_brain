/**
	Copyright © 2021 Oleh Ihorovych Novosad 
*/

#include "unity.h"
#include "lib/_module.h"

lu_value values_00[] = { 
	1, 2, 3,
	4, 5, 6,
	7, 8, 9
};

struct lu_data data_0 = {
	.w = 3,
	.h = 3, 
	.d = 1,
	.values = values_00
};


// setUp is executed for each test, even if test does nothing
void setUp(void)
{ 
}

void tearDown(void)
{	
}

void test_lu_data_create_via_shift(void)
{
	Lu_Data data_1 = lu_data_create_via_shift(lu_g_mem, &data_0, -1, 0);

	// lu_data_debug(data_1);

	TEST_ASSERT(lu_data_value_get(data_1, 0, 0, 0) == 1);
	TEST_ASSERT(lu_data_value_get(data_1, 1, 1, 0) == 4);

	lu_data_destroy(data_1, lu_g_mem);

	data_1 = lu_data_create_via_shift(lu_g_mem, &data_0, 1, 0);

	// lu_data_debug(data_1);

	TEST_ASSERT(lu_data_value_get(data_1, 0, 0, 0) == 2);
	TEST_ASSERT(lu_data_value_get(data_1, 1, 1, 0) == 6);

	lu_data_destroy(data_1, lu_g_mem);

	data_1 = lu_data_create_via_shift(lu_g_mem, &data_0, 0, -1);

	// lu_data_debug(data_1);

	TEST_ASSERT(lu_data_value_get(data_1, 0, 0, 0) == 1);
	TEST_ASSERT(lu_data_value_get(data_1, 1, 1, 0) == 2);

	lu_data_destroy(data_1, lu_g_mem);

	data_1 = lu_data_create_via_shift(lu_g_mem, &data_0, 1, 1);

	// lu_data_debug(data_1);

	TEST_ASSERT(lu_data_value_get(data_1, 0, 0, 0) == 5);
	TEST_ASSERT(lu_data_value_get(data_1, 1, 1, 0) == 9);

	lu_data_destroy(data_1, lu_g_mem);
}