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

	extern union lu_la_addr LU_LA_ADDR__NULL; 

	//
	// Get
	//

	static inline lu_size lu_la_addr__get_la_ix(Lu_La_Addr self)
	{
		return self->la_ix;
	}

	//
	// Is
	//

	static inline lu_bool lu_la_addr__is_present(Lu_La_Addr self)
	{
		return self->value != LU_LA_ADDR__NULL.value;
	}

	static inline lu_bool lu_la_addr__is_eq(Lu_La_Addr a, Lu_La_Addr b)
	{
		return a->value == b->value;
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_La_Link_Addr

	union lu_la_link_addr {
		struct {
			lu_size link_ix;
		};

		lu_size value;
	};

	extern union lu_la_link_addr LU_LA_LINK_ADDR__NULL; 

	//
	// Is 
	//

	static inline lu_bool lu_la_link_addr__is_present(Lu_La_Link_Addr self)
	{
		return self->value != LU_LA_LINK_ADDR__NULL.value;
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_La_Link

	struct lu_la_link {
		union lu_la_addr la_addr;

		union lu_la_link_addr next;
	}; 

	static inline Lu_La_Link lu_la_link__init(Lu_La_Link self, union lu_la_addr la_addr, union lu_la_link_addr next)
	{
		self->la_addr = la_addr;
		self->next = next;

		return self;
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_La_Link_Mem

	struct lu_la_link_mem {
		Lu_Mem_Table mem_table;
	};

	//
	// Constructors / Destructors
	// 

	Lu_La_Link_Mem lu_la_link_mem__init(Lu_La_Link_Mem self, Lu_Mem mem, lu_size size);
	void lu_la_link_mem__deinit(Lu_La_Link_Mem self);

	//
	// Get
	//

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
	
	//
	// Methods
	//

	static inline Lu_La_Link lu_la_link_mem__link_alloc(Lu_La_Link_Mem self)
	{
		lu__debug_assert(self);

		lu_p_byte record = lu_mem_record__alloc(self->mem_table);

		if (!record)
		{
			self->mem_table = lu_mem_table__realloc(
				self->mem_table, 
				lu_mem_table__records_count(self->mem_table) * 2
			); 
			lu__alloc_assert(self->mem_table);

			lu__mem_debug("\n (!) la_link_mem realloc");

			record = lu_mem_record__alloc(self->mem_table);
			lu__assert(record);
		}

		return (Lu_La_Link) record;
	}

	static inline void lu_la_link_mem__free_link(Lu_La_Link_Mem self, Lu_La_Link la_link)
	{
		lu__assert(self);
		lu__assert(self->mem_table);
		lu__assert(la_link);

		lu_mem_record__free(self->mem_table, (lu_p_byte) la_link);
	}
