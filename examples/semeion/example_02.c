/**
	Copyright © 2022 Oleh Ihorovych Novosad 

	Lu Brain Example 02

	WARNING: WORK IN PROGRESS

	Execute from file folder:
	$  clear && printf '\e[3J'; rm ./build/semeion; gcc -g -Wall -Wno-unused-function -Wno-unused-value example_02.c -o ./build/semeion -lm; ./build/semeion 

	parts:
		clear && printf '\e[3J';   - this is just to clear screen (optional)
		rm ./build/semeion; - this is to delete previous executable to make sure we run new one (optional)
		gcc ... - and this is to complile this file using gcc compiler (required)

	Flags:
	-Wno-unused-function - to not show warning about unused functions
	-Wno-unused-value - to not show warning about unused values
	
	DESCRIPTION:

*/

#include "semeion.h"
#include "semeion.c" 
#include "brain_and_waves.h"
 
static inline void le_print_training(clock_t start, clock_t end)
{
 	double time_taken = (double)(end - start) / (double)(CLOCKS_PER_SEC);

	printf(
		"\nTraining of %ld samples in a single thread without hardware acceleration took %.1f sec\n", 
		smn_training_samples_count, 
		time_taken
	);
}

int main()
{
	char command[120];
	char token_1[30];
	char token_2[30];
	char token_3[30];
	char greeting[LE__GREETING_SIZE];

	//
	// Show greeting and command list
	// 

	FILE *fp = fopen("example_02_greeting.txt", "r");
	if (fp != NULL) {
	    size_t newLen = fread(greeting, sizeof(char), LE__GREETING_SIZE, fp);
	    if ( ferror( fp ) != 0 ) {
	        fputs("Error reading file", stderr);
	    } else {
	        greeting[newLen++] = '\0'; /* Just to be safe. */
	    }

	    fclose(fp);
	}

	printf("\n%s\n", greeting);

	//
	// Load and prepare samples
	//

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

	// Create brain and waves

	le_brain_and_waves__create();

	printf("\n");

	enum le_set_type set_type;
	int sample;

	// clock_t start;
	// clock_t end;
	// double time_taken;

	do {
		
		//
		// Reset command and tokens
		//
		command[0] = 0;
		token_1[0] = 0;
		token_2[0] = 0;
		token_3[0] = 0;

		printf("\ninput> ");
		fgets(command, 120, stdin);
		sscanf(command, "%30s %30s %30s", token_1, token_2, token_3);
		// printf("Tokens: %s, %s, %s", token_1, token_2, token_3); 

		if (strcmp(token_1, "exit") == 0)
		{
			break;
		}

		if (strcmp(token_1, "learn") == 0)
		{
			set_type = le_token__to_type(token_2);
			sample = le_token__to_num(token_3);

			le_user_action__learn(set_type, sample);
		} 
		else if (strcmp(token_1, "show") == 0)
		{
			set_type = le_token__to_type(token_2);
			sample = le_token__to_num(token_3);

			le_user_action__show(set_type, sample);
		}
		else if (strcmp(token_1, "match") == 0)
		{
			set_type = le_token__to_type(token_2);
			sample = le_token__to_num(token_3);

			le_user_action__match(set_type, sample);
		} 
		else if (strcmp(token_1, "delete") == 0)
		{
			sample = le_token__to_num(token_2);
			le_user_action__delete(sample);
		} 
		else if (strcmp(token_1, "restore") == 0)
		{
			sample = le_token__to_num(token_2);
			le_user_action__restore(sample);
		} 
		else if (strcmp(token_1, "net_stats") == 0)
		{
			lu_brain__print_net_stats(le_brain);
		}
		else if (strcmp(token_1, "reset") == 0)
		{
			le_brain_and_waves__destroy();
			le_brain_and_waves__create();
			printf("Lu_Brain was reset.");
		}
	    else if (strcmp(token_1, "help") == 0)
	    {
	    	printf("Not implemented yet.");
	    }
		else if (strcmp(token_1, "mem_stats") == 0)
		{
			lu_mem_debugger__print_stats(md);
		}
		else 
		{
			printf("Unknown command.");
		}


	} while(strcmp(token_1, "exit") != 0);

	printf("\n");


	//
	// Destroy brain and waves
	// 

	le_brain_and_waves__destroy();

	//
	// Clean up memory for data
	//

	smn_data__samples_free();
	smn_groups__data_free();
	smn_data__free();

	//
	// Exit app
	//

	lu_mem_debugger__destroy(md, true);

	exit(EXIT_SUCCESS);
}


