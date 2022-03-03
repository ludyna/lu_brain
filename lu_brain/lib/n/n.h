/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Lu_N_Cell_0

	struct lu_n_cell_0 {
		lu_byte type;
	};
	
	static inline Lu_N_Cell_0 n_cell_0__init(Lu_N_Cell_0 self, lu_byte type)
	{
		lu__assert(self);
		self->type = type;

		return self;
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_N_Cell_V

	struct lu_n_cell_v {
		struct lu_n_cell_0 super;

		lu_value value; 
		lu_size x;
		lu_size y;
		lu_size z;
	};

	static inline Lu_N_Cell_V n_cell_value__init(
		Lu_N_Cell_V self, 
		lu_byte type, 
		lu_value value,
		lu_size x,
		lu_size y,
		lu_size z
	)
	{
		n_cell_0__init((Lu_N_Cell_0) self, type);

		self->value = value;
		self->x = x;
		self->y = y;
		self->z = z;
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_N_Cell_1

	struct lu_n_cell_1 {
		struct lu_n_cell_0 super;

		Lu_N_Cell_0 top_left;
	};

	static inline Lu_N_Cell_1 n_cell_1__init(Lu_N_Cell_1 self, lu_byte type)
	{
		n_cell_0__init((Lu_N_Cell_0) self, type);

		self->top_left = NULL;

		return self;
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_N_Cell_2

	struct lu_n_cell_2 {
		struct lu_n_cell_1 super;

		Lu_N_Cell_0 top_right;
	};

	static inline Lu_N_Cell_2 n_cell_2__init(Lu_N_Cell_2 self, lu_byte type)
	{
		n_cell_1__init((Lu_N_Cell_1) self, type);

		self->top_right = NULL;

		return self;
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_N_Cell_3

	struct lu_n_cell_3 {
		struct lu_n_cell_2 super;

		Lu_N_Cell_0 bottom_left;
	};

	static inline Lu_N_Cell_3 n_cell_3__init(Lu_N_Cell_3 self, lu_byte type)
	{
		n_cell_2__init((Lu_N_Cell_2) self, type);

		self->bottom_left = NULL;

		return self;
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_N_Cell_4

	struct lu_n_cell_4 {
		struct lu_n_cell_3 super;

		Lu_N_Cell_0 bottom_right;
	}; 

	static inline Lu_N_Cell_4 n_cell_4__init(Lu_N_Cell_4 self, lu_byte type)
	{
		n_cell_3__init((Lu_N_Cell_3) self, type);

		self->bottom_right = NULL;

		return self;
	}

///////////////////////////////////////////////////////////////////////////////
// Macro

	#define n_cell__type_get(c) (((Lu_N_Cell_0)c)->type)
	#define n_cell__top_left_get(c) (((Lu_N_Cell_0)c)->top_left)
	#define n_cell__top_right_get(c) (((Lu_N_Cell_2)c)->top_right)
	#define n_cell__bottom_left_get(c) (((Lu_N_Cell_3)c)->bottom_left)
	#define n_cell__bottom_right_get(c) (((Lu_N_Cell_4)c)->bottom_right)

///////////////////////////////////////////////////////////////////////////////
// Parent Equality

	static inline lu_bool n_cell__parent_eq_1(Lu_N_Cell_1 self, Lu_N_Cell_0 top_left)
	{
		return self->top_left == top_left;
	}

	static inline lu_bool n_cell__parent_eq_2(Lu_N_Cell_2 self, Lu_N_Cell_0 top_left, Lu_N_Cell_0 top_right)
	{
		return self->top_right == top_right && n_cell__parent_eq_1((Lu_N_Cell_1) self, top_left);
	}

	static inline lu_bool n_cell__parent_eq_3(Lu_N_Cell_3 self, Lu_N_Cell_0 top_left, Lu_N_Cell_0 top_right, Lu_N_Cell_0 bottom_left)
	{
		return self->bottom_left == bottom_left && n_cell__parent_eq_2((Lu_N_Cell_2) self, top_left, top_right);
	}

	static inline lu_bool n_cell__parent_eq_4(Lu_N_Cell_4 self, Lu_N_Cell_0 top_left, Lu_N_Cell_0 top_right, Lu_N_Cell_0 bottom_left, Lu_N_Cell_0 bottom_right)
	{
		self->bottom_right == bottom_right && n_cell__parent_eq_3((Lu_N_Cell_3) self, top_left, top_right, bottom_left);
	}

///////////////////////////////////////////////////////////////////////////////
// 

	struct lu_n_cell_allocator {

		Lu_Mem mem;
		Lu_Mem_Table 	mt_cell_0;
		Lu_Mem_Table 	mt_cell_1;
		Lu_Mem_Table	mt_cell_2;
		Lu_Mem_Table 	mt_cell_3;
		Lu_Mem_Table 	mt_cell_4;

	};

///////////////////////////////////////////////////////////////////////////////
// 

	Lu_N_Cell_Allocator n_cell_allocator_create(
		Lu_Mem mem, 
		lu_size size_in_cell_0,
		lu_size size_in_cell_1,
		lu_size size_in_cell_2,
		lu_size size_in_cell_3, 
		lu_size size_in_cell_4
	);

	void n_cell_allocator_destroy(Lu_N_Cell_Allocator self);

///////////////////////////////////////////////////////////////////////////////
// Cell Allocators

	Lu_N_Cell_0 n_cell__alloc_0(Lu_N_Cell_Allocator self);
	void n_cell__free_0(Lu_N_Cell_Allocator self, Lu_N_Cell_0 cell);

	Lu_N_Cell_1 n_cell__alloc_1(Lu_N_Cell_Allocator self);
	void n_cell__free_1(Lu_N_Cell_Allocator self, Lu_N_Cell_0 cell);

	Lu_N_Cell_2 n_cell__alloc_2(Lu_N_Cell_Allocator self);
	void n_cell__free_2(Lu_N_Cell_Allocator self, Lu_N_Cell_2 cell);

	Lu_N_Cell_3 n_cell__alloc_3(Lu_N_Cell_Allocator self);
	void n_cell__free_3(Lu_N_Cell_Allocator self, Lu_N_Cell_3 cell);

	Lu_N_Cell_4 n_cell__alloc_4(Lu_N_Cell_Allocator self);
	void n_cell__free_4(Lu_N_Cell_Allocator self, Lu_N_Cell_4 cell);

///////////////////////////////////////////////////////////////////////////////
// Shifts

	static inline lu_size n_cell__shift_0(Lu_N_Cell_Allocator self, Lu_N_Cell_0 cell)
	{
		lu__assert(self);
		lu__assert(cell);

		return lu_mem_table__record_shift(self->mt_cell_0, (lu_p_byte) cell);
	}

	static inline lu_size n_cell__shift_1(Lu_N_Cell_Allocator self, Lu_N_Cell_0 cell)
	{
		lu__assert(self);
		lu__assert(cell);

		return lu_mem_table__record_shift(self->mt_cell_1, (lu_p_byte) cell);
	}

	static inline lu_size n_cell__shift_2(Lu_N_Cell_Allocator self, Lu_N_Cell_2 cell)
	{
		lu__assert(self);
		lu__assert(cell);

		return lu_mem_table__record_shift(self->mt_cell_2, (lu_p_byte) cell);
	}

	static inline lu_size n_cell__shift_3(Lu_N_Cell_Allocator self, Lu_N_Cell_3 cell)
	{
		lu__assert(self);
		lu__assert(cell);

		return lu_mem_table__record_shift(self->mt_cell_3, (lu_p_byte) cell);
	}

	static inline lu_size n_cell__shift_4(Lu_N_Cell_Allocator self, Lu_N_Cell_4 cell)
	{
		lu__assert(self);
		lu__assert(cell);

		return lu_mem_table__record_shift(self->mt_cell_4, (lu_p_byte) cell);
	}

	static inline lu_size n_cell__shift(Lu_N_Cell_Allocator self, Lu_N_Cell_0 cell)
	{
		lu__assert(self);
		lu__assert(cell);

		switch(cell->type)
		{
			case N_CT__0:
				return n_cell__shift_0(self, cell);
			case N_CT__1:
				return n_cell__shift_1(self, cell);
			case N_CT__2:
				return n_cell__shift_2(self, (Lu_N_Cell_2) cell);
			case N_CT__3:
				return n_cell__shift_3(self, (Lu_N_Cell_3) cell);
			case N_CT__4:
				return n_cell__shift_4(self, (Lu_N_Cell_4) cell);			
			default:
				lu__assert(false);
		}

		lu__assert(false);

		return 0;
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_N_Comp_Table

	struct lu_n_comp_table {
		Lu_Mem mem;
		lu_size w;
		lu_size h;
		lu_size d;

		// w x h x d, empty by default
		struct lu_n_cell_v* cells;
	};

	static Lu_N_Comp_Table lu_n_comp_table__create(Lu_Config config, lu_size width, lu_size height, lu_size depth);
	static void lu_n_comp_table__destroy(Lu_N_Comp_Table self);


///////////////////////////////////////////////////////////////////////////////
// Lu_N_Table_Node

	struct lu_n_table_node {
		Lu_N_Table_Node prev;
		Lu_N_Cell_0 cell;
	};

	static inline Lu_N_Table_Node n_table_node__create(Lu_Mem mem, Lu_N_Cell_0 cell, Lu_N_Table_Node prev)
	{
		Lu_N_Table_Node self = (Lu_N_Table_Node) lu_mem__alloc(mem, sizeof(struct lu_n_table_node));

		self->prev = prev;
		self->cell = cell;

		return self;
	}

	static void n_table_node__destroy(Lu_N_Table_Node self, Lu_Mem mem);

///////////////////////////////////////////////////////////////////////////////
// Lu_N_Table 


	// tut bude po inshomu, tut mozhna optymizuvaty
	// bo naspavdi, ce bude w x h cells
	// i kozhna vertycalna cell ne bude peretynatys z inshymy, vidpovidno
	// Lu_N_Table_Node* units; bude okreymyy dlia kozhnoho vertykalna cell
 
	struct lu_n_table {
		Lu_Mem mem;
		Lu_N_Table_Node* units; // unit might contain more than one node
		lu_size size_in_cells;
		lu_byte cell_type;
	};

	//
	// Create & destroy
	// 

	static Lu_N_Table n_table__create(Lu_Mem mem, lu_size size_in_cells, lu_byte cell_type);
	static void n_table__destroy(Lu_N_Table self);

	//
	// Main methods
	//

	static inline lu_size n_table__hash_to_index(Lu_N_Table self, lu_size hash)
	{
		return hash % self->size_in_cells;
	}

	static inline Lu_N_Table_Node n_table__cell_add(Lu_N_Table self, lu_size hash, Lu_N_Cell_0 new_cell)
	{
		lu__assert(self);
		lu__assert(new_cell);
		lu__assert(self->size_in_cells > 0);
		lu__assert(self->units);
		lu__assert(self->mem);
		lu__assert(self->cell_type == new_cell->type);

		lu_size index = n_table__hash_to_index(self, hash);

		Lu_N_Table_Node node = n_table_node__create(self->mem, new_cell, self->units[index]);
		self->units[index] = node;

		return node;
	}

	static Lu_N_Table_Node n_table__node_find(Lu_N_Table self, Lu_N_Cell_0 cell, lu_size hash);

	static void n_table__cell_remove(Lu_N_Table self, lu_size hash, Lu_N_Cell_0 cell);
 
 	static Lu_N_Cell_0 n_table__cell_get_1(Lu_N_Table self, lu_size hash, Lu_N_Cell_0 top_left);
 	static Lu_N_Cell_0 n_table__cell_get_2(Lu_N_Table self, lu_size hash, Lu_N_Cell_0 top_left, Lu_N_Cell_0 top_right);
 	static Lu_N_Cell_0 n_table__cell_get_3(Lu_N_Table self, lu_size hash, Lu_N_Cell_0 top_left, Lu_N_Cell_0 top_right, Lu_N_Cell_0 bottom_left);
 	static Lu_N_Cell_0 n_table__cell_get_4(Lu_N_Table self, lu_size hash, Lu_N_Cell_0 top_left, Lu_N_Cell_0 top_right, Lu_N_Cell_0 bottom_left, Lu_N_Cell_0 bottom_right);

	//
	// Utility
	//  

	static void n_table__print_distribution(Lu_N_Table self);