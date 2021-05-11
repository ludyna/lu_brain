/**
	Copyright © 2021 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// N_Mem

	struct n_mem_config {
		lu_size names_size;

		struct hnn_config hnn_config;
	};
	
	struct n_mem {
		// vlasnyk
		Lu_Brain 				brain;

		lu_size 				names_size;
		Simple_Hash				names;
	};

///////////////////////////////////////////////////////////////////////////////
// N_Mem Create & Destroy

	static N_Mem n_mem_create(Lu_Brain brain, lu_size names_size);
	static void n_mem_destroy(N_Mem self);

///////////////////////////////////////////////////////////////////////////////
// N_Mem Utility

	static void n_mem_print_info(N_Mem);
