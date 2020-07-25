/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// N Net

	struct n_cell {
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
// N Dopomizhni

	struct n_mem_opts {
		lu_size 				names_size;
	};

	static inline N_Mem_Opts n_mem_opts_init(N_Mem_Opts self)
	{
		self->names_size = LU_NAMES_SIZE;
	}

	static inline N_Mem_Opts n_mem_opts_validate(N_Mem_Opts opts)
	{
		lu_user_assert(opts, "N_Mem_Opts is NULL");
		lu_user_assert(opts->names_size > 0, "names_size should be greater than 0");

		return opts;
	}
	
	struct n_mem {
		// vlasnyk
		Lu_Brain 				brain;

		struct n_mem_opts 		opts;

		// Tut potriben Mem_Table bo teoretychno neu mozhut vydaliatys
		Mem_Table				cells_2;
		Mem_Table 				cells;
		Mem_Table				lins;
		Simple_Hash				names;
	};

	static N_Mem n_mem_create(Lu_Brain brain, N_Mem_Opts opts);
	
	static N_Mem n_mem_tables_alloc(N_Mem self, Mem mem);

	static Mem_Table n_mem_cells_2_create(N_Mem self, Mem mem);
	static Mem_Table n_mem_cells_create(N_Mem self, Mem mem);
	static Mem_Table n_mem_lins_create(N_Mem self, Mem mem);

	static void n_mem_print_info(N_Mem);
	static N_Cell n_mem_cell_alloc(N_Mem self);
	static N_Lin n_mem_lin_alloc(N_Mem self);
