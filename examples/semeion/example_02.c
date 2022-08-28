/**
	Copyright © 2022 Oleh Ihorovych Novosad 

	WARNING: not working at this moment, WORK IN PROGRESS

	Execute with 
	$  clear && printf '\e[3J'; rm ./build/semeion; gcc -g -Wall -Wno-unused-function -Wno-unused-value example_01.c -o ./build/semeion -lm; ./build/semeion 

	Flags:
	-Wno-unused-function - to not show warning about unused functions
	-Wno-unused-value - to not show warning about unused values
	
	DESCRIPTION:

*/

#include <stdio.h>
#include "semeion.h"
#include "semeion.c"

#define LU_EX__GREETING_SIZE 2000

int main()
{
	char command[120];
	char token_1[30];
	char token_2[30];
	char token_3[30];
	char greeting[LU_EX__GREETING_SIZE];

	FILE *fp = fopen("example_02_greeting.txt", "r");
	if (fp != NULL) {
	    size_t newLen = fread(greeting, sizeof(char), LU_EX__GREETING_SIZE, fp);
	    if ( ferror( fp ) != 0 ) {
	        fputs("Error reading file", stderr);
	    } else {
	        greeting[newLen++] = '\0'; /* Just to be safe. */
	    }

	    fclose(fp);
	}

	printf("\n%s\n", greeting);

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

		if (strcmp(token_1, "learn") == 0)
		{

		} else if (strcmp(token_1, "match") == 0)
		{

		} else if (strcmp(token_1, "delete") == 0)
		{

		} else if (strcmp(token_1, "restore") == 0)
		{

		} else if (strcmp(token_1, "exit") == 0)
		{

		}
		else 
		{
			printf("Unknown command.");
		}


	} while(strcmp(token_1, "exit") != 0);

	printf("\n");
}

