/**
	Copyright © 2021 Oleh Ihorovych Novosad 
*/

#include "unity.h"
#include "lib/_module.h"

// Lu_Brain 			brain;
// Lu_Rec 				rec_1;

// Lu_Brain_Config 		brain_config;
// Lu_Rec_Opts 		rec_opts_1;
// Lu_Rec_Opts 		rec_opts_2;

// lu_value			data_0[] 		= { 0 }; 
// lu_value			data_01[] 		= { 1.0 };
// lu_value			data_3[] 		= { 3.0 };
// lu_value			data_5[] 		= { 5.0 };
// lu_value			data_10[] 		= { 10.0 };
// lu_value			data_999[] 		= { 999.0 };
// lu_value			data_m1[] 		= { -1.0 };

// Lu_Mem 				mem;
// Lu_S				s;
// S_Rec 				s_rec;
// S_Cell				s_neu_com_0;
// S_Cell 				s_neu_com_1;


// setUp is executed for each test, even if test does nothing
void setUp(void)
{ 

}

void tearDown(void)
{	

}

void test_s_col1and2(void)
{
	// brain_config 			= lu_brain_opts_create(1, 200 * 1024);
	// rec_opts_1 			= lu_rec_opts_create(
	// 	brain_config, 
	// 	/*w*/				3, 
	// 	/*h*/				3, 
	// 	/*depth*/	1,
	// 	/*block_size*/		10, 
	// 	/*v_min*/ 			0.0, 
	// 	/*v_max*/			10.0, 
	// 	/*v_neu_size*/		10
	// );
	// TEST_ASSERT(rec_opts_1);

	// rec_opts_2 			= lu_rec_opts_create(
	// 	brain_config, 
	// 	/*w*/				1, 
	// 	/*h*/				1, 
	// 	/*depth*/	1,
	// 	/*block_size*/		10, 
	// 	/*v_min*/ 			0.0, 
	// 	/*v_max*/			10.0, 
	// 	/*v_neu_size*/		10
	// );

	// TEST_ASSERT(rec_opts_2);

	// brain 				= lu_brain_create(brain_config);

	// TEST_ASSERT(brain);
	// TEST_ASSERT(brain->recs);
	// TEST_ASSERT(brain->recs->count);

	// rec_1 				= lu_brain_rec_get(brain, 0);
	// TEST_ASSERT(rec_1);

	// s = brain->s;
	// TEST_ASSERT(s);

	// s_rec = s_mem_s_rec_get(s, 0);
	// TEST_ASSERT(s_rec);

	// s_neu_com_0 = s_rec_v_cell_get(s_rec, 0, 0, 0, 0);
	// TEST_ASSERT(s_neu_com_0);


	// s_rec = s_mem_s_rec_get(s, 1);
	// TEST_ASSERT(s_rec);

	// s_neu_com_1 = s_rec_v_cell_get(s_rec, 0, 0, 0, 0);
	// TEST_ASSERT(s_neu_com_1);


	// // s_col1 tests

	// //N_Col n_col = s_col_n_get(s_col1, 5.0);
	// // s_col2 tests

	// lu_brain_opts_destroy(brain_config);
	// lu_brain_destroy(brain);
}