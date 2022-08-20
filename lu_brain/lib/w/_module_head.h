/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Module typedefs 
//

	//
	// Save
	//

	typedef struct lu_w_rec * Lu_W_Rec;
	typedef struct lu_w_table_p* Lu_W_Table_P;
	typedef struct lu_w_table_v* Lu_W_Table_V;
	typedef struct lu_w_table* Lu_W_Table;
	typedef struct lu_w_child* Lu_W_Child;

	//
	// Match
	//

	typedef struct lu_w_proc_item* Lu_W_Proc_Item;
	typedef struct lu_w_proc_list* Lu_W_Proc_List;
	typedef struct lu_w_match_processor* Lu_W_Match_Processor;


	// 
	// General
	//
	typedef struct lu_w_manager* Lu_W_Manager;


///////////////////////////////////////////////////////////////////////////////
// Prototypes 
//

	//
	// Lu_S_Layer
	//

	typedef struct lu_s_layer* Lu_S_Layer;

	static inline Lu_S_Table lu_s_layer__get_s_table(Lu_S_Layer self);
	static inline void lu_s_layer__print_basic_info(Lu_S_Layer self);

	//
	// Lu_S 
	//

	typedef struct lu_s* Lu_S;
	static inline void lu_s__find_n_cell_and_s_column(		
		Lu_S self,
		union lu_n_addr addr,
		Lu_N_Cell* n_cell,
		Lu_S_Column* s_column
	);
