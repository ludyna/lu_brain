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
	union lu_n_addr a1[] = {{.value = 12}, {.value = 13}, {.value = 0}};
	union lu_n_addr  b1[] = {{.value = 12}, {.value = 13}, {.value = 0}};

	lu_n_str__print(a1);

	TEST_ASSERT( lu_n_str__eq(a1, b1) );

	union lu_n_addr a2[] = {{.value = 0}};
	union lu_n_addr b2[] = {{.value = 12}, {.value = 13}, {.value = 0}};

	TEST_ASSERT( lu_n_str__eq(a2, b2) == false );

	union lu_n_addr a3[] = {{.value = 12}, {.value = 13}, {.value = 0}};
	union lu_n_addr b3[] = {{.value = 0}};

	TEST_ASSERT( lu_n_str__eq(a3, b3) == false );

	union lu_n_addr a4[] = {{.value = 0}};
	union lu_n_addr b4[] = {{.value = 0}};

	TEST_ASSERT( lu_n_str__eq(a4, b4) );

	union lu_n_addr a5[] = {{.value = 12}, {.value = 13}, {.value = 0}};
	union lu_n_addr b5[] = {{.value = 12}, {.value = 13}, {.value = 1}};

	TEST_ASSERT( lu_n_str__eq(a5, b5) == false );
}

void test_string__copy(void) 
{
	union lu_n_addr a1[10];
	union lu_n_addr b1[] = {{.value = 12}, {.value = 13}, {.value = 0}};

	lu_n_str__copy(a1, b1);

	lu_n_str__print(a1);

	TEST_ASSERT( lu_n_str__eq(a1, b1) );

	union lu_n_addr a2[10] = {{.value = 0}};
	union lu_n_addr b2[] = {{.value = 0}};

	lu_n_str__copy(a2, b2);

	TEST_ASSERT( lu_n_str__eq(a2, b2) );

	union lu_n_addr a3[] = {{.value = 12}, {.value = 13}, {.value = 0}};
	union lu_n_addr b3[] = {{.value = 0}};

	lu_n_str__copy(a3, b3);

	TEST_ASSERT( lu_n_str__eq(a3, b3) );

	union lu_n_addr a4[10] = {{.cell_ix = 12, .layer_ix = 1}, {.value = 13}, {.value = 0}};
	union lu_n_addr b4[] = {{.value = 12}, {.value = 13}, {.value = 0}};

	lu_n_str__copy(a4, b4);

	TEST_ASSERT( lu_n_str__eq(a4, b4) );
}





