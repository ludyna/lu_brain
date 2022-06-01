/**
	Copyright © 2022 Oleh Ihorovych Novosad 

*/

///////////////////////////////////////////////////////////////////////////////
// 
	union lu_la_addr {
		struct {
			lu_size la_ix;
		};

		lu_size value;
	};

///////////////////////////////////////////////////////////////////////////////
// 

	struct lu_la_cell {
		lu_size label;

		Lu_N_Link children;
		lu_size children_count;

		union lu_w_match_addr* w_cells;
	};

///////////////////////////////////////////////////////////////////////////////
// 

	union lu_la_link_addr {
		struct {
			lu_size link_ix;
		};

		lu_size value;
	};

///////////////////////////////////////////////////////////////////////////////
// 

	struct lu_la_link {
		union lu_la_addr la_addr;

		union lu_la_link_addr next;
	}; 

///////////////////////////////////////////////////////////////////////////////
// 

	struct lu_la_link_mem {

	};

///////////////////////////////////////////////////////////////////////////////
// 
	
	struct lu_la_column {


		struct lu_la_cell* cells;
		lu_size cells_size;

		Lu_N_Link_Mem n_link_mem;
		Lu_La_Link_Mem la_link_mem;
	};