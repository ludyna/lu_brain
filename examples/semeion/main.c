/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

#include "semeion.h"
#include "semeion.c"

// gcc -g main.c -o semeion -lm; ./semeion
int main()
{
	// Use current time as  
    // seed for random generator 
    srand(time(0));

	Lu_Brain_Opts brain_opts 			= lu_brain_opts_create(1, 200 * 1024);

	size_t lines_count = smn_data_read(smn_data);

	Smn_Digit digit = &smn_data[rand_in_range(0, (int) lines_count)];
	smn_digit_print(digit);

	lu_brain_opts_destroy(brain_opts);

	if (smn_data) free(smn_data);

	exit(EXIT_SUCCESS);
}

