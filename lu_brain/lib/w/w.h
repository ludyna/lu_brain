/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Lu_W_Cell 

	struct lu_w_cell {
		Lu_N_Cell_Base n_cell_0;
		lu_value sig;
	};

///////////////////////////////////////////////////////////////////////////////
// Lu_W_Cell_P

	struct lu_w_cell_p {
		struct lu_w_cell super;

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
		self->state == LU_W_CELL_P__START && (self->p1 = p);
		self->state == LU_W_CELL_P__ONE && (self->p2 = p); 

		++self->state; 

		lu__debug_assert(self->state <= LU_W_CELL_P__READY);
		// self->state > LU_W_CELL_P__READY && self->state == LU_W_CELL_P__START;
	}

	static inline lu_bool lu_w_cell_p__is_ready(Lu_W_Cell_P self)
	{
		return self->state == LU_W_CELL_P__READY;
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
		p < 0 && (p = -p); 
		p = lu_comp_calc__norm(comp_calc, p);

		lu_size ix = lu_comp_calc__ix(comp_calc, p);

		Lu_N_Cell_V n_cell = lu_n_table_comp__get_cell(n_table, x, y, ix);
		lu__debug_assert(n_cell);

		self->super.n_cell_0 = (Lu_N_Cell_Base) n_cell;
		self->super.sig = 1.0;
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_W_Cell_V

	#define LU_W_CELL_V__NOT_SET 0
	#define LU_W_CELL_V__READY 1

	struct lu_w_cell_v {
		struct lu_w_cell super;

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
		lu_size ix = lu_comp_calc__ix(comp_calc, v);

		Lu_N_Cell_V n_cell = lu_n_table_comp__get_cell(n_table, x, y, ix);
		lu__debug_assert(n_cell);

		self->super.n_cell_0 = (Lu_N_Cell_Base) n_cell;
		self->super.sig = 1.0;
	}

	static inline void lu_w_cell_v__reset(Lu_W_Cell_V self)
	{
		self->state = LU_W_CELL_V__NOT_SET;
		self->super.sig = 0;
	}

///////////////////////////////////////////////////////////////////////////////
//  Lu_W_Table_P

	struct lu_w_table_p {
		Lu_Mem mem;

		lu_size w;
		lu_size h;

		// always "2D"
		struct lu_w_cell_p* cells;
	};

	static Lu_W_Table_P lu_w_table_p__create(Lu_Config config, lu_size width, lu_size height);
	static void lu_w_table_p__destroy(Lu_W_Table_P self);

	static inline Lu_W_Cell_P lu_w_table_p__get_cell(Lu_W_Table_P self, lu_size x, lu_size y)
	{
		return &self->cells[y * self->w + x];
	}

///////////////////////////////////////////////////////////////////////////////
//  Lu_W_Table_V

	struct lu_w_table_v {
		Lu_Mem mem;

		lu_size w;
		lu_size h;

		// always "2D"
		struct lu_w_cell_v* cells;
	};

	static inline Lu_W_Cell_V lu_w_table_v__get_cell(Lu_W_Table_V self, lu_size x, lu_size y)
	{
		return &self->cells[y * self->w + x];
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_W_Table 

	struct lu_w_table {
		Lu_Mem mem;

		lu_size wave_id;
		lu_size block_id;

		lu_size w;
		lu_size h;

		// always "2D"
		struct lu_w_cell* cells;
	};

	static Lu_W_Table lu_w_table__create(
		Lu_Config config, 
		lu_size width, 
		lu_size height
	);

	static void lu_w_table__destroy(Lu_W_Table self);

	static inline Lu_W_Cell lu_w_table__get_cell(Lu_W_Table self, lu_size x, lu_size y)
	{
		return &self->cells[y * self->w + x];
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
	 