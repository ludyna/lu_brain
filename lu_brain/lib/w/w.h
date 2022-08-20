/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
//  Lu_W_Rec 

	static inline void lu_w_rec_state__to_str(enum lu_w_rec_state self, char buffer[])
	{
		switch (self)
		{
			case LU_W_REC_STATE__COLLECT:
				strcpy(buffer, "COLLECT");
				break;
			case LU_W_REC_STATE__COLLECT_AND_FINISH:
				strcpy(buffer, "COLLECT_AND_FINISH");
				break;
			default:
				strcpy(buffer, "(!) UNKNOWN");
				break;
		}
	}

	struct lu_w_rec {
		// data for when we had last access to s_rec
		struct lu_block_id block_id;
		lu_size wave_ix;

		enum lu_w_rec_state state;

		// Rec view is also a rec state. Rec view can be changed dynamically so we should copy it here 
		// so we understand how wave was calculated.
		struct lu_rec_view view; 
	};

	static inline Lu_W_Rec lu_w_rec__reset(Lu_W_Rec self)
	{
		lu__assert(self);

		lu_block_id__reset(&self->block_id);
		self->wave_ix = LU_WAVE_IX__NOT_SET;
		self->state = LU_W_REC_STATE__COLLECT; 

		return self;
	}

	static inline void lu_w_rec__update(
		Lu_W_Rec self, 
		struct lu_block_id block_id,
		lu_size wave_ix, 
		struct lu_rec_view view
	)
	{
		lu__assert(self);
		lu__assert(lu_block_id__is_set(&block_id));

		//
		// Detect state first
		//

		if (self->block_id.wave_id != block_id.wave_id)
		{
			// totally new wave, start with saving one
			self->state = LU_W_REC_STATE__COLLECT;
		}
		else if (self->wave_ix != wave_ix)
		{
			// new wave ix means its new wave also 
			// (should never happen because we get this lu_w_rec from "same" wave_ix, 
			// but put this code here noneless for completeness)
			self->state = LU_W_REC_STATE__COLLECT;
		}
		else if (self->block_id.block_ix == block_id.block_ix)
		{
			// should not happen
			lu__assert(false);
		}
		else
		{
			lu__assert(block_id.block_ix < LU_LONG__MAX);
			lu__assert(self->block_id.block_ix < LU_LONG__MAX);

			lu_long diff = ((lu_long)block_id.block_ix) - ((lu_long)self->block_id.block_ix);

			lu__deep_debug("\nLU_W_REC__UPDATE: block_ix=%ld, self->block_ix=%ld\n", block_id.block_ix, self->block_id.block_ix);

			// if this fails, probably wave was not reset properly or 
			// block_ix was not increased after lu_wave__process
			lu__assert(diff > 0);

			if (diff > 1)
			{
				self->state = LU_W_REC_STATE__COLLECT;
			}
			else
			{
				if (self->state == LU_W_REC_STATE__COLLECT)
				{
					self->state = LU_W_REC_STATE__COLLECT_AND_FINISH;
				}
			}
		}

		//
		// Update values
		//

		self->block_id = block_id;
		self->wave_ix = wave_ix;
		self->view = view; // copy struct data
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

	//
	// Constructors / Destructors
	//

	static Lu_W_Table_P lu_w_table_p__create(Lu_Config config, lu_size w, lu_size h);
	static void lu_w_table_p__destroy(Lu_W_Table_P self);

	static inline void lu_w_table_p__reset(Lu_W_Table_P self)
	{
		lu__assert(self);

		lu_size wh = self->w * self->h;

		Lu_W_Cell_P w_cell_p;
		for (lu_size i = 0; i < wh; i++)
		{
			w_cell_p = &self->cells[i];

			lu_w_cell_p__reset(w_cell_p);
		}	
	}

	//
	// Get
	//

	static inline Lu_W_Cell_P lu_w_table_p__get_w_cell_by_ix(Lu_W_Table_P self, lu_size ix)
	{
		return &self->cells[ix];
	}

	static inline Lu_W_Cell_P lu_w_table_p__get_w_cell(Lu_W_Table_P self, lu_size x, lu_size y)
	{
		return &lu_macro__value_in_2d_array(self->cells, x, y, self->w);
	}

	//
	// Methods
	//

	static inline void lu_w_table_p__print(Lu_W_Table_P self)
	{
		lu__assert(self);

		lu_size x;
		lu_size y;

		Lu_W_Cell_P w_cell_p;

		lu__debug("\n-------- Lu_W_Table_P:"); 

		for (y = 0; y < self->h; y++)
		{
			lu__debug("\n");
			for (x = 0; x < self->w; x++)
			{
				w_cell_p = lu_w_table_p__get_w_cell(self, x, y);
				lu_w_cell_p__print_symbol(w_cell_p);
			}
		}
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

		struct lu_block_id block_id;
		lu_size wave_ix;

		lu_size w;
		lu_size h;
		lu_size h_max;
		lu_size wh;
		lu_size wh_max;

		lu_size normal_children_size;

		// always "2D"
		struct lu_w_cell* cells;

		lu_bool any_fired;

		Lu_S_Table s_table;
	};

	//
	// Constructors / Destructors
	// 

	static Lu_W_Table lu_w_table__create(
		Lu_S_Layer s_layer, 
		Lu_Config config, 
		lu_size w, 
		lu_size h,
		lu_size h_max
	);

	static void lu_w_table__destroy(Lu_W_Table self);

	//
	// Get
	//

	////
	// Returns NULL if x or y out of range.
	static inline Lu_W_Cell lu_w_table__get_w_cell(Lu_W_Table self, lu_size x, lu_size y)
	{ 
		lu__assert(self);
		
		if (x >= self->w || y >= self->h)
		{
			return NULL;
		}

		return &self->cells[y * self->w + x];
	}


	//
	// Methods
	//

	static inline void lu_w_table__prepare_for_wave(
		Lu_W_Table self,
		struct lu_block_id block_id,
		lu_size wave_ix,
		Lu_S_Table s_table
	)
	{
		lu__assert(self);
		lu__assert(s_table);

		//
		// Sanity check
		// 

		lu__assert(lu_block_id__is_not_eq(&self->block_id, &block_id));

		//
		// Prepare
		//

		self->block_id = block_id;
		self->wave_ix = wave_ix;
		self->s_table = s_table;

		self->any_fired = false;
	}

	static inline lu_bool lu_w_table__any_fired(Lu_W_Table self, struct lu_block_id block_id)
	{
		if (self == NULL) return false;

		if (lu_block_id__is_not_eq(&self->block_id, &block_id)) return false;

		return self->any_fired;
	}

	static inline void lu_w_table__print(Lu_W_Table self)
	{
		lu__assert(self);
		lu__assert(self->s_layer);

		lu_size x;
		lu_size y;

		Lu_W_Cell w_cell;

		lu__debug("\nLU_W_TABLE from s_layer (");
		lu_s_layer__print_basic_info(self->s_layer);
		lu__debug("):");

		for (y = 0; y < self->h_max; y++)
		{
			lu__debug("\n   ");
			for (x = 0; x < self->w; x++)
			{
				w_cell = lu_w_table__get_w_cell(self, x, y);
				lu_w_cell__print_symbol(w_cell);
			}
		}
	}

	static inline void lu_w_table__reset_cells_to_null_cells(Lu_W_Table self)
	{
		lu__assert(self);
		lu__assert(self->s_table);

		//
		// Sanity check
		//

		lu__assert(self->w == lu_s_table__get_w(self->s_table));
		lu__assert(self->h == lu_s_table__get_h(self->s_table));

		//
		// Reset
		//

		lu_size y;
		lu_size x;
		Lu_W_Cell w_cell;
		Lu_S_Column s_column;
		Lu_N_Cell n_cell;

		for (y = 0; y < self->h; y++)
		{
			for (x = 0; x < self->w; x++)
			{
				w_cell = lu_w_table__get_w_cell(self, x, y);
				lu__assert(w_cell);

				s_column = lu_s_table__get_s_column(self->s_table, x, y);
				lu__assert(s_column);

				n_cell = lu_s_column__get_null_cell(s_column);
				lu__assert(n_cell);

				lu_w_cell__save(w_cell, n_cell, s_column);
			}
		}
	}

	static inline void lu_w_table__collect_children(
		Lu_W_Table self, 
		lu_size x, 
		lu_size y, 
		struct lu_w_child children[], 
		lu_size *children_count
	)
	{
		lu__assert(self);
		lu__assert(self->s_layer);

		lu_byte i = 0;
		*children_count = 0;

		////
		// Possible situations:
		// 1. Outside bounds
		//		children[i] = NULL;
		// 		
		// 2. w_cell was not fired for this wave (w_cell->n_cell == NULL)
		//		We should set w_cell->n_cell to appropriate s_column "NULL" cell
		// 
		// 3. w_cell was fired for this wave (w_cell->n_cell != NULL)



		Lu_W_Cell w_cell = lu_w_table__get_w_cell(self, x, y);
		if (w_cell)
		{
			lu__assert(lu_w_cell__is_set(w_cell));
			children[i].w_cell = w_cell;
			children[i].child_pos = LU_W_CHILD_POS__TL;
			++i;
		}

		w_cell = lu_w_table__get_w_cell(self, x + 1, y);
		if (w_cell)
		{
			lu__assert(lu_w_cell__is_set(w_cell));
			children[i].w_cell = w_cell;
			children[i].child_pos = LU_W_CHILD_POS__TR;
			++i;
		}

		w_cell = lu_w_table__get_w_cell(self, x, y + 1);
		if (w_cell) 
		{
			lu__assert(lu_w_cell__is_set(w_cell));
			children[i].w_cell = w_cell;
			children[i].child_pos = LU_W_CHILD_POS__BL;
			++i;
		}

		w_cell = lu_w_table__get_w_cell(self, x + 1, y + 1);
		if (w_cell) 
		{
			lu__assert(lu_w_cell__is_set(w_cell));
			children[i].w_cell = w_cell;
			children[i].child_pos = LU_W_CHILD_POS__BR;
			++i;
		}

		*children_count = i;

		lu__debug_assert(*children_count == self->normal_children_size);

	}

///////////////////////////////////////////////////////////////////////////////
// Lu_W_Manager

	struct lu_w_manager {
		Lu_Mem mem;
		Lu_Mem_Table save_waves;
		Lu_Mem_Table match_waves;
		Lu_Mem_Table restore_waves;

		lu_size next_wave_id;
	};

	static Lu_W_Manager lu_w_manager__create(Lu_Mem mem, Lu_Config config);
	static void lu_w_manager__destroy(Lu_W_Manager self); 

	static inline lu_size lu_w_manager__generate_next_wave_id(Lu_W_Manager self)
	{
		lu__assert(self);

		lu_size r = self->next_wave_id;
		++self->next_wave_id;

		return r;
	}

	static bool lu_w_manager__register_wave(Lu_W_Manager self, Lu_Wave wave);
	static void lu_w_manager__unregister_wave(Lu_W_Manager self, Lu_Wave wave);

	static inline bool lu_w_manager__is_empty(Lu_W_Manager self) 
	{
		lu__assert(self);
		lu__assert(self->save_waves);
 
		// lu__debug(
		// 	"\n SAVE_WAVES_COUNT = %ld, MATCH = %ld, RESTORE = %ld \n", 
		// 	lu_mem_table__records_count(self->save_waves),
		// 	lu_mem_table__records_count(self->match_waves),
		// 	lu_mem_table__records_count(self->restore_waves)
		// );

		return lu_mem_table__records_count(self->save_waves) == 0 \
		 && lu_mem_table__records_count(self->match_waves) == 0 \
		 && lu_mem_table__records_count(self->restore_waves) == 0;
	}