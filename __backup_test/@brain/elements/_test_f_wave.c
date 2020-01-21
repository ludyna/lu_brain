#include "unity.h"

// Global
#include "global/debug.h"

// Util and types
#include "lib/utils.h"
#include "lib/arr.h"
#include "lib/sis_alloc.h"
#include "lib/rand.h"
#include "lib/lists/ln_alloc.h"
#include "lib/lists/ln_alloc_fast.h"
#include "lib/lists/list.h"
#include "lib/lists/s_list/s_node.h"
#include "lib/lists/s_list/s_list.h"

// Public
#include "lu_brain.h"

// Elements
#include "@brain/net/neu.h"
#include "@brain/net/neu_iters.h"
#include "@brain/net/lin.h"
#include "@brain/net/linkage.h"
#include "@brain/net/waves/save_wave.h"
#include "@brain/net/waves/find_wave.h"

// Core
#include "@brain/core/processor.h"
#include "@brain/core/core.h"



void setUp(void)
{
}

void tearDown(void)
{
}

void test_f_wave1(void)
{
	// Core core = core_create_for_test();

	// Neu p1 = core_neu_alloc(core);
	// Neu p2 = core_neu_alloc(core);
	// Neu c1 = core_neu_alloc(core);
	// Neu c2 = core_neu_alloc(core);
	// Neu c3 = core_neu_alloc(core);

	// // Lin lin1 = link_neu(p1, c1, core);
	// // Lin lin2 = link_neu(p1, c2, core);
	// // Lin lin3 = link_neu(p1, c3, core);
	// // Lin lin4 = link_neu(p2, c1, core);
	// // Lin lin5 = link_neu(p2, c3, core);

	// // FindWave find_wave = find_wave_create(100, 3, 0.1, 1);

	// TEST_ASSERT(core != NULL);

	// // find_wave_destroy(&find_wave);
	// core_destroy(&core);
}