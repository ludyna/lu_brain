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
// Lu_W_Label_Item

	struct lu_w_la_item {
		Lu_W_Match_Cell match_cell;
		Lu_La_Cell label;
	};

///////////////////////////////////////////////////////////////////////////////
// Lu_W_Processor

	struct lu_w_processor {
		lu_size wave_id;
		lu_size block_id;
		Lu_S s;
		Lu_Mem mem;
		Lu_W_Match_Cell_Mem match_cell_mem;

		Lu_Mem_Table n_mem_table;
		Lu_Mem_Table la_mem_table;

		Lu_Lim_List curr_list;
		Lu_Lim_List next_list;

		Lu_S_List s_list;
	};

	static void lu_w_processor__init(Lu_W_Processor self, Lu_S s, Lu_Config config, Lu_W_Match_Cell_Mem match_cell_mem);
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
		lu__assert(self->wave_id < n_column->w_match_cells_size);

		Lu_W_Match_Cell match_cell = lu_n_cell__get_and_reset_match_cell(n_cell, self->wave_id, self->block_id, self->match_cell_mem);

		lu_w_match_cell__add_sig(match_cell, sig);

		if (lu_w_match_cell__ready_to_fire(match_cell))
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

			lu__debug("\n YOO! \n");

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

	static inline lu_size lu_w_processor__process(Lu_W_Processor self)
	{
		lu__assert(self);
		lu__assert(!lu_list__is_empty((Lu_List) self->curr_list));

		Lu_Lim_List t;
		t = self->curr_list;
		self->curr_list = self->next_list;
		self->next_list = t;


		Lu_List curr_list = (Lu_List) self->curr_list;

		Lu_L_Node current = curr_list->first;

		Lu_W_N_Item n_item;
		lu_size cells_processed = 0;
		while (current)
		{
			n_item = (Lu_W_N_Item) current->value;

			lu__assert(n_item);

			lu_w_processor__fire_n_parents_with_sig(self, n_item->n_cell, n_item->n_column, 1.0);

			++cells_processed;
			current = current->next;
		}

		return cells_processed;
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_W_Manager

	struct lu_w_manager {
		Lu_Mem mem;
		Lu_Mem_Table save_waves;
		Lu_Mem_Table match_waves;
		Lu_Mem_Table restore_waves;
	};

	static Lu_W_Manager lu_w_manager__create(Lu_Mem mem, Lu_Config config);
	static void lu_w_manager__destroy(Lu_W_Manager self); 

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
