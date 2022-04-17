/**
	Copyright © 2022 Oleh Ihorovych Novosad 

	NOTE: not working at this moment, WORK IN PROGRESS

	Execute with 
	$  clear && printf '\e[3J'; rm ./build/semeion; gcc -g -Wall -Wno-unused-function -Wno-unused-value main.c -o ./build/semeion -lm; ./build/semeion 

	Flags:
	-Wno-unused-function - to not show warning about unused functions
	-Wno-unused-value - we have unused vaues because some pieces of code it

*/

#include "semeion.h"
#include "semeion.c"

int main()
{
	Lu_Mem_Debugger md = lu_mem_debugger__create(lu_g_mem);

	// Radomize rand() with time

	srand(time(0));

	// Init samples

	smn_groups_init();

	// Load data into memory  

	smn_data_load();

	// Allocate data for groups and fill groups with samples

	smn_groups_data_alloc();
	smn_groups_data_fill();

	// Select random samples from group

	smn_data_samples_create();

	// Create brain and related

	Lu_Brain brain = lu_brain__create(lu_config__get_by_id(LU_CONFIG__DEFAULT));
	lu__assert(brain);
	
	Lu_Rec image_rec = lu_brain__rec_add(
		/*belongs to*/			brain, 
		/*width*/				16, 
		/*height*/				16, 
		/*depth*/				1,
		/*predefined config */ 	lu_rec_config__get_by_id(LU_REC__MONO1_IMAGE)
	);	
	lu__assert(image_rec);

	// After we added all recs we need to build/rebuild brain
	lu_brain__build(brain);

	// Create save_wave
	
	Lu_Wave save_wave = lu_wave__create_save_wave(brain);
	lu__assert(save_wave);  

	Lu_Wave match_wave = lu_wave__create_match_wave(brain);
	lu__assert(match_wave);

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

	//for (i = 0; i < smn_training_samples_count; i++)
	for (i = 0; i < 1; i++)
	{
		d = smn_training_samples[i];

		lu_wave__push(save_wave, image_rec, d->pixels);
		//lu_wave_save_with_name(save_wave, seq, d->name); 
		lu_wave__process(save_wave, lu_process_config__get_by_id(LU_PROCESS__SAVE_DEFAULT));

		printf("\rTraining samples.. %lu trained.", i + 1);
		fflush(stdout);
	}
	printf("\n");

	// Testing samples
	
	float failed_count 		= 0;
	float success_count 	= 0;

	printf("\rTesting samples.. ");

	//for (i = 0; i < smn_test_samples_count; i++)
	for (i = 0; i < 1; i++)
	{
		d = smn_test_samples[i];
		lu_wave__push(match_wave, image_rec, d->pixels);

		// name = lu_wave_top_name_get(save_wave);

		// if (name && lu_neu_name_get(name) == d->name)
		// 	++success_count;
		// else 
		// 	++failed_count;

		// lu_data_seq__reset(seq);

		// printf("\rTesting samples.. %lu tested.", i + 1);
		// fflush(stdout);
	}
	printf("\n");

	printf("\nReport:");
	printf("\n 	  Successfully recognized: %d", (int) success_count);
	printf("\n 	  Failed recognition: %d", (int) failed_count);
	printf("\n 	  Success rate: %f", success_count / (lu_value) smn_test_samples_count);
	printf("\n\n");

	// Destroy save_wave and brain

	lu_wave__destroy(match_wave);
	lu_wave__destroy(save_wave);
	lu_brain__destroy(brain);

	// Clean up memory for data

	smn_data_samples_free();
	smn_groups_data_free();
	smn_data_free();

	// Exit app

	lu_mem_debugger__print(md);
	lu_mem_debugger__destroy(md, true);

	exit(EXIT_SUCCESS);
}

