/**
	Copyright © 2022 Oleh Ihorovych Novosad 

	test_lu_brain tests public interfaces (from library user point of view) and includes 
	general integration tests. It uses nouns with Lu_ prefix only and methods with lu_ prefixes 
	only.
*/

#include "unity.h"
#include "lib/_module.h"

Mem_Debugger 		md;
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
	md = mem_debugger_create(lu_g_mem);

	brain 				= lu_brain__create(lu_g_mem, lu_config__get_by_id(LU_BC_DEFAULT));
	TEST_ASSERT(brain);
	TEST_ASSERT(brain->recs);

	rec_0 				= lu_brain__rec_add(
		/*belongs to*/			brain, 
		/*width*/				3, 
		/*height*/				3, 
		/*depth*/				1,
		/*config*/ 				lu_rec_config__get_by_id(LU_RC_TEST1)
	);	
	TEST_ASSERT(rec_0);

	rec_1 				= lu_brain__rec_add(
		/*belongs to*/			brain, 
		/*width*/				3, 
		/*height*/				3, 
		/*depth*/				1,
		/*config*/ 				lu_rec_config__get_by_id(LU_RC_TEST1)
	);	
	TEST_ASSERT(rec_1);
	
	TEST_ASSERT(brain->recs->count);

	lu_brain__build(brain);
}

void tearDown(void)
{	
	lu_brain__destroy(brain);

	mem_debugger_print(md);

	TEST_ASSERT(mem_debugger_is_all_clear(md));
    mem_debugger_destroy(md, true);
}

void test_lu_brain_basics(void) 
{ 
	/////////////////////////////////////////////////////////
	// Save 

	TEST_ASSERT(brain);
	TEST_ASSERT(brain->recs);

	lu_brain__print_info(brain);

	Lu_Wave wave = lu_save_wave__create(brain); 

		lu_wave__push(wave, rec_0, data_0);

		lu_wave__block_begin(wave);
		lu_wave__push(wave, rec_0, data_01);
		lu_wave__push(wave, rec_1, data_2);
		lu_wave__block_end(wave);

		lu_wave__push(wave, rec_0, data_3);
 
	lu_wave__process(wave, lu_process_config__get_by_id(LU_PCT__SAVE_DEFAULT));

		lu_wave__block_begin(wave);
		lu_wave__push(wave, rec_0, data_4);
		lu_wave__push(wave, rec_1, data_5);
		lu_wave__block_end(wave);

	lu_wave__step(wave, lu_process_config__get_by_id(LU_PCT__SAVE_DEFAULT));

	lu_wave__destroy(wave); 

	/////////////////////////////////////////////////////////
	// Find

	wave = lu_match_wave__create(brain);

			lu_wave__push(wave, rec_0, data_0);

			lu_wave__block_begin(wave);
			lu_wave__push(wave, rec_0, data_01);
			lu_wave__push(wave, rec_1, data_2);
			lu_wave__block_end(wave);

			lu_wave__push(wave, rec_0, data_3);

	lu_wave__process(wave, lu_process_config__get_by_id(LU_PCT__FIND_FULL_CONTRAST));

			lu_wave__block_begin(wave);
			lu_wave__push(wave, rec_0, data_4);
			lu_wave__push(wave, rec_1, data_5);
			lu_wave__block_end(wave); 

	lu_wave__step(wave, lu_process_config__get_by_id(LU_PCT__SAVE_DEFAULT));

	lu_wave__destroy(wave);


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