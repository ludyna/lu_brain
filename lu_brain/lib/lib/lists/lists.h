/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/
#ifndef _LU_LISTS_H
#define _LU_LISTS_H

///////////////////////////////////////////////////////////////////////////////
// Nouns

	typedef struct l_node* 			L_Node;
	typedef struct list* 			List;

	typedef struct s_node* 			S_Node;
	typedef struct s_list* 			S_List;

///////////////////////////////////////////////////////////////////////////////
// L_Node

	struct l_node {
		L_Node 		next;
		L_Node 		prev;
		lu_p_void 	value;
	};

	// Init, create and destroy

	static inline void l_node_init(L_Node self, lu_p_void value)
	{
		self->next 	= NULL;
		self->prev 	= NULL;
		self->value = value;
	}	

///////////////////////////////////////////////////////////////////////////////
// List

	struct list {
		L_Node 			first;
		L_Node 			last;
		lu_size 		count;
		Mem_Table 		mem_table;
		lu_size 		max_size;
	};

	// Init, create and destroy
	static inline List list_init(List self, Mem_Table mem_table, lu_size max_size)
	{
		self->first 		= NULL;
		self->last 			= NULL;
		self->count 		= 0;
		self->mem_table 	= mem_table;
		self->max_size 		= max_size;
	}

	List list_create(Mem, lu_size);

	// Getters / Setters

	static inline lu_size list_count(List self) { return self->count; }
	static inline L_Node list_first(List self) { return self->first; }
	static inline L_Node list_last(List self) { return self->last; }

	// Main public methods

	L_Node list_attach(List, L_Node);
	L_Node list_append(List, lu_p_void);
	L_Node list_prepend(List, lu_p_void);

	L_Node list_detach(List self, L_Node node);
	void list_remove(List, L_Node);
	static inline void list_remove_first(List self) { list_remove(self, self->first); }
	static inline void list_remove_last(List self) { list_remove(self, self->last); }

	L_Node list_insert_after(List, lu_p_void, L_Node);
	L_Node list_insert_before(List, lu_p_void, L_Node);
	L_Node list_replace(List, lu_p_void, L_Node);

	L_Node list_find_forward(List, lu_fp_is_value);
	L_Node list_find_backward(List, lu_fp_is_value);

	void list_batch_append(List, lu_p_void, lu_size);

	/*
		Call alloc->node_destroy() on each node.
	*/
	void list_destroy_all(List self);

	void list_each(List self, void (*block)(List, L_Node, lu_p_void p1), lu_p_void p1);

///////////////////////////////////////////////////////////////////////////////
// S_Node

	struct s_node
	{
		struct list values;

		S_Node 		next;
		S_Node 		prev;
		S_Node 		below;
		S_Node 		above;

		lu_p_void 	value;
	};

	// Init, create and destroy

	static inline void s_node_init(S_Node self, Mem_Table mem_table, lu_size limit_size)
	{
		list_init(&self->values, mem_table, limit_size);

		self->next 				= NULL;
		self->prev				= NULL;
		self->below 			= NULL;
		self->above				= NULL;

		self->value 			= NULL;
	}

	// Main public methods

	S_Node s_node_create(Mem_Table mem_table, lu_size limit_size);

	void s_node_destroy(Mem_Table mem_table, S_Node* s_node);

///////////////////////////////////////////////////////////////////////////////
// S_List

	typedef enum 
	{
		S_LIST_FIRST, 
		S_LIST_LAST
	} s_list_side;

	struct s_list  
	{
		lu_size 			limit_size;
		s_list_side 		over_limit_remove_side;
		lu_size				level_size;
		lu_size 			count;
		lu_fp_compare 		compare;
		Mem_Table 			mem_table;

		S_Node 				first;
		S_Node 				last;

		S_Node 				header;
	};

	// Init, create and destroy

	S_List s_list_create(Mem, lu_size limit, lu_fp_compare compare, s_list_side over_limit_remove_side);

	// Main public methods

	S_Node s_list_add(S_List, lu_p_void value);
	void s_list_debug(S_List self);

#endif // _LU_LISTS_H
