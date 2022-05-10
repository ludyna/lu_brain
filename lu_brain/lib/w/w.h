/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/

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
// Lu_W_Str
//

	static inline lu_bool lu_w_str__eq(const union lu_w_addr* a, const union lu_w_addr* b)
	{
		while (1)
		{
			if ((*a).value != (*b).value)
			{
				return false;
			}

			if ((*a).value == 0 || (*b).value == 0) break;

			++a;
			++b;
		}	
		
		return true;
	}

	////
	// (!) This method (intentionally!) doesn't check if <dest> has enough space for <src>
	static inline void lu_w_str__copy(union lu_w_addr* dest, const union lu_w_addr* src)
	{
		while((*src).value)
		{
			*dest = *src;
			++src;
			++dest;
		};

		(*dest).value = 0;
	}

	static inline void lu_w_str__print(union lu_w_addr* s)
	{
		lu__debug("\n W_STRING: {");
		union lu_w_addr *p = s;

		while((*p).value)
		{
			if (p != s) lu__debug(", ");
			lu_w_addr__print(&(*p));
			++p;
		} 
		if (p==s) lu__debug("0");
		else lu__debug(", 0");

		lu__debug("}");
	}

	static inline lu_size lu_w_str__hash_comb(const union lu_w_addr* p)
	{
		lu_size p_reg = 0;
		while((*p).value)
		{
			p_reg = lu_hash_comb(p_reg, (*p).value);
			++p;
		}

		return p_reg;
	}


///////////////////////////////////////////////////////////////////////////////
// Lu_W_Cell 

	struct lu_w_cell {
		union lu_n_addr n_addr;
	};

	static inline void lu_w_cell__reset(Lu_W_Cell self)
	{
		lu__debug_assert(self);
		self->n_addr.value = 0;
	}
 	
 	static inline void lu_w_cell__save(Lu_W_Cell self, union lu_n_addr n_addr)
 	{
 		self->n_addr = n_addr;
 	}

///////////////////////////////////////////////////////////////////////////////
// Lu_W_Cell_P

	struct lu_w_cell_p {
		union lu_n_addr n_addr;
		lu_value sig;

		lu_byte state;
		lu_value p1;
		lu_value p2;
	};

	#define LU_W_CELL_P__START 0
	#define LU_W_CELL_P__ONE 1
	#define LU_W_CELL_P__READY 2

	static inline void lu_w_cell_p__register(
		Lu_W_Cell_P self, 
		lu_bool is_reset,
		lu_value p, 
		Lu_Process_Config config
	)
	{
		is_reset && (self->state = LU_W_CELL_P__START);

		#pragma GCC diagnostic ignored "-Wunused-value"
			self->state == LU_W_CELL_P__START && (self->p1 = p);
			self->state == LU_W_CELL_P__ONE && (self->p2 = p); 
		#pragma GCC diagnostic pop

		++self->state; 

		lu__debug_assert(self->state <= LU_W_CELL_P__READY);
		// self->state > LU_W_CELL_P__READY && self->state == LU_W_CELL_P__START;
	}

	static inline lu_bool lu_w_cell_p__is_ready(Lu_W_Cell_P self, lu_value signif_p)
	{
		//lu__debug("\n P STEP: %.1f, P1: %.1f, P2: %.1f, P_DIFF: %.1f", signif_p, self->p1, self->p2, lu_value_abs(self->p1 - self->p2));
		return self->state == LU_W_CELL_P__READY && lu_value_abs(self->p1 - self->p2) >= signif_p;
	}

	static inline void lu_w_cell_p__save(
		Lu_W_Cell_P self, 
		lu_size x,
		lu_size y, 
		Lu_Comp_Calc comp_calc, 
		Lu_N_Table_Comp n_table
	)
	{
		lu_value p = self->p2 - self->p1;

		#pragma GCC diagnostic ignored "-Wunused-value"
			p < 0 && (p = -p); 
		#pragma GCC diagnostic pop

		p = lu_comp_calc__norm(comp_calc, p);

		lu_size column_ix = lu_comp_calc__ix(comp_calc, p);

		self->n_addr = lu_n_table_comp__get_cell(n_table, x, y, column_ix)->addr;
		self->sig = 1.0;
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_W_Cell_V

	#define LU_W_CELL_V__NOT_SET 0
	#define LU_W_CELL_V__READY 1

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
		self->state = LU_W_CELL_V__READY;
	}

	static inline lu_bool lu_w_cell_v__is_ready(Lu_W_Cell_V self)
	{
		return self->state == LU_W_CELL_V__READY;
	}

	static inline void lu_w_cell_v__save(
		Lu_W_Cell_V self, 
		lu_size x,
		lu_size y, 
		Lu_Comp_Calc comp_calc, 
		Lu_N_Table_Comp n_table
	)
	{
		lu_value v = self->v;
		v = lu_comp_calc__norm(comp_calc, v);
		lu_size column_ix = lu_comp_calc__ix(comp_calc, v);

		self->n_addr = lu_n_table_comp__get_cell(n_table, x, y, column_ix)->addr;
		self->sig = 1.0;
	}

	static inline void lu_w_cell_v__reset(Lu_W_Cell_V self)
	{
		self->state = LU_W_CELL_V__NOT_SET;
		self->sig = 0;
	}

///////////////////////////////////////////////////////////////////////////////
//  Lu_W_Table_P

	struct lu_w_table_p {
		Lu_Mem mem;

		lu_size w;
		lu_size h;
 
 		// 2d because its for one Z layer
		struct lu_w_cell_p* cells;
	};

	static Lu_W_Table_P lu_w_table_p__create(Lu_Config config, lu_size w, lu_size h);
	static void lu_w_table_p__destroy(Lu_W_Table_P self);

	static inline Lu_W_Cell_P lu_w_table_p__get_cell(Lu_W_Table_P self, lu_size addr)
	{
		return &self->cells[addr];
	}

///////////////////////////////////////////////////////////////////////////////
//  Lu_W_Table_V

	struct lu_w_table_v {
		Lu_Mem mem;

		lu_size w;
		lu_size h;
		lu_size d;

		struct lu_w_cell_v* cells;
	};

	static inline Lu_W_Cell_V lu_w_table_v__get_cell(Lu_W_Table_V self, lu_size x, lu_size y)
	{
		return &self->cells[y * self->w + x];
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_W_Table 

	typedef struct lu_s_layer_base* Lu_S_Layer_Base;

	struct lu_w_table {
		Lu_Mem mem;
		Lu_S_Layer_Base s_layer;

		lu_size wave_id;
		lu_size block_id;

		lu_size w;
		lu_size h;
		lu_size h_max;

		// always "2D"
		struct lu_w_cell* cells;

		lu_bool any_fired;
	};

	static Lu_W_Table lu_w_table__create(
		Lu_S_Layer_Base s_layer, 
		Lu_Config config, 
		lu_size w, 
		lu_size h,
		lu_size h_max
	);

	static void lu_w_table__destroy(Lu_W_Table self);

	static inline lu_bool lu_w_table__any_fired(Lu_W_Table self, lu_size wave_id, lu_size block_id)
	{
		if (self == NULL) return false;

		if (self->wave_id != wave_id || self->block_id != block_id) return false;

		return self->any_fired;
	}

	static inline Lu_W_Cell lu_w_table__get_cell(Lu_W_Table self, lu_size x, lu_size y)
	{ 
		lu__debug_assert(x < self->w);
		lu__debug_assert(y < self->h);
		
		return &self->cells[y * self->w + x];
	} 

	static inline union lu_n_addr lu_w_table__get_n_addr(Lu_W_Table self, lu_size x, lu_size y)
	{ 
		if (x < self->w && y < self->h)
		{
			return lu_w_table__get_cell(self, x, y)->n_addr;
		}
		else
		{
			return LU_N_ADDR__NULL;
		}
	}

	static inline void lu_w_table__cipher_children(Lu_W_Table self, lu_size x, lu_size y, union lu_n_addr children[])
	{
		lu_byte i = 0;
		union lu_n_addr addr;

		addr = lu_w_table__get_n_addr(self, x, y);
		
		if (lu_n_addr__is_present(&addr))
		{
			children[i] = addr;
			++i;
		}

		addr = lu_w_table__get_n_addr(self, x + 1, y);
		
		if (lu_n_addr__is_present(&addr))
		{
			children[i] = addr;
			++i;
		}

		addr = lu_w_table__get_n_addr(self, x + 1, y + 1);
		
		if (lu_n_addr__is_present(&addr))
		{
			children[i] = addr;
			++i;
		}

		addr = lu_w_table__get_n_addr(self, x, y + 1);
		
		if (lu_n_addr__is_present(&addr))
		{
			children[i] = addr;
			++i;
		}

		lu_n_addr__set_to_null(&children[i]);
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_W_Manager

	struct lu_w_manager {
		Lu_Mem mem;
		Lu_Mem_Table waves;
	};

	static Lu_W_Manager lu_w_manager__create(Lu_Mem mem, lu_size w_waves_size);
	static void lu_w_manager__destroy(Lu_W_Manager self); 

	static bool lu_w_manager__register_wave(Lu_W_Manager self, Lu_Wave wave);
	static void lu_w_manager__unregister_wave(Lu_W_Manager self, Lu_Wave wave);

	static inline bool lu_w_manager__is_empty(Lu_W_Manager self) 
	{
		lu__assert(self);
		lu__assert(self->waves);

		return lu_mem_table__records_count(self->waves) == 0;
	}

	static inline Lu_Wave lu_w_manager__get_wave_by_id(Lu_W_Manager self, lu_size id)
	{
		lu__assert(self);
		lu__assert(self->waves);

		return *((Lu_Wave*) lu_mem_table__get(self->waves, id));
	}
	 