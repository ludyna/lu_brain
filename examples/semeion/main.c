/**
	Copyright © 2022 Oleh Ihorovych Novosad 

	WARNING: not working at this moment, WORK IN PROGRESS

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

	smn_groups__init();

	// Load data into memory  

	smn_data__load();

	// Allocate data for groups and fill groups with samples

	smn_groups__data_alloc();
	smn_groups__data_fill();

	// Select random samples from group

	smn_data__samples_create();

	// Create brain and related

	Lu_Brain brain = lu_brain__create(lu_config__get_by_id(LU_CONFIG__SEMEION));
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

	// Show random digit

	printf("\nRandom sample:");
	Smn_Digit digit = &smn_data[smn__rand_in_range(0, (int) smn_data_count)];
	smn_digit__print(digit);

	// Training samples

	size_t i;
	Smn_Digit d;
	
	printf("\nTraining samples.. (total: %ld)", smn_training_samples_count);

	Lu_La_Cell la_cell;
	for (i = 0; i < smn_training_samples_count - 100; i++)
	{
		d = smn_training_samples[i];

		lu_wave__push(save_wave, image_rec, smn_blank_pixels, 16, 16, 1);
		lu_wave__push(save_wave, image_rec, d->pixels, 16, 16, 1);

		lu_wave__process(save_wave, lu_process_config__get_by_id(LU_PROCESS__SAVE_DEFAULT));

		la_cell = lu_wave__link_to_label(match_wave, 2, 0, 0, 0, d->name);
		lu__assert(la_cell);

		//printf("\nTraining samples.. %lu trained.", i + 1);
		// fflush(stdout);
	}
	printf("\n");

	// Show network stast

	lu_brain__print_net_stats(brain);

	// Testing samples
	
	float failed_count 		= 0;
	float success_count 	= 0;

	printf("\nTesting samples.. ");

	Lu_Label* labels = NULL;

	lu_size samples_to_test = 10;  // smn_test_samples_count there is accumulation bug atm, so dont test big numbers
	for (i = 0; i < samples_to_test; i++)
	{
		if (i >= smn_test_samples_count) break;

		d = smn_test_samples[smn__rand_in_range(0, (int) smn_test_samples_count)]; 

		printf("\nMATCHING UNTRAINED SAMPLE:");
		smn_digit__print(d);

		lu_wave__push(match_wave, image_rec, smn_blank_pixels, 16, 16, 1);
		lu_wave__push(match_wave, image_rec, d->pixels, 16, 16, 1);

		lu_wave__process(match_wave, lu_process_config__get_by_id(LU_PROCESS__MATCH_DIFF_ONLY));

		labels = lu_wave__get_result_labels(match_wave);

		if (labels)
		{
			if(labels[0])
			{
				lu_wave__print_match_results(match_wave);

				if (lu_label__get_id(labels[0]) == d->name)
				{
					printf("\nRESULT: %ld (SUCCESS)", lu_label__get_id(labels[0]));
					++success_count;
				}
				else
				{
					printf("\nRESULT: %ld (FAILED)", lu_label__get_id(labels[0]));
					++failed_count;
				}
			}
			else
			{
				printf("\nRESULT: no match (FAILED)");
				++failed_count;
			}
		}
		else
		{
			++failed_count;
		}
	}

	printf("\nTesting samples.. %lu tested.", i);
	// fflush(stdout);
	printf("\n");

	printf("\nReport:");
	printf("\n 	  Successfully recognized: %d", (int) success_count);
	printf("\n 	  Failed recognition: %d", (int) failed_count);
	printf("\n 	  Success rate: %.2f%%", (success_count / (lu_value) samples_to_test) * 100.0);
	printf("\n");

	// Destroy save_wave and brain

	lu_wave__destroy(match_wave);
	lu_wave__destroy(save_wave);
	lu_brain__destroy(brain);

	// Clean up memory for data

	smn_data__samples_free();
	smn_groups__data_free();
	smn_data__free();

	// Exit app

	lu_mem_debugger__print(md);
	lu_mem_debugger__destroy(md, true);

	exit(EXIT_SUCCESS);
}

