/**
	Copyright © 2022 Oleh Ihorovych Novosad 

*/

///////////////////////////////////////////////////////////////////////////////
// 
	union lu_la_addr {
		struct {
			lu_size la_ix;
		};

		lu_size value;
	};

///////////////////////////////////////////////////////////////////////////////
// 

	struct lu_la_cell {
		lu_size label;

		Lu_La_Link children;
		lu_size children_count;

		union lu_w_match_addr* w_cells;
	};

///////////////////////////////////////////////////////////////////////////////
// 

	union lu_la_link_addr {
		struct {
			lu_size link_ix;
		};

		lu_size value;
	};

///////////////////////////////////////////////////////////////////////////////
// 

	struct lu_la_link {
		union lu_la_addr la_addr;

		union lu_la_link_addr next;
	}; 

///////////////////////////////////////////////////////////////////////////////
// 

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
// 
	
	struct lu_la_column {


		struct lu_la_cell* cells;
		lu_size cells_size;

		Lu_La_Link_Mem n_link_mem;
		Lu_La_Link_Mem la_link_mem;
	};