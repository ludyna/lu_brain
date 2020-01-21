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

// 
#include "@brain/@receiver/val_layer.h"
#include "@brain/@receiver/pyra_layer.h"
#include "@brain/@receiver/pyra.h"
#include "@brain/@receiver/receiver.h"
#include "@brain/@sequence/sequence.h"


#include "@brain/brain.h"


void setUp(void)
{
}

void tearDown(void)
{
}

void test_save1(void)
{
    LuBrain brain = lu_brain_create(NULL);
    TEST_ASSERT(brain != NULL);

    lu_size rec_id = lu_brain_create_receiver(brain, 2, 2, 0.0, 99.0, 100, 0.001);
    TEST_ASSERT(rec_id == 0);

    lu_value data[] = { 1.0, 2.0, 3.0, 4.0 };

    lu_brain_save(brain, rec_id, data, NULL);

    // LuSRequest request = lu_s_request_create_simple(rec_id, data);

    // lu_debug("\nNeu count4x4: %lu", lu_brain_neu_count(brain));

    // struct lu_s_response resp = lu_brain_save(brain, request);
    // TEST_ASSERT(resp.neuron != NULL);

    // resp = lu_brain_save(brain, request);
    // TEST_ASSERT(resp.neuron != NULL);

    // lu_debug("\nNeu count4x4: %lu", lu_brain_neu_count(brain));

    // lu_s_request_destroy(&request);
    lu_brain_destroy(&brain);
    TEST_ASSERT(brain == NULL);
}


