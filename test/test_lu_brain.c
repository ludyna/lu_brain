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
Lu_Rec 				rec_0;
Lu_Rec 				rec_1;

lu_value			data_0[] 		= { 
										0, 0, 0,
										1, 1, 1,
										1, 1, 1
									};
lu_value			data_01[] 		= { 
										1, 0, 0, 
										1, 1, 1,
										1, 1, 1
									};
lu_value			data_2[] 		= { 
										2, 0, 0,
										1, 1, 1,
										1, 1, 1
									};
lu_value			data_3[] 		= { 
										3, 0, 0, 
										1, 1, 1,
										1, 1, 1
									};
lu_value			data_4[] 		= { 
										4, 0, 0, 
										1, 1, 1,
										1, 1, 1
									};
lu_value			data_5[] 		= { 
										5, 0, 0, 
										1, 1, 1,
										1, 1, 1
									};
lu_value			data_6[] 		= { 
										6, 0, 0, 
										1, 1, 1,
										1, 1, 1
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
}

void tearDown(void)
{	
	lu_brain__destroy(brain);

	lu_mem_debugger__print(md);

	TEST_ASSERT(mem_debugger_is_all_clear(md));
    lu_mem_debugger__destroy(md, true);
}

void test_lu_brain_basics_01(void) 
{ 
	/////////////////////////////////////////////////////////
	// Save 

	TEST_ASSERT(brain);
	TEST_ASSERT(brain->recs);
	TEST_ASSERT(LU_N_ADDR__INACTIVE.value != LU_N_ADDR__NULL.value);
	TEST_ASSERT(LU_N_ADDR__INACTIVE.area_ix < LU_N_AREA__SPECIAL_AREA_SKIP);

	lu_brain__print_areas(brain);

	Lu_Wave s_wave = lu_wave__create_save_wave(brain); 

		TEST_ASSERT(s_wave);
		TEST_ASSERT(lu_wave__get_id(s_wave) == 0);
		TEST_ASSERT(lu_brain__get_wave_by_id(brain, lu_wave__get_id(s_wave)) == s_wave);

		lu_wave__push(s_wave, rec_0, data_0);
		lu_wave__push(s_wave, rec_0, data_01);
 
	lu_wave__process(s_wave, lu_process_config__get_by_id(LU_PROCESS__SAVE_DEFAULT));

	Lu_Label label_cell = lu_wave__link_to_label(s_wave, 2, 0, 0, 0, 3);
	TEST_ASSERT(label_cell);

	///////////////////////////////////////////////////////
	// Match

	Lu_Wave m_wave = lu_wave__create_match_wave(brain);

		TEST_ASSERT(m_wave);
		TEST_ASSERT(lu_wave__get_id(m_wave) == 1);
		TEST_ASSERT(lu_brain__get_wave_by_id(brain, lu_wave__get_id(m_wave)) == m_wave);

		lu_wave__push(s_wave, rec_0, data_0);
		lu_wave__push(s_wave, rec_0, data_01);

	lu_wave__process(m_wave, lu_process_config__get_by_id(LU_PROCESS__MATCH_DIFF_ONLY));

	label_cell = lu_wave__get_top_label(m_wave, 0);
	TEST_ASSERT(label_cell);

	// TEST_ASSERT(lu_label__get_id(label_cell) == 3);


	/////////////////////////////////////////////////////////
	// Destroy waves

	lu_wave__destroy(s_wave); 
	lu_wave__destroy(m_wave);
}

void test_lu_brain_basics_02(void) 
{ 
	/////////////////////////////////////////////////////////
	// Save 

	// TEST_ASSERT(brain);
	// TEST_ASSERT(brain->recs);
	// TEST_ASSERT(LU_N_ADDR__INACTIVE.value != LU_N_ADDR__NULL.value);
	// TEST_ASSERT(LU_N_ADDR__INACTIVE.area_ix < LU_N_AREA__SPECIAL_AREA_SKIP);

	// lu_brain__print_areas(brain);

	// Lu_Wave s_wave = lu_wave__create_save_wave(brain); 

	// 	TEST_ASSERT(s_wave);
	// 	TEST_ASSERT(lu_wave__get_id(s_wave) == 0);
	// 	TEST_ASSERT(lu_brain__get_wave_by_id(brain, lu_wave__get_id(s_wave)) == s_wave);

	// 	lu_wave__push(s_wave, rec_0, data_0);
	// 	lu_wave__push(s_wave, rec_0, data_01);

	// 	// lu_wave__block_begin(s_wave);
	// 	// lu_wave__push(s_wave, rec_0, data_01);
	// 	// lu_wave__push(s_wave, rec_1, data_2);
	// 	// lu_wave__block_end(s_wave);

	// 	// lu_wave__push(s_wave, rec_0, data_3);
 
	// lu_wave__process(s_wave, lu_process_config__get_by_id(LU_PROCESS__SAVE_DEFAULT));


	// Lu_Label label_cell = lu_wave__link_to_label(s_wave, 2, 0, 0, 0, 3);
	// TEST_ASSERT(label_cell);
	

		// 	lu_wave__block_begin(s_wave);
		// 	lu_wave__push(s_wave, rec_0, data_4);
		// 	lu_wave__push(s_wave, rec_1, data_5);
		// 	lu_wave__block_end(s_wave);

		// lu_wave__step(s_wave, lu_process_config__get_by_id(LU_PROCESS__SAVE_DEFAULT));

	/////////////////////////////////////////////////////////
	// Match

	// Lu_Wave m_wave = lu_wave__create_match_wave(brain);

	// 	// TEST_ASSERT(m_wave);
	// 	// TEST_ASSERT(lu_wave__get_id(m_wave) == 1);
	// 	// TEST_ASSERT(lu_brain__get_wave_by_id(brain, lu_wave__get_id(m_wave)) == m_wave);

	// 	lu_wave__push(m_wave, rec_0, data_0);

	// 	lu_wave__block_begin(m_wave);
	// 	lu_wave__push(m_wave, rec_0, data_01);
	// 	lu_wave__push(m_wave, rec_1, data_2);
	// 	lu_wave__block_end(m_wave);

	// 	lu_wave__push(m_wave, rec_0, data_3);

	// lu_wave__process(m_wave, lu_process_config__get_by_id(LU_PROCESS__MATCH_DIFF_ONLY));

	// 	lu_wave__block_begin(m_wave);
	// 	lu_wave__push(m_wave, rec_0, data_4);
	// 	lu_wave__push(m_wave, rec_1, data_5);
	// 	lu_wave__block_end(m_wave); 

	// lu_wave__step(m_wave, lu_process_config__get_by_id(LU_PROCESS__SAVE_DEFAULT));


	/////////////////////////////////////////////////////////
	// Destroy waves

	// lu_wave__destroy(s_wave); 
	// lu_wave__destroy(m_wave);


	// lu_byte state = 3;
	// lu_value p1 = 0;
	// lu_value p2 = 0;
	// lu_value p3 = 0;

	// state == 1 && (p1 = 0.1);
	// state == 2 && (p2 = 0.2);
	// state == 3 && (p3 = 0.3);
	// lu__debug("\n\n %f | %f | %f \n\n", p1, p2, p3);



	/////////////////////////////////////////////////////////
	// Lu_Name

	// Lu_Neuron save_neuron = lu_save_resp_neuron(save_response);

	// Lu_Name apple = lu_name_create(brain);

	// lu_name_give(apple, save_neuron);

	/////////////////////////////////////////////////////////
	// Restore

	// Lu_Restore_Resp lu_restore_resp = lu_seq_restore(brain, save_neuron, restore_opts);

	/////////////////////////////////////////////////////
	// Restore stories by lu_name

}