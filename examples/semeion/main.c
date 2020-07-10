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

	Lu_Brain_Opts brain_opts 			= lu_brain_opts_create(1, 200 * 1024);
 
	// 

	Smn_Digit digit = &smn_data[rand_in_range(0, (int) smn_data_count)];
	smn_digit_print(digit);

	// Destroy brain and related  

	lu_brain_opts_destroy(brain_opts);

	// Clean up memory for data

	smn_data_samples_free();
	smn_data_free();

	// Exit app

	exit(EXIT_SUCCESS);
}

