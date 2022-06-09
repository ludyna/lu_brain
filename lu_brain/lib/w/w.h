/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// 
//

	typedef struct lu_s_layer* Lu_S_Layer;
	static inline Lu_N_Table lu_s_layer__get_n_table(Lu_S_Layer self);


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

	struct lu_w_table {
		Lu_Mem mem;
		Lu_S_Layer s_layer;

		lu_size wave_id;
		lu_size block_id;

		lu_size w;
		lu_size h;
		lu_size h_max;

		lu_size normal_children_size;

		// always "2D"
		struct lu_w_cell* cells;

		lu_bool any_fired;
	};

	static Lu_W_Table lu_w_table__create(
		Lu_S_Layer s_layer, 
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

	////
	// Returns NULL if x or y out of range.
	static inline Lu_W_Cell lu_w_table__get_w_cell(Lu_W_Table self, lu_size x, lu_size y)
	{ 
		if (x < self->w && y < self->h)
		{
			return &self->cells[y * self->w + x];
		}
		else
		{
			return NULL;
		}
	}

	static inline void lu_w_table__collect_children(
		Lu_W_Table self, 
		lu_size x, 
		lu_size y, 
		Lu_W_Cell children[], 
		lu_size *non_null_count
	)
	{
		lu__assert(self);
		lu__assert(self->s_layer);

		lu_byte i = 0;
		lu_size local_non_null_count = 0;

		Lu_N_Table n_table = lu_s_layer__get_n_table(self->s_layer);
		lu__assert(n_table);
		Lu_N_Column n_column;

		////
		// Possible situations:
		// 1. Outside bounds
		//		children[i] = NULL;
		// 		
		// 2. w_cell was not fired for this wave (w_cell->n_cell == NULL)
		//		We should set w_cell->n_cell to appropriate n_column "NULL" cell
		// 
		// 3. w_cell was fired for this wave (w_cell->n_cell != NULL)

		children[i] = lu_w_table__get_w_cell(self, x, y);
		if (children[i])
		{
			++local_non_null_count;

			if (children[i]->n_cell == NULL)
			{
				n_column = lu_n_table__get_column(n_table, x, y);
			 	children[i]->n_cell = lu_n_column__get_null_cell(n_column);
			 	children[i]->n_column = n_column;
			}
		}

		++i;
		children[i] = lu_w_table__get_w_cell(self, x + 1, y);
		if (children[i])
		{
			++local_non_null_count;

			if (children[i]->n_cell == NULL)
			{
				n_column = lu_n_table__get_column(n_table, x + 1, y);
			 	children[i]->n_cell = lu_n_column__get_null_cell(n_column);
			 	children[i]->n_column = n_column;
			}
		}

		++i;
		children[i] = lu_w_table__get_w_cell(self, x, y + 1);
		if (children[i]) 
		{
			++local_non_null_count;

			if (children[i]->n_cell == NULL)
			{
				n_column = lu_n_table__get_column(n_table, x, y + 1);
			 	children[i]->n_cell = lu_n_column__get_null_cell(n_column);
			 	children[i]->n_column = n_column;
			}
		}

		++i;
		children[i] = lu_w_table__get_w_cell(self, x + 1, y + 1);
		if (children[i]) 
		{
			++local_non_null_count;

			if (children[i]->n_cell == NULL)
			{
				n_column = lu_n_table__get_column(n_table, x + 1, y + 1);
			 	children[i]->n_cell = lu_n_column__get_null_cell(n_column);
			 	children[i]->n_column = n_column;
			}
		}

		lu__debug_assert(local_non_null_count <= self->normal_children_size);

		*non_null_count = local_non_null_count;
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_W_Processor

	struct lu_w_processor {
		lu_size wave_id;
		lu_size block_id;
	};

	static inline void lu_w_processor__init(Lu_W_Processor self)
	{
		self->wave_id = LU_WAVE_ID__NOT_SET;
		self->block_id = LU_BLOCK_ID__NOT_SET;
	}

	static inline void lu_w_processor__deinit(Lu_W_Processor self)
	{

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
	 