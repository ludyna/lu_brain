/**
	Copyright © 2021 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// N_Mem
	
	struct n_mem {
		// vlasnyk
		Lu_Brain 				brain;

		lu_size 				names_size;
		Simple_Hash				names;
	};

	// n_mem_creates.lu
	static N_Mem n_mem_create(Lu_Brain brain, lu_size names_size);
	static void n_mem_destroy(N_Mem self);
	static N_Mem n_mem_tables_create(N_Mem self, Mem mem);
	static Mem_Table n_mem_cells_2_create(N_Mem self, Mem mem);
	static Mem_Table n_mem_cells_create(N_Mem self, Mem mem);
	static Mem_Table n_mem_cells_3_create(N_Mem self, Mem mem);
	static Mem_Table n_mem_lins_create(N_Mem self, Mem mem);

	// n_mem.lu
	static void n_mem_print_info(N_Mem);

	// n_mem_allocs.lu
	static N_Cell n_mem_cell_alloc(N_Mem self);
	static N_Cell_2 n_mem_cell_2_alloc(N_Mem self);
	static N_Cell_3 n_mem_cell_3_alloc(N_Mem self);
	static N_Lin n_mem_lin_alloc(N_Mem self);
