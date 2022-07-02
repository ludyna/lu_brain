/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/

#include "unity.h"
#include "lib/_module.h"

lu_value			data_0[] 		= { 
										0, 0, 0,
										1, 2.4, 1,
										1, 1, 1,

										1, 3, 4, 
										7, 2.4, 3.8,
										6, 6, 6
									};

void setUp(void)
{ 

}

void tearDown(void)
{	

}

void test_comp_calc_1(void) 
{ 
	Lu_Data data = lu_data__create_via_mem_copy(lu_g_mem, data_0, 3, 3, 2);

	TEST_ASSERT(lu_data__get_value(data, 1, 1, 0) == 2.4);
	TEST_ASSERT(lu_data__get_value(data, 1, 1, 1) == 2.4);
	
	struct lu_comp_calc cc;

	lu_comp_calc__init(&cc, lu_g_mem, 2, 5, 6);

	// lu_comp_calc__debug(&cc);

	// lu_data__print(data);
	lu_comp_calc__digitalize_data(&cc, data, 1);

	TEST_ASSERT(lu_data__get_value(data, 1, 1, 0) == 2.4);
	TEST_ASSERT(lu_data__get_value(data, 1, 1, 1) == 0);
	TEST_ASSERT(lu_data__get_value(data, 2, 1, 1) == 1.5);
	// lu_data__print(data);

	lu_comp_calc__deinit(&cc);

	lu_data__destroy(data, lu_g_mem);
}