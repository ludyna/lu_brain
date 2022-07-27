/**
	Copyright © 2022 Oleh Ihorovych Novosad 

	$ clear; ceedling clean; ceedling test:brain_01 --trace
*/

#include "unity.h"
#include "lib/_module.h"

Lu_Mem_Debugger     md;
Lu_Brain 			brain;
struct lu_config 	brain_config;
Lu_Wave 			s_wave;
Lu_Wave  			m_wave;

Lu_Rec 				rec_0;
Lu_Rec 				rec_1; 

lu_value blank_values[] = {
	0, 0,
	0, 0
};

lu_value values[][4] = {
	{ 
		1, 0,  
		0, 0, 
	},
	{ 
		0, 1, 
		0, 0
	},
	{ 
		1, 0, 
		1, 1
	},
	{ 
		1, 0, 
		0, 1
	},
	{ 
		0, 0, 
		1, 0
	}
};


lu_size labels[] = { 0, 1, 2, 3, 4 };

// setUp is executed for each test, even if test does nothing
void setUp(void)
{ 
	md = lu_mem_debugger__create(lu_g_mem);
 
	brain_config 		= lu_config__get_by_id(LU_CONFIG__DEFAULT);

	brain 				= lu_brain__create(brain_config);
	TEST_ASSERT(brain);
	TEST_ASSERT(brain->recs);

	rec_0 				= lu_brain__rec_add(
		/*belongs to*/			brain, 
		/*width*/				3, 
		/*height*/				3, 
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

void test_brain_01(void) 
{ 

	Lu_La_Cell label_cell;

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

	lu__debug("\n\n ======================== S A V E - 0 =========================\n");
	lu__debug("\nvalues before push: ");
	lu_values__print_symbols(values[0], 2, 2, 1);

		lu_wave__push(s_wave, rec_0, blank_values, 2, 2, 1);
		lu_wave__push(s_wave, rec_0, values[0], 2, 2, 1);

		lu_wave__process(s_wave, lu_process_config__get_by_id(LU_PROCESS__SAVE_DEFAULT));
		label_cell = lu_wave__link_to_label(s_wave, 2, 0, 0, 0, labels[0]);
		TEST_ASSERT(label_cell);

	lu__debug("\n\n ======================== S A V E - 1 =========================\n");
	lu__debug("\nvalues before push: ");
	lu_values__print_symbols(values[1], 2, 2, 1);

		lu_wave__push(s_wave, rec_0, blank_values, 2, 2, 1);
		lu_wave__push(s_wave, rec_0, values[1], 2, 2, 1);

		lu_wave__process(s_wave, lu_process_config__get_by_id(LU_PROCESS__SAVE_DEFAULT));
		label_cell = lu_wave__link_to_label(s_wave, 2, 0, 0, 0, labels[1]);
		TEST_ASSERT(label_cell);

	lu__debug("\n\n ======================== S A V E - 2 =========================\n");
	lu__debug("\nvalues before push: ");
	lu_values__print_symbols(values[2], 2, 2, 1);

		lu_wave__push(s_wave, rec_0, blank_values, 2, 2, 1);
		lu_wave__push(s_wave, rec_0, values[2], 2, 2, 1);

		lu_wave__process(s_wave, lu_process_config__get_by_id(LU_PROCESS__SAVE_DEFAULT));
		label_cell = lu_wave__link_to_label(s_wave, 2, 0, 0, 0, labels[2]);
		TEST_ASSERT(label_cell);

	lu__debug("\n\n ======================== S A V E - 3 =========================\n");
	lu__debug("\nvalues before push: ");
	lu_values__print_symbols(values[3], 2, 2, 1);

		lu_wave__push(s_wave, rec_0, blank_values, 2, 2, 1);
		lu_wave__push(s_wave, rec_0, values[3], 2, 2, 1);

		lu_wave__process(s_wave, lu_process_config__get_by_id(LU_PROCESS__SAVE_DEFAULT));
		label_cell = lu_wave__link_to_label(s_wave, 2, 0, 0, 0, labels[3]);
		TEST_ASSERT(label_cell);

	//
	// Match
	//

	m_wave = lu_wave__create_match_wave(brain);

	TEST_ASSERT(m_wave);
	TEST_ASSERT(lu_wave__get_ix(m_wave) == 0);
	TEST_ASSERT(lu_brain__get_wave_by_ix(brain, lu_wave__get_ix(m_wave), lu_wave__get_type(m_wave)) == m_wave);
	lu__debug("\n\n ======================== M A T C H - 0 =========================\n");

		lu__debug("\nvalues before push: ");
		lu_values__print_symbols(values[0], 2, 2, 1);

		lu_wave__push(m_wave, rec_0, blank_values, 2, 2, 1);
		lu_wave__push(m_wave, rec_0, values[0], 2, 2, 1);

		lu_wave__process(m_wave, lu_process_config__get_by_id(LU_PROCESS__MATCH_DIFF_ONLY));

		Lu_Label* results = lu_wave__get_result_labels(m_wave);
		TEST_ASSERT(results);
		TEST_ASSERT(results[0]);

		lu_labels__print_results(results, brain_config.w_match_results_size);

		TEST_ASSERT(lu_label__get_id(results[0]) == labels[0]);

	lu__debug("\n\n ======================== M A T C H - 1 =========================\n");
		lu__debug("\nvalues before push: ");
		lu_values__print_symbols(values[1], 2, 2, 1);

		lu_wave__push(m_wave, rec_0, blank_values, 2, 2, 1);
		lu_wave__push(m_wave, rec_0, values[1], 2, 2, 1);

		lu_wave__process(m_wave, lu_process_config__get_by_id(LU_PROCESS__MATCH_DIFF_ONLY));

		results = lu_wave__get_result_labels(m_wave);
		TEST_ASSERT(results);
		TEST_ASSERT(results[0]);

		lu_labels__print_results(results, brain_config.w_match_results_size);

		TEST_ASSERT(lu_label__get_id(results[0]) == labels[1]);

	lu__debug("\n\n ======================== M A T C H - 2 =========================\n");
		lu__debug("\nvalues before push: ");
		lu_values__print_symbols(values[2], 2, 2, 1);

		lu_wave__push(m_wave, rec_0, blank_values, 2, 2, 1);
		lu_wave__push(m_wave, rec_0, values[2], 2, 2, 1);

		lu_wave__process(m_wave, lu_process_config__get_by_id(LU_PROCESS__MATCH_DIFF_ONLY));

		results = lu_wave__get_result_labels(m_wave);
		TEST_ASSERT(results);
		TEST_ASSERT(results[0]);

		lu_labels__print_results(results, brain_config.w_match_results_size);

		TEST_ASSERT(lu_label__get_id(results[0]) == labels[2]);

	lu__debug("\n\n ======================== M A T C H - 3 =========================\n");
		lu__debug("\nvalues before push: ");
		lu_values__print_symbols(values[3], 2, 2, 1);

		lu_wave__push(m_wave, rec_0, blank_values, 2, 2, 1);
		lu_wave__push(m_wave, rec_0, values[3], 2, 2, 1);

		lu_wave__process(m_wave, lu_process_config__get_by_id(LU_PROCESS__MATCH_DIFF_ONLY));

		results = lu_wave__get_result_labels(m_wave);
		TEST_ASSERT(results);
		TEST_ASSERT(results[0]);

		lu_labels__print_results(results, brain_config.w_match_results_size);

		TEST_ASSERT(lu_label__get_id(results[0]) == labels[3]);

	lu__debug("\n\n ======================== M A T C H - 4 =========================\n");
		lu__debug("\nvalues before push: ");
		lu_values__print_symbols(values[4], 2, 2, 1);

		lu_wave__push(m_wave, rec_0, blank_values, 2, 2, 1);
		lu_wave__push(m_wave, rec_0, values[4], 2, 2, 1);

		lu_wave__process(m_wave, lu_process_config__get_by_id(LU_PROCESS__MATCH_DIFF_ONLY));

		results = lu_wave__get_result_labels(m_wave);
		TEST_ASSERT(results);
		TEST_ASSERT(results[0]);

		lu_labels__print_results(results, brain_config.w_match_results_size);

		TEST_ASSERT(lu_label__get_id(results[0]) == labels[2]);

}
