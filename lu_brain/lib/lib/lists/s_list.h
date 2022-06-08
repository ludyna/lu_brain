/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Lu_S_Node

	struct lu_s_node
	{
		struct lu_lim_list 	values;

		Lu_S_Node 				next;
		Lu_S_Node 				prev;
		Lu_S_Node 				below;
		Lu_S_Node 				above;

		lu_p_void 				value;
	};

	// Init, create and destroy

	static inline void lu_s_node__init(Lu_S_Node self, Lu_Mem_Table mem_table, lu_size limit_size)
	{
		lu_lim_list__init(&self->values, mem_table, limit_size);

		self->next 				= NULL;
		self->prev				= NULL;
		self->below 			= NULL;
		self->above				= NULL;

		self->value 			= NULL;
	}

	// Main public methods

	Lu_S_Node lu_s_node__create(Lu_Mem_Table mem_table, lu_size limit_size);

	void lu_s_node__destroy(Lu_Mem_Table mem_table, Lu_S_Node* s_node);

///////////////////////////////////////////////////////////////////////////////
// Lu_S_List

	enum lu_s_list_side_type
	{
		LU_S_LST__FIRST, 
		LU_S_LST__LAST
	};

	struct lu_s_list  
	{
		Lu_Mem 				mem;
		lu_size 			limit_size;
		enum lu_s_list_side_type 	over_limit_remove_side;
		lu_size				level_size;
		lu_size 			count;
		lu_fp_compare 		compare;
		Lu_Mem_Table 		mem_table;

		Lu_S_Node 			first;
		Lu_S_Node 			last;

		Lu_S_Node 			header;
	};

	// Init, create and destroy

	Lu_S_List lu_s_list__create(Lu_Mem, lu_size limit, lu_fp_compare compare, enum lu_s_list_side_type over_limit_remove_side);
	void lu_s_list__destroy(Lu_S_List self);

	// Main public methods

	Lu_S_Node lu_s_list__add(Lu_S_List, lu_p_void value);
	void lu_s_list__debug(Lu_S_List self);