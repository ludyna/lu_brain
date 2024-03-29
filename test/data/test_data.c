/**
	Copyright © 2022 Oleh Ihorovych Novosad 
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

struct lu_rec_view rec_view;

// setUp is executed for each test, even if test does nothing
void setUp(void)
{ 
	lu_rec_view__init(&rec_view, 3, 3, 1);
}	

void tearDown(void)
{	
}

void test__lu_data_create_via_shift(void)
{
	Lu_Data data_1 = lu_data__create_via_shift(lu_g_mem, &data_0, -1, 0);

	// lu_data__print(data_1);

	TEST_ASSERT(lu_data__get_value(data_1, 0, 0, 0) == 1);
	TEST_ASSERT(lu_data__get_value(data_1, 1, 1, 0) == 4);

	lu_data__destroy(data_1, lu_g_mem);

	data_1 = lu_data__create_via_shift(lu_g_mem, &data_0, 1, 0);

	// lu_data__print(data_1);

	TEST_ASSERT(lu_data__get_value(data_1, 0, 0, 0) == 2);
	TEST_ASSERT(lu_data__get_value(data_1, 1, 1, 0) == 6);

	lu_data__destroy(data_1, lu_g_mem);

	data_1 = lu_data__create_via_shift(lu_g_mem, &data_0, 0, -1);

	// lu_data__print(data_1);

	TEST_ASSERT(lu_data__get_value(data_1, 0, 0, 0) == 1);
	TEST_ASSERT(lu_data__get_value(data_1, 1, 1, 0) == 2);

	lu_data__destroy(data_1, lu_g_mem);

	data_1 = lu_data__create_via_shift(lu_g_mem, &data_0, 1, 1);

	// lu_data__print(data_1);

	TEST_ASSERT(lu_data__get_value(data_1, 0, 0, 0) == 5);
	TEST_ASSERT(lu_data__get_value(data_1, 1, 1, 0) == 9);

	lu_data__destroy(data_1, lu_g_mem);
}

void test__lu_data_seq(void)
{
	struct lu_rec rec;
	rec.brain = NULL;
	rec.id = 0;
	rec.width = 3;
	rec.height = 3;
	rec.depth = 1;

	Lu_Data_Seq ds = lu_data_seq__create(lu_g_mem, 0, 1);

	lu_data_seq__push(ds, &rec, values_00, 3, 3, 1, rec_view);
	lu_data_seq__push(ds, &rec, values_00, 3, 3, 1, rec_view);
	lu_data_seq__push(ds, &rec, values_00, 3, 3, 1, rec_view);
	lu_data_seq__push(ds, &rec, values_00, 3, 3, 1, rec_view);
	lu_data_seq__push(ds, &rec, values_00, 3, 3, 1, rec_view);
	lu_data_seq__push(ds, &rec, values_00, 3, 3, 1, rec_view);
	lu_data_seq__push(ds, &rec, values_00, 3, 3, 1, rec_view);
	lu_data_seq__push(ds, &rec, values_00, 3, 3, 1, rec_view);
	

	lu_data_seq__destroy(ds);
}