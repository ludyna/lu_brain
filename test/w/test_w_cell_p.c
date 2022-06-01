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

lu_size foo()
{
	lu__debug("\n  \n");
	return 25;
}

void test_lu_brain_basics(void) 
{ 
	// lu_byte state = 3;
	// lu_value p_1 = 0;
	// lu_value p_2 = 0;
	// lu_value p3 = 0;

	// state == 1 && (p_1 = 0.1);
	// state == 2 && (p_2 = 0.2);
	// state == 3 && (p3 = 0.3);
	// lu__debug("\n\n %f | %f | %f \n\n", p_1, p_2, p3);

	struct lu_w_save_cell_p cell_data;

	Lu_W_Save_Cell_P cell = &cell_data;

	cell->state = 33;
	cell->p_1 = 333;
	cell->p_2 = 333;

	lu_w_save_cell_p__register(cell, 1, .2, NULL);
	TEST_ASSERT(cell->p_1 == .2);

	lu_w_save_cell_p__register(cell, 1, .3, NULL);
	TEST_ASSERT(cell->p_1 == .3);
	TEST_ASSERT(cell->state == LU_W_SAVE_CELL_P__ONE);

	lu_w_save_cell_p__register(cell, 0, .4, NULL);
	TEST_ASSERT(cell->p_1 == .3);
	TEST_ASSERT(cell->p_2 == .4);
	TEST_ASSERT(cell->state == LU_W_SAVE_CELL_P__READY);

	TEST_ASSERT(lu_w_save_cell_p__is_ready(cell, 0) == true);

	lu_w_save_cell_p__register(cell, 1, .5, NULL);
	TEST_ASSERT(cell->p_1 == .5);
	TEST_ASSERT(cell->p_2 == .4);
	TEST_ASSERT(lu_w_save_cell_p__is_ready(cell, 0) == false);

	lu_w_save_cell_p__register(cell, 0, .6, NULL);
	TEST_ASSERT(cell->p_1 == .5);
	TEST_ASSERT(cell->p_2 == .6);
	TEST_ASSERT(lu_w_save_cell_p__is_ready(cell, 0) == true);

	lu_size a = true && foo();
	TEST_ASSERT(a == true);

	false && foo();
}