/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// N_Cells 
//
// Putting it here instead of _typedef.h to make it visible and to resolve circle referencing.
// These typedefs are not part of this module. It is why they don't go to _typedef.h.

	typedef struct lu_n_cell* Lu_N_Cell;
	typedef struct lu_n_cell_vp* Lu_N_Cell_VP;
	typedef struct lu_n_column_comp* Lu_N_Column_Comp;
	typedef struct lu_n_column* Lu_N_Column;
	typedef struct lu_n_table_comp* Lu_N_Table_Comp;

	static inline lu_value lu_n_cell__get_default_sig(Lu_N_Cell self);
	static inline Lu_N_Addr lu_n_cell_vp__get_cell_addr(Lu_N_Cell_VP self);
	static inline Lu_N_Addr lu_n_cell__get_cell_addr(Lu_N_Cell self);

	static inline Lu_N_Cell_VP lu_n_table_comp__get_cell(Lu_N_Table_Comp self, lu_size x, lu_size y, lu_size z);
	static inline Lu_N_Column_Comp lu_n_table_comp__get_column(Lu_N_Table_Comp self, lu_size x, lu_size y);
	static inline Lu_N_Cell_VP lu_n_column_comp__get_cell(Lu_N_Column_Comp self, lu_size z);

	enum lu_w_rec_state {
		LU_W_REC_STATE__COLLECT,
		LU_W_REC_STATE__COLLECT_AND_FINISH,
		LU_W_REC_STATE__END
	};

///////////////////////////////////////////////////////////////////////////////
//  Lu_W_Addr

	#define LU_W_CELL_IX__SIZE 40

	union lu_w_addr {
		struct {
			lu_size cell_ix: LU_W_CELL_IX__SIZE;
			lu_size layer_ix: LU_N_LAYER_IX__SIZE;
			lu_size area_ix: LU_N_AREA_IX__SIZE;
		};
		lu_size value;
	};

	// NULL addr
	extern const union lu_w_addr LU_W_ADDR__NULL; 

	static inline lu_bool lu_w_addr__is_blank(Lu_W_Addr self)
	{
		return (self->value == 0);
	}

	static inline lu_bool lu_w_addr__is_present(Lu_W_Addr self)
	{
		return (self->value != 0);
	}

	static inline void lu_w_addr__set_to_null(Lu_W_Addr self)
	{
		self->value = 0;
	}

	static inline lu_bool lu_w_addr__is_eq(Lu_W_Addr self, Lu_W_Addr b)
	{
		return self->value == b->value;
	}

	static inline void lu_w_addr__print(Lu_W_Addr self)
	{
		lu__debug("%d:%d:%d", self->area_ix, self->layer_ix, self->cell_ix);
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_W_Cell - winner cell

	////
	// We are using this cell and related "infrastructure" for both save and restore operations.
	struct lu_w_cell {
		Lu_N_Cell n_cell;
		Lu_N_Column n_column;
	};

	//
	// Constructors / Destructors
	//

	static inline void lu_w_cell__reset(Lu_W_Cell self)
	{
		lu__debug_assert(self);

		self->n_cell = NULL;
		self->n_column = NULL;
	}

	//
	// Is / Has
	//

	static inline lu_bool lu_w_cell__is_not_set(Lu_W_Cell self)
	{
		lu__assert(self);

		return (self->n_cell == NULL) || (self->n_column == NULL);
	}

 	static inline lu_bool lu_w_cell__is_set(Lu_W_Cell self)
	{
		return !lu_w_cell__is_not_set(self);
	}

	static inline lu_bool lu_w_cell__has_null_n_cell(Lu_W_Cell self)
	{
		if (self == NULL) return false;
		if (self->n_cell == NULL) return false;

		return lu_n_addr__get_cell_ix(lu_n_cell__get_cell_addr(self->n_cell)) == 0;
	}

	//
	// Methods
	//

	static inline Lu_W_Cell lu_w_cell__save(
		Lu_W_Cell self,
		Lu_N_Cell n_cell,
		Lu_N_Column n_column
	)
	{
		lu__assert(self);

		self->n_cell = n_cell;
		self->n_column = n_column;

		return self;
	}

	static inline void lu_w_cell__print_symbol(Lu_W_Cell self)
	{
		if (self == NULL)
		{
			lu__debug("0 ");
		}
		else if (lu_w_cell__is_not_set(self))
		{
			lu__debug("E ");
		}
		else if (lu_w_cell__has_null_n_cell(self))
		{
			lu__debug("N ");
		}
		else
		{
			lu__debug("X ");
		}
	}

	static inline void lu_w_cell__find_matching_parent(
		Lu_W_Cell self,
		Lu_Block_Id block_id,
		lu_size wave_ix,
		Lu_W_Save_Cell* max_w_save_cell,
		Lu_N_Cell* max_n_cell
	);

	static inline lu_size lu_w_cell__children_hash_comp(Lu_W_Cell* children, lu_size children_count)
	{
		lu_size p_reg = 0;

		Lu_W_Cell w_cell;
		lu_size value;
		for (lu_size i = 0; i < children_count; i++)
		{
			w_cell = children[i];
			lu__assert(w_cell);
			lu__assert(w_cell->n_cell); // this is correct

			value = lu_n_cell__get_cell_addr(w_cell->n_cell)->value;

			p_reg = lu_calc__hash_comb(p_reg, value);
		}

		return p_reg;
	}
 
///////////////////////////////////////////////////////////////////////////////
// Lu_W_Cell_P

	struct lu_w_cell_p {
		
		Lu_N_Cell_VP n_cell_vp;
		Lu_N_Column_Comp n_column_comp;
		
		// sig doesn't make much sense for save cell, but
		// we have it here to indicate if cell was active (not "null" cell)
		lu_value sig;

		lu_value p_1;
		lu_value p_2;
	};

	//
	// Constructors / Destructors
	// 

	static inline void lu_w_cell_p__reset(Lu_W_Cell_P self)
	{
		lu__debug_assert(self);

		self->n_column_comp = NULL;
		self->n_cell_vp = NULL;
		self->sig = 0;
		self->p_1 = 0;
		self->p_2 = 0;
	}

	//
	// Is
	// 

	static inline lu_bool lu_w_cell_p__is_not_set(Lu_W_Cell_P self)
	{
		lu__assert(self);

		return (self->n_cell_vp == NULL) || (self->n_column_comp == NULL);
	}

 	static inline lu_bool lu_w_cell_p__is_set(Lu_W_Cell_P self)
	{
		return !lu_w_cell_p__is_not_set(self);
	}

	static inline lu_bool lu_w_cell_p__has_null_n_cell(Lu_W_Cell_P self)
	{
		if (self == NULL) return false;
		if (self->n_cell_vp == NULL) return false;

		return lu_n_addr__get_cell_ix(lu_n_cell_vp__get_cell_addr(self->n_cell_vp)) == 0;
	}

	//
	// Methods
	//

	static inline lu_value lu_w_cell_p__calc_p(Lu_W_Cell_P self)
	{
		lu_value p = self->p_2 - self->p_1;

		#pragma GCC diagnostic ignored "-Wunused-value"
			p < 0 && (p = -p); 
		#pragma GCC diagnostic pop 

		return p;
	}

	////
	//
	static inline Lu_W_Cell_P lu_w_cell_p__save(
		Lu_W_Cell_P self, 
		lu_size x,
		lu_size y, 
		Lu_Comp_Calc comp_calc, 
		Lu_N_Table_Comp n_table
	)
	{
		lu_value p = lu_w_cell_p__calc_p(self);

		lu_size z = 0; // points to NULL cell by default

		// By default, we will not fire
		// sig doesn't matter for saving, but it is just to indicate 
		// if was active or not
		self->sig = 0;

		if (p >= comp_calc->step)
		{
			p = lu_comp_calc__norm(comp_calc, p);
			z = lu_comp_calc__ix(comp_calc, p);

			// We will fire this cell only p >= comp_calc->step
			self->sig = 1.0;
		}

		// If difference between p_1 and p_2 is small, z will 0, which means its "NULL" cell
		// z being 0 doesnt mean addr->cell_x is 0 (!)
		
		self->n_column_comp = lu_n_table_comp__get_column(n_table, x, y);
		self->n_cell_vp = lu_n_column_comp__get_cell(self->n_column_comp, z);

		lu__debug_assert(self->n_cell_vp);

		return self;
	}

	static inline lu_size lu_w_cell_p__children_hash_comp(Lu_W_Cell_P* children, lu_size children_count)
	{
		lu_size p_reg = 0;

		Lu_W_Cell_P w_cell;
		for (lu_size i = 0; i < children_count; i++)
		{
			w_cell = children[i];
			lu__debug_assert(w_cell);
			lu__debug_assert(w_cell->n_cell_vp);

			p_reg = lu_calc__hash_comb(p_reg, lu_n_cell_vp__get_cell_addr(w_cell->n_cell_vp)->value);
		}

		return p_reg;
	}

	static inline void lu_w_cell_p__collect_and_shift(Lu_W_Cell_P self, lu_value v)
	{
		self->p_1 = self->p_2;
		self->p_2 = v;
	}

	static inline void lu_w_cell_p__print(Lu_W_Cell_P self)
	{
		lu__assert(self);

		lu__debug(
			"\nLU_W_CELL_P: n_column=%s, n_cell=%s, sig=%.1f, p_1=%.1f, p_2=%.1f",
			self->n_column_comp ? "Y" : "N", 
			self->n_cell_vp ? "Y" : "N",
			self->sig,
			self->p_1,
			self->p_2
		);
	}

	static inline void lu_w_cell_p__print_symbol(Lu_W_Cell_P self)
	{
		if (self == NULL)
		{
			lu__debug("00 "); // error
		}
		else if (lu_w_cell_p__is_not_set(self))  // (self->n_cell == NULL) || (self->n_column == NULL)
		{
			lu__debug("EE "); // error
		}
		else if (lu_w_cell_p__has_null_n_cell(self)) // self->n_cell->addr.cell_ix == 0
		{
			lu__debug("NN "); // just null (no changes for p)
		}
		else
		{
			char buff[4];
			sprintf(buff, "%.0f", self->p_2 - self->p_1);
			lu__debug("%2s ", buff); // value
		}
	}

///////////////////////////////////////////////////////////////////////////////
// lu_w_children_p

	static void lu_w_children_p__reset_children(Lu_W_Cell_P* children, lu_size depth)
	{
		lu__assert(children);

		for (lu_size i = 0; i < depth; i++)
		{
			children[i] = NULL;
		}
	}

///////////////////////////////////////////////////////////////////////////////
//  lu_w_children

	static inline void lu_w_children__print_symbols(Lu_W_Cell* self, lu_size children_count)
	{
		lu__assert(self);

		lu__debug("\nCHILDREN(count=%ld): ", children_count);
		Lu_W_Cell w_cell;
		for (lu_size i = 0; i < children_count; i++)
		{
			w_cell = self[i];
			lu_w_cell__print_symbol(w_cell);
		}
	}

	static inline void lu_w_children__reset(Lu_W_Cell* self, lu_size children_count)
	{
		lu__assert(self);
		for (lu_size i = 0; i < children_count; i++)
		{
			self[i] = NULL;
		}
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_W_Cell_V

	#define LU_W_SAVE_CELL_V__NOT_SET 0
	#define LU_W_SAVE_CELL_V__READY 1

	struct lu_w_cell_v {
		union lu_n_addr n_addr;
		lu_value sig;

		lu_byte state;
		lu_value v;
	};

	static inline void lu_w_cell_v__register(
		Lu_W_Cell_V self, 
		lu_bool is_reset,
		lu_value v, 
		Lu_Process_Config config
	)
	{
		self->v = v;
		self->state = LU_W_SAVE_CELL_V__READY;
	}

	static inline lu_bool lu_w_cell_v__is_ready(Lu_W_Cell_V self)
	{
		return self->state == LU_W_SAVE_CELL_V__READY;
	}

	static inline void lu_w_cell_v__save(
		Lu_W_Cell_V self, 
		lu_size x,
		lu_size y, 
		Lu_Comp_Calc comp_calc, 
		Lu_N_Table_Comp n_table
	)
	{
		// lu_value v = self->v;
		// v = lu_comp_calc__norm(comp_calc, v);
		// lu_size column_ix = lu_comp_calc__ix(comp_calc, v);

		// self->n_addr = lu_n_table_comp__get_cell(n_table, x, y, column_ix)->addr;
		// self->sig = 1.0;
	}

	static inline void lu_w_cell_v__reset(Lu_W_Cell_V self)
	{
		self->state = LU_W_SAVE_CELL_V__NOT_SET;
		self->sig = 0;
	}

///////////////////////////////////////////////////////////////////////////////
//  Lu_W_Match_Addr

	////
	// Using as an index in Lu_W_Match_Cell_Mem so reallocation will not break pointer
	union lu_w_match_addr {
		lu_size value;
	};

	// NULL addr
	extern const union lu_w_match_addr LU_W_MATCH_ADDR__NULL; 

	static inline void lu_w_match_addr__reset(Lu_W_Match_Addr self)
	{
		self->value = LU_W_MATCH_ADDR__NULL.value;
	}

	static inline lu_bool lu_w_match_addr__is_blank(Lu_W_Match_Addr self)
	{
		return self->value == LU_W_MATCH_ADDR__NULL.value;
	}


///////////////////////////////////////////////////////////////////////////////
//  Lu_W_Match_Cell 

	struct lu_w_match_cell {
		struct lu_block_id block_id;
		lu_value sig;

		// We need fired flag, because with breakpoint 0.5 or less cells can fire more than one time
		lu_bool fired;
	};

	//
	// Constructors / Destructors
	//

	static inline Lu_W_Match_Cell lu_w_match_cell__init(
		Lu_W_Match_Cell self, 
		struct lu_block_id block_id
	)
	{	
		lu__assert(lu_block_id__is_set(&block_id));

		self->block_id = block_id;
		self->sig = 0;
		self->fired = false;

		return self;
	}


	//
	// Methods
	//

	static inline void lu_w_match_cell__add_sig(Lu_W_Match_Cell self, lu_value sig)
	{
		self->sig += sig;
	}

	static inline lu_bool lu_w_match_cell__is_sig_over_breakpoint(Lu_W_Match_Cell self, Lu_N_Cell n_cell, lu_value breakpoint)
	{
		if (self->fired) return false;
		
		lu_value def_sig = lu_n_cell__get_default_sig(n_cell);
		lu_value res_sig = def_sig - self->sig;

		lu__assert(res_sig >= 0); // should never go below 0

		// lu__debug(
		// 	"\n def_sig: %.1f, sig: %.1f, res_sig: %.1f, (def_sig * breakpoint): %.1f, res: %d",
		// 	def_sig,
		// 	self->sig,
		// 	res_sig,
		// 	(def_sig * breakpoint),
		// 	self->sig >= (def_sig * breakpoint)
		// );

		return self->sig >= (def_sig * breakpoint);
	}

	static inline lu_value lu_w_match_cell__calc_fire_sig(Lu_W_Match_Cell self, lu_value default_sig)
	{
		return self->sig / default_sig;
	}

	static inline lu_bool lu_w_match_cell__no_sig(Lu_W_Match_Cell self)
	{
		return self->sig == 0;
	}

	static inline void lu_w_match_cell__print(Lu_W_Match_Cell self)
	{
		lu_block_id__print(&self->block_id);
		lu__debug("SIG=%.1f", self->sig);
	}


///////////////////////////////////////////////////////////////////////////////
//  Lu_W_Save_Addr

	////
	// Using as an index in Lu_W_Save_Cell_Mem so reallocation will not break pointer
	union lu_w_save_addr {
		lu_size value;
	};

	// NULL addr
	extern const union lu_w_save_addr LU_W_SAVE_ADDR__NULL; 

	static inline void lu_w_save_addr__reset(Lu_W_Save_Addr self)
	{
		self->value = LU_W_SAVE_ADDR__NULL.value;
	}

	static inline lu_bool lu_w_save_addr__is_blank(Lu_W_Save_Addr self)
	{
		return self->value == LU_W_SAVE_ADDR__NULL.value;
	}


///////////////////////////////////////////////////////////////////////////////
//  Lu_W_Save_Cell 

	struct lu_w_save_cell {
		struct lu_block_id block_id;
		lu_value sig;
	};

	//
	// Constructors / Destructors
	//

	static inline Lu_W_Save_Cell lu_w_save_cell__init(
		Lu_W_Save_Cell self, 
		struct lu_block_id block_id
	)
	{	
		lu__assert(lu_block_id__is_set(&block_id));

		self->block_id = block_id;
		self->sig = 0;

		return self;
	}

	static inline void lu_w_save_cell__reset(Lu_W_Save_Cell self)
	{
		lu__assert(self);

		lu_block_id__reset(&self->block_id);
		self->sig = 0;
	}

	//
	// Methods
	//

	static inline void lu_w_save_cell__add_sig(Lu_W_Save_Cell self, lu_value sig)
	{
		self->sig += sig;
	}

	static inline lu_bool lu_w_save_cell__is_sig_over_breakpoint(Lu_W_Save_Cell self, Lu_N_Cell n_cell, lu_value breakpoint)
	{
		lu_value def_sig = lu_n_cell__get_default_sig(n_cell);
		lu_value res_sig = def_sig - self->sig;

		lu__assert(res_sig >= 0); // should never go below 0

		// lu__debug(
		// 	"\n def_sig: %.1f, sig: %.1f, res_sig: %.1f, (def_sig * breakpoint): %.1f, res: %d",
		// 	def_sig,
		// 	self->sig,
		// 	res_sig,
		// 	(def_sig * breakpoint),
		// 	self->sig >= (def_sig * breakpoint)
		// );

		return self->sig >= (def_sig * breakpoint);
	}

	static inline lu_value lu_w_save_cell__calc_fire_sig(Lu_W_Save_Cell self, lu_value default_sig)
	{
		return self->sig / default_sig;
	}

	static inline lu_bool lu_w_save_cell__no_sig(Lu_W_Save_Cell self)
	{
		return self->sig == 0;
	}

	static inline void lu_w_save_cell__print(Lu_W_Save_Cell self)
	{
		lu_block_id__print(&self->block_id);
		lu__debug("SIG=%.1f", self->sig);
	}


///////////////////////////////////////////////////////////////////////////////
//  Lu_W_Match_Cell_Mem

	struct lu_w_match_cell_mem {
		Lu_Mem_Table mem_table;
	};


	static Lu_W_Match_Cell_Mem lu_w_match_cell_mem__init(Lu_W_Match_Cell_Mem self, Lu_Mem mem, lu_size size);
	static void lu_w_match_cell_mem___deinit(Lu_W_Match_Cell_Mem self);

	static inline Lu_W_Match_Cell lu_w_match_cell_mem__cell_alloc(Lu_W_Match_Cell_Mem self)
	{
		lu__debug_assert(self);
		lu__debug_assert(self->mem_table);

		lu_p_byte record = lu_mem_record__alloc(self->mem_table);

		if (!record)
		{
			self->mem_table = lu_mem_table__realloc(
				self->mem_table, 
				lu_mem_table__records_count(self->mem_table) * 2
			); 
			lu__alloc_assert(self->mem_table);

			lu__mem_debug("\n (!) w_match_cell_mem realloc");

			record = lu_mem_record__alloc(self->mem_table);
			lu__assert(record);
		}

		return (Lu_W_Match_Cell) record;
	}

	static inline Lu_W_Match_Cell lu_w_match_cell_mem__get_cell(Lu_W_Match_Cell_Mem self, union lu_w_match_addr addr)
	{
		if (lu_w_match_addr__is_blank(&addr)) return NULL;

		lu__debug_assert(self);
		lu__debug_assert(self->mem_table);

		return (Lu_W_Match_Cell) lu_mem_table__get(self->mem_table, addr.value);
	}

	static inline union lu_w_match_addr lu_w_match_cell_mem__get_addr(Lu_W_Match_Cell_Mem self, Lu_W_Match_Cell cell)
	{
		if (cell == NULL) return LU_W_MATCH_ADDR__NULL;

		lu__debug_assert(self);
		lu__debug_assert(cell);

		union lu_w_match_addr addr;

		addr.value = lu_mem_table__record_ix(self->mem_table, (lu_p_byte) cell);

		return addr;
	}

///////////////////////////////////////////////////////////////////////////////
//  Lu_W_La_Match_Cell 

	struct lu_w_la_match_cell {
		struct lu_block_id block_id;
		lu_value sig;
		lu_value sig_received_count;
	};

	//
	// Constructors / Destructors
	//

	static inline Lu_W_La_Match_Cell lu_w_la_match_cell__init(Lu_W_La_Match_Cell self, struct lu_block_id block_id)
	{
		lu__assert(self);

		self->block_id = block_id;
		self->sig = 0;
		self->sig_received_count = 0;

		return self;
	}

	static inline Lu_W_La_Match_Cell lu_w_la_match_cell__reset(Lu_W_La_Match_Cell self)
	{
		lu__assert(self);

		lu_block_id__reset(&self->block_id);
		self->sig = 0;
		self->sig_received_count = 0;

		return self;
	}
	
	//
	// Get
	// 

	static inline lu_value lu_w_la_match_cell__get_sig(Lu_W_La_Match_Cell self)
	{
		lu__assert(self);

		return self->sig;
	}

	static inline lu_value lu_w_la_match_cell__get_normalized_sig(Lu_W_La_Match_Cell self)
	{
		lu__assert(self);

		return self->sig / self->sig_received_count;
	}

	static inline lu_value lu_w_la_match_cell__get_sig_received_count(Lu_W_La_Match_Cell self)
	{
		lu__assert(self);

		return self->sig_received_count;
	}

	//
	// Is / Has
	//


	static inline lu_bool lu_w_la_match_cell__no_sig(Lu_W_La_Match_Cell self)
	{
		return self->sig == 0;
	}

	//
	// Methods
	//

	static inline void lu_w_la_match_cell__add_sig(Lu_W_La_Match_Cell self, lu_value sig)
	{
		lu__assert(self);

		self->sig += sig;
		++self->sig_received_count;
	}


