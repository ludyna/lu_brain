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

void test_string__eq(void) 
{
	lu_size a1[] = {12, 13, 0};
	lu_size b1[] = {12, 13, 0};

	TEST_ASSERT( lu_n_str__eq(a1, b1) );

	lu_size a2[] = {0};
	lu_size b2[] = {12, 13, 0};

	TEST_ASSERT( lu_n_str__eq(a2, b2) == false );

	lu_size a3[] = {12, 13, 0};
	lu_size b3[] = {0};

	TEST_ASSERT( lu_n_str__eq(a3, b3) == false );

	lu_size a4[] = {0};
	lu_size b4[] = {0};

	TEST_ASSERT( lu_n_str__eq(a4, b4) );

	lu_size a5[] = {12, 13, 0};
	lu_size b5[] = {12, 13, 1};

	TEST_ASSERT( lu_n_str__eq(a5, b5) == false );
}

void test_string__copy(void) 
{
	lu_size a1[10];
	lu_size b1[] = {12, 13, 0};

	lu_n_str__copy(a1, b1);

	lu_n_str__print(a1);

	TEST_ASSERT( lu_n_str__eq(a1, b1) );

	lu_size a2[10] = {0};
	lu_size b2[] = {0};

	lu_n_str__copy(a2, b2);

	TEST_ASSERT( lu_n_str__eq(a2, b2) );

	lu_size a3[] = {12, 13, 0};
	lu_size b3[] = {0};

	lu_n_str__copy(a3, b3);

	TEST_ASSERT( lu_n_str__eq(a3, b3) );

	lu_size a4[10] = {12, 13, 0};
	lu_size b4[] = {12, 13, 1};

	lu_n_str__copy(a4, b4);

	TEST_ASSERT( lu_n_str__eq(a4, b4) );
}





