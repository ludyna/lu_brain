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
// Lu_W_Cell 

	////
	// We are using this cell and related "infrastructure" for both save and restore operations.
	struct lu_w_cell {
		Lu_N_Cell n_cell;
		Lu_N_Column n_column;
	};

	static inline void lu_w_cell__reset(Lu_W_Cell self)
	{
		lu__debug_assert(self);

		self->n_cell = NULL;
		self->n_column = NULL;
	}

	static inline Lu_W_Cell lu_w_cell__save(
		Lu_W_Cell self,
		Lu_N_Cell n_cell,
		Lu_N_Column n_column
	)
	{
		lu__debug_assert(self);

		self->n_cell = n_cell;
		self->n_column = n_column;

		return self;
	}
 	

///////////////////////////////////////////////////////////////////////////////
// Lu_W_Cell_P

	struct lu_w_cell_p {
		
		Lu_N_Cell_VP n_cell;
		Lu_N_Column_Comp n_column;
		
		// sig doesn't make much sense for save cell, but
		// we have it here to indicate if cell was active (not "null" cell)
		lu_value sig;

		lu_byte state;
		lu_value p_1;
		lu_value p_2;
	};

	#define LU_W_CELL_P__START 0
	#define LU_W_CELL_P__ONE 1
	#define LU_W_CELL_P__READY 2

	static inline void lu_w_cell_p__reset(Lu_W_Cell_P self)
	{
		lu__debug_assert(self);

		self->n_column = NULL;
		self->n_cell = NULL;
		self->sig = 0;
		self->state = LU_W_CELL_P__START;
		self->p_1 = 0;
		self->p_2 = 0;
	}

	static inline void lu_w_cell_p__register(
		Lu_W_Cell_P self, 
		lu_bool is_reset,
		lu_value p, 
		Lu_Process_Config config
	)
	{
		is_reset && (self->state = LU_W_CELL_P__START);

		#pragma GCC diagnostic ignored "-Wunused-value"
			self->state == LU_W_CELL_P__START && (self->p_1 = p);
			self->state == LU_W_CELL_P__ONE && (self->p_2 = p); 
		#pragma GCC diagnostic pop

		++self->state; 

		lu__debug_assert(self->state <= LU_W_CELL_P__READY);
		// self->state > LU_W_CELL_P__READY && self->state == LU_W_CELL_P__START;
	}

	static inline lu_bool lu_w_cell_p__is_ready(Lu_W_Cell_P self, lu_value signif_p)
	{
		// If no changes its important information for us
		return self->state == LU_W_CELL_P__READY; // && lu_value_abs(self->p_1 - self->p_2) >= signif_p;
	}

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
		
		self->n_column = lu_n_table_comp__get_column(n_table, x, y);
		self->n_cell = lu_n_column_comp__get_cell(self->n_column, z);

		lu__debug_assert(self->n_cell);

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
			lu__debug_assert(w_cell->n_cell);

			p_reg = lu_hash_comb(p_reg, lu_n_cell_vp__get_cell_addr(w_cell->n_cell)->value);
		}

		return p_reg;
	}

	static inline lu_size lu_w_cell__children_hash_comp(Lu_W_Cell* children, lu_size children_count)
	{
		lu_size p_reg = 0;

		Lu_W_Cell w_cell;
		lu_size value;
		for (lu_size i = 0; i < children_count; i++)
		{
			w_cell = children[i];
			lu__debug_assert(w_cell);
			lu__debug_assert(w_cell->n_cell); // this is correct

			value = lu_n_cell__get_cell_addr(w_cell->n_cell)->value;

			p_reg = lu_hash_comb(p_reg, value);
		}

		return p_reg;
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

	static inline lu_bool lu_w_match_addr__is_blank(Lu_W_Match_Addr self)
	{
		return self->value == LU_W_MATCH_ADDR__NULL.value;
	}

///////////////////////////////////////////////////////////////////////////////
//  Lu_W_Match_Cell 

	struct lu_w_match_cell {
		lu_size wave_id;
		lu_size block_id;
		lu_value sig;
	};	

	static inline Lu_W_Match_Cell lu_w_match_cell__init(
		Lu_W_Match_Cell self, 
		lu_size wave_id, 
		lu_size block_id,
		lu_value sig
	)
	{	
		self->wave_id = wave_id;
		self->block_id = block_id;
		self->sig = 0;

		return self;
	}

	static inline Lu_W_Match_Cell lu_w_match_cell__init_null(Lu_W_Match_Cell self)
	{
		return lu_w_match_cell__init(self, LU_WAVE_ID__NOT_SET, LU_BLOCK_ID__NOT_SET, 0);
	}

	static inline void lu_w_match_cell__add_sig(Lu_W_Match_Cell self, lu_value sig)
	{
		self->sig += sig;
	}

	static inline lu_bool lu_w_match_cell__ready_to_fire(Lu_W_Match_Cell self, Lu_N_Cell n_cell)
	{
		return (lu_n_cell__get_default_sig(n_cell) - self->sig) < 1.0;
	}

	static inline lu_bool lu_w_match_cell__no_sig(Lu_W_Match_Cell self)
	{
		return self->sig == 0;
	}

///////////////////////////////////////////////////////////////////////////////
//  Lu_W_Match_Cell_Mem

	struct lu_w_match_cell_mem {
		Lu_Mem_Table mem_table;
	};


	static Lu_W_Match_Cell_Mem lu_w_match_cell_mem__init(Lu_W_Match_Cell_Mem self, Lu_Mem mem, lu_size size);
	static void lu_w_match_cell_mem___deinit(Lu_W_Match_Cell_Mem self);

	static inline Lu_W_Match_Cell lu_w_match_cell_mem___cell_alloc(Lu_W_Match_Cell_Mem self)
	{
		lu__debug_assert(self);
		lu__debug_assert(self->mem_table);

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