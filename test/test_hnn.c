/**
	Copyright © 2021 Oleh Ihorovych Novosad 
*/

#include "unity.h"

#include <stdio.h>
#include <string.h>

#include "lib/_module.h"

///////////////////////////////////////////////////////////////////////////////
// Globals

lu_size boost_combine(lu_size seed, lu_size value)
{
    seed ^= value + 0x9e3779b9 + (seed<<6) + (seed>>2);
    return seed;
}

Hnn g_hnn = NULL;
Mem_Debugger g_md = NULL;
struct hnn_config g_config = {
        .size_in_cell_0 = 5, 
        .size_in_cell_1 = 5,
        .size_in_cell_2 = 5, 
        .size_in_cell_3 = 5, 
        .size_in_cell_4 = 5,
        .t1_size = 0, 
        .t2_size = 0,
        .t3_size = 0,
        .t4_size = 0
    };

///////////////////////////////////////////////////////////////////////////////
// Setup

void setUp(void)
{ 
	lu_debug("\nsetUp");

    g_md = mem_debugger_create(g_mem_temp);
    TEST_ASSERT(g_md);

    g_hnn = hnn_create(g_mem_temp, g_config);
    TEST_ASSERT(g_hnn);
}

void tearDown(void)
{	
	lu_debug("\ntearDown");
    hnn_destroy(g_hnn);

    mem_debugger_print(g_md);
    if(!mem_debugger_is_all_clear(g_md))
    {
        mem_debugger_destroy(g_md, true);
        TEST_ASSERT(false);
    }
    mem_debugger_destroy(g_md, true);
}

///////////////////////////////////////////////////////////////////////////////
// Tests

// void test_spawn_and_die(void) 
// {
	
//     Hnn_Cell c1 = hnn_cell_spawn(g_hnn, HNN_CT_1);
//     TEST_ASSERT(c1);
//     TEST_ASSERT(c1->type == HNN_CT_1); 

//     Hnn_Cell c2 = hnn_cell_spawn(g_hnn, HNN_CT_2);
//     TEST_ASSERT(c2);
//     TEST_ASSERT(c2->type == HNN_CT_2);

//     Hnn_Cell c3 = hnn_cell_spawn(g_hnn, HNN_CT_3);
//     TEST_ASSERT(c3);
//     TEST_ASSERT(c3->type == HNN_CT_3);

//     Hnn_Cell c4 = hnn_cell_spawn(g_hnn, HNN_CT_4);
//     TEST_ASSERT(c4);
//     TEST_ASSERT(c4->type == HNN_CT_4);

//     hnn_cell_die(g_hnn, c1);
//     hnn_cell_die(g_hnn, c2);
//     hnn_cell_die(g_hnn, c3);
//     hnn_cell_die(g_hnn, c4);
// }

void test_spawn_connect_and_get(void)
{
    // Cell Spawn

    Hnn_Cell top_left = hnn_cell_spawn(g_hnn, HNN_CT_0);
    TEST_ASSERT(top_left);
    TEST_ASSERT(top_left->type == HNN_CT_0); 

    Hnn_Cell top_right = hnn_cell_spawn(g_hnn, HNN_CT_0);
    TEST_ASSERT(top_right);
    TEST_ASSERT(top_right->type == HNN_CT_0);

    Hnn_Cell bottom_left = hnn_cell_spawn(g_hnn, HNN_CT_0);
    TEST_ASSERT(bottom_left);
    TEST_ASSERT(bottom_left->type == HNN_CT_0);

    Hnn_Cell bottom_right = hnn_cell_spawn(g_hnn, HNN_CT_0);
    TEST_ASSERT(bottom_right);
    TEST_ASSERT(bottom_right->type == HNN_CT_0);

    // Cell Spawn Connect 

    Hnn_Cell t = NULL;

    Hnn_Cell child_1 = hnn_cell_spawn_connect_1(g_hnn, top_left);
    TEST_ASSERT(child_1 != NULL);
    t = hnn_cell_get_1(g_hnn, top_left);
    TEST_ASSERT(t);
    TEST_ASSERT(child_1 == t);

    // Hnn_Cell child_2 = hnn_cell_spawn_connect_2(g_hnn, top_left, top_right);
    // TEST_ASSERT(child_2 != NULL);
    // t = hnn_cell_get_2(g_hnn, top_left, top_right);
    // TEST_ASSERT(t);
    // TEST_ASSERT(child_2 == t);

    // Hnn_Cell child_3 = hnn_cell_spawn_connect_1(g_hnn, top_left);
    // TEST_ASSERT(child_2 != NULL);
    // TEST_ASSERT(child_2 == hnn_cell_get_1(g_hnn, top_left));

    // Hnn_Cell child_4 = hnn_cell_spawn_connect_1(g_hnn, top_left);
    // TEST_ASSERT(child_2 != NULL);
    // TEST_ASSERT(child_2 == hnn_cell_get_1(g_hnn, top_left));
  
    hnn_cell_die(g_hnn, top_left);
    hnn_cell_die(g_hnn, child_1);
}

