/**
	Copyright © 2022 Oleh Ihorovych Novosad 

*/

///////////////////////////////////////////////////////////////////////////////
// Label

	
	
	union lu_l_label {
		struct {
			lu_size label : 32;
			lu_size count : 32;
		};	
		lu_size value;
	};

	struct lu_l_cell {
		union lu_n_addr add;
		union lu_l_label* labels;
	};

	struct lu_l_label_cell {

	};

	struct lu_l_table {
		Lu_Mem mem;
		
		lu_size h;
		lu_size d;

		// h x d hash/map
		struct lu_l_cell *addr_to_labels;

		// Label to addrs, where lu_list contains address (&) to Lu_L_Cell in addr_to_labels.
		struct lu_list *label_to_addrs;
	};
