/**
	Copyright © 2022 Oleh Ihorovych Novosad 

	Fast limited list with preallocated memory for nodes.
*/


///////////////////////////////////////////////////////////////////////////////
// Lu_Lim_List

	struct lu_lim_list {
		struct lu_list 	super;

		Lu_Mem_Table 	mem_table;
		lu_size 		max_size;

		// We need callbacks feature for this data structure because this data structure 
		// "randomly" destroys its nodes 
		void 			(*node_after_create)(Lu_Lim_List, Lu_L_Node);
		void 			(*node_before_destroy)(Lu_Lim_List, Lu_L_Node);
	};

	// Properties

	static inline lu_size lu_lim_list__count(Lu_Lim_List self) { return lu_list__count(&self->super); }
	static inline lu_size lu_lim_list__size(Lu_Lim_List self) { return self->max_size; }
	static inline lu_bool lu_lim_list__is_empty(Lu_Lim_List self) { return lu_list__count(&self->super) == 0; }

	static inline Lu_L_Node lu_lim_list__get_last_node(Lu_Lim_List self) { return self->super.last; }
	static inline Lu_L_Node lu_lim_list__get_first_node(Lu_Lim_List self) { return self->super.first; } 

	static inline lu_bool lu_lim_list__is_present(Lu_Lim_List self) { return lu_list__is_present((Lu_List) self); }
	static inline lu_bool lu_lim_list__is_blank(Lu_Lim_List self) { return lu_list__is_blank((Lu_List) self); }

	static inline lu_p_void lu_lim_list__get_first_value(Lu_Lim_List self) { return lu_list__get_first_value((Lu_List) self); }
	static inline lu_p_void lu_lim_list__get_last_value(Lu_Lim_List self) { return lu_list__get_last_value((Lu_List) self); }
	
	// Init
	
	static inline Lu_Lim_List lu_lim_list__init(Lu_Lim_List self, Lu_Mem_Table mem_table, lu_size limit_size)
	{
		lu__assert(self);
		lu__assert(mem_table);
		lu__assert(limit_size > 0);

		lu_list__init((Lu_List) self, lu_mem_table__mem_get(mem_table));

		self->mem_table = mem_table;
		self->max_size 	= limit_size;

		return self;
	}
	
	// Create and destroy

	Lu_Lim_List lu_lim_list__create(Lu_Mem, lu_size);
	void lu_lim_list__destroy(Lu_Lim_List self);

	// Methods

	Lu_L_Node lu_lim_list__append(Lu_Lim_List, lu_p_void);
	Lu_L_Node lu_lim_list__prepend(Lu_Lim_List, lu_p_void);
	
	void lu_lim_list__node_remove(Lu_Lim_List, Lu_L_Node);

	void lu_lim_list__clear(Lu_Lim_List);

	lu_p_void lu_lim_list__pop_first_value(Lu_Lim_List self);
	lu_p_void lu_lim_list__pop_last_value(Lu_Lim_List self);