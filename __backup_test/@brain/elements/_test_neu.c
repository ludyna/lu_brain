#include "unity.h"

// Global
#include "global/debug.h"

// Util and types
#include "lib/utils.h"
#include "lib/arr.h"
#include "lib/sis_alloc.h"

// Public 
#include "lu_brain.h"

// Elements
#include "@brain/net/neu.h"
#include "@brain/net/neu_iters.h"
#include "@brain/net/lin.h"
#include "@brain/net/linkage.h"

// Core
#include "@brain/core/processor.h"
#include "@brain/core/core.h"



void setUp(void)
{
}

void tearDown(void)
{
}

void test_link_neu(void)
{
	// Core core = core_create_for_test();

	// Neu p1 = core_neu_alloc(core);
	// Neu p2 = core_neu_alloc(core);
	// Neu c1 = core_neu_alloc(core);
	// Neu c2 = core_neu_alloc(core);
	// Neu c3 = core_neu_alloc(core);

	// Lin lin1 = link_neu(p1, c1, core);
	// Lin lin2 = link_neu(p1, c2, core);
	// Lin lin3 = link_neu(p1, c3, core);
	// Lin lin4 = link_neu(p2, c1, core);
	// Lin lin5 = link_neu(p2, c3, core);

	// lin1->w = 2.0;
	// lin2->w = 3.0;
	// lin3->w = 4.0;
	// lin4->w = 5.0;
	// lin5->w = 6.0;

	// TEST_ASSERT(p1->l_c->w == 4.0);
	// TEST_ASSERT(p1->l_c->p_p->w == 3.0);
	// TEST_ASSERT(p1->l_c->p_p->p_n->w == 4.0);
	// TEST_ASSERT(p1->l_c->p_p->p_p->w == 2.0);
	// TEST_ASSERT(p1->l_c->p_p->p_p->p_p == NULL);

	// TEST_ASSERT(c1->l_p->w == 5.0);
	// TEST_ASSERT(c1->l_p->c_p->w == 2.0);
	// TEST_ASSERT(c1->l_p->c_p->c_p == NULL);

	// //lu_debug("NEU_TEST %f", p2->l_c->w);
	// TEST_ASSERT(p2->l_c->w == 6.0);
	// TEST_ASSERT(p2->l_c->p_p->w == 5.0);
	// TEST_ASSERT(p2->l_c->p_p->p_n->w == 6.0);
	// TEST_ASSERT(p2->l_c->p_p->p_p == NULL);

	// core_destroy(&core);
}

static void each_child_1p(Neu parent, Neu item, lu_p_void p1)
{ 
	// if(!item) return;
	// lu_debug("\nitem->p: %f", item->p);
	// arr_append(p1, item);
}

void test_each_child_1p(void)
{
	// Core core = core_create_for_test();

	// Neu p1 = core_neu_alloc(core);
	// Neu c1 = core_neu_alloc(core);
	// Neu c2 = core_neu_alloc(core);
	// Neu c3 = core_neu_alloc(core);

	// Lin lin1 = link_neu(p1, c1, core);
	// Lin lin2 = link_neu(p1, c2, core);
	// Lin lin3 = link_neu(p1, c3, core);

	// neu_receive(c1, 0.2);
	// neu_receive(c2, 0.3);
	// neu_receive(c3, 0.4);

	// TEST_ASSERT(p1->l_c != NULL);
	// TEST_ASSERT(p1->l_c->p_p != NULL);
	// TEST_ASSERT(p1->l_c->p_p->p_p != NULL);
	// TEST_ASSERT(p1->l_c->p_p->p_p->p_p == NULL);

	// Arr arr = arr_create(3);

	// neu_each_child_1p(p1, each_child_1p, arr);

	// TEST_ASSERT(arr->count == 3);
	// TEST_ASSERT(((Neu)arr->items[0])->p == 0.4);
	// TEST_ASSERT(((Neu)arr->items[1])->p == 0.3);
	// TEST_ASSERT(((Neu)arr->items[2])->p == 0.2);

	// arr_destroy(&arr);
	// core_destroy(&core);
}

void test_neu_flags(void)
{
	// Core core = core_create_for_test();

	// Neu p1 = core_neu_alloc(core);

	// TEST_ASSERT(neu_has_flag(p1, NEU_WAVE_END) == false);
	
	// neu_flag(p1, NEU_WAVE_END);

	// TEST_ASSERT(neu_has_flag(p1, NEU_WAVE_END) == true);

	// neu_unflag(p1, NEU_WAVE_END);

	// TEST_ASSERT(neu_has_flag(p1, NEU_WAVE_END) == false);

	// core_destroy(&core);
}
