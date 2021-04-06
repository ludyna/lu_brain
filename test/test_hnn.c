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

void setUp(void)
{ 
	lu_debug("\nsetUp");
}

void tearDown(void)
{	
	lu_debug("\ntearDown");
}

void test_1(void) 
{
	Mem_Debugger md = mem_debugger_create(g_mem_temp);

    Mem mem        = (Mem) mem_perm_create(g_mem_temp, 512);
    Mem_Table mt   = mem_table_create(
        /*Mem*/                     mem, 
        /*record_size_in_bytes*/    sizeof(struct hnn_cell), 
        /*table_size_in_records*/   3, 
        /*percent*/                 0, 
        /*flags*/                   MTF_FREEABLE
    );

    mem_destroy(mem, g_mem_temp);

    TEST_ASSERT(mem_debugger_is_all_clear(md));
    mem_debugger_destroy(md, true);
}

void test_2(void)
{

}

