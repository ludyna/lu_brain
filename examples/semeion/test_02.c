/**
	Copyright © 2022 Oleh Ihorovych Novosad 

	WARNING: not working at this moment, WORK IN PROGRESS

	Execute with 
	$  clear && printf '\e[3J'; rm ./build/semeion; gcc -g -Wall -Wno-unused-function -Wno-unused-value test_02.c -o ./build/semeion -lm; ./build/semeion 

	Flags:
	-Wno-unused-function - to not show warning about unused functions
	-Wno-unused-value - to not show warning about unused values

	DESCRIPTION:
		SMARTER WAY
*/

#include "brain_objects.h"


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

	// Select random samples from each group

	smn_data__samples_create();

	// Get brain config 
	struct lu_config config = lu_config__get_by_id(LU_CONFIG__SEMEION_02);

	config.w_match_sig_breakpoint = 0.4;

	focuses__create(config);

	// Create brain and related

	// Show random digit

	// printf("\nRandom sample:");
	// Smn_Digit digit = &smn_data[smn__rand_in_range(0, (int) smn_data_count)];
	// smn_digit__print(digit);

	// // Training samples

	// size_t i;
	// Smn_Digit d;
	
	// printf("\nTraining %ld samples.. ", smn_training_samples_count);

	// Lu_La_Cell la_cell;
	// clock_t start;
	// clock_t end;
	// start = clock();
	// for (i = 0; i < smn_training_samples_count; i++)
	// {
	// 	d = smn_training_samples[i];

	// 	lu_wave__push(save_wave, image_rec, smn_blank_pixels, 16, 16, 1);
	// 	lu_wave__push(save_wave, image_rec, d->pixels, 16, 16, 1);

	// 	lu_wave__process(save_wave, lu_process_config__get_by_id(LU_PROCESS__SAVE_DEFAULT));

	// 	la_cell = lu_wave__link_to_label(match_wave, 2, 0, 0, 0, d->name);
	// 	lu__assert(la_cell);

	// 	//printf("\nTraining samples.. %lu trained.", i + 1);
	// 	// fflush(stdout);
	// }
	// end = clock();

	// // Calculating total time taken 
 //    double time_taken = (double)(end - start) / (double)(CLOCKS_PER_SEC);

	// printf(
	// 	"\nTraining of %ld samples in a single thread without hardware acceleration took %.1f sec\n", 
	// 	smn_training_samples_count, 
	// 	time_taken
	// );

	// // Show network stats

	// lu_brain__print_net_stats(brain);

	// // Testing samples
	
	// float failed_count 		= 0;
	// float success_count 	= 0;

	// printf("\nTesting samples.. ");

	// Lu_Label* labels = NULL;

	// lu_size samples_to_test = smn_test_samples_count; 
	// for (i = 0; i < smn_test_samples_count; i++)
	// {
	// 	if (i >= smn_test_samples_count) break;

	// 	// d = smn_test_samples[smn__rand_in_range(0, (int) smn_test_samples_count - 1)]; 
	// 	d = smn_test_samples[i];

	// 	printf("\nMATCHING UNTRAINED SAMPLE:");
	// 	smn_digit__print(d);

	// 	lu_wave__push(match_wave, image_rec, smn_blank_pixels, 16, 16, 1);
	// 	lu_wave__push(match_wave, image_rec, d->pixels, 16, 16, 1);

	// 	lu_wave__process(match_wave, lu_process_config__get_by_id(LU_PROCESS__MATCH_DIFF_ONLY));

	// 	labels = lu_wave__get_result_labels(match_wave);

	// 	if (labels)
	// 	{
	// 		if(labels[0])
	// 		{
	// 			lu_wave__print_match_results(match_wave);

	// 			if (lu_label__get_id(labels[0]) == d->name)
	// 			{
	// 				printf("\nRESULT: %ld (SUCCESS)", lu_label__get_id(labels[0]));
	// 				++success_count;
	// 			}
	// 			else
	// 			{
	// 				printf("\nRESULT: %ld (FAILED)", lu_label__get_id(labels[0]));
	// 				++failed_count;
	// 			}
	// 		}
	// 		else
	// 		{
	// 			printf("\nRESULT: no match (FAILED)");
	// 			++failed_count;
	// 		}
	// 	}
	// 	else
	// 	{
	// 		++failed_count;
	// 	}
	// }

	// printf("\nTesting samples.. %lu tested.", i);
	// // fflush(stdout);
	// printf("\n");

	// printf("\nReport:");
	// printf("\n 	  Successfully recognized: %d", (int) success_count);
	// printf("\n 	  Failed recognition: %d", (int) failed_count);
	// printf("\n 	  Accuracy rate: %.2f%%", (success_count / (lu_value) samples_to_test) * 100.0);
	// printf("\n");

	// Destroy save_wave and brain

	// lu_wave__destroy(match_wave);
	// lu_wave__destroy(save_wave);
	// lu_brain__destroy(brain_tl);

	focuses__destroy();

	// Clean up memory for data

	smn_data__samples_free();
	smn_groups__data_free();
	smn_data__free();

	// Exit app

	lu_mem_debugger__print(md);
	lu_mem_debugger__destroy(md, true);

	exit(EXIT_SUCCESS);
}

