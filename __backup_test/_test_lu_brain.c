#include "unity.h"

// Vendor
#include "vendor/CException.h"

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

void test_brain_create_and_destroy(void)
{
    // LuBrain brain = lu_brain_create_default();
    // TEST_ASSERT(brain != NULL);

    // lu_brain_destroy(&brain);
    // TEST_ASSERT(brain == NULL);
}

void test_brain_create_recs(void)
{
    // LuBrain brain = lu_brain_create_default();
    // TEST_ASSERT(brain != NULL);

    // lu_size rec_id1 = lu_brain_create_receiver(brain, 1, 1, 0.0, 9.0, 10, 0.15);
    // TEST_ASSERT(rec_id1 == 0);

    // lu_size rec_id2 = lu_brain_create_receiver(brain, 1, 1, 0.0, 1.0, 10, 0.15);
    // TEST_ASSERT(rec_id2 == 1);

    // lu_brain_destroy(&brain);
    // TEST_ASSERT(brain == NULL);
}
 
void test_brain_save1x1(void)
{
    // LuBrain brain = lu_brain_create_default();
    // TEST_ASSERT(brain != NULL);

    // lu_size rec_id = lu_brain_create_receiver(brain, 1, 1, 0.0, 9.0, 10, 0.15);
    // TEST_ASSERT(rec_id == 0);

    // lu_value data[] = { 1.0 };
    // LuSRequest request = lu_s_request_create_simple(rec_id, data);

    // struct lu_s_response resp = lu_brain_save(brain, request);
    // TEST_ASSERT(resp.neuron != NULL);

    // lu_debug("\nNeu count1x1: %lu", lu_brain_neu_count(brain));

    // lu_s_request_destroy(&request);
    // lu_brain_destroy(&brain);
    // TEST_ASSERT(brain == NULL);
}

void test_brain_save2x2(void)
{
    // LuBrain brain = lu_brain_create_default();
    // TEST_ASSERT(brain != NULL);

    // lu_size rec_id = lu_brain_create_receiver(brain, 2, 2, 0.0, 9.0, 10, 0.15);
    // TEST_ASSERT(rec_id == 0);

    // lu_value data[] = { 1.0, 2.0, 3.0, 2.0 };
    // LuSRequest request = lu_s_request_create_simple(rec_id, data);

    // lu_debug("\nNeu count2x2: %lu", lu_brain_neu_count(brain));

    // struct lu_s_response resp = lu_brain_save(brain, request);
    // TEST_ASSERT(resp.neuron != NULL);

    // lu_size neu_count = lu_brain_neu_count(brain);
    
    // lu_debug("\nNeu count2x2: %lu", neu_count);

    // TEST_ASSERT(neu_count == 5);

    // lu_s_request_destroy(&request);
    // lu_brain_destroy(&brain);
    // TEST_ASSERT(brain == NULL);
}

void test_brain_save4x4(void)
{
    // LuBrain brain = lu_brain_create_default();
    // TEST_ASSERT(brain != NULL);

    // lu_size rec_id = lu_brain_create_receiver(brain, 4, 4, 0.0, 99.0, 100, 0.001);
    // TEST_ASSERT(rec_id == 0);

    // lu_value data[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0 };
    // LuSRequest request = lu_s_request_create_simple(rec_id, data);

    // lu_debug("\nNeu count4x4: %lu", lu_brain_neu_count(brain));

    // struct lu_s_response resp = lu_brain_save(brain, request);
    // TEST_ASSERT(resp.neuron != NULL);

    // resp = lu_brain_save(brain, request);
    // TEST_ASSERT(resp.neuron != NULL);

    // lu_debug("\nNeu count4x4: %lu", lu_brain_neu_count(brain));

    // lu_s_request_destroy(&request);
    // lu_brain_destroy(&brain);
    // TEST_ASSERT(brain == NULL);
}

void test_brain_save_and_find(void)
{
    // LuBrain brain = lu_brain_create_default();
    // TEST_ASSERT(brain != NULL);

    // lu_size rec_id = lu_brain_create_receiver(brain, 1, 1, 0.0, 9.0, 10, 0.15);
    // TEST_ASSERT(rec_id == 0);

    // lu_value data1[] = { 1.0 };
    // LuSRequest req1 = lu_s_request_create_simple(rec_id, data1);

    // struct lu_s_response resp = lu_brain_save(brain, req1);
    // TEST_ASSERT(resp.neuron != NULL);

    // lu_value data2[] = { 7.0 };
    // LuSRequest req2 = lu_s_request_create_simple(rec_id, data2);

    // resp = lu_brain_save(brain, req2);
    // TEST_ASSERT(resp.neuron != NULL);

    // // lu_value data3[] = { 5.0 };
    // // lu_value data4[] = { 2.0 };
    // // LuFResponseponse fr1 = lu_brain_find_simple(rec_id, data3);
    // // LuFResponseponse fr2 = lu_brain_find_simple(rec_id, data4);

    // // TEST_ASSERT(lu_f_response_top(fr1) != lu_find_re

    // lu_s_request_destroy(&req1);
    // lu_s_request_destroy(&req2);
    // lu_brain_destroy(&brain);
    // TEST_ASSERT(brain == NULL);
}