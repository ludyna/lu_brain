/**
	Copyright © 2022 Oleh Ihorovych Novosad 

	test_lu_brain tests public interfaces (from library user point of view) and includes 
	general integration tests. It uses nouns with Lu_ prefix only and methods with lu_ prefixes 
	only.

	$ clear; ceedling clean; ceedling test:lu_brain --trace
*/

#include "unity.h"
#include "lib/_module.h"

Lu_Mem_Debugger     md;
Lu_Brain 			brain;
Lu_Wave 			s_wave;
Lu_Wave  			m_wave;

Lu_Rec 				rec_0;
Lu_Rec 				rec_1;

lu_value			values_dot[] 	= { 
										0, 0, 0, 
										0, 0, 0, 
										0, 1, 0, 
										0, 0, 0, 
										0, 0, 0, 
									};

lu_value			values_0[] 		= { 
										1, 1, 1, 
										1, 0, 1, 
										1, 0, 1, 
										1, 0, 1, 
										1, 1, 1, 
									};
lu_value			values_1[] 		= { 
										0, 0, 1, 
										0, 1, 1, 
										0, 0, 1, 
										0, 0, 1, 
										0, 0, 1, 
									};
lu_value			values_2[] 		= { 
										1, 1, 1, 
										0, 0, 1, 
										0, 1, 0, 
										1, 0, 0, 
										1, 1, 1, 
									};
lu_value			values_3[] 		= { 
										1, 1, 1, 
										0, 0, 1, 
										1, 1, 1, 
										0, 0, 1, 
										1, 1, 1, 
									};
lu_value			values_4[] 		= { 
										1, 0, 1, 
										1, 0, 1, 
										1, 1, 1, 
										0, 0, 1,
										0, 0, 1,
									};
lu_value			values_5[] 		= { 
										1, 1, 1, 
										1, 0, 0,
										1, 1, 1, 
										0, 0, 1,
										1, 1, 1, 
									};
lu_value			values_6[] 		= { 
										1, 1, 1, 
										1, 0, 0, 
										1, 1, 1, 
										1, 0, 1, 
										1, 1, 1, 
									};

// setUp is executed for each test, even if test does nothing
void setUp(void)
{ 
	md = lu_mem_debugger__create(lu_g_mem);

	brain 				= lu_brain__create(lu_config__get_by_id(LU_CONFIG__DEFAULT));
	TEST_ASSERT(brain);
	TEST_ASSERT(brain->recs);

	rec_0 				= lu_brain__rec_add(
		/*belongs to*/			brain, 
		/*width*/				4, 
		/*height*/				6, 
		/*depth*/				1,
		/*config*/ 				lu_rec_config__get_by_id(LU_REC__MONO1_IMAGE)
	);	
	TEST_ASSERT(rec_0);

	// rec_1 				= lu_brain__rec_add(
	// 	/*belongs to*/			brain, 
	// 	/*width*/				3, 
	// 	/*height*/				3, 
	// 	/*depth*/				1,
	// 	/*config*/ 				lu_rec_config__get_by_id(LU_REC__TEST1)
	// );	
	// TEST_ASSERT(rec_1);
	
	TEST_ASSERT(brain->recs->count);

	lu_brain__build(brain);


	//
	// Reset waves variables
	// 

	s_wave = NULL;
	m_wave = NULL;
}

void tearDown(void)
{	
	//
	// Destroy waves
	//

	if (s_wave) lu_wave__destroy(s_wave); 
	if (m_wave) lu_wave__destroy(m_wave);

	//
	// Destroy brain
	//

	lu_brain__destroy(brain);

	//
	// Destroy debugger
	//

	lu_mem_debugger__print(md);

	TEST_ASSERT(lu_mem_debugger__is_all_freed(md));
    lu_mem_debugger__destroy(md, true);
}

void test_lu_brain_basics_01(void) 
{ 
	//
	// Save
	//

	TEST_ASSERT(brain);
	TEST_ASSERT(brain->recs);
	TEST_ASSERT(LU_N_ADDR__INACTIVE.value != LU_N_ADDR__NULL.value);
	TEST_ASSERT(LU_N_ADDR__INACTIVE.area_ix < LU_N_AREA__SPECIAL_AREA_SKIP);

	lu_brain__print_areas(brain);

	s_wave = lu_wave__create_save_wave(brain); 

		TEST_ASSERT(s_wave);
		TEST_ASSERT(lu_wave__get_ix(s_wave) == 0);
		TEST_ASSERT(lu_brain__get_wave_by_ix(brain, lu_wave__get_ix(s_wave), lu_wave__get_type(s_wave)) == s_wave);

		lu__debug("\nvalues_0 before push: ");
		lu_values__print_symbols(values_dot, 3, 5, 1);

		lu_rec__set_dest_start_pos(rec_0, 0, 0);

		lu_wave__push(s_wave, rec_0, values_dot, 3, 5, 1);

		lu_rec__set_dest_start_pos(rec_0, 1, 1);

		lu_wave__push(s_wave, rec_0, values_dot, 3, 5, 1);

	lu_wave__process(s_wave, lu_process_config__get_by_id(LU_PROCESS__SAVE_DEFAULT));

	Lu_La_Cell label_cell = lu_wave__link_to_label(s_wave, 2, 0, 0, 0, 15);
	TEST_ASSERT(label_cell);

	//
	// Match
	//

	m_wave = lu_wave__create_match_wave(brain);

		TEST_ASSERT(m_wave);
		// TEST_ASSERT(lu_wave__get_id(m_wave) == 1);
		TEST_ASSERT(lu_wave__get_ix(m_wave) == 0);
		TEST_ASSERT(lu_brain__get_wave_by_ix(brain, lu_wave__get_ix(m_wave), lu_wave__get_type(m_wave)) == m_wave);

		lu__debug("\nvalues_0 before push: ");
		lu_values__print_symbols(values_dot, 3, 5, 1);

		lu_rec__set_dest_start_pos(rec_0, 0, 0);

		lu_wave__push(m_wave, rec_0, values_dot, 3, 5, 1);

		lu_rec__set_dest_start_pos(rec_0, 1, 1);

		lu_wave__push(m_wave, rec_0, values_dot, 3, 5, 1);

	lu_wave__process(m_wave, lu_process_config__get_by_id(LU_PROCESS__MATCH_DIFF_ONLY));

	Lu_Label* results = lu_wave__get_result_labels(m_wave);
	TEST_ASSERT(results);
	TEST_ASSERT(results[0]);

	TEST_ASSERT(lu_label__get_id(results[0]) == 15);
}
