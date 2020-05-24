/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

#include "unity.h"
#include "brain/brain.h"

Lu_Brain 			brain;
Lu_Rec 				rec_1;

Lu_Brain_Opts 		brain_opts;
Lu_Rec_Opts 		rec_opts_1;

lu_value			data_0[] 		= { 0, 0, 1, 1 };

Mem 				mem;
S_Mem				s_mem;
S_Rec 				s_rec;
S_Cell				s_cell;
S_Col 				s_col;

// setUp is executed for each test, even if test does nothing
void setUp(void)
{ 
	brain_opts 			= lu_brain_opts_create(1, 20 * 1024);
	rec_opts_1 			= lu_rec_opts_create(brain_opts, 2, 2, 1, 0.0, 10.0, 10, .2);

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

	s_col = s_cell_s_col_get(s_cell, 0);
	TEST_ASSERT(s_col);
}

void tearDown(void)
{	
	lu_brain_opts_destroy(brain_opts);
	lu_brain_destroy(brain);
}


void test_s_col(void)
{

}