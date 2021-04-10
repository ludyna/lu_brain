/**
	Copyright © 2021 Oleh Ihorovych Novosad 
*/

#include "unity.h"

#include <stdio.h>
#include <string.h>

#include "lib/_module.h"

lu_size boost_combine(lu_size seed, lu_size value)
{
    seed ^= value + 0x9e3779b9 + (seed<<6) + (seed>>2);
    return seed;
}

Hnn g_hnn = NULL;
Mem_Debugger g_md = NULL;
struct hnn_config g_config = {
        .size_in_cell_1 = 1,
        .size_in_cell_2 = 2, 
        .size_in_cell_3 = 3, 
        .size_in_cell_4 = 4,
        .t1_size = 0, 
        .t2_size = 0,
        .t3_size = 0,
        .t4_size = 0
    };

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

    if(!mem_debugger_is_all_clear(g_md))
    {
        mem_debugger_destroy(g_md, true);
        TEST_ASSERT(false);
    }
    mem_debugger_destroy(g_md, true);
}

void test_1(void) 
{
	

    // Mem mem        = (Mem) mem_perm_create(g_mem_temp, 512);
    // Mem_Table mt   = mem_table_create(
    //     /*Mem*/                     mem, 
    //     /*record_size_in_bytes*/    sizeof(struct hnn_cell), 
    //     /*table_size_in_records*/   3, 
    //     /*percent*/                 0, 
    //     /*flags*/                   MTF_FREEABLE
    // );

    // mem_destroy(mem, g_mem_temp);


}

void test_2(void)
{

}

