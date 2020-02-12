///////////////////////////////////////////////////////////////////////////////
// EXAMPLES
// 
// Do not compile this file. These are just code snipets of examples.
//
// NOTES:
// 1. Controlling focus is out of scope.
// 2. Process of "naming" is manual by user. "Automatic" naming is out of scope.
//
// Create brain:
// 

Lu_Brain brain = lu_brain_create(opts);

// 
// Create recs:

rec_1 = lu_rec_create(brain, rec_opts_1);
rec_2 = lu_rec_create(brain, rec_opts_2);

//
// Save data:

Lu_Story story = lu_story_create(brain); 

	lu_story_push(story, rec_1, data_0);

	lu_block_begin(story);
	lu_story_push(story, reveiver_1, data_1);
	lu_story_push(story, rec_2, data_2);
	lu_block_end(story);

	lu_story_push(story, rec_1, data_3);

Lu_Save_Response response = lu_story_save(story); 

	lu_block_begin(story);
	lu_story_push(story, reveiver_1, data_4);
	lu_story_push(story, rec_2, data_5);
	lu_block_end(story);

Lu_Wave wave = lu_story_save_async(story);
while (lu_wave_is_working(wave)) sleep(1);
response = (Lu_Save_Response) lu_wave_response(wave);

// Destroy all temporary info associated with story. 
// Does not destroy created related neurons.
lu_story_destroy(&story); 

//
// Find data:

Lu_Story story = lu_story_create(brain); 

	lu_story_push(story, rec_1, data_0);

	lu_block_begin(story);
	lu_story_push(story, reveiver_1, data_1);
	lu_story_push(story, rec_2, data_2);
	lu_block_end(story);

	lu_story_push(story, rec_1, data_3);

Lu_Find_Response response = lu_story_find(story); 

	lu_block_begin(story);
	lu_story_push(story, reveiver_1, data_4);
	lu_story_push(story, rec_2, data_5);
	lu_block_end(story);

Lu_Wave wave = lu_story_find_async(story);
while (lu_wave_is_working(wave)) sleep(1);
response = (Lu_Find_Response) lu_wave_response(wave);

lu_story_destroy(&story);


//
// Restore data:

// Return story info associated with Neto
Lu_Restore_Response response = lu_story_restore(neto); // lu_story_restore_async()

// 
// Name data:

lu_neto_link(neto_dst, neto_src1, neto_src2);

// 
// Destroy brain:

lu_brain_destroy(&brain);
