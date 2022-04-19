/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/

#include "unity.h"
#include "lib/_module.h"

Lu_Mem_Debugger md;
struct lu_label_map m;
Lu_Label_Map map;

// setUp is executed for each test, even if test does nothing
void setUp(void)
{ 
	md = lu_mem_debugger__create(lu_g_mem);
	TEST_ASSERT(md);
	map = &m;

	map = lu_label_map__init(map, lu_g_mem, 10, 100, 3);
	TEST_ASSERT(map);
}

void tearDown(void)
{	
	lu_label_map__deinit(map);

	lu_mem_debugger__print(md);

	TEST_ASSERT(mem_debugger_is_all_clear(md));
    lu_mem_debugger__destroy(md, true);
}

void test_label_map(void)
{
	union lu_n_addr addr;

	// lu_n_addr__init(&addr, 

	// lu_mabel_map__add_label(map, 
}