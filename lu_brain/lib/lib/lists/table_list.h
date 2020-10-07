/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/


///////////////////////////////////////////////////////////////////////////////
// Lu_Table_List

	struct lu_table_list {
		struct lu_list 	super;

		Mem_Table 		mem_table;
		lu_size 		max_size;

		// We need callbacks feature for this data structure because this data structure 
		// "randomly" destroys its nodes while in lu_list, for example, we 
		// fully control when nodes are created or destroyed
		void 			(*node_after_create)(Lu_Table_List, Lu_L_Node);
		void 			(*node_before_destroy)(Lu_Table_List, Lu_L_Node);
	};

	static inline lu_size lu_table_list_count(Lu_Table_List self) { return lu_list_count(&self->super); }
	static inline lu_size lu_table_list_size(Lu_Table_List self) { return self->max_size; }

	static inline Lu_Table_List lu_table_list_init(Lu_Table_List self, Mem_Table mem_table, lu_size limit_size)
	{
		lu_assert(self);
		lu_assert(mem_table);
		lu_assert(limit_size > 0);

		lu_list_init((Lu_List) self, mem_table_mem_get(mem_table));

		self->mem_table = mem_table;
		self->max_size 	= limit_size;

		return self;
	}
	
	Lu_Table_List lu_table_list_create(Mem, lu_size);
	void lu_table_list_destroy(Lu_Table_List self);

	static inline Lu_L_Node lu_table_list_node_last(Lu_Table_List self) { return self->super.last; }
	static inline Lu_L_Node lu_table_list_node_first(Lu_Table_List self) { return self->super.first; }
	
	Lu_L_Node lu_table_list_append(Lu_Table_List, lu_p_void);
	void lu_table_list_node_remove(Lu_Table_List, Lu_L_Node);

	void lu_table_list_node_destroy_all(Lu_Table_List self);