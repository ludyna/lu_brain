/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/

#include "unity.h"
#include "lib/_module.h"

Lu_Mem_Debugger md;
Lu_N_Table n_table;
struct lu_config config;

void setUp(void)
{ 
	md = lu_mem_debugger__create(lu_g_mem);
	TEST_ASSERT(md);

	config = lu_config__get_by_id(LU_CONFIG__DEFAULT);

	n_table = lu_n_table__create(lu_g_mem, 2, 2, LU_N_CELL__N, &config);
	TEST_ASSERT(n_table);
	TEST_ASSERT(n_table->w == 2);
	TEST_ASSERT(n_table->h == 2);
	TEST_ASSERT(n_table->columns);
}

void tearDown(void)
{	
	lu_n_table__destroy(n_table);

	lu_mem_debugger__print(md);

	TEST_ASSERT(mem_debugger_is_all_clear(md));
    lu_mem_debugger__destroy(md, true);
}

void test_1(void) 
{
	
}

