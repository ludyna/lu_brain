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

	static void lu_w_del_processor__init(
		Lu_W_Del_Processor self,  
		Lu_Mem mem, 
		Lu_S s, 
		Lu_Delete_Config config
	);

	static void lu_w_del_processor__deinit(Lu_W_Del_Processor self);
