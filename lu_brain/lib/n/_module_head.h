/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/	
 
///////////////////////////////////////////////////////////////////////////////
//  
	//
	// Lu_N_Located_Cell
	//
	
	typedef struct lu_n_located_cell* Lu_N_Located_Cell;

	//
	//
	//
	
	typedef struct lu_n_pos* Lu_N_Pos;
	typedef struct lu_n_pos_3d* Lu_N_Pos_3d;
	
	typedef union lu_n_link_addr* Lu_N_Link_Addr;
	typedef struct lu_n_link* Lu_N_Link;
	typedef struct lu_n_link_mem* Lu_N_Link_Mem;

	enum lu_n_cell_type {
		LU_N_CELL__0,
		LU_N_CELL__VP, // for p and v
		LU_N_CELL__N,
		LU_N_CELL__END
	};

	typedef struct lu_n_cell_vp* Lu_N_Cell_VP;
	typedef struct lu_n_cell* Lu_N_Cell;
	typedef struct lu_n_strs* Lu_N_Strs;
	typedef struct lu_n_cells* Lu_N_Cells;


///////////////////////////////////////////////////////////////////////////////
// 



	static inline Lu_N_Link lu_n_link_mem__alloc_link(Lu_N_Link_Mem self);
	static inline union lu_n_link_addr lu_n_link_mem__get_addr(Lu_N_Link_Mem self, Lu_N_Link link);
	static inline Lu_N_Link lu_n_link_mem__get_link(Lu_N_Link_Mem self, union lu_n_link_addr addr);
	static inline Lu_N_Link_Mem lu_s_column__get_link_mem(Lu_S_Column self);

	typedef union lu_la_addr* Lu_La_Addr;
	typedef struct lu_la_link* Lu_La_Link;
	typedef struct lu_la_link_mem* Lu_La_Link_Mem;

	static inline Lu_La_Link lu_la_link_mem__link_alloc(Lu_La_Link_Mem self);
	static inline union lu_la_link_addr lu_la_link_mem__get_addr(Lu_La_Link_Mem self, Lu_La_Link link);
	static inline Lu_La_Link lu_la_link__init(Lu_La_Link self, union lu_la_addr la_addr, union lu_la_link_addr next);

	static inline union lu_n_link_addr lu_n_link_addr__prepend(union lu_n_link_addr self, Lu_N_Link_Mem link_mem, union lu_n_addr addr);


	////
	// TODO: Need to replace this later with lu_mem_table , with dynamic w_cells size and access to list of w_cells
	// using lu_n_cell.addr
	#define LU_N_CELL__W_MATCH_CELLS_SIZE 1
	#define LU_N_CELL__W_SAVE_CELLS_SIZE 1

	//
	// Lu_S_Layer_Comp
	//

	typedef struct lu_s_layer_comp* Lu_S_Layer_Comp;


	//
	// Lu_S_Layer
	//

	typedef struct lu_s_layer_base* Lu_S_Layer_Base;
	static inline void lu_s_layer_base__print_basic_info(Lu_S_Layer_Base self);

	//
	// S Columns
	//

	typedef struct lu_s_column* Lu_S_Column;
	
	typedef struct lu_s_column* Lu_S_Column;

	typedef struct lu_s_column_comp* Lu_S_Column_Comp;
	static inline Lu_N_Link_Mem lu_s_column_comp__get_n_link_mem(Lu_S_Column_Comp self);
