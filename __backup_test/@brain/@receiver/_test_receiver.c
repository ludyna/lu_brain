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
#include "@brain/net/linkage.h"
#include "@brain/net/waves/save_wave.h"
#include "@brain/net/waves/find_wave.h"

// Core
#include "@brain/core/processor.h"
#include "@brain/core/core.h"

// Component
#include "@brain/@receiver/pyra_layer.h"
#include "@brain/@receiver/pyra.h"
#include "@brain/@receiver/val_layer.h"
#include "@brain/@receiver/receiver.h"



void setUp(void)
{

}

void tearDown(void)
{

}

void test_lu_receiver_create_and_destroy(void)
{
    Receiver rec = receiver_create(NULL, 1, 1, -1.0, 3.0, 2, 0.1);
    TEST_ASSERT(rec != NULL);

    receiver_destroy(&rec);
    TEST_ASSERT(rec == NULL);
}




