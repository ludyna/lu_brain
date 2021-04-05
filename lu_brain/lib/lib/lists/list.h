/**
	Copyright © 2021 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Lu_L_Node

	struct lu_l_node {
		Lu_L_Node 		next;
		Lu_L_Node 		prev;
		lu_p_void 		value;
	};

	// Init, create and destroy

	static inline Lu_L_Node lu_l_node_init(Lu_L_Node self, lu_p_void value)
	{
		self->next 		= NULL;
		self->prev 		= NULL;
		self->value 	= value;

		return self;
	}	

	static inline Lu_L_Node lu_l_node_next(Lu_L_Node self) { return self->next; }
	static inline Lu_L_Node lu_l_node_prev(Lu_L_Node self) { return self->prev; }
	static inline Lu_L_Node lu_l_node_value(Lu_L_Node self) { return self->value; }
	static inline void lu_l_node_value_set(Lu_L_Node self, lu_p_void value) { self->value = value; }


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

		return self;
	}
	Lu_List lu_list_create(Mem); 
	void lu_list_destroy(Lu_List self);

	// Getters / Setters

	static inline lu_size lu_list_count(Lu_List self) { return self->count; }
	static inline Lu_L_Node lu_list_node_first(Lu_List self) { return self->first; }
	static inline lu_p_void lu_list_first(Lu_List self) { if (!self->first) return NULL; return self->first->value; }
	static inline Lu_L_Node lu_list_node_last(Lu_List self) { return self->last; }
	static inline lu_p_void lu_list_last(Lu_List self) { if (!self->last) return NULL; return self->last->value; } 

	// State checks

	static inline lu_bool lu_list_is_empty(Lu_List self) { return self->first == NULL; }

	// Main public methods

	Lu_L_Node lu_list_node_attach(Lu_List, Lu_L_Node);
	Lu_L_Node lu_list_node_append_with_creator(Lu_List self, lu_p_void value, Lu_L_Node (*node_creator)(Lu_List));
	Lu_L_Node lu_list_append(Lu_List, lu_p_void);
	Lu_L_Node lu_list_prepend(Lu_List, lu_p_void);

	Lu_L_Node lu_list_node_detach(Lu_List self, Lu_L_Node node);
	void lu_list_node_remove_with_destroyer(Lu_List self, Lu_L_Node node, void (*node_destroyer)(Lu_List self, Lu_L_Node* l_node));
	void lu_list_node_remove(Lu_List, Lu_L_Node);
	
	static inline void lu_list_node_remove_first(Lu_List self) { lu_list_node_remove(self, self->first); }
	#define lu_list_remove_first lu_list_node_remove_first

	static inline void lu_list_node_remove_last(Lu_List self) { lu_list_node_remove(self, self->last); } 
	#define lu_list_remove_last lu_list_node_remove_last

	Lu_L_Node lu_list_insert_after(Lu_List, lu_p_void, Lu_L_Node);
	Lu_L_Node lu_list_insert_before(Lu_List, lu_p_void, Lu_L_Node);
	Lu_L_Node lu_list_replace(Lu_List, lu_p_void, Lu_L_Node);

	Lu_L_Node lu_list_find_node_forward(Lu_List, lu_fp_is_value);
	Lu_L_Node lu_list_find_node_backward(Lu_List, lu_fp_is_value);

	void lu_list_batch_append(Lu_List, lu_p_void, lu_size);

	void lu_list_node_destroy_all(Lu_List self);		//	Call alloc->node_destroy() on each node.

	void lu_list_node_each_1p(Lu_List self, void (*block)(Lu_List, Lu_L_Node, lu_p_void p1), lu_p_void p1);
	void lu_list_each_1p(Lu_List self, void (*block)(Lu_List, lu_p_void, lu_p_void p1), lu_p_void p1);

	lu_p_void lu_list_find_forward_1p(Lu_List self, lu_bool (*block)(lu_p_void value, lu_p_void p1), lu_p_void p1);

	void lu_list_clear(Lu_List self);

