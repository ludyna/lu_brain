/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// 
//

	typedef struct lu_s_layer* Lu_S_Layer;
	static inline Lu_N_Table lu_s_layer__get_n_table(Lu_S_Layer self);

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
			case LU_W_REC_STATE__START:
				strcpy(buffer, "START");
				break;
			case LU_W_REC_STATE__ONE:
				strcpy(buffer, "ONE");
				break;
			case LU_W_REC_STATE__TWO:
				strcpy(buffer, "TWO");
				break;
			case LU_W_REC_STATE__SWITCH:
				strcpy(buffer, "SWITCH");
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
	};

	static inline Lu_W_Rec lu_w_rec__init_null(Lu_W_Rec self)
	{
		lu__assert(self);

		self->wave_id = LU_WAVE_ID__NOT_SET;
		self->wave_ix = LU_WAVE_IX__NOT_SET;
		self->block_ix = LU_BLOCK_IX__NOT_SET;
		self->state = LU_W_REC_STATE__START; 

		return self;
	}

	static inline void lu_w_rec__update(Lu_W_Rec self, lu_size wave_id, lu_size wave_ix, lu_size block_ix)
	{
		lu__assert(self);

		//
		// Detect state first
		//

		if (self->wave_id != wave_id)
		{
			// totally new wave, start with saving one
			self->state = LU_W_REC_STATE__ONE;
		}
		else if (self->wave_ix != wave_ix)
		{
			// new wave ix means its new wave also 
			// (should never happen because we get this lu_w_rec from "same" wave_ix, 
			// but put this code here noneless for completeness)
			self->state = LU_W_REC_STATE__ONE;
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

			lu__assert(diff > 0); // if this fails, probably wave was not reset properly 

			if (diff > 1)
			{
				self->state = LU_W_REC_STATE__ONE;
			}
			else
			{
				if (self->state == LU_W_REC_STATE__ONE)
				{
					self->state = LU_W_REC_STATE__TWO;
				}
				else if (self->state == LU_W_REC_STATE__TWO)
				{
					self->state = LU_W_REC_STATE__SWITCH;
				}
			}
		}

		//
		// Update values
		//

		self->wave_id = wave_id;
		self->wave_ix = wave_ix;
		self->block_ix = block_ix;
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

	struct lu_w_table {
		Lu_Mem mem;
		Lu_S_Layer s_layer;

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
	};

	static Lu_W_Table lu_w_table__create(
		Lu_S_Layer s_layer, 
		Lu_Config config, 
		lu_size w, 
		lu_size h,
		lu_size h_max
	);

	static void lu_w_table__destroy(Lu_W_Table self);

	static inline lu_bool lu_w_table__any_fired(Lu_W_Table self, lu_size wave_ix, lu_size block_ix)
	{
		if (self == NULL) return false;

		if (self->wave_ix != wave_ix || self->block_ix != block_ix) return false;

		return self->any_fired;
	}

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

		lu__debug("\nlocal_non_null_count=%ld, self->normal_children_size=%ld\n", local_non_null_count, self->normal_children_size);
		lu__debug_assert(local_non_null_count == self->normal_children_size);

		*children_count = local_non_null_count;
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
		Lu_Label *sorted_results;

		Lu_Lim_List curr_list;
		Lu_Lim_List next_list;

		Lu_S_List s_list;
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

	static inline void lu_w_processor__prepare_results(Lu_W_Processor self)
	{
		lu__assert(self);
		lu__assert(self->la_column);

		lu_size i;
		Lu_La_Cell la_cell;
		union lu_w_match_addr addr;
		Lu_La_Column la_column = self->la_column;
		Lu_W_Match_Cell match_cell;

		//
		// Reset s_list
		//
		if (self->s_list) lu_s_list__destroy(self->s_list);
		self->s_list = lu_s_list__create(self->mem, self->w_result_labels_size, lu_label__compare, LU_S_LST__LAST);
		lu__alloc_assert(self->s_list);
		
		//
		// Reset Lu Labels mem
		//
		lu_mem_table__reset(self->la_mem_table); // invalidates existing Lu_Labels

		// Reset sorted results
		if (self->sorted_results) lu_mem__free(self->mem, (lu_p_byte) self->sorted_results);
		self->sorted_results = (Lu_Label*) lu_mem__alloc(self->mem, sizeof(Lu_Label) * self->w_result_labels_size);
		lu__alloc_assert(self->sorted_results);
		
		for (i = 0; i < self->w_result_labels_size; i++)
		{
			self->sorted_results[i] = NULL;
		}

		//
		// Collect new results in s_list
		//
		Lu_Label label;
		for (i = 0; i < la_column->cells_size; i++)
		{
			la_cell = lu_la_column__get_la_cell(la_column, i);
			lu__assert(la_cell);

			addr = lu_la_cell__get_w_match_cell_addr(la_cell, self->wave_ix);

			if (lu_w_match_addr__is_blank(&addr)) continue;

			match_cell = lu_w_match_cell_mem__get_cell(self->match_cell_mem, addr);
			if (match_cell == NULL) continue;

			if (lu_w_match_cell__no_sig(match_cell)) continue;

			// lu__debug("\n\n OH YEAH %ld \n\n", la_cell->addr.la_ix);
			label = (Lu_Label) lu_mem_record__alloc(self->la_mem_table);
			lu__alloc_assert(label);

			lu_label__init(label, self->wave_ix, self->block_ix, la_cell, match_cell);

			lu_s_list__add(self->s_list, (lu_p_void) label);
		}

		//
		// Copy sorted results from s_list to sorted_results
		//

		i = 0;
		Lu_S_Node curr = lu_s_list__get_first_node(self->s_list);
		while (curr)
		{
			self->sorted_results[i] = (Lu_Label) lu_s_node__get_value(curr);
			++i;

			lu__assert(i < self->w_result_labels_size);

			curr = lu_s_node__get_next_node(curr);
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
