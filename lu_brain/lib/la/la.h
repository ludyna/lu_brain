/**
	Copyright © 2022 Oleh Ihorovych Novosad 

*/

///////////////////////////////////////////////////////////////////////////////
// Lu_La_Addr

	union lu_la_addr {
		struct {
			lu_size la_ix;
		};

		lu_size value;
	};

///////////////////////////////////////////////////////////////////////////////
// Lu_La_Cell

	#define LU_LA_CELL__LABEL_NOT_SET LU_SIZE__MAX

	struct lu_la_cell {
		lu_size label; // we need this because same label_ix might "contain" more than one label

		Lu_La_Link children;
		lu_size children_count;

		union lu_w_match_addr* w_cells;
	};

	static inline Lu_La_Cell lu_la_cell__init(Lu_La_Cell self, lu_size label)
	{
		lu__debug_assert(self);

		self->label = label;
		self->children = NULL;
		self->children_count = 0;
		self->w_cells = NULL;

		return self;
	}

	static inline Lu_La_Cell lu_la_cell__deinit(Lu_La_Cell self, Lu_Mem w_mem)
	{
		lu__assert(self);
		lu__assert(w_mem);

		if (self->w_cells)
			lu_mem__free(w_mem, (lu_p_byte) self->w_cells);

		self->children = NULL;
		self->children_count = 0;
		self->w_cells = 0;
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_La_Link_Addr

	union lu_la_link_addr {
		struct {
			lu_size link_ix;
		};

		lu_size value;
	};

///////////////////////////////////////////////////////////////////////////////
// Lu_La_Link

	struct lu_la_link {
		union lu_la_addr la_addr;

		union lu_la_link_addr next;
	}; 

///////////////////////////////////////////////////////////////////////////////
// Lu_La_Link_Mem

	struct lu_la_link_mem {
		Lu_Mem_Table mem_table;
	};

	Lu_La_Link_Mem lu_la_link_mem__init(Lu_La_Link_Mem self, Lu_Mem mem, lu_size size);
	void lu_la_link_mem__deinit(Lu_La_Link_Mem self);

	static inline Lu_La_Link lu_la_link_mem__link_alloc(Lu_La_Link_Mem self)
	{
		lu__debug_assert(self);

		lu_p_byte record = lu_mem_record__alloc(self->mem_table);

		if (!record)
		{
			lu_mem_table__realloc(
				self->mem_table, 
				lu_mem_table__records_count(self->mem_table) * 2, 
				LU_MEM_TABLE__DEFAULT
			); 

			record = lu_mem_record__alloc(self->mem_table);
			lu__assert(record);
		}

		return (Lu_La_Link) record;
	}

	static inline Lu_La_Link lu_la_link_mem__get_link(Lu_La_Link_Mem self, union lu_la_link_addr addr)
	{
		lu__debug_assert(self);
		lu__debug_assert(self->mem_table);

		if (addr.value == 0) return NULL;

		return (Lu_La_Link) lu_mem_table__get(self->mem_table, addr.value);
	}

	////
	// 
	static inline union lu_la_link_addr lu_la_link_mem__get_addr(Lu_La_Link_Mem self, Lu_La_Link link)
	{
		lu__debug_assert(self);
		lu__debug_assert(link);

		union lu_la_link_addr addr;

		addr.value = lu_mem_table__record_ix(self->mem_table, (lu_p_byte) link);

		return addr;
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_La_Column
	
	struct lu_la_column {
		Lu_Mem la_mem;
		Lu_Mem w_mem;
		Lu_Mem n_mem;

		struct lu_la_cell* cells;
		lu_size cells_size;

		Lu_N_Link_Mem n_link_mem;
		Lu_La_Link_Mem la_link_mem;


	};

	static Lu_La_Column lu_la_column__init(Lu_La_Column self, Lu_Config config);

	static void lu_la_column__deinit(Lu_La_Column self);

	static inline Lu_N_Link_Mem lu_la_column__get_n_link_mem(Lu_La_Column self)
	{
		lu__debug_assert(self);

		return self->n_link_mem;
	}

	static inline lu_size lu_la_column__label_to_ix(Lu_La_Column self, lu_size label)
	{
		lu__debug_assert(self);

		lu__assert(label < self->cells_size); // simplified, when we add realloc, everything will be fine

		return label;
	}

	static inline Lu_La_Cell lu_la_column__get_la_cell(Lu_La_Column self, lu_size label)
	{
		lu__debug_assert(self);

		lu_size label_ix = lu_la_column__label_to_ix(self, label);

		return &self->cells[label_ix];
	}

	static inline Lu_La_Cell lu_la_column__save_label(Lu_La_Column self, Lu_N_Cell n_cell, lu_size label)
	{
		lu__assert(self);
		lu__assert(n_cell);
		lu__assert(label < self->cells_size);

		Lu_La_Cell cell = &self->cells[lu_la_column__label_to_ix(self, label)];


	}
