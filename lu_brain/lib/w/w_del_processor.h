/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/


///////////////////////////////////////////////////////////////////////////////
// Lu_W_Del_Item

	struct lu_w_del_item {
		Lu_N_Cell n_cell;
		Lu_S_Column s_column;
	};

	static inline Lu_W_Del_Item lu_w_del_item__init(
		Lu_W_Del_Item self, 
		Lu_N_Cell n_cell,
		Lu_S_Column s_column
	)
	{
		lu__assert(self);
		lu__assert(n_cell);
		lu__assert(s_column);

		self->n_cell = n_cell;
		self->s_column = s_column;

		return self;
	}

	static inline Lu_W_Del_Item lu_w_del_item__print(Lu_W_Del_Item self)
	{
		lu__assert(self);
		lu__assert(self->n_cell);
		lu__assert(self->s_column);

		lu__assert(self->n_cell->addr.column_ix == lu_s_column__get_column_ix(self->s_column));

		//lu_s_column__print(self->s_column);
		lu__debug("\n[%ld, %ld] | ", self->s_column->x, self->s_column->y);
		lu_n_addr__print(&self->n_cell->addr);
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_W_Del_List

	struct lu_w_del_list {
		Lu_Mem mem;
		struct lu_w_del_item* items;
		lu_size items_size;
		lu_size items_count;
	};

	//
	// Constructors / Destructors
	//

	static inline Lu_W_Del_List lu_w_del_list__init(Lu_W_Del_List self, Lu_Mem mem, lu_size items_size)
	{
		lu__assert(self);
		lu__assert(mem);
		lu__assert(items_size > 0);

		self->mem =	mem;

		self->items_size = items_size;
		self->items = (struct lu_w_del_item*) lu_mem__alloc(
			self->mem, 
			sizeof(struct lu_w_del_list) * self->items_size
		);

		lu__alloc_assert(self->items);

		self->items_count = 0;

		return self;
	}

	static inline void lu_w_del_list__deinit(Lu_W_Del_List self)
	{
		lu__assert(self);
		lu__assert(self->items_size > 0);

		lu_mem__free(self->mem, (lu_p_byte) self->items);

		self->items = NULL;
		self->items_size = 0;
		self->items_count = 0;
	}

	static inline Lu_W_Del_List lu_w_del_list__create(Lu_Mem mem, lu_size items_size)
	{
		lu__assert(mem);

		Lu_W_Del_List self = (Lu_W_Del_List) lu_mem__alloc(mem, sizeof(struct lu_w_del_list));
		lu__alloc_assert(self);

		lu_w_del_list__init(self, mem, items_size);

		return self;
	}

	static inline void lu_w_del_list__destroy(Lu_W_Del_List self)
	{
		lu__assert(self);
		lu__assert(self->mem);

		lu_w_del_list__deinit(self);

		lu_mem__free(self->mem, (lu_p_byte) self); 
	}


	//
	// Is 
	//

	static inline lu_bool lu_w_del_list__is_blank(Lu_W_Del_List self)
	{
		return self->items_count == 0;
	}

	static inline lu_bool lu_w_del_list__is_present(Lu_W_Del_List self)
	{
		return self->items_count > 0;
	}

	//
	// Methods
	//

	static inline void lu_w_del_list__realloc(Lu_W_Del_List self, lu_size new_items_size)
	{
		lu__assert(self);
		lu__assert(self->items_count < new_items_size);
		lu__assert(self->mem);

		lu__mem_debug("\n (!) lu_w_del_list__realloc, new_size: %ld", new_items_size);

		self->items = (struct lu_w_del_item*) lu_mem__realloc(
			self->mem, 
			(lu_p_byte) self->items, 
			sizeof(struct lu_w_del_item) * new_items_size
		);
		lu__alloc_assert(self->items);

		self->items_size = new_items_size;
	}

	static inline Lu_W_Del_Item lu_w_del_list__add(
		Lu_W_Del_List self,
		Lu_N_Cell n_cell,
		Lu_S_Column s_column
	)
	{
		lu__assert(self);
		lu__assert(self->items);
		lu__assert(self->items_size > 0);

		if (self->items_count >= self->items_size)
		{
			lu_w_del_list__realloc(self, self->items_size * 2);
		}

		Lu_W_Del_Item w_del_item = &self->items[self->items_count];
		++self->items_count;

		lu_w_del_item__init(w_del_item, n_cell, s_column);

		return w_del_item;
	}

	static inline void lu_w_del_list__reset(Lu_W_Del_List self)
	{
		lu__assert(self);

		self->items_count = 0;
	}

	static inline void lu_w_del_list__print_counts(Lu_W_Del_List self, char* name)
	{
		lu__assert(self);
		lu__debug("\n%s: %ld / %ld", name, self->items_count, self->items_size);
	}	

///////////////////////////////////////////////////////////////////////////////
// Lu_W_Del_Processor

	struct lu_w_del_processor {
		struct lu_block_id block_id;
		lu_size wave_ix;

		Lu_S s;
		Lu_Mem mem;

		Lu_W_Del_List curr_list;
		Lu_W_Del_List next_list;

		//
		// Stats
		//  

		struct lu_w_processor_stats stats;
	};

	//
	// Constructor / Destructor
	//

	static void lu_w_del_processor__init(
		Lu_W_Del_Processor self,  
		Lu_Mem mem, 
		Lu_S s, 
		Lu_Delete_Config config
	);

	static void lu_w_del_processor__deinit(Lu_W_Del_Processor self);

	//
	// Is / Has
	// 

	static inline lu_bool lu_w_del_processor__has_items_to_process(Lu_W_Del_Processor self)
	{
		return lu_w_del_list__is_present(self->next_list);
	}

	//
	// Methods
	//

	static inline void lu_w_del_processor__print_symbols(Lu_W_Del_Processor self)
	{
		lu__assert(self);

		Lu_W_Del_Item w_del_item;

		for (lu_size i = 0; i < self->next_list->items_count; i++)
		{
			w_del_item = &self->next_list->items[i];

			lu_w_del_item__print(w_del_item);
		}
	}

	static inline lu_size lu_w_del_processor__run_iteration(Lu_W_Del_Processor self)
	{
		lu__assert(self);
		lu__assert(lu_w_del_list__is_blank(self->curr_list));
		lu__assert(lu_w_del_list__is_present(self->next_list));

		Lu_W_Del_List t;
		t = self->curr_list;
		self->curr_list = self->next_list;
		self->next_list = t;

		Lu_W_Del_Item w_del_item;
		lu_size cells_processed = 0;

		Lu_N_Cell n_cell;
		Lu_S_Column s_column;

		union lu_n_link_addr child_link_addr;
		Lu_N_Link child_link;
		Lu_N_Cell child_n_cell;
		Lu_S_Column child_s_column;

		for (lu_size i = 0; i < self->curr_list->items_count; i++)
		{
			w_del_item = &self->curr_list->items[i];

			n_cell = w_del_item->n_cell;
			lu__assert(n_cell);

			s_column = w_del_item->s_column;
			lu__assert(s_column);

			//
			// Still connected to parents?
			//

			if (lu_n_link_addr__is_present(&n_cell->tl) || lu_n_link_addr__is_present(&n_cell->tr) ||
				lu_n_link_addr__is_present(&n_cell->bl) || lu_n_link_addr__is_present(&n_cell->br))
			{
				// this neuron is used in other patterns, we cant delete it.
				continue;
			}

			//
			// Free children=>n_cell links
			// 

			child_link_addr = n_cell->children;
			
			struct lu_n_located_cell located_cell;

			while (lu_n_link_addr__is_present(&child_link_addr))
			{
				child_link = lu_n_link_mem__get_link(&s_column->link_mem, child_link_addr);
				lu__assert(child_link);

				lu__assert(lu_n_addr__is_present(&child_link->n_cell_addr)); 

				child_n_cell = NULL;
				child_s_column = NULL;

				lu_n_located_cell__reset(&located_cell);

				lu_s__find_n_cell_and_s_column(
					self->s, 
					child_link->n_cell_addr, 
					&located_cell
				);

				// Wrong cell type, continue
				if (located_cell.n_cell_type != LU_N_CELL__N) goto next_child;

				child_n_cell = located_cell.n_cell;
				child_s_column = located_cell.s_column;

				lu__assert(child_n_cell);
				lu__assert(child_s_column);

				lu_n_cell__remove_link_to_parent(child_n_cell, n_cell->addr, &child_s_column->link_mem, &child_n_cell->tl);
				lu_n_cell__remove_link_to_parent(child_n_cell, n_cell->addr, &child_s_column->link_mem, &child_n_cell->tr);
				lu_n_cell__remove_link_to_parent(child_n_cell, n_cell->addr, &child_s_column->link_mem, &child_n_cell->bl);
				lu_n_cell__remove_link_to_parent(child_n_cell, n_cell->addr, &child_s_column->link_mem, &child_n_cell->br);

				// Queue child to be deleted next
				lu_w_del_list__add(self->next_list, child_n_cell, child_s_column);

next_child:

				child_link_addr = child_link->next;
			}

			//
			// Free children links (n_cell=>children)
			//

			lu_n_cell__free_children_links(n_cell, &s_column->link_mem);

			//
			// Free neuron
			//

			lu_s_column__free_n_cell(s_column, n_cell);

			++cells_processed;
		}

		lu_w_del_list__reset(self->curr_list);

		return cells_processed;
	}

	static inline void lu_w_del_processor__run(Lu_W_Del_Processor self)
	{
		lu__assert(self);

		while (lu_w_del_processor__has_items_to_process(self))
		{
			#ifdef LU__DEEP_DEBUG
			lu__debug("\nDEL PROCESSOR BATCH:");
			lu_w_del_processor__print_symbols(self);
			#endif 

			lu_w_del_processor__run_iteration(self);
		}
	}