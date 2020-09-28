/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// N Net

	struct n_cell {
		enum n_cell_type 		type;
		S_Cell 					s_cell;
		lu_size 				sl_ix;   	// nomer v s_layer

		N_Lin 					b_l; 		
		lu_value 				b_count;

		N_Lin  					d_l;		
	
	};

	struct n_cell_2 {
		struct n_cell 			super;

		lu_value 				value;
	};

	struct n_cell_3 {
		struct n_cell 			super;

		lu_size 				name;
	};

	struct n_lin {
		N_Cell	 				b;			// b i d potribni bo po tomu samomu zviazku my mozhemo jty vverh abo vnyz
		N_Cell					d;

		// ce dva spysky
		// odyn z storony b, inshyy z storony d
		N_Lin	 				b_p;
		N_Lin	 				b_n;

		N_Lin	 				d_p; 		// p i n potribni u vypadku yakshou my vydaliayemo zviazok?
		N_Lin					d_n; 		// yaksho my vydaliayemo zviazok, to my mozhemo podyvytys p ale my neznayemo n
		 		   							// tomu naspravdi i p i n potribni
	};

///////////////////////////////////////////////////////////////////////////////
// N_Mem
	
	struct n_mem {
		// vlasnyk
		Lu_Brain 				brain;

		// Tut potriben Mem_Table bo teoretychno neu mozhut vydaliatys
		Mem_Table 				cells;
		Mem_Table				cells_2;
		Mem_Table 				cells_3;
		Mem_Table				lins;

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
