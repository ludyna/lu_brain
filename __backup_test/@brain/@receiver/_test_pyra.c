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

void test_pyra1(void)
{
// 	Core core = core_create_for_test();

// 	struct pyra_args args =
// 	{
// 		.width 			= 2, 
// 		.height 		= 2, 
// 		.core 			= core, 
// 		.step_norm_dist = 0.01
// 	};

// 	Pyra pyra = pyra_create(&args);

// 	Neu a = core_neu_alloc(core);
// 	Neu p1 = core_neu_alloc(core);
// 	Neu p2 = core_neu_alloc(core);
// 	Neu p3 = core_neu_alloc(core);
// 	Neu p4 = core_neu_alloc(core);

// 	TEST_ASSERT(a != NULL);

// 	link_neu(p1, a, core);
// 	TEST_ASSERT(p1->l_c != NULL);

// 	link_neu(p2, a, core);
// 	link_neu(p3, a, core);
// 	link_neu(p4, a, core);

// 	neu_inc_count(p1);
// 	neu_inc_count(p2); 
// 	neu_inc_count(p3);
// 	neu_inc_count(p4);

// 	pyra_cell_init(pyra, 0, 0, p1);
// 	pyra_cell_init(pyra, 1, 0, p2);
// 	pyra_cell_init(pyra, 0, 1, p3);
// 	pyra_cell_init(pyra, 1, 1, p4);

// 	TEST_ASSERT(p1->l_c != NULL);

// 	Neu res = pyra_save(pyra);

// 	TEST_ASSERT(res != NULL);
// 	TEST_ASSERT(res == a);

// 	pyra_destroy(&pyra);

// 	////////////////////////////////////////////////////////////////////////////////
// 	// Second time 

// 	pyra = pyra_create(&args);

// 	pyra_cell_init(pyra, 0, 0, p1);
// 	pyra_cell_init(pyra, 1, 0, p2);
// 	pyra_cell_init(pyra, 0, 1, p3);
// 	pyra_cell_init(pyra, 1, 1, p4);

// 	res = pyra_save(pyra);

// 	TEST_ASSERT(res != NULL);
// 	TEST_ASSERT(res == a);

// 	pyra_destroy(&pyra);
// 	core_destroy(&core);
// }

// void test_pyra_in_space(void)
// {
// 	Core core = core_create_for_test();

// 	struct pyra_args args =
// 	{
// 		.width 			= 2, 
// 		.height 		= 2, 
// 		.core 			= core, 
// 		.step_norm_dist = 0.01
// 	};

// 	Pyra pyra = pyra_create(&args);

// 	Neu a 	= core_neu_alloc(core);
// 	Neu p1 	= core_neu_alloc(core);
// 	Neu p2 	= core_neu_alloc(core);
// 	Neu p3 	= core_neu_alloc(core);
// 	Neu p4 	= core_neu_alloc(core);

// 	TEST_ASSERT(a != NULL);

// 	link_neu(p1, a, core);
// 	link_neu(p2, a, core);
// 	link_neu(p3, a, core);
// 	link_neu(p4, a, core);

// 	neu_inc_count(p1);
// 	neu_inc_count(p2); 
// 	neu_inc_count(p3);
// 	neu_inc_count(p4);

// 	pyra_cell_init(pyra, 0, 0, p1);
// 	pyra_cell_init(pyra, 1, 0, p2);
// 	pyra_cell_init(pyra, 0, 1, p3);
// 	pyra_cell_init(pyra, 1, 1, p4);

// 	TEST_ASSERT(p1->l_c != NULL);

// 	Neu res = pyra_save(pyra);

// 	TEST_ASSERT(res != NULL);
// 	TEST_ASSERT(res == a);

// 	pyra_destroy(&pyra);

// 	////////////////////////////////////////////////////////////////////////////////
// 	// Second time 

// 	pyra = pyra_create(&args);

// 	pyra_cell_init(pyra, 0, 0, p1);
// 	pyra_cell_init(pyra, 1, 0, p2);
// 	pyra_cell_init(pyra, 0, 1, p3);
// 	pyra_cell_init(pyra, 1, 1, p4);

// 	res = pyra_save(pyra);

// 	TEST_ASSERT(res != NULL);
// 	TEST_ASSERT(res == a);

// 	pyra_destroy(&pyra);
// 	core_destroy(&core);
}