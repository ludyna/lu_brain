/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/


///////////////////////////////////////////////////////////////////////////////
// Lu_W_Restore_Item

	struct lu_w_restore_item {
		Lu_N_Cell n_cell;
		Lu_S_Column s_column;
	};

	static inline Lu_W_Restore_Item lu_w_restore_item__init(
		Lu_W_Restore_Item self, 
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

	static inline Lu_W_Restore_Item lu_w_restore_item__print(Lu_W_Restore_Item self)
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
// Lu_W_Restore_List

	struct lu_w_restore_list {
		Lu_Mem mem;
		struct lu_w_restore_item* items;
		lu_size items_size;
		lu_size items_count;
	};

	//
	// Constructors / Destructors
	//

	static inline Lu_W_Restore_List lu_w_restore_list__init(Lu_W_Restore_List self, Lu_Mem mem, lu_size items_size)
	{
		lu__assert(self);
		lu__assert(mem);
		lu__assert(items_size > 0);

		self->mem =	mem;

		self->items_size = items_size;
		self->items = (struct lu_w_restore_item*) lu_mem__alloc(
			self->mem, 
			sizeof(struct lu_w_restore_list) * self->items_size
		);

		lu__alloc_assert(self->items);

		self->items_count = 0;

		return self;
	}

	static inline void lu_w_restore_list__deinit(Lu_W_Restore_List self)
	{
		lu__assert(self);
		lu__assert(self->items_size > 0);

		lu_mem__free(self->mem, (lu_p_byte) self->items);

		self->items = NULL;
		self->items_size = 0;
		self->items_count = 0;
	}

	static inline Lu_W_Restore_List lu_w_restore_list__create(Lu_Mem mem, lu_size items_size)
	{
		lu__assert(mem);

		Lu_W_Restore_List self = (Lu_W_Restore_List) lu_mem__alloc(mem, sizeof(struct lu_w_restore_list));
		lu__alloc_assert(self);

		lu_w_restore_list__init(self, mem, items_size);

		return self;
	}

	static inline void lu_w_restore_list__destroy(Lu_W_Restore_List self)
	{
		lu__assert(self);
		lu__assert(self->mem);

		lu_w_restore_list__deinit(self);

		lu_mem__free(self->mem, (lu_p_byte) self); 
	}


	//
	// Is 
	//

	static inline lu_bool lu_w_restore_list__is_blank(Lu_W_Restore_List self)
	{
		return self->items_count == 0;
	}

	static inline lu_bool lu_w_restore_list__is_present(Lu_W_Restore_List self)
	{
		return self->items_count > 0;
	}

	//
	// Methods
	//

	static inline void lu_w_restore_list__realloc(Lu_W_Restore_List self, lu_size new_items_size)
	{
		lu__assert(self);
		lu__assert(self->items_count < new_items_size);
		lu__assert(self->mem);

		lu__mem_debug("\n (!) lu_w_restore_list__realloc, new_size: %ld", new_items_size);

		self->items = (struct lu_w_restore_item*) lu_mem__realloc(
			self->mem, 
			(lu_p_byte) self->items, 
			sizeof(struct lu_w_restore_item) * new_items_size
		);
		lu__alloc_assert(self->items);

		self->items_size = new_items_size;
	}

	static inline Lu_W_Restore_Item lu_w_restore_list__add(
		Lu_W_Restore_List self,
		Lu_N_Cell n_cell,
		Lu_S_Column s_column
	)
	{
		lu__assert(self);
		lu__assert(self->items);
		lu__assert(self->items_size > 0);

		if (self->items_count >= self->items_size)
		{
			lu_w_restore_list__realloc(self, self->items_size * 2);
		}

		Lu_W_Restore_Item w_restore_item = &self->items[self->items_count];
		++self->items_count;

		lu_w_restore_item__init(w_restore_item, n_cell, s_column);

		return w_restore_item;
	}

	static inline void lu_w_restore_list__reset(Lu_W_Restore_List self)
	{
		lu__assert(self);

		self->items_count = 0;
	}

	static inline void lu_w_restore_list__print_counts(Lu_W_Restore_List self, char* name)
	{
		lu__assert(self);
		lu__debug("\n%s: %ld / %ld", name, self->items_count, self->items_size);
	}	

///////////////////////////////////////////////////////////////////////////////
// Lu_W_Restore_Processor

	struct lu_w_restore_processor {
		struct lu_block_id block_id;
		lu_size wave_ix;

		Lu_S s;
		Lu_Mem mem;

		Lu_W_Restore_List curr_list;
		Lu_W_Restore_List next_list;

		//
		// Stats
		//  

		struct lu_w_processor_stats stats;

		//
		// This is temporary solution
		//

		Lu_Data data;
	};

	//
	// Constructor / Destructor
	//

	static void lu_w_restore_processor__init(
		Lu_W_Restore_Processor self,  
		Lu_Wave wave,  
		Lu_Mem mem, 
		Lu_S s, 
		Lu_Restore_Config config
	);

	static void lu_w_restore_processor__deinit(Lu_W_Restore_Processor self);

	static inline void lu_w_restore_processor__reset(Lu_W_Restore_Processor self)
	{
		lu__assert(self);

		lu_block_id__increase_block_ix(&self->block_id);

		lu_w_restore_list__reset(self->curr_list);
		lu_w_restore_list__reset(self->next_list);

		lu_w_processor_stats__reset(&self->stats);
		self->data = NULL;
	}	

	//
	// Is / Has
	// 

	static inline lu_bool lu_w_restore_processor__has_items_to_process(Lu_W_Restore_Processor self)
	{
		return lu_w_restore_list__is_present(self->next_list);
	}

	//
	// Methods
	//

	static inline void lu_w_restore_processor__print_symbols(Lu_W_Restore_Processor self)
	{
		lu__assert(self);

		Lu_W_Restore_Item w_restore_item;

		for (lu_size i = 0; i < self->next_list->items_count; i++)
		{
			w_restore_item = &self->next_list->items[i];

			lu_w_restore_item__print(w_restore_item);
		}
	}

	static inline lu_size lu_w_restore_processor__run_iteration(Lu_W_Restore_Processor self);

	static inline void lu_w_restore_processor__run(Lu_W_Restore_Processor self);