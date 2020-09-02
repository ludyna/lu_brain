/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/
#ifndef _LU_LISTS_H
#define _LU_LISTS_H

///////////////////////////////////////////////////////////////////////////////
// Nouns

	typedef struct lu_l_node* 		Lu_L_Node;
	typedef struct lu_list* 		Lu_List;
	typedef struct lu_table_list* 	Lu_Table_List;

	typedef struct lu_s_node* 		Lu_S_Node;
	typedef struct lu_s_list* 		Lu_S_List;

///////////////////////////////////////////////////////////////////////////////
// Lu_L_Node

	struct lu_l_node {
		Lu_L_Node 		next;
		Lu_L_Node 		prev;
		lu_p_void 		value;
	};

	// Init, create and destroy

	static inline void lu_l_node_init(Lu_L_Node self, lu_p_void value)
	{
		self->next 		= NULL;
		self->prev 		= NULL;
		self->value 	= value;
	}	

///////////////////////////////////////////////////////////////////////////////
// Lu_List

	struct lu_list {
		Lu_L_Node 			first;
		Lu_L_Node 			last;
		lu_size 			count;
		Mem 				mem;
	};

	// Init, create and destroy
	static inline Lu_List lu_list_init(Lu_List self, Mem mem)
	{
		self->first 		= NULL;
		self->last 			= NULL;
		self->count 		= 0;
		self->mem 			= mem;
	}

	Lu_List lu_list_create(Mem); 
	void lu_list_destroy(Lu_List self);

	// Getters / Setters

	static inline lu_size lu_list_count(Lu_List self) { return self->count; }
	static inline Lu_L_Node lu_list_first(Lu_List self) { return self->first; }
	static inline Lu_L_Node lu_list_last(Lu_List self) { return self->last; }

	// Main public methods

	Lu_L_Node lu_list_attach(Lu_List, Lu_L_Node);
	Lu_L_Node lu_list_append(Lu_List, lu_p_void);
	Lu_L_Node lu_list_prepend(Lu_List, lu_p_void);

	Lu_L_Node lu_list_detach(Lu_List self, Lu_L_Node node);
	void lu_list_remove(Lu_List, Lu_L_Node);
	static inline void lu_list_remove_first(Lu_List self) { lu_list_remove(self, self->first); }
	static inline void lu_list_remove_last(Lu_List self) { lu_list_remove(self, self->last); }

	Lu_L_Node lu_list_insert_after(Lu_List, lu_p_void, Lu_L_Node);
	Lu_L_Node lu_list_insert_before(Lu_List, lu_p_void, Lu_L_Node);
	Lu_L_Node lu_list_replace(Lu_List, lu_p_void, Lu_L_Node);

	Lu_L_Node lu_list_find_forward(Lu_List, lu_fp_is_value);
	Lu_L_Node lu_list_find_backward(Lu_List, lu_fp_is_value);

	void lu_list_batch_append(Lu_List, lu_p_void, lu_size);

	void lu_list_destroy_all(Lu_List self);		//	Call alloc->node_destroy() on each node.

	void lu_list_each(Lu_List self, void (*block)(Lu_List, Lu_L_Node, lu_p_void p1), lu_p_void p1);

///////////////////////////////////////////////////////////////////////////////
// Lu_Table_List

	struct lu_table_list {
		struct lu_list 	super;

		Mem_Table 		mem_table;
		lu_size 		max_size;
	};

	Lu_Table_List lu_table_list_create(Mem, lu_size);
	void lu_table_list_destroy(Lu_Table_List self);


///////////////////////////////////////////////////////////////////////////////
// Lu_S_Node

	struct lu_s_node
	{
		struct lu_list 	values;

		Lu_S_Node 		next;
		Lu_S_Node 		prev;
		Lu_S_Node 		below;
		Lu_S_Node 		above;

		lu_p_void 		value;
	};

	// Init, create and destroy

	static inline void s_node_init(Lu_S_Node self, Mem_Table mem_table, lu_size limit_size)
	{
		lu_list_init(&self->values, mem_table, limit_size);

		self->next 				= NULL;
		self->prev				= NULL;
		self->below 			= NULL;
		self->above				= NULL;

		self->value 			= NULL;
	}

	// Main public methods

	Lu_S_Node s_node_create(Mem_Table mem_table, lu_size limit_size);

	void s_node_destroy(Mem_Table mem_table, Lu_S_Node* s_node);

///////////////////////////////////////////////////////////////////////////////
// Lu_S_List

	typedef enum 
	{
		S_LIST_FIRST, 
		S_LIST_LAST
	} s_list_side;

	struct lu_s_list  
	{
		lu_size 			limit_size;
		s_list_side 		over_limit_remove_side;
		lu_size				level_size;
		lu_size 			count;
		lu_fp_compare 		compare;
		Mem_Table 			mem_table;

		Lu_S_Node 				first;
		Lu_S_Node 				last;

		Lu_S_Node 				header;
	};

	// Init, create and destroy

	Lu_S_List s_list_create(Mem, lu_size limit, lu_fp_compare compare, s_list_side over_limit_remove_side);

	// Main public methods

	Lu_S_Node s_list_add(Lu_S_List, lu_p_void value);
	void s_list_debug(Lu_S_List self);

#endif // _LU_LISTS_H
