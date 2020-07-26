/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

#include "semeion.h"
#include "semeion.c"

///////////////////////////////////////////////////////////////////////////////
// Execute with 
// $  clear && printf '\e[3J'; rm semeion; gcc -g main.c -o semeion -lm; ./semeion

int main()
{
	// Radomize rand() with time

	srand(time(0));

	// Load data into memory  

	smn_data_load();

	// Select random samples

	smn_data_samples_create();

    // Create brain and related

	Lu_Brain_Opts brain_opts 	= lu_brain_opts_create(1, 1024 * 1024);
	Lu_Rec_Opts rec_opts 		= lu_rec_opts_create(
		brain_opts,
		16,
		16,
		1,
		2,
		0.0,
		1.0,
		2
	);
	Lu_Brain brain 				= lu_brain_create(brain_opts);
	Lu_Wave wave 				= lu_wave_create(brain);
	Lu_Story story 				= lu_story_create(brain, 1);
	Lu_Rec rec_0 				= lu_brain_rec_get(brain, 0);
	Lu_Wave_Mem	wave_mem 		= NULL;
	Lu_Neu name 				= NULL;
 
	// Show random digit

	printf("\nRandom sample:");
	Smn_Digit digit = &smn_data[rand_in_range(0, (int) smn_data_count)];
	smn_digit_print(digit);

	// Training samples

	size_t i;
	Smn_Digit d;
	
	printf("\n");
	printf("\rTraining samples..");
	for (i = 0; i < smn_training_samples_count; i++)
	{
		d = smn_training_samples[i];

		lu_story_push(story, rec_0, d->pixels);
		lu_wave_save_with_name(wave, story, d->name);
		lu_story_reset(story);

		printf("\rTraining samples.. %lu trained.", i+1);
		fflush(stdout);
	}
	printf("\n");

	// Testing samples
	
	float failed_count = 0;
	float success_count = 0;

	printf("\rTesting samples.. ");
	for (i = 0; i < smn_test_samples_count; i++)
	{
		d = smn_test_samples[i];
		lu_story_push(story, rec_0, d->pixels);
		wave_mem = lu_wave_find(wave, story);

		name = lu_wave_mem_name_neu(wave_mem);

		if (name && lu_neu_name_get(name) == d->name)
			++success_count;
		else 
			++failed_count;

		lu_story_reset(story);

		printf("\rTesting samples.. %lu tested.", i + 1);
		fflush(stdout);
	}
	printf("\n");

	printf("\nReport:");
	printf("\n 	  Successfully recognized: %d", (int) success_count);
	printf("\n 	  Failed recognition: %d", (int) failed_count);
	printf("\n 	  Success rate: %f", success_count / (lu_value) smn_test_samples_count);
	printf("\n\n");

	// Destroy brain and related  

	lu_story_destroy(story);
	lu_wave_destroy(wave);
	lu_brain_destroy(brain);
	lu_brain_opts_destroy(brain_opts);

	// Clean up memory for data

	smn_data_samples_free();
	smn_data_free();

	// Exit app

	exit(EXIT_SUCCESS);
}

