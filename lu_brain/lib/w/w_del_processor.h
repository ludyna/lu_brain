/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Lu_W_Del_Processor

	struct lu_w_del_processor {
		struct lu_block_id block_id;
		lu_size wave_ix;

		Lu_S s;
		Lu_Mem mem;
		Lu_W_Match_Cell_Mem match_cell_mem;
		Lu_La_Column la_column;

		Lu_W_Proc_List curr_list;
		Lu_W_Proc_List next_list;

		Lu_Mem_Table la_mem_table;

		//
		// Stats
		//  

		struct lu_w_processor_stats stats;
	};

	static void lu_w_del_processor__init(
		Lu_W_Match_Processor self,  
		Lu_S s, 
		Lu_Config config, 
		Lu_W_Match_Cell_Mem match_cell_mem,
		Lu_La_Column la_column
	);

	static void lu_w_del_processor__deinit(Lu_W_Match_Processor self);
