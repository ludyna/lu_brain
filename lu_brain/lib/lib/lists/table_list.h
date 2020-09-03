/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Lu_Table_List

	struct lu_table_list {
		struct lu_list 	super;

		Mem_Table 		mem_table;
		lu_size 		max_size;
	};


	static inline Lu_Table_List lu_table_list_init(Lu_Table_List self, Mem_Table mem_table, lu_size limit_size)
	{
		lu_assert(self);
		lu_assert(mem_table);
		lu_assert(limit_size > 0);

		lu_list_init((Lu_List) self, mem_table_mem_get(mem_table));

		self->mem_table = mem_table;
		self->max_size 	= limit_size;
	}
	Lu_Table_List lu_table_list_create(Mem, lu_size);
	void lu_table_list_destroy(Lu_Table_List self);



