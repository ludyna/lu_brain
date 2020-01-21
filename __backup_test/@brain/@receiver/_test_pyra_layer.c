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



void setUp(void)
{
}

void tearDown(void)
{
}

void test_pyra_layer1(void)
{
	// Core core = core_create_for_test();

	// struct pyra_layer_args args = 
	// {
	// 	.width 			= 2,
	// 	.height 		= 2,
	// 	.core 			= core,
	// 	.step_norm_dist = 0.05
	// };

	// PyraLayer bottom 	= pyra_layer_create(&args);
	// PyraLayer top 		= pyra_layer_create(&args);
	// top->width 			= bottom->width - 1;
	// top->height 		= bottom->height - 1;

	// Neu p1 = core_neu_alloc(core);
	// Neu p2 = core_neu_alloc(core);
	// Neu p3 = core_neu_alloc(core);
	// Neu p4 = core_neu_alloc(core);

	// pyra_layer_set(bottom, 0, 0, p1);
	// pyra_layer_set(bottom, 0, 1, p2);
	// pyra_layer_set(bottom, 1, 0, p3);
	// pyra_layer_set(bottom, 1, 1, p4);

	// pyra_layer_save(bottom, top);

	// TEST_ASSERT(pyra_layer_is_apex_reached(top) == true);
	// Neu apex = pyra_layer_apex(top);
	// TEST_ASSERT(apex->count == 4);
	// TEST_ASSERT(apex->p == 0);
	// TEST_ASSERT(core_neu_count(core) == 5);

 // 	pyra_layer_destroy(&top);
	// pyra_layer_destroy(&bottom);
	// core_destroy(&core);
}

void test_pyra_layer2(void)
{
	// Core core = core_create_for_test();

	// struct pyra_layer_args args = 
	// {
	// 	.width 			= 2,
	// 	.height 		= 2,
	// 	.core 			= core,
	// 	.step_norm_dist = 0.05
	// };

	// PyraLayer bottom 	= pyra_layer_create(&args);
	// PyraLayer top 		= pyra_layer_create(&args);
	// top->width 			= bottom->width - 1;
	// top->height 		= bottom->height - 1;

	// Neu p1 = core_neu_alloc(core);
	// Neu p2 = core_neu_alloc(core);
	// Neu p3 = core_neu_alloc(core);
	// Neu p4 = core_neu_alloc(core);
	// Neu a = core_neu_alloc(core);
	// TEST_ASSERT(a != NULL);

	// link_neu(p1, a, core);
	// TEST_ASSERT(p1->l_c != NULL);

	// link_neu(p2, a, core);
	// link_neu(p3, a, core);
	// link_neu(p4, a, core);

	// neu_inc_count(p1);
	// neu_inc_count(p2);
	// neu_inc_count(p3);
	// neu_inc_count(p4);

	// pyra_layer_set(bottom, 0, 0, p1);
	// pyra_layer_set(bottom, 0, 1, p2);
	// pyra_layer_set(bottom, 1, 0, p3);
	// pyra_layer_set(bottom, 1, 1, p4);

	// TEST_ASSERT(p1->l_c != NULL);

	// pyra_layer_save(bottom, top);

	// TEST_ASSERT(pyra_layer_is_apex_reached(top) == true);
	// Neu apex = pyra_layer_apex(top);
	// TEST_ASSERT(a == apex);
	// TEST_ASSERT(apex->count == 4);
	// lu_debug("\nAPEX->P: %f", apex->p);
	// TEST_ASSERT(lu_value_eq(apex->p, 0.0));

	// pyra_layer_save(bottom, top);
	// TEST_ASSERT(pyra_layer_is_apex_reached(top) == true);
	// apex = pyra_layer_apex(top);
	// TEST_ASSERT(a == apex);
	// TEST_ASSERT(apex->count == 4);
	// lu_debug("\nAPEX->P: %f", apex->p);
	// TEST_ASSERT(lu_value_eq(apex->p, 0.0));
	// TEST_ASSERT(core_neu_count(core) == 5);

 // 	pyra_layer_destroy(&top);
	// pyra_layer_destroy(&bottom);
	// core_destroy(&core);
}