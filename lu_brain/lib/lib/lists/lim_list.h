/**
	Copyright © 2021 Oleh Ihorovych Novosad 
*/


///////////////////////////////////////////////////////////////////////////////
// Lu_Lim_List

	struct lu_lim_list {
		struct lu_list 	super;

		Lu_Mem_Table 	mem_table;
		lu_size 		max_size;

		// We need callbacks feature for this data structure because this data structure 
		// "randomly" destroys its nodes while in lu_list, for example, we 
		// fully control when nodes are created or destroyed
		void 			(*node_after_create)(Lu_Lim_List, Lu_L_Node);
		void 			(*node_before_destroy)(Lu_Lim_List, Lu_L_Node);
	};

	// Properties

	static inline lu_size lu_lim_list_count(Lu_Lim_List self) { return lu_list_count(&self->super); }
	static inline lu_size lu_lim_list_size(Lu_Lim_List self) { return self->max_size; }
	static inline lu_bool lu_lim_list_is_empty(Lu_Lim_List self) { return lu_list_count(&self->super) == 0; }

	static inline Lu_L_Node lu_lim_list_node_last(Lu_Lim_List self) { return self->super.last; }
	static inline Lu_L_Node lu_lim_list_node_first(Lu_Lim_List self) { return self->super.first; }
	
	// Init
	
	static inline Lu_Lim_List lu_lim_list_init(Lu_Lim_List self, Lu_Mem_Table mem_table, lu_size limit_size)
	{
		lu_assert(self);
		lu_assert(mem_table);
		lu_assert(limit_size > 0);

		lu_list_init((Lu_List) self, lu_mem_table_mem_get(mem_table));

		self->mem_table = mem_table;
		self->max_size 	= limit_size;

		return self;
	}
	
	// Create and destroy

	Lu_Lim_List lu_lim_list_create(Lu_Mem, lu_size);
	void lu_lim_list_destroy(Lu_Lim_List self);

	// Methods

	Lu_L_Node lu_lim_list_append(Lu_Lim_List, lu_p_void);
	void lu_lim_list_node_remove(Lu_Lim_List, Lu_L_Node);