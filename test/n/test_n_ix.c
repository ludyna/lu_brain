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

union u1 {
	lu_byte pos;
	lu_size ix;
};

void test_string__eq(void) 
{
	union lu_n_ix ix;
	ix.pos = 1;
	ix.ix = 2;

	union u1 u1;
	u1.pos = 1;
	u1.ix = 2;

	lu__debug("\n struct lu_n_ix SIZE: %d", sizeof(union lu_n_ix));
	lu__debug("\n lu_size SIZE: %d", sizeof(lu_size));
	lu__debug("\n union u1 SIZE: %d", sizeof(union u1));

	lu__debug("\n ix.pos = %d", ix.pos);
	lu__debug("\n ix.ix = %d", ix.ix);
	lu__debug("\n ix.value = %d", ix.value);

	lu__debug("\n u1.pos = %d", u1.pos);
	lu__debug("\n u1.ix = %d", u1.ix);

	TEST_ASSERT(ix.pos == 1);
	TEST_ASSERT(ix.ix == 2);
	TEST_ASSERT(ix.value == 33);

}





