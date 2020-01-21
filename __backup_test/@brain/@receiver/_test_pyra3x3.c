#include "unity.h"

// Global
#include "global/debug.h"

// Util and types
#include "lib/utils.h"
#include "lib/arr.h"
#include "lib/arr2.h"
#include "lib/sis_alloc.h"

// Public
#include "lu_brain.h"

// Elements
#include "@brain/net/neu.h"
#include "@brain/net/neu_iters.h"
#include "@brain/net/lin.h"
#include "@brain/net/linkage.h"
#include "@brain/net/waves/save_wave.h"

// Core
#include "@brain/core/processor.h"
#include "@brain/core/core.h"

// Receiver
#include "@brain/@receiver/pyra_layer.h"
#include "@brain/@receiver/pyra.h"



void setUp(void)
{
}

void tearDown(void)
{
}

void test_pyra3x3_1(void)
{
	// Core core = core_create_for_test();

	// struct pyra_args args =
	// {
	// 	.width 			= 3, 
	// 	.height 		= 3, 
	// 	.core 			= core, 
	// 	.step_norm_dist = 0.01
	// };

	// Pyra pyra = pyra_create(&args);

	// Neu a = core_neu_alloc(core);
	// Neu p1 = core_neu_alloc(core);
	// Neu p2 = core_neu_alloc(core);
	// Neu p3 = core_neu_alloc(core);
	// Neu p4 = core_neu_alloc(core);
	// Neu p5 = core_neu_alloc(core);
	// Neu p6 = core_neu_alloc(core);
	// Neu p7 = core_neu_alloc(core);
	// Neu p8 = core_neu_alloc(core);
	// Neu p9 = core_neu_alloc(core);

	// neu_inc_count(p1);
	// neu_inc_count(p2); 
	// neu_inc_count(p3);
	// neu_inc_count(p4);
	// neu_inc_count(p5);
	// neu_inc_count(p6); 
	// neu_inc_count(p7);
	// neu_inc_count(p8);
	// neu_inc_count(p9);

	// pyra_cell_init(pyra, 0, 0, p1);
	// pyra_cell_init(pyra, 1, 0, p2);
	// pyra_cell_init(pyra, 2, 0, p3);

	// pyra_cell_init(pyra, 0, 1, p4);
	// pyra_cell_init(pyra, 1, 1, p5);
	// pyra_cell_init(pyra, 2, 1, p6);

	// pyra_cell_init(pyra, 0, 2, p7);
	// pyra_cell_init(pyra, 1, 2, p8);
	// pyra_cell_init(pyra, 2, 2, p9);

	// Neu res1 = pyra_save(pyra);

	// TEST_ASSERT(res1 != NULL);

	// lu_debug("\nRes neu: ");
	// neu_debug(res1);

	// pyra_destroy(&pyra);

	// ////////////////////////////////////////////////////////////////////////////////
	// // Second time 

	// pyra = pyra_create(&args);

	// pyra_cell_init(pyra, 0, 0, p1);
	// pyra_cell_init(pyra, 1, 0, p2);
	// pyra_cell_init(pyra, 2, 0, p3);

	// pyra_cell_init(pyra, 0, 1, p4);
	// pyra_cell_init(pyra, 1, 1, p5);
	// pyra_cell_init(pyra, 2, 1, p6);

	// pyra_cell_init(pyra, 0, 2, p7);
	// pyra_cell_init(pyra, 1, 2, p8);
	// pyra_cell_init(pyra, 2, 2, p9);
	// Neu res2 = pyra_save(pyra);

	// TEST_ASSERT(res2 != NULL);

	// lu_debug("\nRes neu: ");
	// neu_debug(res2);

	// TEST_ASSERT(res1 == res2);

	// pyra_destroy(&pyra);
	// core_destroy(&core);
}


void test_pyra3x3_2(void)
{
	// Core core = core_create_for_test();
	
	// struct pyra_args args =
	// {
	// 	.width 			= 3, 
	// 	.height 		= 3, 
	// 	.core 			= core, 
	// 	.step_norm_dist = 0.01
	// };

	// Pyra pyra = pyra_create(&args);

	// Neu a = core_neu_alloc(core);
	// Neu p1 = core_neu_alloc(core);
	// Neu p2 = core_neu_alloc(core);
	// Neu p3 = core_neu_alloc(core);
	// Neu p4 = core_neu_alloc(core);
	// Neu p5 = core_neu_alloc(core);
	// Neu p6 = core_neu_alloc(core);
	// Neu p7 = core_neu_alloc(core);
	// Neu p8 = core_neu_alloc(core);
	// Neu p9 = core_neu_alloc(core);
	// Neu p10 = core_neu_alloc(core);

	// neu_inc_count(p1);
	// neu_inc_count(p2); 
	// neu_inc_count(p3);
	// neu_inc_count(p4);
	// neu_inc_count(p5);
	// neu_inc_count(p6); 
	// neu_inc_count(p7);
	// neu_inc_count(p8);
	// neu_inc_count(p9);

	// pyra_cell_init(pyra, 0, 0, p1);
	// pyra_cell_init(pyra, 1, 0, p2);
	// pyra_cell_init(pyra, 2, 0, p3);

	// pyra_cell_init(pyra, 0, 1, p4);
	// pyra_cell_init(pyra, 1, 1, p5);
	// pyra_cell_init(pyra, 2, 1, p6);

	// pyra_cell_init(pyra, 0, 2, p7);
	// pyra_cell_init(pyra, 1, 2, p8);
	// pyra_cell_init(pyra, 2, 2, p9);

	// Neu res1 = pyra_save(pyra);

	// TEST_ASSERT(res1 != NULL);

	// lu_debug("\nRes neu: ");
	// neu_debug(res1);

	// pyra_destroy(&pyra);

	// ////////////////////////////////////////////////////////////////////////////////
	// // Second time 

	// pyra = pyra_create(&args);

	// pyra_cell_init(pyra, 0, 0, p1);
	// pyra_cell_init(pyra, 1, 0, p2);
	// pyra_cell_init(pyra, 2, 0, p3);

	// pyra_cell_init(pyra, 0, 1, p4);
	// pyra_cell_init(pyra, 1, 1, p5);
	// pyra_cell_init(pyra, 2, 1, p6);

	// pyra_cell_init(pyra, 0, 2, p7);
	// pyra_cell_init(pyra, 1, 2, p8);
	// pyra_cell_init(pyra, 2, 2, p10);
	// Neu res2 = pyra_save(pyra);

	// TEST_ASSERT(res2 != NULL);

	// lu_debug("\nRes neu: ");
	// neu_debug(res2);

	// TEST_ASSERT(res1 != res2);

	// pyra_destroy(&pyra);
	// core_destroy(&core);
}