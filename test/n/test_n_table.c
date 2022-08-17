/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/

#include "unity.h"
#include "lib/_module.h"

Lu_Mem_Debugger md;
struct lu_s_table s_table_data;
Lu_S_Table s_table;
struct lu_config config;

void setUp(void)
{ 
	md = lu_mem_debugger__create(lu_g_mem);
	TEST_ASSERT(md);

	config = lu_config__get_by_id(LU_CONFIG__DEFAULT);

	s_table = lu_s_table__init(&s_table_data, lu_g_mem, 2, 2, 2, &config, 32, 55, NULL);
	TEST_ASSERT(s_table);
	TEST_ASSERT(s_table->w == 2);
	TEST_ASSERT(s_table->h == 2);
	TEST_ASSERT(s_table->columns);

	Lu_S_Column column = lu_s_table__get_s_column(s_table, 1, 1);
	TEST_ASSERT(column); 

	lu_s_column__alloc_n_cell(column);

	union lu_n_addr n_addr;

	lu_n_addr__reset(&n_addr);

	n_addr.cell_ix = 0;

	Lu_N_Cell cell = lu_s_column__get_n_cell(column, n_addr);
	TEST_ASSERT(cell);

	lu_n_addr__print(&cell->addr);

	TEST_ASSERT(cell->addr.layer_ix == 32);
	TEST_ASSERT(cell->addr.cell_ix == 0);

	struct lu_n_pos pos = lu_n_pos__from_column_ix(cell->addr.column_ix, s_table->w);
 
 	Lu_S_Column column_2 = lu_s_table__get_s_column(s_table, pos.x, pos.y);

 	TEST_ASSERT(column_2 == column);

	Lu_N_Cell cell_2 = lu_s_column__get_n_cell(column, n_addr);

	TEST_ASSERT(cell_2 == cell);
}

void tearDown(void)
{	
	lu_s_table__deinit(s_table);

	lu_mem_debugger__print(md);

	TEST_ASSERT(lu_mem_debugger__is_all_freed(md));
    lu_mem_debugger__destroy(md, true);
}

void test_1(void) 
{
	
}

