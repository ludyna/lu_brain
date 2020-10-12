/**
	Copyright © 2020 Oleh Ihorovych Novosad 
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
	Lu_Data data_1 = lu_data_create_via_shift(g_mem_temp, &data_0, -1, 0);

	lu_data_debug(data_1);

	lu_data_destroy(data_1, g_mem_temp);
}