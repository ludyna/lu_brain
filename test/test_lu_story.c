/**
	Copyright © 2020 Oleh Ihorovych Novosad 

	test_lu_brain tests public interfaces (from library user point of view) and includes 
	general integration tests. It uses nouns with Lu_ prefix only and methods with lu_ prefixes 
	only.
*/

#include "unity.h"
#include "brain/brain.h"

Lu_Brain 			brain;
Lu_Rec 				rec_0;
Lu_Rec 				rec_1;

Lu_Brain_Config 	brain_config;
Lu_Rec_Opts 		rec_opts_1;
Lu_Rec_Opts 		rec_opts_2;
Lu_Save_Opts		save_opts 		= NULL;
Lu_Find_Opts		find_opts 		= NULL;
Lu_Restore_Opts		restore_opts 	= NULL;

lu_value			data_00[] 		= { 
										0, 0, 0,
										1, 1, 1,
										1, 1, 1
									};
lu_value			data_01[] 		= { 
										1, 0, 0, 
										1, 1, 1,
										1, 1, 1
									};
lu_value			data_02[] 		= { 
										2, 0, 0,
										1, 1, 1,
										1, 1, 1
									};
lu_value			data_03[] 		= { 
										3, 0, 0, 
										1, 1, 1,
										1, 1, 1
									};
lu_value			data_04[] 		= { 
										4, 0, 0, 
										1, 1, 1,
										1, 1, 1
									};
lu_value			data_05[] 		= { 
										5, 0, 0, 
										1, 1, 1,
										1, 1, 1
									};
lu_value			data_06[] 		= { 
										6, 0, 0, 
										1, 1, 1,
										1, 1, 1
									};

lu_value			data_10[] 		= { 
										0, 0, 
										1, 1,
									};
lu_value			data_11[] 		= { 
										1, 0,
										1, 1,
									};
lu_value			data_12[] 		= { 
										2, 0,
										1, 1,
									};
lu_value			data_13[] 		= { 
										3, 0, 
										1, 1,
									};
lu_value			data_14[] 		= { 
										4, 0, 
										1, 1,
									};
lu_value			data_15[] 		= { 
										5, 0, 
										1, 1,
									};
lu_value			data_16[] 		= { 
										6, 0,
										1, 1,
									};


// setUp is executed for each test, even if test does nothing
void setUp(void)
{ 
	brain_config 			= lu_brain_opts_create(1, 200 * 1024);
	rec_opts_1 			= lu_rec_opts_create(
		brain_config, 
		/*w*/				3, 
		/*h*/				3, 
		/*depth*/			1,
		/*block_size*/		10, 
		/*v_min*/ 			0.0, 
		/*v_max*/			10.0, 
		/*v_neu_size*/		10
	);
			
	rec_opts_2 			= lu_rec_opts_create(
		brain_config, 
		/*w*/				2, 
		/*h*/				2, 
		/*depth*/			1,
		/*block_size*/		10, 
		/*v_min*/ 			0.0, 
		/*v_max*/			10.0, 
		/*v_neu_size*/		10
	);
	
	brain 				= lu_brain_create(brain_config);

	TEST_ASSERT(brain);
	TEST_ASSERT(brain->recs);
	TEST_ASSERT(brain->recs->count);

	rec_0 				= lu_brain_rec_get(brain, 0);

	TEST_ASSERT(rec_0);

	rec_1 				= lu_brain_rec_get(brain, 1);

	TEST_ASSERT(rec_1);

	TEST_ASSERT(brain->recs->count);

	save_opts 			= lu_save_opts_create();
}

void tearDown(void)
{	
	lu_save_opts_destroy(save_opts);

	lu_brain_opts_destroy(brain_config);
	lu_brain_destroy(brain);
}

void test_lu_story_1(void)
{ 
	lu_p_value d;
	Lu_Story story = lu_story_create(brain, 0); 

 		TEST_ASSERT(story->y == 0);
 		TEST_ASSERT(lu_story_data_get(story, 0, 0)->values == NULL);
		
	lu_story_push(story, rec_0, data_00);

		d = lu_story_data_get(story, rec_0->id, 0)->values;
		TEST_ASSERT(d[0] == 0);
		TEST_ASSERT(story->y == 0);

	lu_story_push(story, rec_0, data_01);
		TEST_ASSERT(story->y == 1);
	lu_story_push(story, rec_1, data_12);

		TEST_ASSERT(story->y == 1);
		d = lu_story_data_get(story, rec_0->id, story->y)->values;
		TEST_ASSERT(d[0] == 1);
		d = lu_story_data_get(story, rec_1->id, story->y)->values;
		TEST_ASSERT(d[0] == 2);

	lu_block_begin(story);

		TEST_ASSERT(story->y == 1);

	lu_story_push(story, rec_0, data_02);
	
		TEST_ASSERT(story->y == 2);

	lu_story_push(story, rec_1, data_13);
		
		d = lu_story_data_get(story, rec_1->id, story->y)->values;
		TEST_ASSERT(d[0] == 3);

	lu_block_end(story);
		
		TEST_ASSERT(story->y == 2);

	lu_story_push(story, rec_0, data_04);
		
		TEST_ASSERT(story->y == 3);

	Lu_Save_Resp save_response = lu_story_save(story, save_opts); 

		TEST_ASSERT(story->y == 0);

	lu_block_begin(story);
		
		TEST_ASSERT(story->y == 0);

	lu_story_push(story, rec_0, data_05);

		TEST_ASSERT(story->y == 0);
		TEST_ASSERT(story->blocks_count == 1);

	lu_story_push(story, rec_1, data_16);

		TEST_ASSERT(story->y == 0);
		TEST_ASSERT(story->blocks_count == 1);

	lu_block_end(story);

		TEST_ASSERT(story->y == 0);
		TEST_ASSERT(story->blocks_count == 1);

	lu_story_destroy(story);
}

void test_lu_story_2(void)
{ 
	lu_p_value d;
	Lu_Story story = lu_story_create(brain, 0); 
	lu_block_begin(story);
	lu_block_begin(story);
	lu_block_begin(story);

 		TEST_ASSERT(story->y == 0);
 		TEST_ASSERT(lu_story_data_get(story, 0, 0)->values == NULL);
	
	lu_block_end(story);
		TEST_ASSERT(story->y == 0);
	lu_block_end(story);
	lu_story_push(story, rec_0, data_00);
	lu_block_begin(story);
	lu_block_begin(story);

		d = lu_story_data_get(story, rec_0->id, 0)->values;
		TEST_ASSERT(d[0] == 0);
		TEST_ASSERT(story->y == 0);

	lu_story_destroy(story);
}

void test_lu_story_data(void)
{
	lu_p_value d;
	Data data;
	Lu_Story story = lu_story_create(brain, 0); 

 		TEST_ASSERT(story->y == 0);

 		data = lu_story_data_get(story, 0, 0);

 		TEST_ASSERT(data->values == NULL);
 		TEST_ASSERT(data->w == 0);
 		TEST_ASSERT(data->h == 0);

 		 data = lu_story_data_get(story, 0, 1);

 		TEST_ASSERT(data->values == NULL);
 		TEST_ASSERT(data->w == 0);
 		TEST_ASSERT(data->h == 0);
		
	lu_story_push(story, rec_0, data_00);
 		TEST_ASSERT(story->y == 0);
		
		data = lu_story_data_get(story, 0, 0);
		
		TEST_ASSERT(data->values);
		TEST_ASSERT(data->values[0] == 0);
		TEST_ASSERT(data->w == 3);
 		TEST_ASSERT(data->h == 3);
		
	lu_story_push(story, rec_1, data_16);
 		
 		TEST_ASSERT(story->y == 0);
		
		data = lu_story_data_get(story, 1, 0);
		
		TEST_ASSERT(data->values);
		TEST_ASSERT(data->values[0] == 6);
		TEST_ASSERT(data->w == 2);
 		TEST_ASSERT(data->h == 2);
		
	data = lu_story_data_get(story, 0, 1);
	TEST_ASSERT(data);
	TEST_ASSERT(data->values == NULL);


	lu_story_destroy(story);
}