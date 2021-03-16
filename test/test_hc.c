/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

#include "unity.h"

// #include <limits.h> 
#include <stdio.h>
// #include <stdint.h>
// #include <stdlib.h>
// #include <math.h>
// #include <float.h>
// #include <stdarg.h>
#include <string.h>

#include "lib/_module.h"

lu_size boost_combine(lu_size seed, lu_size value)
{
    seed ^= value + 0x9e3779b9 + (seed<<6) + (seed>>2);
    return seed;
}

void setUp(void)
{ 

}

void tearDown(void)
{	

}

void test_1(void) 
{
	lu_size r1 = 0;
	lu_size r2 = 0;

	r1 = boost_combine(r1, 2);
	r1 = boost_combine(r1, 3);

	r2 = boost_combine(r2, 3);
	r2 = boost_combine(r2, 2);

	/* Intializes random number generator */ 
	time_t t;
	srand((unsigned) time(&t));

	printf("\n%lu: %lu, %ld, %ld, %ld", (long unsigned int) -1, r1, r2, (long unsigned int) rand(), r2 % 100);

	//TEST_ASSERT(r1 == r2);

	lu_size arr[100];

	memset(arr, 0, sizeof(arr));

	lu_size x;
	lu_size y;
	lu_size ind;

	for (x = 0; x < 100; x++)
	{
		for (y = 0; y < 100; y++)
		{
			r1 = 0;
			r1 = boost_combine(r1, x + (lu_size) rand());
			r1 = boost_combine(r1, y + 18444073709551615u);

			ind = r1 % 100;
			arr[ind]++;
		}
	}

	for (x = 0; x < 100; x++)
	{
		printf("\n %ld) %ld", x, arr[x]);
	}
}

