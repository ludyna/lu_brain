#include "unity.h"

// Global
#include "global/debug.h"

// Util and types
#include "lib/utils.h"
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
#include "@brain/core/core.h"



void setUp(void)
{
}

void tearDown(void)
{
}

void test_s_wave1(void)
{
	Core core = core_create_for_test();

	Neu p1 = core_neu_alloc(core);
	Neu p2 = core_neu_alloc(core);
	Neu c1 = core_neu_alloc(core);
	Neu c2 = core_neu_alloc(core);
	Neu c3 = core_neu_alloc(core);

	Lin lin1 = link_neu(p1, c1, core);
	Lin lin2 = link_neu(p1, c2, core);
	Lin lin3 = link_neu(p1, c3, core);
	Lin lin4 = link_neu(p2, c1, core);
	Lin lin5 = link_neu(p2, c3, core);

	SaveWave save_wave = save_wave_create();

	p1->count = 1;
	p2->count = 1;

	save_wave_process(save_wave, p1, 0.8);
	save_wave_process(save_wave, p2, 1.0);

	TEST_ASSERT(save_wave_top(save_wave) == c3);
	TEST_ASSERT(c3->p = 1.8);
	TEST_ASSERT(c3->count = 2);
	TEST_ASSERT(neu_norm_p(c3) == 0.9);

	lu_debug("\nC1->p: %f", c1->p);
	lu_debug("\nC1->count: %f", c1->count);

	lu_debug("\nC2->p: %f", c2->p);
	lu_debug("\nC2->count: %f", c2->count);

	lu_debug("\nC3->p: %f", c3->p);
	lu_debug("\nC3->count: %f", c3->count);

	TEST_ASSERT(neu_norm_p(c1) == 0.9);
	TEST_ASSERT(neu_norm_p(c2) == 0.8);

	save_wave_destroy(&save_wave);
	core_destroy(&core);
}