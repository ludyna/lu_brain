/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Lu_W_Match_Item

	struct lu_w_match_item {
		Lu_W_Match_Cell match_cell;
		Lu_N_Cell n_cell;
		Lu_S_Column s_column;
	};

	static inline Lu_W_Match_Item lu_w_match_item__init(
		Lu_W_Match_Item self, 
		Lu_W_Match_Cell match_cell,
		Lu_N_Cell n_cell,
		Lu_S_Column s_column
	)
	{
		lu__assert(self);
		lu__assert(match_cell);
		lu__assert(n_cell);
		lu__assert(s_column);

		self->match_cell = match_cell;
		self->n_cell = n_cell;
		self->s_column = s_column;

		return self;
	}

	static inline Lu_W_Match_Item lu_w_match_item__print(Lu_W_Match_Item self)
	{
		lu__assert(self);
		lu__assert(self->n_cell);
		lu__assert(self->s_column);
		lu__assert(self->match_cell);

		lu__assert(self->n_cell->addr.column_ix == lu_s_column__get_column_ix(self->s_column));

		//lu_s_column__print(self->s_column);
		lu__debug("\n[%ld, %ld] sig=%.f | ", self->s_column->x, self->s_column->y, self->match_cell->sig);
		lu_n_addr__print(&self->n_cell->addr);
	}

	static inline lu_value lu_w_match_item__calc_fire_sig(Lu_W_Match_Item self)
	{
		return self->match_cell->sig / self->n_cell->default_sig;

		return lu_w_match_cell__calc_fire_sig(self->match_cell, self->n_cell->default_sig);
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_W_Match_List

	struct lu_w_match_list {
		Lu_Mem mem;
		struct lu_w_match_item* items;
		lu_size items_size;
		lu_size items_count;
	};

	//
	// Constructors / Destructors
	//

	static inline Lu_W_Match_List lu_w_match_list__init(Lu_W_Match_List self, Lu_Mem mem, lu_size items_size)
	{
		lu__assert(self);
		lu__assert(mem);
		lu__assert(items_size > 0);

		self->mem =	mem;

		self->items_size = items_size;
		self->items = (struct lu_w_match_item*) lu_mem__alloc(
			self->mem, 
			sizeof(struct lu_w_match_list) * self->items_size
		);

		lu__alloc_assert(self->items);

		self->items_count = 0;

		return self;
	}

	static inline void lu_w_match_list__deinit(Lu_W_Match_List self)
	{
		lu__assert(self);
		lu__assert(self->items_size > 0);

		lu_mem__free(self->mem, (lu_p_byte) self->items);

		self->items = NULL;
		self->items_size = 0;
		self->items_count = 0;
	}

	static inline Lu_W_Match_List lu_w_match_list__create(Lu_Mem mem, lu_size items_size)
	{
		lu__assert(mem);

		Lu_W_Match_List self = (Lu_W_Match_List) lu_mem__alloc(mem, sizeof(struct lu_w_match_list));
		lu__alloc_assert(self);

		lu_w_match_list__init(self, mem, items_size);

		return self;
	}

	static inline void lu_w_match_list__destroy(Lu_W_Match_List self)
	{
		lu__assert(self);
		lu__assert(self->mem);

		lu_w_match_list__deinit(self);

		lu_mem__free(self->mem, (lu_p_byte) self); 
	}


	//
	// Is 
	//

	static inline lu_bool lu_w_match_list__is_blank(Lu_W_Match_List self)
	{
		return self->items_count == 0;
	}

	static inline lu_bool lu_w_match_list__is_present(Lu_W_Match_List self)
	{
		return self->items_count > 0;
	}

	//
	// Methods
	//

	static inline void lu_w_match_list__realloc(Lu_W_Match_List self, lu_size new_items_size)
	{
		lu__assert(self);
		lu__assert(self->items_count < new_items_size);
		lu__assert(self->mem);

		lu__mem_debug("\n (!) lu_w_match_list__realloc, new_size: %ld", new_items_size);

		self->items = (struct lu_w_match_item*) lu_mem__realloc(
			self->mem, 
			(lu_p_byte) self->items, 
			sizeof(struct lu_w_match_item) * new_items_size
		);
		lu__alloc_assert(self->items);

		self->items_size = new_items_size;
	}

	static inline Lu_W_Match_Item lu_w_match_list__add(
		Lu_W_Match_List self,
		Lu_W_Match_Cell match_cell,
		Lu_N_Cell n_cell,
		Lu_S_Column s_column
	)
	{
		lu__assert(self);
		lu__assert(self->items);
		lu__assert(self->items_size > 0);

		if (self->items_count >= self->items_size)
		{
			lu_w_match_list__realloc(self, self->items_size * 2);
		}

		Lu_W_Match_Item w_proc_item = &self->items[self->items_count];
		++self->items_count;

		lu_w_match_item__init(w_proc_item, match_cell, n_cell, s_column);

		return w_proc_item;
	}

	static inline void lu_w_match_list__reset(Lu_W_Match_List self)
	{
		lu__assert(self);

		self->items_count = 0;
	}

	static inline void lu_w_match_list__print_counts(Lu_W_Match_List self, char* name)
	{
		lu__assert(self);
		lu__debug("\n%s: %ld / %ld", name, self->items_count, self->items_size);
	}	


///////////////////////////////////////////////////////////////////////////////
// lu_labels_

	static inline void lu_labels__print_results(Lu_Label* self, lu_size size)
	{
		lu__assert(self);

		Lu_Label label;
		Lu_La_Cell la_cell;
		Lu_W_La_Match_Cell match_cell;

		for (lu_size i = 0; i < size; i++)
		{
			label = self[i];
			if (label == NULL) break;

			la_cell = label->la_cell;
			lu__assert(la_cell);

			match_cell = label->match_cell;
			lu__assert(match_cell);

			lu__debug(
				"\n\tlabel=%ld, sig=%.2f (%.0f) [MATCH_CELL: wave_id=%ld, block_ix=%ld, LA_CELL: children_count=%ld]", 
				la_cell->addr.la_ix, 
				lu_label__get_sig(label),
				match_cell->sig_received_count,
				match_cell->block_id.wave_id,
				match_cell->block_id.block_ix,
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
// Lu_W_Match_Processor 

	struct lu_w_match_processor {
		struct lu_block_id block_id;
		lu_size wave_ix;

		Lu_S s;
		Lu_Mem mem;
		Lu_W_Match_Cell_Mem match_cell_mem;
		Lu_La_Column la_column;

		Lu_W_Match_List curr_list;
		Lu_W_Match_List next_list;

		Lu_Mem_Table la_mem_table;

		Lu_S_List s_list;
		Lu_Label* sorted_results;

		// 
		// Config
		//

		lu_size w_match_results_size;
		lu_value w_match_sig_breakpoint;

		//
		// Stats
		//  

		struct lu_w_processor_stats stats;
	};

	static void lu_w_match_processor__init(
		Lu_W_Match_Processor self,  
		Lu_S s, 
		Lu_Config config, 
		Lu_W_Match_Cell_Mem match_cell_mem,
		Lu_La_Column la_column
	);

	static void lu_w_match_processor__deinit(Lu_W_Match_Processor self);

	static inline void lu_w_match_processor__fire_n_cell(
		Lu_W_Match_Processor self,
		Lu_N_Cell n_cell,
		Lu_S_Column s_column,
		lu_value sig
	)
	{
		lu__assert(self->wave_ix < s_column->w_match_cells_size);

		Lu_W_Match_Cell match_cell = lu_n_cell__get_and_reset_match_cell(n_cell, self->block_id, self->wave_ix, self->match_cell_mem);

		lu_w_match_cell__add_sig(match_cell, sig);

		if (lu_w_match_cell__is_sig_over_breakpoint(match_cell, n_cell, self->w_match_sig_breakpoint))
		{
			match_cell->fired = true;

			lu_w_match_list__add(self->next_list, match_cell, n_cell, s_column);

			++self->stats.cells_processed;
		}
	}

	static inline void lu_w_match_processor__fire_n_parents(
		Lu_W_Match_Processor self, 
		Lu_N_Link_Mem link_mem,
		lu_value sig,
		union lu_n_link_addr parent_link_addr
	)
	{
		Lu_N_Link n_link_parent = lu_n_link_mem__get_link(link_mem, parent_link_addr);

		Lu_N_Cell n_cell_parent;
		Lu_S_Column s_column_parent;

		struct lu_n_located_cell located_cell;
 
		while (n_link_parent)
		{
			n_cell_parent = NULL;
			s_column_parent = NULL;

			lu_n_located_cell__reset(&located_cell);

			lu_s__find_n_cell_and_s_column(self->s, n_link_parent->n_cell_addr, &located_cell);

			lu__assert(located_cell.n_cell_type == LU_N_CELL__N);

			n_cell_parent = located_cell.n_cell;
			s_column_parent = located_cell.s_column;

			lu__assert(n_cell_parent);
			lu__assert(s_column_parent);

			lu_w_match_processor__fire_n_cell(self, n_cell_parent, s_column_parent, sig);

			n_link_parent = lu_n_link_mem__get_link(link_mem, n_link_parent->next);
		}
	}

	static inline void lu_w_match_processor__fire_vp_parents_with_sig(
		Lu_W_Match_Processor self, 
		Lu_N_Cell_VP n_cell, 
		Lu_S_Column_Comp s_column,
		lu_value sig
	)
	{
		lu__debug_assert(self);
		lu__debug_assert(n_cell);
		lu__debug_assert(s_column);
		lu__debug_assert(sig > 0);
	
		//lu_n_addr__print(&n_cell->addr);
		if (lu_n_link_addr__is_present(&n_cell->parents))
			lu_w_match_processor__fire_n_parents(self, &s_column->link_mem, sig, n_cell->parents);
	}

	static inline void lu_w_match_processor__fire_n_parents_with_sig(
		Lu_W_Match_Processor self, 
		Lu_N_Cell n_cell, 
		Lu_S_Column s_column,
		lu_value sig
	)
	{
		lu__debug_assert(self);
		lu__debug_assert(n_cell);
		lu__debug_assert(s_column);
		lu__debug_assert(sig > 0);

		if (lu_n_link_addr__is_present(&n_cell->tl))
			lu_w_match_processor__fire_n_parents(self, &s_column->link_mem, sig, n_cell->tl);

		if (lu_n_link_addr__is_present(&n_cell->tr))
			lu_w_match_processor__fire_n_parents(self, &s_column->link_mem, sig, n_cell->tr);

		if (lu_n_link_addr__is_present(&n_cell->bl))
			lu_w_match_processor__fire_n_parents(self, &s_column->link_mem, sig, n_cell->bl);

		if (lu_n_link_addr__is_present(&n_cell->br))
			lu_w_match_processor__fire_n_parents(self, &s_column->link_mem, sig, n_cell->br);
	}

	static inline void lu_w_match_processor__fire_n_labels_with_sig(
		Lu_W_Match_Processor self, 
		Lu_N_Cell n_cell,
		Lu_La_Column la_column,
		lu_value sig
	)
	{
		lu__debug_assert(self);
		lu__assert(n_cell);
		lu__debug_assert(la_column);
		lu__debug_assert(sig > 0);

		union lu_la_link_addr labels = n_cell->labels;

		Lu_La_Link_Mem link_mem = lu_la_column__get_la_link_mem(la_column);
		lu__assert(link_mem);

		Lu_La_Link la_link_label = lu_la_link_mem__get_link(link_mem, labels);

		Lu_La_Cell la_cell;
		Lu_W_La_Match_Cell match_cell;
 
		while (la_link_label)
		{
			la_cell = NULL;

			la_cell = lu_la_column__get_la_cell_by_addr(la_column, la_link_label->la_addr);
			lu__assert(la_cell);

			match_cell = lu_la_cell__get_and_reset_match_cell(la_cell, self->block_id, self->wave_ix, self->match_cell_mem);
			lu__assert(match_cell);
			
			lu_w_la_match_cell__add_sig(match_cell, n_cell, sig);

			la_link_label = lu_la_link_mem__get_link(link_mem, la_link_label->next);
		}
	}

	static inline lu_size lu_w_match_processor__run_iteration(Lu_W_Match_Processor self)
	{
		lu__assert(self);
		lu__assert(lu_w_match_list__is_blank(self->curr_list));
		lu__assert(lu_w_match_list__is_present(self->next_list));

		Lu_W_Match_List t;
		t = self->curr_list;
		self->curr_list = self->next_list;
		self->next_list = t;

		Lu_W_Match_Item w_proc_item;
		lu_size cells_processed = 0;

		lu_value fire_sig = 0;

		for (lu_size i = 0; i < self->curr_list->items_count; i++)
		{
			w_proc_item = &self->curr_list->items[i];

			fire_sig = lu_w_match_item__calc_fire_sig(w_proc_item);

			// proc_item with fire sig < breakpoint should not be here
			lu__assert(fire_sig >= self->w_match_sig_breakpoint); 

			// fire_sig should be always less or equal to one
			lu__assert(fire_sig <= 1.0); 

			lu_w_match_processor__fire_n_parents_with_sig(self, w_proc_item->n_cell, w_proc_item->s_column, fire_sig);

			if (lu_la_link_addr__is_present(&w_proc_item->n_cell->labels))
			{
				lu__deep_debug(
					"\nN_CELL has label (n_cell->cell_ix=%ld) link_addr=%ld", 
					w_proc_item->n_cell->addr.cell_ix, 
					w_proc_item->n_cell->labels.value
				);
				lu_w_match_processor__fire_n_labels_with_sig(self, w_proc_item->n_cell, self->la_column, fire_sig);
			}

			++cells_processed;
		}

		lu_w_match_list__reset(self->curr_list);

		return cells_processed;
	}

	static inline lu_bool lu_w_match_processor__has_items_to_process(Lu_W_Match_Processor self)
	{
		return lu_w_match_list__is_present(self->next_list);
	}

	static inline void lu_w_match_processor__prepare_results(Lu_W_Match_Processor self)
	{
		lu__assert(self);
		lu__assert(self->la_column);
		lu__assert(self->w_match_results_size > 0);
		lu__assert(self->mem);

		lu_size i;
		Lu_La_Cell la_cell;
		// union lu_w_match_addr addr;
		Lu_La_Column la_column = self->la_column;
		Lu_W_La_Match_Cell match_cell;

		//
		// Collect new results in s_list
		//
		Lu_Label label;
		for (i = 0; i < la_column->cells_size; i++)
		{
			la_cell = lu_la_column__get_la_cell(la_column, i);
			lu__assert(la_cell);

			if (la_cell->children_count == 0) continue;

			lu__deep_debug("\nPREPARING (wave_ix=%ld)", self->wave_ix);
			#ifdef LU__DEEP_DEBUG
			lu_la_cell__print(la_cell);
			#endif

			// addr = lu_la_cell__get_w_match_cell_addr(la_cell, self->wave_ix);

			// if (lu_w_match_addr__is_blank(&addr)) continue;

			// match_cell = lu_w_match_cell_mem__get_cell(self->match_cell_mem, addr);
			// if (match_cell == NULL) continue;

			match_cell = lu_la_cell__get_w_match_cell(la_cell, self->wave_ix);

			if (lu_w_la_match_cell__no_sig(match_cell)) continue;

			if (lu_block_id__is_not_eq(&self->block_id, &match_cell->block_id)) continue;

			lu__deep_debug("\nALLOCATING Lu_Label, initing and addingg to s_list, la_ix=%ld \n", la_cell->addr.la_ix);

			label = (Lu_Label) lu_mem_record__alloc(self->la_mem_table);
			lu__alloc_assert(label);

			lu_label__init(label, la_cell, match_cell);

			lu_s_list__add(self->s_list, (lu_p_void) label);
		}

		//
		// Copy sorted results from s_list to sorted_results
		//

		i = 0;
		Lu_S_Node curr = lu_s_list__get_first_node(self->s_list);
		while (curr)
		{
			lu__assert(i < self->w_match_results_size);

			self->sorted_results[i] = (Lu_Label) lu_s_node__get_value(curr);
			++i;	

			curr = lu_s_node__get_next_node(curr);
		}
	}

	static inline void lu_w_match_processor__run(Lu_W_Match_Processor self)
	{
		while (lu_w_match_processor__has_items_to_process(self))
		{
			#ifdef LU__DEEP_DEBUG
			lu__debug("\nMATCH PROCESSOR BATCH:");
			lu_w_match_processor__print_symbols(self);
			#endif 

			lu_w_match_processor__run_iteration(self);
		}

		lu_w_match_processor__prepare_results(self);
	}

	static inline void lu_w_match_processor__print_symbols(Lu_W_Match_Processor self)
	{
		lu__assert(self);

		Lu_W_Match_Item w_proc_item;

		for (lu_size i = 0; i < self->next_list->items_count; i++)
		{
			w_proc_item = &self->next_list->items[i];

			lu_w_match_item__print(w_proc_item);
		}
	}

	static inline void lu_w_match_processor__reset_results(Lu_W_Match_Processor self)
	{
		lu__assert(self);
		//
		// Reset s_list
		//
		
		if (self->s_list) lu_s_list__destroy(self->s_list);

		lu__deep_debug("\n !! self->w_match_results_size=%ld", self->w_match_results_size);

		self->s_list = lu_s_list__create(self->mem, self->w_match_results_size, lu_label__compare, LU_S_LST__LAST);
		lu__alloc_assert(self->s_list);
		
		//
		// Reset Lu Labels mem
		//
		lu_mem_table__reset(self->la_mem_table); // invalidates existing Lu_Labels

		//
		// Reset sorted results
		//

		lu_labels__reset(self->sorted_results, self->w_match_results_size);

		//
		// Reset proc stats
		//

		lu_w_processor_stats__reset(&self->stats);
	}
