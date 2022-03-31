/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/

#include "unity.h"
#include "lib/_module.h"


void setUp(void)
{ 

}

void tearDown(void)
{	
}

void test_string_eq(void) 
{
	lu_size a1[] = {12, 13, 0};
	lu_size b1[] = {12, 13, 0};

	TEST_ASSERT( lu_n_string__eq((lu_size*)&a1, (lu_size*)&b1) );

	lu_size a2[] = {0};
	lu_size b2[] = {12, 13, 0};

	TEST_ASSERT( lu_n_string__eq((lu_size*)&a2, (lu_size*)&b2) == false );

	lu_size a3[] = {12, 13, 0};
	lu_size b3[] = {0};

	TEST_ASSERT( lu_n_string__eq((lu_size*)&a3, (lu_size*)&b3) == false );

	lu_size a4[] = {0};
	lu_size b4[] = {0};

	TEST_ASSERT( lu_n_string__eq((lu_size*)&a4, (lu_size*)&b4) );

	lu_size a5[] = {12, 13, 0};
	lu_size b5[] = {12, 13, 1};

	TEST_ASSERT( lu_n_string__eq((lu_size*)&a5, (lu_size*)&b5) == false );
}





