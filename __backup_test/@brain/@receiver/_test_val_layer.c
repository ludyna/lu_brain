#include "unity.h"

// Global
#include "global/debug.h"

// Util and types
#include "lib/utils.h"
#include "lib/arr.h"
#include "lib/arr2.h"
#include "lib/sis_alloc.h"
#include "lib/rand.h"
#include "lib/lists/ln_alloc.h"
#include "lib/lists/ln_alloc_fast.h"
#include "lib/lists/list.h"
#include "lib/lists/s_list/s_node.h"
#include "lib/lists/s_list/s_list.h"

// Elements
#include "@brain/net/neu.h"
#include "@brain/net/neu_iters.h"
#include "@brain/net/lin.h"
#include "@brain/net/waves/find_wave.h"

// Core
#include "@brain/core/processor.h"
#include "@brain/core/core.h"

#include "@brain/@receiver/val_layer.h"


void setUp(void)
{
}

void tearDown(void)
{
}

void test_lu_value_layer_create_and_destroy(void)
{
    ValLayer layer = val_layer_create(NULL, -1.0, 3.0, 2, 0.1);
    TEST_ASSERT(layer != NULL);

    val_layer_destroy(&layer);
    TEST_ASSERT(layer == NULL);
}

void test_lu_value_layer_math(void)
{
	///////////////////////////////////////////////////////////////////////////
	// Rec 1
	ValLayer layer = val_layer_create(NULL, -1.0, 3.0, 4, 0.4);
    TEST_ASSERT(layer != NULL);
    TEST_ASSERT(lu_value_eq(layer->orig_min_val, -1.0));
    TEST_ASSERT(lu_value_eq(layer->orig_max_val, 3.0));
    TEST_ASSERT(layer->val_neu_size == 4);
    TEST_ASSERT(lu_value_eq(layer->max_val, 4.0));
    TEST_ASSERT(lu_value_eq(layer->val_step, 1.0));
    TEST_ASSERT(layer->ssp_i == 2);

    lu_value val = val_layer_norm(layer, 0.0);
    TEST_ASSERT(lu_value_eq(val, 1.0));

    val = val_layer_norm(layer, -1.0);
	TEST_ASSERT(lu_value_eq(val, 0.0));

	struct lu_size_range r = val_layer_indx_range(layer, val);
	TEST_ASSERT(r.begin == 0);
	TEST_ASSERT(r.end == 2);

	val = val_layer_norm(layer, 1.6);
	TEST_ASSERT(lu_value_eq(val, 2.6));
	
	r = val_layer_indx_range(layer, val);
	TEST_ASSERT(r.begin == 1);
	TEST_ASSERT(r.end == 3);

    val_layer_destroy(&layer);
    TEST_ASSERT(layer == NULL);

	///////////////////////////////////////////////////////////////////////////
	// Rec 2
    layer = val_layer_create(NULL, -1.0, 3.0, 3, 0.4);
    TEST_ASSERT(layer != NULL);
    TEST_ASSERT(lu_value_eq(layer->orig_min_val, -1.0));
    TEST_ASSERT(lu_value_eq(layer->orig_max_val, 3.0));
    TEST_ASSERT(layer->val_neu_size == 3);
    TEST_ASSERT(lu_value_eq(layer->max_val, 4.0));
    //lu_debug("%f\n", layer->val_step);
    TEST_ASSERT(lu_value_eq(layer->val_step, 1.333333));
    //lu_debug("%ld\n", layer->ssp_i);
    TEST_ASSERT(layer->ssp_i == 1);
    TEST_ASSERT(lu_value_eq(val_layer_step_norm_dist(layer), 0.3333));

    val = val_layer_norm(layer, 0.0);
    //lu_debug("%f\n", val);
    TEST_ASSERT(lu_value_eq(val, 1.0));

    val = val_layer_norm(layer, -1.0);
	TEST_ASSERT(lu_value_eq(val, 0.0));

	r = val_layer_indx_range(layer, val);
	// lu_debug("%ld\n", r.begin);
	// lu_debug("%ld\n", r.end);
	TEST_ASSERT(r.begin == 0);
	TEST_ASSERT(r.end == 1);

	val = val_layer_norm(layer, 1.6);
	//lu_debug("%f\n", val);	
	TEST_ASSERT(lu_value_eq(val, 2.6));
	
	r = val_layer_indx_range(layer, val);
	lu_debug("%ld\n", r.begin);
	lu_debug("%ld\n", r.end);
	TEST_ASSERT(r.begin == 1);
	TEST_ASSERT(r.end == 2);

	TEST_ASSERT(lu_value_eq(0.0, layer->val_steps[0]));
	TEST_ASSERT(lu_value_eq(1.33333, layer->val_steps[1]));
	TEST_ASSERT(lu_value_eq(2.66666, layer->val_steps[2]));

	lu_value p = val_layer_calc_potent(layer, 0, 1.0);
	TEST_ASSERT(lu_value_eq(p, 0.75));
	p = val_layer_calc_potent(layer, 1, 1.0);
	TEST_ASSERT(lu_value_eq(p, 0.9166));
	p = val_layer_calc_potent(layer, 2, 1.0);
	TEST_ASSERT(lu_value_eq(p, 0.5833));

    val_layer_destroy(&layer);
    TEST_ASSERT(layer == NULL);
}


