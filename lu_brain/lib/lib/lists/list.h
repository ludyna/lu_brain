/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/

	void lu_list__node_destroy_all(Lu_List self);		

///////////////////////////////////////////////////////////////////////////////
// Lu_L_Node

	struct lu_l_node {
		Lu_L_Node 		next;
		Lu_L_Node 		prev;
		lu_p_void 		value;
	};

	// Init, create and destroy

	static inline Lu_L_Node lu_l_node__init(Lu_L_Node self, lu_p_void value)
	{
		self->next 		= NULL;
		self->prev 		= NULL;
		self->value 	= value;

		return self;
	}	

	static inline Lu_L_Node lu_l_node__next(Lu_L_Node self) { return self->next; }
	static inline Lu_L_Node lu_l_node__prev(Lu_L_Node self) { return self->prev; }
	static inline lu_p_void lu_l_node__value(Lu_L_Node self) { return self->value; }
	static inline void lu_l_node__value_set(Lu_L_Node self, lu_p_void value) { self->value = value; }


///////////////////////////////////////////////////////////////////////////////
// Lu_List

	struct lu_list {
		Lu_L_Node 			first;
		Lu_L_Node 			last;
		lu_size 			count;
		Lu_Mem 				mem;
	};

	// Init, create and destroy

	static inline Lu_List lu_list__init(Lu_List self, Lu_Mem mem)
	{
		self->first 		= NULL;
		self->last 			= NULL;
		self->count 		= 0;
		self->mem 			= mem;

		return self;
	}

	static inline void lu_list__deinit(Lu_List self)
	{
		lu__assert(self);
		lu_list__node_destroy_all(self);
		lu_list__init(self, NULL);
	}

	Lu_List lu_list__create(Lu_Mem); 
	void lu_list__destroy(Lu_List self);

	// Getters / Setters

	static inline lu_size lu_list__count(Lu_List self) { return self->count; }
	static inline Lu_L_Node lu_list__first_node(Lu_List self) { return self->first; }
	static inline lu_p_void lu_list__first_value(Lu_List self) { if (!self->first) return NULL; return self->first->value; }
	static inline Lu_L_Node lu_list__last_node(Lu_List self) { return self->last; }
	static inline lu_p_void lu_list__last_value(Lu_List self) { if (!self->last) return NULL; return self->last->value; } 
	
	static inline lu_bool lu_list__is_initialized(Lu_List self)
	{
		lu__debug_assert(self);

		return !self->mem;
	}

	static inline lu_bool lu_list__is_empty(Lu_List self) { return self->first == NULL; }
	static inline lu_bool lu_list__is_present(Lu_List self) { return self->first != NULL; }

	// Main public methods

	Lu_L_Node lu_list__node_append_with_creator(Lu_List self, lu_p_void value, Lu_L_Node (*node_creator)(Lu_List));
	Lu_L_Node lu_list__node_prepend_with_creator(Lu_List self, lu_p_void value, Lu_L_Node (*node_creator)(Lu_List));
	Lu_L_Node lu_list__append(Lu_List, lu_p_void);
	Lu_L_Node lu_list__prepend(Lu_List, lu_p_void);

	Lu_L_Node lu_list__node_detach(Lu_List self, Lu_L_Node node);
	void lu_list__node_remove_with_destroyer(Lu_List self, Lu_L_Node node, void (*node_destroyer)(Lu_List self, Lu_L_Node* l_node));
	void lu_list__node_remove(Lu_List, Lu_L_Node);
	
	static inline void lu_list__node_remove_first(Lu_List self) { lu_list__node_remove(self, self->first); }
	#define lu_list__remove_first lu_list__node_remove_first

	static inline void lu_list__node_remove_last(Lu_List self) { lu_list__node_remove(self, self->last); } 
	#define lu_list__remove_last lu_list__node_remove_last

	Lu_L_Node lu_list__insert_after(Lu_List, lu_p_void, Lu_L_Node);
	Lu_L_Node lu_list__insert_before(Lu_List, lu_p_void, Lu_L_Node);
	Lu_L_Node lu_list__replace(Lu_List, lu_p_void, Lu_L_Node);

	Lu_L_Node lu_list__find_node_forward(Lu_List, lu_fp_is_value);
	Lu_L_Node lu_list__find_node_backward(Lu_List, lu_fp_is_value);

	void lu_list__batch_append(Lu_List, lu_p_void, lu_size);

	void lu_list__node_destroy_all(Lu_List self);		//	Call alloc->node_destroy() on each node.

	void lu_list__node_each_1p(Lu_List self, void (*block)(Lu_List, Lu_L_Node, lu_p_void p1), lu_p_void p1);
	void lu_list__each_1p(Lu_List self, void (*block)(Lu_List, lu_p_void, lu_p_void p1), lu_p_void p1);

	lu_p_void lu_list__find_forward(Lu_List self, lu_p_void p1);
	lu_p_void lu_list__find_forward_1p(Lu_List self, lu_bool (*block)(lu_p_void value, lu_p_void p1), lu_p_void p1);

	void lu_list__clear(Lu_List self);

	lu_p_void lu_list__pop_first_value(Lu_List self);
	lu_p_void lu_list__pop_last_value(Lu_List self);

