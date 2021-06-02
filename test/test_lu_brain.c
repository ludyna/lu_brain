/**
	Copyright © 2021 Oleh Ihorovych Novosad 

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

	brain 				= lu_brain_create(lu_brain_config_get_by_id(LU_BC_DEFAULT));
	TEST_ASSERT(brain);
	TEST_ASSERT(brain->recs);

	rec_0 				= lu_rec_create(
		/*belongs to*/			brain, 
		/*width*/				3, 
		/*height*/				3, 
		/*config*/ 				lu_rec_config_get_by_id(LU_RC_TEST1)
	);	
	TEST_ASSERT(rec_0);

	rec_1 				= lu_rec_create(
		/*belongs to*/			brain, 
		/*width*/				3, 
		/*height*/				3, 
		/*config*/ 				lu_rec_config_get_by_id(LU_RC_TEST1)
	);	
	TEST_ASSERT(rec_1);
	
	TEST_ASSERT(brain->recs->count);
}

void tearDown(void)
{	
	lu_rec_destroy(rec_0);
	lu_rec_destroy(rec_1);
	lu_brain_destroy(brain);

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

	lu_brain_print_info(brain);

	Lu_Wave wave = lu_save_wave_create(brain, lu_wave_config_get_by_id(LU_WC_SAVE_DEFAULT)); 

		lu_wave_push(wave, rec_0, data_0);

		lu_wave_block_start(wave);
		lu_wave_push(wave, rec_0, data_01);
		lu_wave_push(wave, rec_1, data_2);
		lu_wave_block_end(wave);

		lu_wave_push(wave, rec_0, data_3);
 
	lu_wave_process(wave);

		lu_wave_block_start(wave);
		lu_wave_push(wave, rec_0, data_4);
		lu_wave_push(wave, rec_1, data_5);
		lu_wave_block_end(wave);

	lu_wave_process(wave);

	lu_wave_destroy(wave); 

	/////////////////////////////////////////////////////////
	// Find

	wave = lu_find_wave_create(brain, lu_wave_config_get_by_id(LU_WC_FIND_FULL_CONTRAST));

			lu_wave_push(wave, rec_0, data_0);

			lu_wave_block_start(wave);
			lu_wave_push(wave, rec_0, data_01);
			lu_wave_push(wave, rec_1, data_2);
			lu_wave_block_end(wave);

			lu_wave_push(wave, rec_0, data_3);

	lu_wave_process(wave);

			lu_wave_block_start(wave);
			lu_wave_push(wave, rec_0, data_4);
			lu_wave_push(wave, rec_1, data_5);
			lu_wave_block_end(wave); 

	lu_wave_process(wave);

	lu_wave_destroy(wave);


	/////////////////////////////////////////////////////////
	// Lu_Name

	// Lu_Neuron save_neuron = lu_save_resp_neuron(save_response);

	// Lu_Name apple = lu_name_create(brain);

	// lu_name_give(apple, save_neuron);

	/////////////////////////////////////////////////////////
	// Restore

	// Lu_Restore_Resp lu_restore_resp = lu_story_restore(brain, save_neuron, restore_opts);

	/////////////////////////////////////////////////////
	// Restore stories by lu_name

}