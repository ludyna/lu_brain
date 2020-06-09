/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

#include "unity.h"
#include "brain/brain.h"

Lu_Brain 			brain;
Lu_Rec 				rec_1;

Lu_Brain_Opts 		brain_opts;
Lu_Rec_Opts 		rec_opts_1;
Lu_Rec_Opts 		rec_opts_2;

lu_value			data_0[] 		= { 0 }; 
lu_value			data_1[] 		= { 1.0 };
lu_value			data_3[] 		= { 3.0 };
lu_value			data_5[] 		= { 5.0 };
lu_value			data_10[] 		= { 10.0 };
lu_value			data_999[] 		= { 999.0 };
lu_value			data_m1[] 		= { -1.0 };

Mem 				mem;
S_Mem				s_mem;
S_Rec 				s_rec;
S_Cell				s_cell;
S_Col 				s_col1;
S_Col 				s_col2;

// setUp is executed for each test, even if test does nothing
void setUp(void)
{ 

}

void tearDown(void)
{	

}

void test_s_col1and2(void)
{
	brain_opts 			= lu_brain_opts_create(1, 20 * 1024);
	rec_opts_1 			= lu_rec_opts_create(brain_opts, 1, 1, 1, 0.0, 10.0, 10, 4, 0);
	TEST_ASSERT(rec_opts_1);

	rec_opts_2			= lu_rec_opts_create(brain_opts, 1, 1, 2, -3.0, 4.0, 3, 2, 0);
	TEST_ASSERT(rec_opts_2);

	brain 				= lu_brain_create(brain_opts);

	TEST_ASSERT(brain);
	TEST_ASSERT(brain->recs);
	TEST_ASSERT(brain->recs->count);

	rec_1 				= lu_brain_rec_get(brain, 0);
	TEST_ASSERT(rec_1);

	s_mem = brain->s_mem;
	TEST_ASSERT(s_mem);

	s_rec = s_mem_s_rec_get(s_mem, 0);
	TEST_ASSERT(s_rec);

	s_cell = s_rec_s_cell_get(s_rec, 0, 0);
	TEST_ASSERT(s_cell);

	s_col1 = s_cell_s_col_get(s_cell, 0);
	TEST_ASSERT(s_col1);

	s_rec = s_mem_s_rec_get(s_mem, 1);
	TEST_ASSERT(s_rec);

	s_cell = s_rec_s_cell_get(s_rec, 0, 0);
	TEST_ASSERT(s_cell);

	s_col2 = s_cell_s_col_get(s_cell, 0);
	TEST_ASSERT(s_col2);

	// s_col1 tests

	//N_Col n_col = s_col_n_get(s_col1, 5.0);


	// s_col2 tests


	lu_brain_opts_destroy(brain_opts);
	lu_brain_destroy(brain);
}