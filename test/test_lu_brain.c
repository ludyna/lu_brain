#include "unity.h"
#include "src/brain.h"

Lu_Brain 			brain;
Lu_Rec 				rec_1;
Lu_Rec 				rec_2;

Lu_Brain_Opts 		brain_opts;
Lu_Rec_Opts 		rec_opts_1;
Lu_Rec_Opts 		rec_opts_2;
Lu_Save_Opts		save_opts 		= NULL;
Lu_Find_Opts		find_opts 		= NULL;
Lu_Restore_Opts		restore_opts 	= NULL;

lu_value*			data_0 			= NULL;
lu_value*			data_1 			= NULL;
lu_value* 			data_2 			= NULL;
lu_value* 			data_3 			= NULL;
lu_value* 			data_4 			= NULL;
lu_value* 			data_5 			= NULL; 

void setUp(void)
{ 
	brain_opts 		= brain_opts_create(1, 2048);
	rec_opts_1 		= rec_opts_create(brain_opts, 2, 2, 0.0, 10.0);
	rec_opts_2		= rec_opts_create(brain_opts, 2, 2, 0.0, 10.0);

	brain 			= lu_brain_create(brain_opts);

	rec_1 			= lu_brain_rec_get(brain, 0);
	rec_2 			= lu_brain_rec_get(brain, 1);
}

void tearDown(void)
{	
	brain_opts_destroy(&brain_opts);
	lu_brain_destroy(&brain);
}

void sleep(lu_size t)
{

}

void test_lu_brain_basics(void) 
{
	/////////////////////////////////////////////////////////
	// Save 

	Lu_Story story = lu_story_create(brain); 

		lu_story_push(story, rec_1, data_0);

		lu_block_begin(story);
		lu_story_push(story, rec_1, data_1);
		lu_story_push(story, rec_2, data_2);
		lu_block_end(story);

		lu_story_push(story, rec_1, data_3);

	Lu_Save_Resp save_response = lu_story_save(story, save_opts); 

		lu_block_begin(story);
		lu_story_push(story, rec_1, data_4);
		lu_story_push(story, rec_2, data_5);
		lu_block_end(story);

	Lu_Wave wave = lu_story_save_async(story, save_opts);
	while (lu_wave_is_working(wave)) sleep(1);
	save_response = (Lu_Save_Resp) lu_wave_response(wave);

	// Destroy all temporary info associated with story. 
	// Does not destroy created related neurons.
	lu_story_destroy(&story);  

	/////////////////////////////////////////////////////////
	// Find

	story = lu_story_create(brain); 

		lu_story_push(story, rec_1, data_0);

		lu_block_begin(story);
		lu_story_push(story, rec_1, data_1);
		lu_story_push(story, rec_2, data_2);
		lu_block_end(story);

		lu_story_push(story, rec_1, data_3);

	Lu_Find_Resp find_response = lu_story_find(story, find_opts); 

		lu_block_begin(story);
		lu_story_push(story, rec_1, data_4);
		lu_story_push(story, rec_2, data_5);
		lu_block_end(story);

	wave = lu_story_find_async(story, find_opts);
	while (lu_wave_is_working(wave)) sleep(1);
	find_response = (Lu_Find_Resp) lu_wave_response(wave);

	/////////////////////////////////////////////////////////
	// Name

	Lu_Neto save_neto = lu_save_resp_neto(save_response);

	Lu_Name apple = lu_name_create(brain);

	lu_name_link(apple, save_neto);

	/////////////////////////////////////////////////////////
	// Restore

	Lu_Restore_Resp restore_resp = lu_story_restore(save_neto, restore_opts);

	

}