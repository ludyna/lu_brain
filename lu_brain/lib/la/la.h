/**
	Copyright © 2022 Oleh Ihorovych Novosad 

*/


///////////////////////////////////////////////////////////////////////////////
// Lu_La_Cell

	struct lu_la_cell {
		union lu_la_addr addr;

		Lu_N_Link children;
		lu_size children_count;

		union lu_w_match_addr* w_cells;
	};

	static inline Lu_La_Cell lu_la_cell__init(Lu_La_Cell self, lu_size label, Lu_Mem w_mem, lu_size w_waves_size)
	{
		lu__debug_assert(self);

		self->addr.la_ix = label;
		self->children = NULL;
		self->children_count = 0;
		self->w_cells = (union lu_w_match_addr*) lu_mem__alloc(w_mem, sizeof(union lu_w_match_addr) * w_waves_size);
		lu__alloc_assert(self->w_cells);

		return self;
	}

	static inline Lu_La_Cell lu_la_cell__deinit(Lu_La_Cell self, Lu_Mem w_mem)
	{
		lu__assert(self);
		lu__assert(w_mem);

		if (self->w_cells)
			lu_mem__free(w_mem, (lu_p_byte) self->w_cells);

		self->children = NULL;
		self->children_count = 0;
		self->w_cells = 0;
	}

	static inline lu_bool lu_la_cell__child_exist(Lu_La_Cell self, Lu_N_Addr n_addr)
	{
		return false;
	}

	static inline Lu_N_Link lu_la_cell__prepend_child(Lu_La_Cell self, union lu_n_addr n_addr, Lu_N_Link_Mem n_link_mem)
	{

	}

///////////////////////////////////////////////////////////////////////////////
// Lu_La_Link

	struct lu_la_link {
		union lu_la_addr la_addr;

		union lu_la_link_addr next;
	}; 

///////////////////////////////////////////////////////////////////////////////
// Lu_La_Link_Mem

	struct lu_la_link_mem {
		Lu_Mem_Table mem_table;
	};

	Lu_La_Link_Mem lu_la_link_mem__init(Lu_La_Link_Mem self, Lu_Mem mem, lu_size size);
	void lu_la_link_mem__deinit(Lu_La_Link_Mem self);

	static inline Lu_La_Link lu_la_link_mem__link_alloc(Lu_La_Link_Mem self)
	{
		lu__debug_assert(self);

		lu_p_byte record = lu_mem_record__alloc(self->mem_table);

		if (!record)
		{
			lu_mem_table__realloc(
				self->mem_table, 
				lu_mem_table__records_count(self->mem_table) * 2, 
				LU_MEM_TABLE__DEFAULT
			); 

			record = lu_mem_record__alloc(self->mem_table);
			lu__assert(record);
		}

		return (Lu_La_Link) record;
	}

	static inline Lu_La_Link lu_la_link_mem__get_link(Lu_La_Link_Mem self, union lu_la_link_addr addr)
	{
		lu__debug_assert(self);
		lu__debug_assert(self->mem_table);

		if (addr.value == 0) return NULL;

		return (Lu_La_Link) lu_mem_table__get(self->mem_table, addr.value);
	}

	////
	// 
	static inline union lu_la_link_addr lu_la_link_mem__get_addr(Lu_La_Link_Mem self, Lu_La_Link link)
	{
		lu__debug_assert(self);
		lu__debug_assert(link);

		union lu_la_link_addr addr;

		addr.value = lu_mem_table__record_ix(self->mem_table, (lu_p_byte) link);

		return addr;
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_La_Column
	
	struct lu_la_column {
		Lu_Mem la_mem;
		Lu_Mem w_mem;
		Lu_Mem n_mem;

		struct lu_la_cell* cells;
		lu_size cells_size;

		Lu_N_Link_Mem n_link_mem;
		Lu_La_Link_Mem la_link_mem;

		lu_size w_waves_size;
	};

	static Lu_La_Column lu_la_column__init(Lu_La_Column self, Lu_Config config);

	static void lu_la_column__deinit(Lu_La_Column self);

	static inline Lu_N_Link_Mem lu_la_column__get_n_link_mem(Lu_La_Column self)
	{
		lu__debug_assert(self);

		return self->n_link_mem;
	}

	static inline lu_size lu_la_column__label_to_ix(Lu_La_Column self, lu_size label)
	{
		lu__debug_assert(self);

		lu__assert(label < self->cells_size); // simplified, when we add realloc, everything will be fine

		return label;
	}

	static inline Lu_La_Cell lu_la_column__get_la_cell(Lu_La_Column self, lu_size label)
	{
		lu__debug_assert(self);

		lu_size label_ix = lu_la_column__label_to_ix(self, label);

		return &self->cells[label_ix];
	}

	static inline Lu_La_Cell lu_la_column__save_label(Lu_La_Column self, Lu_N_Cell n_cell, lu_size label)
	{
		lu__assert(self);
		lu__assert(n_cell);
		lu__assert(label < self->cells_size);

		Lu_La_Cell la_cell = &self->cells[lu_la_column__label_to_ix(self, label)];

		if (lu_la_cell__child_exist(la_cell, &n_cell->addr)) return la_cell;
		
		lu_la_cell__prepend_child(la_cell, n_cell->addr, self->n_link_mem);

		lu_n_cell__prepend_label(n_cell, la_cell->addr, self->la_link_mem);

		return la_cell;
	}
