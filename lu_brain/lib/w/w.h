/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// 
//

	//
	// Lu_S_Layer
	//

	typedef struct lu_s_layer* Lu_S_Layer;

	static inline Lu_N_Table lu_s_layer__get_n_table(Lu_S_Layer self);
	static inline void lu_s_layer__print_basic_info(Lu_S_Layer self);

	//
	// Lu_S 
	//

	typedef struct lu_s* Lu_S;
	static inline void lu_s__find_n_cell_and_n_column(		
		Lu_S self,
		union lu_n_addr addr,
		Lu_N_Cell* n_cell,
		Lu_N_Column* n_column
	);

///////////////////////////////////////////////////////////////////////////////
//  Lu_W_Rec 

	static inline void lu_w_rec_state__to_str(enum lu_w_rec_state self, char buffer[])
	{
		switch (self)
		{
			case LU_W_REC_STATE__COLLECT:
				strcpy(buffer, "COLLECT");
				break;
			case LU_W_REC_STATE__COLLECT_AND_SAVE:
				strcpy(buffer, "COLLECT_AND_SAVE");
				break;
			default:
				strcpy(buffer, "(!) UNKNOWN");
				break;
		}
	}

	struct lu_w_rec {
		// data for when we had last access to s_rec
		lu_size wave_id;
		lu_size wave_ix;
		lu_size block_ix;

		enum lu_w_rec_state state;

		// Rec view is also a rec state. Rec view can be changed dynamically so we should copy it here 
		// so we understand how wave was calculated.
		struct lu_rec_view view; 
	};

	static inline Lu_W_Rec lu_w_rec__reset(Lu_W_Rec self)
	{
		lu__assert(self);

		self->wave_id = LU_WAVE_ID__NOT_SET;
		self->wave_ix = LU_WAVE_IX__NOT_SET;
		self->block_ix = LU_BLOCK_IX__NOT_SET;
		self->state = LU_W_REC_STATE__COLLECT; 

		return self;
	}

	static inline void lu_w_rec__update(
		Lu_W_Rec self, 
		lu_size wave_id, 
		lu_size wave_ix, 
		lu_size block_ix,
		struct lu_rec_view view
	)
	{
		lu__assert(self);

		//
		// Detect state first
		//

		if (self->wave_id != wave_id)
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
		else if (self->block_ix == block_ix)
		{
			// should not happen
			lu__assert(false);
		}
		else
		{
			lu__assert(self->block_ix != LU_BLOCK_IX__NOT_SET);
			lu__assert(block_ix < LU__LONG_MAX);
			lu__assert(self->block_ix < LU__LONG_MAX);

			lu_long diff = ((lu_long)block_ix) - ((lu_long)self->block_ix);

			// if this fails, probably wave was not reset properly or 
			// block_ix was not increased after lu_wave__process
			lu__debug("\nLU_W_REC__UPDATE: block_ix=%ld, self->block_ix=%ld\n", block_ix, self->block_ix);

			lu__assert(diff > 0);

			if (diff > 1)
			{
				self->state = LU_W_REC_STATE__COLLECT;
			}
			else
			{
				if (self->state == LU_W_REC_STATE__COLLECT)
				{
					self->state = LU_W_REC_STATE__COLLECT_AND_SAVE;
				}
			}
		}

		//
		// Update values
		//

		self->wave_id = wave_id;
		self->wave_ix = wave_ix;
		self->block_ix = block_ix;
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
		lu_size y_shift;

		lu__debug("\nLU_W_TABLE_P:"); 

		for (y = 0; y < self->h; y++)
		{
			y_shift = y * self->w;
			lu__debug("\n\t");
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

		lu_size wave_id;
		lu_size wave_ix;
		lu_size block_ix;

		lu_size w;
		lu_size h;
		lu_size h_max;
		lu_size wh;
		lu_size wh_max;

		lu_size normal_children_size;

		// always "2D"
		struct lu_w_cell* cells;

		lu_bool any_fired;

		Lu_N_Table n_table;
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
		lu_size wave_id,
		lu_size wave_ix,
		lu_size block_ix,
		Lu_N_Table n_table
	)
	{
		lu__assert(self);
		lu__assert(n_table);

		//
		// Sanity check
		// 

		lu__assert(self->wave_id != wave_id || self->wave_ix != wave_ix || self->block_ix != block_ix);

		//
		// Prepare
		//

		self->wave_id = wave_id;
		self->wave_ix = wave_ix;
		self->block_ix = block_ix;
		self->n_table = n_table;

		self->any_fired = false;
	}

	static inline lu_bool lu_w_table__any_fired(Lu_W_Table self, lu_size wave_ix, lu_size block_ix)
	{
		if (self == NULL) return false;

		if (self->wave_ix != wave_ix || self->block_ix != block_ix) return false;

		return self->any_fired;
	}

	static inline void lu_w_table__print(Lu_W_Table self)
	{
		lu__assert(self);
		lu__assert(self->s_layer);

		lu_size x;
		lu_size y;

		Lu_W_Cell w_cell;
		lu_size y_shift;

		lu__debug("\nLU_W_TABLE from s_layer (");
		lu_s_layer__print_basic_info(self->s_layer);
		lu__debug("):");

		for (y = 0; y < self->h_max; y++)
		{
			y_shift = y * self->w;
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
		lu__assert(self->n_table);

		//
		// Sanity check
		//

		lu__assert(self->w == self->n_table->w);
		lu__assert(self->h == self->n_table->h);

		//
		// Reset
		//

		lu_size y;
		lu_size x;
		Lu_W_Cell w_cell;
		Lu_N_Column n_column;
		Lu_N_Cell n_cell;

		for (y = 0; y < self->h; y++)
		{
			for (x = 0; x < self->w; x++)
			{
				w_cell = lu_w_table__get_w_cell(self, x, y);
				lu__assert(w_cell);

				n_column = lu_n_table__get_n_column(self->n_table, x, y);
				lu__assert(n_column);

				n_cell = lu_n_column__get_null_cell(n_column);
				lu__assert(n_cell);

				lu_w_cell__save(w_cell, n_cell, n_column);
			}
		}
	}


	static inline void lu_w_table__collect_children(
		Lu_W_Table self, 
		lu_size x, 
		lu_size y, 
		Lu_W_Cell children[], 
		lu_size *children_count
	)
	{
		lu__assert(self);
		lu__assert(self->s_layer);

		lu_byte i = 0;
		*children_count = 0;

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



		Lu_W_Cell w_cell = lu_w_table__get_w_cell(self, x, y);
		if (w_cell)
		{
			lu__assert(lu_w_cell__is_set(w_cell));
			children[i++] = w_cell;
		}

		w_cell = lu_w_table__get_w_cell(self, x + 1, y);
		if (w_cell)
		{
			lu__assert(lu_w_cell__is_set(w_cell));
			children[i++] = w_cell;
		}

		w_cell = lu_w_table__get_w_cell(self, x, y + 1);
		if (w_cell) 
		{
			lu__assert(lu_w_cell__is_set(w_cell));
			children[i++] = w_cell;
		}

		w_cell = lu_w_table__get_w_cell(self, x + 1, y + 1);
		if (w_cell) 
		{
			lu__assert(lu_w_cell__is_set(w_cell));
			children[i++] = w_cell;
		}

		*children_count = i;

		// lu__debug("\n*children_count=%ld, self->normal_children_size=%ld\n", *children_count, self->normal_children_size);
		lu__debug_assert(*children_count == self->normal_children_size);

	}

///////////////////////////////////////////////////////////////////////////////
// Lu_W_N_Item

	struct lu_w_n_item {
		Lu_W_Match_Cell match_cell;
		Lu_N_Cell n_cell;
		Lu_N_Column n_column;
	};

	static inline Lu_W_N_Item lu_w_n_item__init(
		Lu_W_N_Item self, 
		Lu_W_Match_Cell match_cell,
		Lu_N_Cell n_cell,
		Lu_N_Column n_column
	)
	{
		lu__assert(self);
		lu__assert(match_cell);
		lu__assert(n_cell);
		lu__assert(n_column);

		self->match_cell = match_cell;
		self->n_cell = n_cell;
		self->n_column = n_column;

		return self;
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_W_Processor

	struct lu_w_processor {
		lu_size wave_id;
		lu_size wave_ix;
		lu_size block_ix;
		Lu_S s;
		Lu_Mem mem;
		Lu_W_Match_Cell_Mem match_cell_mem;
		Lu_La_Column la_column;

		Lu_Mem_Table n_mem_table;
		Lu_Mem_Table la_mem_table;
		lu_size w_result_labels_size;
	
		Lu_Lim_List curr_list;
		Lu_Lim_List next_list;

		Lu_S_List s_list;
		Lu_Label* sorted_results;
	};

	static void lu_w_processor__init(
		Lu_W_Processor self,  
		Lu_S s, 
		Lu_Config config, 
		Lu_W_Match_Cell_Mem match_cell_mem,
		Lu_La_Column la_column
	);

	static void lu_w_processor__deinit(Lu_W_Processor self);
	//static inline void lu_w_process__

	static inline void lu_w_processor__put_in_queue(
		Lu_W_Processor self,
		Lu_W_Match_Cell match_cell,
		Lu_N_Cell n_cell,
		Lu_N_Column n_column
	)
	{
		Lu_W_N_Item n_item = (Lu_W_N_Item) lu_mem_record__alloc(self->n_mem_table);

		lu_w_n_item__init(n_item, match_cell, n_cell, n_column);

		// prepend, because we want FIFO queue
		lu_lim_list__prepend(self->next_list, (lu_p_void) n_item);
	}

	static inline void lu_w_processor__fire_n_cell(
		Lu_W_Processor self,
		Lu_N_Cell n_cell,
		Lu_N_Column n_column,
		lu_value sig
	)
	{
		lu__assert(self->wave_ix < n_column->w_match_cells_size);

		Lu_W_Match_Cell match_cell = lu_n_cell__get_and_reset_match_cell(n_cell, self->wave_ix, self->block_ix, self->match_cell_mem);

		lu_w_match_cell__add_sig(match_cell, sig);

		if (lu_w_match_cell__ready_to_fire(match_cell, n_cell))
		{
			lu_w_processor__put_in_queue(self, match_cell, n_cell, n_column);
		}
	}
	
	static inline void lu_w_processor__find_n_cell_and_n_column(
		Lu_W_Processor self,
		union lu_n_addr addr,
		Lu_N_Cell* n_cell,
		Lu_N_Column* n_column
	)
	{
		lu__assert(self);

		lu_s__find_n_cell_and_n_column(self->s, addr, n_cell, n_column);
	}

	static inline void lu_w_processor__fire_n_parents(
		Lu_W_Processor self, 
		Lu_N_Link_Mem link_mem,
		lu_value sig,
		union lu_n_link_addr parent_link_addr
	)
	{
		Lu_N_Link n_link_parent = lu_n_link_mem__get_link(link_mem, parent_link_addr);

		Lu_N_Cell n_cell_parent;
		Lu_N_Column n_column_parent;
 
		while (n_link_parent)
		{
			n_cell_parent = NULL;
			n_column_parent = NULL;

			lu_w_processor__find_n_cell_and_n_column(self, n_link_parent->cell_addr, &n_cell_parent, &n_column_parent);
		
			lu__assert(n_cell_parent);
			lu__assert(n_column_parent);

			//lu__debug("\n YOO! \n");

			lu_w_processor__fire_n_cell(self, n_cell_parent, n_column_parent, sig);

			n_link_parent = lu_n_link_mem__get_link(link_mem, n_link_parent->next);
		}
	}

	static inline void lu_w_processor__fire_vp_parents_with_sig(
		Lu_W_Processor self, 
		Lu_N_Cell_VP n_cell, 
		Lu_N_Column_Comp n_column,
		lu_value sig
	)
	{
		lu__debug_assert(self);
		lu__debug_assert(n_cell);
		lu__debug_assert(n_column);
		lu__debug_assert(sig > 0);
	
		lu_n_addr__print(&n_cell->addr);
		if (lu_n_link_addr__is_present(&n_cell->parents))
			lu_w_processor__fire_n_parents(self, &n_column->link_mem, sig, n_cell->parents);
	}

	static inline void lu_w_processor__fire_n_parents_with_sig(
		Lu_W_Processor self, 
		Lu_N_Cell n_cell, 
		Lu_N_Column n_column,
		lu_value sig
	)
	{
		lu__debug_assert(self);
		lu__debug_assert(n_cell);
		lu__debug_assert(n_column);
		lu__debug_assert(sig > 0);

		if (lu_n_link_addr__is_present(&n_cell->tl))
			lu_w_processor__fire_n_parents(self, &n_column->link_mem, sig, n_cell->tl);

		if (lu_n_link_addr__is_present(&n_cell->tr))
			lu_w_processor__fire_n_parents(self, &n_column->link_mem, sig, n_cell->tr);

		if (lu_n_link_addr__is_present(&n_cell->bl))
			lu_w_processor__fire_n_parents(self, &n_column->link_mem, sig, n_cell->bl);

		if (lu_n_link_addr__is_present(&n_cell->br))
			lu_w_processor__fire_n_parents(self, &n_column->link_mem, sig, n_cell->br);
	}

	static inline void lu_w_processor__fire_n_labels_with_sig(
		Lu_W_Processor self, 
		union lu_la_link_addr labels,
		Lu_La_Column la_column,
		lu_value sig
	)
	{
		lu__debug_assert(self);
		lu__debug_assert(la_column);
		lu__debug_assert(sig > 0);

		Lu_La_Link_Mem link_mem = lu_la_column__get_la_link_mem(la_column);
		lu__assert(link_mem);

		Lu_La_Link la_link_label = lu_la_link_mem__get_link(link_mem, labels);

		Lu_La_Cell la_cell;
		Lu_W_Match_Cell match_cell;
 
		while (la_link_label)
		{
			la_cell = NULL;

			la_cell = lu_la_column__get_la_cell_by_addr(la_column, la_link_label->la_addr);
			lu__assert(la_cell);

			match_cell = lu_la_cell__get_and_reset_match_cell(la_cell, self->wave_ix, self->block_ix, self->match_cell_mem);
			lu_w_match_cell__add_sig(match_cell, sig);

			la_link_label = lu_la_link_mem__get_link(link_mem, la_link_label->next);
		}
	}

	static inline lu_size lu_w_processor__process(Lu_W_Processor self)
	{
		lu__assert(self);
		lu__assert(lu_list__is_blank((Lu_List) self->curr_list));

		Lu_Lim_List t;
		t = self->curr_list;
		self->curr_list = self->next_list;
		self->next_list = t;

		Lu_Lim_List curr_list = self->curr_list;

		Lu_W_N_Item n_item;
		lu_size cells_processed = 0;
		while (lu_lim_list__is_present(curr_list))
		{
			n_item = (Lu_W_N_Item) lu_lim_list__pop_first_value(curr_list);
			lu__assert(n_item);

			lu_w_processor__fire_n_parents_with_sig(self, n_item->n_cell, n_item->n_column, 1.0);

			lu_w_processor__fire_n_labels_with_sig(self, n_item->n_cell->labels, self->la_column, 1.0);

			lu_mem_record__free(self->n_mem_table, (lu_p_byte) n_item);

			++cells_processed;
		}

		return cells_processed;
	}

	static inline lu_bool lu_w_processor__has_items_to_process(Lu_W_Processor self)
	{
		return !lu_list__is_blank((Lu_List) self->next_list);
	}

	static void lu_w_processor__prepare_results(Lu_W_Processor self);

///////////////////////////////////////////////////////////////////////////////
// lu_labels_

	static inline void lu_labels__print(Lu_Label* self, lu_size size)
	{
		lu__assert(self);

		lu__debug("\nLABELS:");
		Lu_Label label;
		Lu_La_Cell la_cell;
		Lu_W_Match_Cell match_cell;

		for (lu_size i = 0; i < size; i++)
		{
			label = self[i];
			if (label == NULL) break;

			la_cell = label->la_cell;
			lu__assert(la_cell);

			match_cell = label->match_cell;
			lu__assert(match_cell);

			lu__debug(
				"\n\tlabel=%ld, sig=%.2f [wave_id=%ld, block_ix=%ld, MATCH_CELL: wave_id=%ld, block_ix=%ld, LA_CELL: children_count=%ld]", 
				la_cell->addr.la_ix, 
				match_cell->sig,
				label->wave_id,
				label->block_ix,
				match_cell->wave_id,
				match_cell->block_ix,
				la_cell->children_count
			);
		}
	}

	static inline void lu_labels__reset(Lu_Label* self, lu_size size)
	{
		lu__assert(self);

		for (lu_size i = 0; i < size; i++)
		{
			self[i] = NULL;
		}
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