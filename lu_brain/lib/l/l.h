/**
	Copyright © 2022 Oleh Ihorovych Novosad 

*/

///////////////////////////////////////////////////////////////////////////////
// Lu_L_Label
	
	union lu_label {
		struct {
			lu_size label : 32;
			lu_size count : 32;
		};	
		lu_size value;
	};  

	static inline Lu_L_Label lu_label__init(Lu_L_Label self, lu_size label, lu_size count)
	{
		lu__debug_assert(self);

		self->label = label;
		self->count = count;

		return self;
	}


///////////////////////////////////////////////////////////////////////////////
// Lu_L_Cell

	struct lu_l_cell {
		union lu_n_addr add;
		union lu_label* labels;
	};



///////////////////////////////////////////////////////////////////////////////
// Lu_L_Table

	struct lu_l_table {
		Lu_Mem mem;
		
		lu_size h;
		lu_size d;

		// h x d hash/map
		struct lu_l_cell *addr_to_labels;

		// Label to addrs, where lu_list contains address (&) to Lu_L_Cell in addr_to_labels.
		struct lu_list *label_to_addrs;
	};
