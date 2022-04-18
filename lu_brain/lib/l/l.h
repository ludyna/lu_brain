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

	static inline Lu_Label lu_label__init(Lu_Label self, lu_size label, lu_size count)
	{
		lu__debug_assert(self);

		self->label = label;
		self->count = count;

		return self;
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_L_Unit

	struct lu_l_unit {
		union lu_n_addr addr;
		union lu_label* labels;
	};

	static Lu_L_Unit lu_l_unit__init(Lu_L_Unit self, Lu_Mem mem, union lu_n_addr addr, lu_size size);
	static void lu_l_unit__deinit(Lu_L_Unit self, Lu_Mem mem);

///////////////////////////////////////////////////////////////////////////////
// Lu_L_Table

	struct lu_l_table {
		Lu_Mem mem;
		
		lu_size labels_size;
		lu_size h;
		lu_size d;

		// Addr to labels, h x d hash/map
		struct lu_l_unit *addr_to_labels;

		// Label to addrs, where lu_list contains address (&) to Lu_L_Unit in addr_to_labels.
		struct lu_list *label_to_addrs;
	};

	static Lu_L_Table lu_l_table__init(Lu_L_Table self, Lu_Mem mem, lu_size labels_size, lu_size h, lu_size d);
	static void lu_l_table__deinit(Lu_L_Table self);