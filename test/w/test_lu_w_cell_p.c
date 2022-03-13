/**
	Copyright © 2022 Oleh Ihorovych Novosad 

	test_lu_brain tests public interfaces (from library user point of view) and includes 
	general integration tests. It uses nouns with Lu_ prefix only and methods with lu_ prefixes 
	only.
*/

#include "unity.h"
#include "lib/_module.h"


// setUp is executed for each test, even if test does nothing
void setUp(void)
{ 

}

void tearDown(void)
{	

}

void test_lu_brain_basics(void) 
{ 
	// lu_byte state = 3;
	// lu_value p1 = 0;
	// lu_value p2 = 0;
	// lu_value p3 = 0;

	// state == 1 && (p1 = 0.1);
	// state == 2 && (p2 = 0.2);
	// state == 3 && (p3 = 0.3);
	// lu__debug("\n\n %f | %f | %f \n\n", p1, p2, p3);

	struct lu_w_cell_p cell_data;

	Lu_W_Cell_P cell = &cell_data;

	cell->state = 33;
	cell->p1 = 333;
	cell->p2 = 333;

	lu_w_cell_p__register(cell, 1, .2, NULL);
	TEST_ASSERT(cell->p1 == .2);

	lu_w_cell_p__register(cell, 1, .3, NULL);
	TEST_ASSERT(cell->p1 == .3);
	TEST_ASSERT(cell->state == LU_W_CELL_P__STATE_ONE);

	lu_w_cell_p__register(cell, 0, .4, NULL);
	TEST_ASSERT(cell->p1 == .3);
	TEST_ASSERT(cell->p2 == .4);
	TEST_ASSERT(cell->state == LU_W_CELL_P__STATE_READY);

	TEST_ASSERT(lu_w_cell_p__is_ready(cell) == true);

	lu_w_cell_p__register(cell, 1, .5, NULL);
	TEST_ASSERT(cell->p1 == .5);
	TEST_ASSERT(cell->p2 == .4);
	TEST_ASSERT(lu_w_cell_p__is_ready(cell) == false);

	lu_w_cell_p__register(cell, 0, .6, NULL);
	TEST_ASSERT(cell->p1 == .5);
	TEST_ASSERT(cell->p2 == .6);
	TEST_ASSERT(lu_w_cell_p__is_ready(cell) == true);
}