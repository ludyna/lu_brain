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

	n_table = lu_n_table__create(lu_g_mem, 2, 2, &config, 32);
	TEST_ASSERT(n_table);
	TEST_ASSERT(n_table->w == 2);
	TEST_ASSERT(n_table->h == 2);
	TEST_ASSERT(n_table->columns);

	Lu_N_Column column = lu_n_table__get_column(n_table, 1, 1);
	TEST_ASSERT(column);

	Lu_N_Cell cell = lu_n_column__get_cell(column, 0, 3);
	TEST_ASSERT(cell);

	lu_n_addr__print(&cell->addr);

	TEST_ASSERT(cell->addr.layer_ix == 32);
	TEST_ASSERT(cell->addr.cell_ix == 3);

	struct lu_n_pos pos = lu_n_pos__from_column_ix(cell->addr.column_ix, n_table->w);
 
 	Lu_N_Column column_2 = lu_n_table__get_column(n_table, pos.x, pos.y);

 	TEST_ASSERT(column_2 == column);

	Lu_N_Cell cell_2 = lu_n_column__get_cell(column, 0, 3);

	TEST_ASSERT(cell_2 == cell);
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

