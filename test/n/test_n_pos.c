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

void test__lu_n_pos(void) 
{
    struct lu_n_pos pos;
    lu_size column_ix;

    pos = lu_n_pos__from_column_ix(119, 10);

    TEST_ASSERT(pos.x == 9);
    TEST_ASSERT(pos.y == 11);

    column_ix = lu_n_pos__to_column_ix(&pos, 10);

    TEST_ASSERT(column_ix == 119);

    pos = lu_n_pos__from_column_ix(34, 5);

    TEST_ASSERT(pos.x == 4);
    TEST_ASSERT(pos.y == 6);

    column_ix = lu_n_pos__to_column_ix(&pos, 5);

    TEST_ASSERT(column_ix == 34);

    column_ix = lu_n_pos__to_column_ix(&pos, 10);

    TEST_ASSERT(column_ix == 64);

    pos.x = 1;
    column_ix = lu_n_pos__to_column_ix(&pos, 2);

    TEST_ASSERT(column_ix == 13);

    pos = lu_n_pos__from_column_ix(13, 2);

    TEST_ASSERT(pos.x == 1);
    TEST_ASSERT(pos.y == 6);

}





