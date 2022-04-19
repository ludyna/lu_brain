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

	static inline lu_bool lu_label__is_blank(Lu_Label self)
	{
		return self->value == 0;
	}

	static inline Lu_Label lu_label__init(Lu_Label self, lu_size label, lu_size count)
	{
		lu__debug_assert(self);

		self->label = label;
		self->count = count;

		return self;
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_Label_Unit

	struct lu_label_unit {
		union lu_n_addr addr;
		union lu_label* labels;
	};

	static inline Lu_Label_Unit lu_label_unit__null_init(Lu_Label_Unit self)
	{
		lu__debug_assert(self);

		self->addr = LU_N_ADDR__NULL;
		self->labels = NULL;

		return self;
	}

	static inline lu_bool lu_label_unit__is_blank(Lu_Label_Unit self)
	{
		lu__debug_assert(self);

		return lu_n_addr__is_blank(&self->addr);
	}

	static inline lu_bool lu_label_unit__is_match(Lu_Label_Unit self, union lu_n_addr addr)
	{
		lu__debug_assert(self);

		if (lu_label_unit__is_blank(self)) return true;

		return lu_n_addr__is_eq(&self->addr, &addr);
	}

	static inline Lu_Label lu_label_unit__inc(Lu_Label_Unit self, lu_size label_ix)
	{
		lu__debug_assert(self);

		Lu_Label label = &self->labels[label_ix];

		if (lu_label__is_blank(label)) 
		{
			label->label = label_ix;
			label->count = 1;
		}
		else
		{
			++label->count;
		}

		return label;
	}

	static Lu_Label_Unit lu_label_unit__init(Lu_Label_Unit self, Lu_Mem mem, union lu_n_addr addr, lu_size size);
	static void lu_label_unit__deinit(Lu_Label_Unit self, Lu_Mem mem);

///////////////////////////////////////////////////////////////////////////////
// Lu_Label_Map

	struct lu_label_map {
		Lu_Mem mem;
		
		lu_size labels_size;
		lu_size h;
		lu_size d;

		// Addr to labels, h x d hash/map
		struct lu_label_unit *addr_to_labels;

		// Label to addrs, where lu_list contains address (&) to Lu_Label_Unit in addr_to_labels.
		struct lu_list *label_to_addrs;
	};

	static Lu_Label_Map lu_label_map__init(Lu_Label_Map self, Lu_Mem mem, lu_size labels_size, lu_size h, lu_size d);
	static void lu_label_map__deinit(Lu_Label_Map self);

	static inline lu_size lu_label_map__addr_to_ix(Lu_Label_Map self, union lu_n_addr addr)
	{
		return lu_hash_comb(0, addr.value) % self->h;
	}

	//
	//
	//

	static Lu_Label lu_label_map__add_label(Lu_Label_Map self, union lu_n_addr addr, lu_size label);
	static Lu_Label_Unit lu_label_map__get_labels(Lu_Label_Map self, union lu_n_addr addr);
	static Lu_List lu_label_map__get_units(Lu_Label_Map self, lu_size label);






