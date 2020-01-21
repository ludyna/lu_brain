/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/
#ifndef _LU_LISTS_H
#define _LU_LISTS_H

#include "basic/basic.h"

///////////////////////////////////////////////////////////////////////////////
// Nouns

	typedef struct l_node* 			L_Node;
	typedef struct ln_alloc_fast* 	Ln_Alloc_Fast;
	typedef struct list* 			List;

	typedef struct s_node* 			S_Node;
	typedef struct s_list* 			S_List;

///////////////////////////////////////////////////////////////////////////////
// LnAlloc

	struct l_node {
		L_Node 		next;
		L_Node 		prev;
		lu_p_void 	value;
	};

	typedef struct ln_alloc* LnAlloc;

	struct ln_alloc {
		L_Node (*node_create)(LnAlloc, lu_p_void);
		void (*node_destroy)(LnAlloc, L_Node*);
		void (*destroy)(LnAlloc*, L_Node);
	};

	// Init, create and destroy

	static inline void l_node_init(L_Node self, lu_p_void value)
	{
		self->next 	= NULL;
		self->prev 	= NULL;
		self->value = value;
	}	

	void ln_alloc_init(LnAlloc self);
	LnAlloc ln_alloc_create();
	void ln_alloc_destroy(LnAlloc* self, L_Node first);

///////////////////////////////////////////////////////////////////////////////
// Ln_Alloc_Fast

	struct ln_alloc_fast {
		struct ln_alloc 	super;
		Ph_Sisa 			sis_alloc;
	};

	// Init, create and destroy

	Ln_Alloc_Fast ln_alloc_fast_create(Ph_Sisa, lu_size size);
	void ln_alloc_fast_destroy(Ln_Alloc_Fast*, L_Node first);

	// Main public methods

	void ln_alloc_fast_resize(Ln_Alloc_Fast self, lu_size new_size);

///////////////////////////////////////////////////////////////////////////////
// List

	struct list {
		L_Node 	first;
		L_Node 	last;
		lu_size count;
		LnAlloc alloc;
		bool 	delete_alloc;
	};

	// Init, create and destroy
	List list_init(List, LnAlloc);
	List list_create(LnAlloc);
	void list_destroy(List*);

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
		//List 		values;
	};

	// Init, create and destroy

	static inline void s_node_init(S_Node self, LnAlloc ln_alloc)
	{
		list_init(&self->values, ln_alloc);

		self->next 		= NULL;
		self->prev		= NULL;
		self->below 	= NULL;
		self->above		= NULL;

		self->value 	= NULL;
	}

	// Main public methods

	S_Node s_node_create(Ph_Sisa s_alloc, LnAlloc ln_alloc);

	void s_node_destroy(Ph_Sisa s_alloc, S_Node* s_node);

///////////////////////////////////////////////////////////////////////////////
// S_List

	typedef enum 
	{
		S_LIST_FIRST, 
		S_LIST_LAST
	} s_list_side;

	struct s_list  
	{
		lu_size 		limit_size;
		s_list_side 	over_limit_remove_side;
		lu_size			level_size;
		lu_size 		count;
		lu_fp_compare 	compare;
		Ph_Sisa 		s_alloc;
		Ln_Alloc_Fast		ln_alloc;


		S_Node 			first;
		S_Node 			last;

		S_Node 			header;
	};

	// Init, create and destroy

	S_List s_list_create(lu_size limit, lu_fp_compare compare, s_list_side over_limit_remove_side);
	void s_list_destroy(S_List*);

	// Main public methods

	S_Node s_list_add(S_List, lu_p_void value);
	void s_list_debug(S_List self);

#endif // _LU_LISTS_H
