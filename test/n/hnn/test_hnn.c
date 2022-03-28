/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/

#include "unity.h"

#include <stdio.h>
#include <string.h>

#include "lib/_module.h"

///////////////////////////////////////////////////////////////////////////////
// Globals

Hnn g_hnn = NULL;
Lu_Mem_Debugger g_md = NULL;
struct lu_n_config g_config = {
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
	lu__debug("\nsetUp");

    g_md = lu_mem_debugger__create(lu_g_mem);
    TEST_ASSERT(g_md);

    g_hnn = n_create(lu_g_mem, g_config);
    TEST_ASSERT(g_hnn);
}

void tearDown(void)
{	
	lu__debug("\ntearDown");
    n_destroy(g_hnn);

    lu_mem_debugger__print(g_md);
    if(!mem_debugger_is_all_clear(g_md))
    {
        lu_mem_debugger__destroy(g_md, true);
        TEST_ASSERT(false);
    }
    lu_mem_debugger__destroy(g_md, true);
}

///////////////////////////////////////////////////////////////////////////////
// Tests

void test_spawn_and_die(void) 
{
	
    Lu_N_Cell_Base c1 = n_cell_spawn(g_hnn, LU_N_CELL__1);
    TEST_ASSERT(c1);
    TEST_ASSERT(c1->type == LU_N_CELL__1); 

    Lu_N_Cell_Base c2 = n_cell_spawn(g_hnn, LU_N_CELL__2);
    TEST_ASSERT(c2);
    TEST_ASSERT(c2->type == LU_N_CELL__2);

    Lu_N_Cell_Base c3 = n_cell_spawn(g_hnn, LU_N_CELL__3);
    TEST_ASSERT(c3);
    TEST_ASSERT(c3->type == LU_N_CELL__3);

    Lu_N_Cell_Base c4 = n_cell_spawn(g_hnn, LU_N_CELL__4);
    TEST_ASSERT(c4);
    TEST_ASSERT(c4->type == LU_N_CELL__4);

    n_cell_die(g_hnn, c1);
    n_cell_die(g_hnn, c2);
    n_cell_die(g_hnn, c3);
    n_cell_die(g_hnn, c4);
}

void test_spawn_connect_and_get(void)
{
    // Cell Spawn

    Lu_N_Cell_Base top_left = n_cell_spawn(g_hnn, LU_N_CELL__0);
    TEST_ASSERT(top_left);
    TEST_ASSERT(top_left->type == LU_N_CELL__0); 

    Lu_N_Cell_Base top_right = n_cell_spawn(g_hnn, LU_N_CELL__0);
    TEST_ASSERT(top_right);
    TEST_ASSERT(top_right->type == LU_N_CELL__0);

    Lu_N_Cell_Base bottom_left = n_cell_spawn(g_hnn, LU_N_CELL__0);
    TEST_ASSERT(bottom_left);
    TEST_ASSERT(bottom_left->type == LU_N_CELL__0);

    Lu_N_Cell_Base bottom_right = n_cell_spawn(g_hnn, LU_N_CELL__0);
    TEST_ASSERT(bottom_right);
    TEST_ASSERT(bottom_right->type == LU_N_CELL__0);

    // Cell Spawn Connect 

    Lu_N_Cell_Base t = NULL;

    Lu_N_Cell_Base child_1 = (Lu_N_Cell_Base) n_cell_spawn_connect_1(g_hnn, top_left);
    TEST_ASSERT(child_1);
    t = n_cell_get_1(g_hnn, top_left);
    TEST_ASSERT(t);
    TEST_ASSERT(child_1 == t);

    Lu_N_Cell_Base child_2 = (Lu_N_Cell_Base) n_cell_spawn_connect_2(g_hnn, top_left, top_right);
    TEST_ASSERT(child_2);
    t = n_cell_get_2(g_hnn, top_left, top_right);
    TEST_ASSERT(t);
    TEST_ASSERT(child_2 == t);

    Lu_N_Cell_Base child_3 = (Lu_N_Cell_Base) n_cell_spawn_connect_3(g_hnn, top_left, top_right, bottom_left);
    TEST_ASSERT(child_3);
    t = n_cell_get_3(g_hnn, top_left, top_right, bottom_left);
    TEST_ASSERT(t);
    TEST_ASSERT(child_3 == t);

    Lu_N_Cell_Base child_4 = (Lu_N_Cell_Base) n_cell_spawn_connect_4(g_hnn, top_left, top_right, bottom_left, bottom_right);
    TEST_ASSERT(child_4);
    t = n_cell_get_4(g_hnn, top_left, top_right, bottom_left, bottom_right);
    TEST_ASSERT(t);
    TEST_ASSERT(child_4 == t);
  
    n_cell_die(g_hnn, top_left);
    n_cell_die(g_hnn, child_1);
}

