/**
	Copyright © 2022 Oleh Ihorovych Novosad 

*/


///////////////////////////////////////////////////////////////////////////////
// Lu_Label

	// Lu_Label for end User
	struct lu_label {
		Lu_La_Cell la_cell;
		Lu_W_La_Match_Cell match_cell;
	};

	static inline Lu_Label lu_label__init(
		Lu_Label self, 
		Lu_La_Cell la_cell,
		Lu_W_La_Match_Cell match_cell
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
		{
			// sig_1 = label_1->match_cell->sig;
			sig_1 = lu_w_la_match_cell__get_sig(label_1->match_cell);
		}

		if (label_2 && label_2->match_cell)
		{
			//sig_2 = label_2->match_cell->sig;
			sig_2 = lu_w_la_match_cell__get_sig(label_2->match_cell);
		}

		lu_value diff = sig_2 - sig_1;

		if (diff < 0 ) diff = -diff;

		if (diff < 0.01)
		{
			return lu_w_la_match_cell__get_sig_received_count(label_2->match_cell) - 
					lu_w_la_match_cell__get_sig_received_count(label_1->match_cell);
		}

		return sig_2 - sig_1;
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_La_Cell

	// Temporary shortcut
	#define LU_LA_CELL__MATCH_CELLS_SIZE 1

	struct lu_la_cell {
		union lu_la_addr addr;

		union lu_n_link_addr children;
		lu_size children_count;

		//union lu_w_match_addr* w_cells;

		struct lu_w_la_match_cell w_match_cells[LU_LA_CELL__MATCH_CELLS_SIZE];
	};

	//
	// Constructor / Destructor
	//

	static inline Lu_La_Cell lu_la_cell__init(Lu_La_Cell self, lu_size label, Lu_Mem w_mem, lu_size w_match_waves_size)
	{
		lu__debug_assert(self);

		self->addr.la_ix = label;
		self->children = LU_N_LINK_ADDR__NULL;
		self->children_count = 0;
		// self->w_cells = (union lu_w_match_addr*) lu_mem__alloc(w_mem, sizeof(union lu_w_match_addr) * w_match_waves_size);
		// lu__alloc_assert(self->w_cells);

		Lu_W_La_Match_Cell match_cell;
		for (lu_size i = 0; i < LU_LA_CELL__MATCH_CELLS_SIZE; i++)
		{
			match_cell = &self->w_match_cells[i];
			lu_w_la_match_cell__reset(match_cell);
		}

		return self;
	}

	static inline void lu_la_cell__deinit(Lu_La_Cell self, Lu_Mem w_mem)
	{
		lu__assert(self);
		lu__assert(w_mem);

		// if (self->w_cells)
		// 	lu_mem__free(w_mem, (lu_p_byte) self->w_cells);

		self->children = LU_N_LINK_ADDR__NULL;
		self->children_count = 0;
		// self->w_cells = 0;
	}

	static inline void lu_la_cell__reset(Lu_La_Cell self)
	{
		lu__assert(self);

		self->children = LU_N_LINK_ADDR__NULL;
		self->children_count = 0;
	}

	//
	// Get / Set
	//

	// static inline union lu_w_match_addr lu_la_cell__get_w_match_cell_addr(Lu_La_Cell self, lu_size wave_ix)
	// {
	// 	lu__assert(self);
	// 	return self->w_cells[wave_ix];
	// }

	// static inline void lu_la_cell__set_w_mach_cell_addr(Lu_La_Cell self, lu_size wave_id, union lu_w_match_addr w_addr)
	// {
	// 	self->w_cells[wave_id] = w_addr;
	// }

	static inline lu_size lu_la_cell__get_ix(Lu_La_Cell self)
	{
		lu__assert(self);
		return lu_la_addr__get_la_ix(&self->addr);
	}

	static inline Lu_W_La_Match_Cell lu_la_cell__get_w_match_cell(Lu_La_Cell self, lu_size wave_ix)
	{
		lu__assert(self);
		lu__assert(wave_ix < LU_LA_CELL__MATCH_CELLS_SIZE);
		
		return &self->w_match_cells[wave_ix];
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
			if (lu_n_addr__is_eq(&n_link->n_cell_addr, &n_addr)) return true;

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
		Lu_N_Link n_link = lu_n_link_mem__alloc_link(n_link_mem);
		lu__assert(n_link);

		n_link->next = self->children;  

		n_link->n_cell_addr = n_addr;

		self->children = lu_n_link_mem__get_addr(n_link_mem, n_link);
		lu__assert(lu_n_link_addr__is_present(&self->children));

		++self->children_count;
	}


	// static inline Lu_W_Match_Cell lu_la_cell__get_and_reset_match_cell(
	// 	Lu_La_Cell self,
	// 	struct lu_block_id block_id,
	// 	lu_size wave_ix,
	// 	Lu_W_Match_Cell_Mem match_cell_mem
	// )
	// {
	// 	union lu_w_match_addr match_addr = lu_la_cell__get_w_match_cell_addr(self, wave_ix);

	// 	Lu_W_Match_Cell match_cell = NULL;
	// 	if (lu_w_match_addr__is_blank(&match_addr))
	// 	{
	// 		lu__deep_debug("\n !! lu_w_match_addr__is_blank(): wave_ix=%ld", wave_ix);

	// 		match_cell = lu_w_match_cell_mem__cell_alloc(match_cell_mem);
	// 		match_addr = lu_w_match_cell_mem__get_addr(match_cell_mem, match_cell);

	// 		lu_la_cell__set_w_mach_cell_addr(self, wave_ix, match_addr);

	// 		lu_w_match_cell__init(match_cell, block_id);
			
	// 		return match_cell;
	// 	}

	// 	match_cell = lu_w_match_cell_mem__get_cell(match_cell_mem, match_addr);
	// 	lu__assert(match_cell);

	// 	lu__deep_debug("\n !! lu_w_match_cell_mem__get_cell()");
	// 	#ifdef LU__DEEP_DEBUG
	// 	lu_w_match_cell__print(match_cell);
	// 	#endif

	// 	if (lu_block_id__is_not_eq(&match_cell->block_id, &block_id))
	// 	{
	// 		// reset
	// 		lu__deep_debug("\n !! lu_w_match_cell__init(match_cell, block_id, 0);");
	// 		lu_w_match_cell__init(match_cell, block_id);
	// 	}

	// 	return match_cell;
	// }

	static inline Lu_W_La_Match_Cell lu_la_cell__get_and_reset_match_cell(
		Lu_La_Cell self,
		struct lu_block_id block_id,
		lu_size wave_ix,
		Lu_W_Match_Cell_Mem match_cell_mem
	)
	{
		lu__assert(self);

		Lu_W_La_Match_Cell match_cell = lu_la_cell__get_w_match_cell(self, wave_ix);
		lu__assert(match_cell);

		if (lu_block_id__is_not_eq(&match_cell->block_id, &block_id))
		{
			// reset
			lu__deep_debug("\n !! lu_w_match_cell__init(match_cell, block_id, 0);");
			lu_w_la_match_cell__init(match_cell, block_id);
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

		lu_size w_match_waves_size;
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

		if (label >= self->cells_size)
		{
			return LU_SIZE__MAX;
		}

		return label;
	}

	static inline Lu_La_Cell lu_la_column__get_la_cell(Lu_La_Column self, lu_size label)
	{
		lu__debug_assert(self);

		lu_size label_ix = lu_la_column__label_to_ix(self, label);

		if (label_ix == LU_SIZE__MAX) return NULL;

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

		// Do not create link if it already exists
		if (lu_la_cell__is_child(la_cell, n_cell->addr, &self->n_link_mem)) return la_cell;
		
		lu__deep_debug("\nLA_CELL (n_cell->cell_ix=%ld) ", n_cell->addr.cell_ix);
		#ifdef LU__DEEP_DEBUG
		lu_la_cell__print(la_cell);
		#endif

		lu_la_cell__prepend_child(la_cell, n_cell->addr, &self->n_link_mem);
		lu_n_cell__prepend_label(n_cell, la_cell->addr, &self->la_link_mem);

		lu__deep_debug("\nLA_CELL (n_cell->cell_ix=%ld) ", n_cell->addr.cell_ix);
		#ifdef LU__DEEP_DEBUG
		lu_la_cell__print(la_cell);
		#endif

		return la_cell;
	}