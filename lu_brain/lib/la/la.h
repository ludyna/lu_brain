/**
	Copyright © 2022 Oleh Ihorovych Novosad 

*/


///////////////////////////////////////////////////////////////////////////////
// Lu_Label

	// Lu_Label for end User
	struct lu_label {
		Lu_La_Cell la_cell;
		Lu_W_Match_Cell match_cell;
	};

	static inline Lu_Label lu_label__init(
		Lu_Label self, 
		Lu_La_Cell la_cell,
		Lu_W_Match_Cell match_cell
	)
	{
		self->la_cell = la_cell;
		self->match_cell = match_cell;

		return self;
	} 

	static lu_value lu_label__compare(lu_p_void p_1, lu_p_void p_2)
	{
		Lu_Label label_1 = (Lu_Label) p_1;
		Lu_Label label_2 = (Lu_Label) p_2;

		lu_value sig_1 = 0;
		lu_value sig_2 = 0;

		if (label_1 && label_1->match_cell)
			sig_1 = label_1->match_cell->sig;

		if (label_2 && label_2->match_cell)
			sig_2 = label_2->match_cell->sig;

		return sig_2 - sig_1;
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_La_Cell

	struct lu_la_cell {
		union lu_la_addr addr;

		union lu_n_link_addr children;
		lu_size children_count;

		union lu_w_match_addr* w_cells;
	};

	//
	// Constructor / Destructor
	//

	static inline Lu_La_Cell lu_la_cell__init(Lu_La_Cell self, lu_size label, Lu_Mem w_mem, lu_size w_save_waves_size)
	{
		lu__debug_assert(self);

		self->addr.la_ix = label;
		self->children = LU_N_LINK_ADDR__NULL;
		self->children_count = 0;
		self->w_cells = (union lu_w_match_addr*) lu_mem__alloc(w_mem, sizeof(union lu_w_match_addr) * w_save_waves_size);
		lu__alloc_assert(self->w_cells);

		return self;
	}

	static inline void lu_la_cell__deinit(Lu_La_Cell self, Lu_Mem w_mem)
	{
		lu__assert(self);
		lu__assert(w_mem);

		if (self->w_cells)
			lu_mem__free(w_mem, (lu_p_byte) self->w_cells);

		self->children = LU_N_LINK_ADDR__NULL;
		self->children_count = 0;
		self->w_cells = 0;
	}

	//
	// Get / Set
	//

	static inline union lu_w_match_addr lu_la_cell__get_w_match_cell_addr(Lu_La_Cell self, lu_size wave_ix)
	{
		lu__assert(self);
		return self->w_cells[wave_ix];
	}

	static inline void lu_la_cell__set_w_mach_cell_addr(Lu_La_Cell self, lu_size wave_id, union lu_w_match_addr w_addr)
	{
		self->w_cells[wave_id] = w_addr;
	}

	static inline lu_size lu_la_cell__get_ix(Lu_La_Cell self)
	{
		lu__assert(self);
		return lu_la_addr__get_la_ix(&self->addr);
	}

	//
	// Is
	//

	static inline lu_bool lu_la_cell__is_child(Lu_La_Cell self, union lu_n_addr n_addr, Lu_N_Link_Mem n_link_mem)
	{
		lu__debug_assert(self);
		lu__debug_assert(n_link_mem);

		Lu_N_Link n_link = lu_n_link_mem__get_link(n_link_mem, self->children);

		while (n_link)
		{
			if (lu_n_addr__is_eq(&n_link->cell_addr, &n_addr)) return true;

			// Will be NULL for &LU_N_LINK_ADDR__NULL (addr.value == 0)
			n_link = lu_n_link_mem__get_link(n_link_mem, n_link->next);
		}

		return false;
	}

	//
	// Methods
	// 

	static inline void lu_la_cell__prepend_child(Lu_La_Cell self, union lu_n_addr n_addr, Lu_N_Link_Mem n_link_mem)
	{
		lu__assert(self);
		lu__assert(n_link_mem);

		// New child link
		Lu_N_Link n_link = lu_n_link_mem__link_alloc(n_link_mem);
		lu__assert(n_link);

		n_link->next = self->children;  

		n_link->cell_addr = n_addr;

		self->children = lu_n_link_mem__get_addr(n_link_mem, n_link);
		lu__assert(lu_n_link_addr__is_present(&self->children));

		++self->children_count;
	}


	static inline Lu_W_Match_Cell lu_la_cell__get_and_reset_match_cell(
		Lu_La_Cell self,
		struct lu_block_id block_id,
		lu_size wave_ix,
		Lu_W_Match_Cell_Mem match_cell_mem
	)
	{
		union lu_w_match_addr match_addr = lu_la_cell__get_w_match_cell_addr(self, wave_ix);

		Lu_W_Match_Cell match_cell = NULL;
		if (lu_w_match_addr__is_blank(&match_addr))
		{
			lu__debug("\n !! lu_w_match_addr__is_blank(): wave_ix=%ld", wave_ix);

			match_cell = lu_w_match_cell_mem__cell_alloc(match_cell_mem);
			match_addr = lu_w_match_cell_mem__get_addr(match_cell_mem, match_cell);

			lu_la_cell__set_w_mach_cell_addr(self, wave_ix, match_addr);

			lu_w_match_cell__init(match_cell, block_id, 0);
			
			return match_cell;
		}

		match_cell = lu_w_match_cell_mem__get_cell(match_cell_mem, match_addr);
		lu__assert(match_cell);

		lu__debug("\n !! lu_w_match_cell_mem__get_cell()");
		lu_w_match_cell__print(match_cell);

		if (lu_block_id__is_not_eq(&match_cell->block_id, &block_id))
		{
			// reset
			lu__debug("\n !! lu_w_match_cell__init(match_cell, block_id, 0);");
			lu_w_match_cell__init(match_cell, block_id, 0);
		}

		return match_cell;
	}

	static inline void lu_la_cell__print(Lu_La_Cell self)
	{
		lu__debug(
			"LA_IX=%ld, children_count=%ld, children_present?=%s", 
			self->addr.la_ix, 
			self->children_count, 
			lu_n_link_addr__is_present(&self->children) ? "Y" : "N"
		);
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_La_Link

	struct lu_la_link {
		union lu_la_addr la_addr;

		union lu_la_link_addr next;
	}; 

	static inline Lu_La_Link lu_la_link__init(Lu_La_Link self, union lu_la_addr la_addr, union lu_la_link_addr next)
	{
		self->la_addr = la_addr;
		self->next = next;

		return self;
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_La_Link_Mem

	struct lu_la_link_mem {
		Lu_Mem_Table mem_table;
	};

	//
	// Constructors / Destructors
	// 

	Lu_La_Link_Mem lu_la_link_mem__init(Lu_La_Link_Mem self, Lu_Mem mem, lu_size size);
	void lu_la_link_mem__deinit(Lu_La_Link_Mem self);

	//
	// Get
	//

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
	
	//
	// Methods
	//

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



///////////////////////////////////////////////////////////////////////////////
// Lu_La_Column
	
	////
	// Basically this is part of network (n).
	struct lu_la_column {
		Lu_Mem la_mem;
		Lu_Mem w_mem;
		Lu_Mem n_mem;

		struct lu_la_cell* cells;
		lu_size cells_size;

		struct lu_n_link_mem n_link_mem;
		struct lu_la_link_mem la_link_mem;

		lu_size w_save_waves_size;
	};

	static Lu_La_Column lu_la_column__init(Lu_La_Column self, Lu_Config config);

	static void lu_la_column__deinit(Lu_La_Column self);

	static inline Lu_N_Link_Mem lu_la_column__get_n_link_mem(Lu_La_Column self)
	{
		lu__debug_assert(self);

		return &self->n_link_mem;
	}

	static inline Lu_La_Link_Mem lu_la_column__get_la_link_mem(Lu_La_Column self)
	{
		lu__debug_assert(self);

		return &self->la_link_mem;
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

	static inline Lu_La_Cell lu_la_column__get_la_cell_by_addr(Lu_La_Column self, union lu_la_addr addr)
	{
		lu__debug_assert(self);

		return lu_la_column__get_la_cell(self, addr.la_ix);
	}

	static inline Lu_La_Cell lu_la_column__save_label(Lu_La_Column self, Lu_N_Cell n_cell, lu_size label)
	{
		lu__assert(self);
		lu__assert(n_cell);
		lu__assert(label < self->cells_size);

		Lu_La_Cell la_cell = &self->cells[lu_la_column__label_to_ix(self, label)];

		if (lu_la_cell__is_child(la_cell, n_cell->addr, &self->n_link_mem)) return la_cell;
		
		lu__debug("\nLA_CELL (n_cell->cell_ix=%ld) ", n_cell->addr.cell_ix);
		lu_la_cell__print(la_cell);

		lu_la_cell__prepend_child(la_cell, n_cell->addr, &self->n_link_mem);
		lu_n_cell__prepend_label(n_cell, la_cell->addr, &self->la_link_mem);

		lu__debug("\nLA_CELL (n_cell->cell_ix=%ld) ", n_cell->addr.cell_ix);
		lu_la_cell__print(la_cell);

		return la_cell;
	}
