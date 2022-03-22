/**
	Copyright © 2022 Oleh Ihorovych Novosad 

	n_tables are always "3d"
*/

///////////////////////////////////////////////////////////////////////////////
// Lu_N_Cell_Base

	struct lu_n_cell_base {
		lu_byte type;
	};
	
	static inline Lu_N_Cell_Base lu_n_cell_base__init(Lu_N_Cell_Base self, lu_byte type)
	{
		lu__assert(self);
		self->type = type;

		return self;
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_N_Cell_VP

	struct lu_n_cell_vp {
		struct lu_n_cell_base super;

		lu_value value; 
		lu_size x;
		lu_size y;
		lu_size z;
	};

	static inline Lu_N_Cell_VP lu_n_cell_vp__init(
		Lu_N_Cell_VP self, 
		lu_byte type, 
		lu_value value,
		lu_size x,
		lu_size y,
		lu_size z
	)
	{
		lu_n_cell_base__init((Lu_N_Cell_Base) self, type);

		self->value = value;
		self->x = x;
		self->y = y;
		self->z = z;
	}

// ///////////////////////////////////////////////////////////////////////////////
// // Lu_N_Cell_1

// 	struct lu_n_cell_1 {
// 		struct lu_n_cell_base super;

// 		Lu_N_Cell_Base top_left;
// 	};

// 	static inline Lu_N_Cell_1 lu_n_cell_1__init(Lu_N_Cell_1 self, lu_byte type)
// 	{
// 		lu_n_cell_base__init((Lu_N_Cell_Base) self, type);

// 		self->top_left = NULL;

// 		return self;
// 	}

// ///////////////////////////////////////////////////////////////////////////////
// // Lu_N_Cell_2

// 	struct lu_n_cell_2 {
// 		struct lu_n_cell_1 super;

// 		Lu_N_Cell_Base top_right;
// 	};

// 	static inline Lu_N_Cell_2 lu_n_cell_2__init(Lu_N_Cell_2 self, lu_byte type)
// 	{
// 		lu_n_cell_1__init((Lu_N_Cell_1) self, type);

// 		self->top_right = NULL;

// 		return self;
// 	}

// ///////////////////////////////////////////////////////////////////////////////
// // Lu_N_Cell_3

// 	struct lu_n_cell_3 {
// 		struct lu_n_cell_2 super;

// 		Lu_N_Cell_Base bottom_left;
// 	};

// 	static inline Lu_N_Cell_3 lu_n_cell_3__init(Lu_N_Cell_3 self, lu_byte type)
// 	{
// 		lu_n_cell_2__init((Lu_N_Cell_2) self, type);

// 		self->bottom_left = NULL;

// 		return self;
// 	}

// ///////////////////////////////////////////////////////////////////////////////
// // Lu_N_Cell_4

// 	struct lu_n_cell_4 {
// 		struct lu_n_cell_3 super;

// 		Lu_N_Cell_Base bottom_right;
// 	}; 

// 	static inline Lu_N_Cell_4 lu_n_cell_4__init(Lu_N_Cell_4 self, lu_byte type)
// 	{
// 		lu_n_cell_3__init((Lu_N_Cell_3) self, type);

// 		self->bottom_right = NULL;

// 		return self;
// 	}

// ///////////////////////////////////////////////////////////////////////////////
// // Macro

// 	#define n_cell__type_get(c) (((Lu_N_Cell_Base)c)->type)
// 	#define n_cell__top_left_get(c) (((Lu_N_Cell_Base)c)->top_left)
// 	#define n_cell__top_right_get(c) (((Lu_N_Cell_2)c)->top_right)
// 	#define n_cell__bottom_left_get(c) (((Lu_N_Cell_3)c)->bottom_left)
// 	#define n_cell__bottom_right_get(c) (((Lu_N_Cell_4)c)->bottom_right)

// ///////////////////////////////////////////////////////////////////////////////
// // Parent Equality

// 	static inline lu_bool n_cell__parent_eq_1(Lu_N_Cell_1 self, Lu_N_Cell_Base top_left)
// 	{
// 		return self->top_left == top_left;
// 	}

// 	static inline lu_bool n_cell__parent_eq_2(Lu_N_Cell_2 self, Lu_N_Cell_Base top_left, Lu_N_Cell_Base top_right)
// 	{
// 		return self->top_right == top_right && n_cell__parent_eq_1((Lu_N_Cell_1) self, top_left);
// 	}

// 	static inline lu_bool n_cell__parent_eq_3(Lu_N_Cell_3 self, Lu_N_Cell_Base top_left, Lu_N_Cell_Base top_right, Lu_N_Cell_Base bottom_left)
// 	{
// 		return self->bottom_left == bottom_left && n_cell__parent_eq_2((Lu_N_Cell_2) self, top_left, top_right);
// 	}

// 	static inline lu_bool n_cell__parent_eq_4(Lu_N_Cell_4 self, Lu_N_Cell_Base top_left, Lu_N_Cell_Base top_right, Lu_N_Cell_Base bottom_left, Lu_N_Cell_Base bottom_right)
// 	{
// 		self->bottom_right == bottom_right && n_cell__parent_eq_3((Lu_N_Cell_3) self, top_left, top_right, bottom_left);
// 	}

// ///////////////////////////////////////////////////////////////////////////////
// // 

// 	struct lu_n_cell_allocator {

// 		Lu_Mem mem;
// 		Lu_Mem_Table 	mt_cell_0;
// 		Lu_Mem_Table 	mt_cell_1;
// 		Lu_Mem_Table	mt_cell_2;
// 		Lu_Mem_Table 	mt_cell_3;
// 		Lu_Mem_Table 	mt_cell_4;

// 	};

// ///////////////////////////////////////////////////////////////////////////////
// // 

// 	Lu_N_Cell_Allocator n_cell_allocator_create(
// 		Lu_Mem mem, 
// 		lu_size size_in_cell_0,
// 		lu_size size_in_cell_1,
// 		lu_size size_in_cell_2,
// 		lu_size size_in_cell_3, 
// 		lu_size size_in_cell_4
// 	);

// 	void n_cell_allocator_destroy(Lu_N_Cell_Allocator self);

// ///////////////////////////////////////////////////////////////////////////////
// // Cell Allocators

// 	Lu_N_Cell_Base n_cell__alloc_0(Lu_N_Cell_Allocator self);
// 	void n_cell__free_0(Lu_N_Cell_Allocator self, Lu_N_Cell_Base cell);

// 	Lu_N_Cell_1 n_cell__alloc_1(Lu_N_Cell_Allocator self);
// 	void n_cell__free_1(Lu_N_Cell_Allocator self, Lu_N_Cell_Base cell);

// 	Lu_N_Cell_2 n_cell__alloc_2(Lu_N_Cell_Allocator self);
// 	void n_cell__free_2(Lu_N_Cell_Allocator self, Lu_N_Cell_2 cell);

// 	Lu_N_Cell_3 n_cell__alloc_3(Lu_N_Cell_Allocator self);
// 	void n_cell__free_3(Lu_N_Cell_Allocator self, Lu_N_Cell_3 cell);

// 	Lu_N_Cell_4 n_cell__alloc_4(Lu_N_Cell_Allocator self);
// 	void n_cell__free_4(Lu_N_Cell_Allocator self, Lu_N_Cell_4 cell);

// ///////////////////////////////////////////////////////////////////////////////
// // Shifts

// 	static inline lu_size n_cell__shift_0(Lu_N_Cell_Allocator self, Lu_N_Cell_Base cell)
// 	{
// 		lu__assert(self);
// 		lu__assert(cell);

// 		return lu_mem_table__record_shift(self->mt_cell_0, (lu_p_byte) cell);
// 	}

// 	static inline lu_size n_cell__shift_1(Lu_N_Cell_Allocator self, Lu_N_Cell_Base cell)
// 	{
// 		lu__assert(self);
// 		lu__assert(cell);

// 		return lu_mem_table__record_shift(self->mt_cell_1, (lu_p_byte) cell);
// 	}

// 	static inline lu_size n_cell__shift_2(Lu_N_Cell_Allocator self, Lu_N_Cell_2 cell)
// 	{
// 		lu__assert(self);
// 		lu__assert(cell);

// 		return lu_mem_table__record_shift(self->mt_cell_2, (lu_p_byte) cell);
// 	}

// 	static inline lu_size n_cell__shift_3(Lu_N_Cell_Allocator self, Lu_N_Cell_3 cell)
// 	{
// 		lu__assert(self);
// 		lu__assert(cell);

// 		return lu_mem_table__record_shift(self->mt_cell_3, (lu_p_byte) cell);
// 	}

// 	static inline lu_size n_cell__shift_4(Lu_N_Cell_Allocator self, Lu_N_Cell_4 cell)
// 	{
// 		lu__assert(self);
// 		lu__assert(cell);

// 		return lu_mem_table__record_shift(self->mt_cell_4, (lu_p_byte) cell);
// 	}

// 	static inline lu_size n_cell__shift(Lu_N_Cell_Allocator self, Lu_N_Cell_Base cell)
// 	{
// 		lu__assert(self);
// 		lu__assert(cell);

// 		switch(cell->type)
// 		{
// 			case LU_N_CELL__0:
// 				return n_cell__shift_0(self, cell);
// 			case LU_N_CELL__1:
// 				return n_cell__shift_1(self, cell);
// 			case LU_N_CELL__2:
// 				return n_cell__shift_2(self, (Lu_N_Cell_2) cell);
// 			case LU_N_CELL__3:
// 				return n_cell__shift_3(self, (Lu_N_Cell_3) cell);
// 			case LU_N_CELL__4:
// 				return n_cell__shift_4(self, (Lu_N_Cell_4) cell);			
// 			default:
// 				lu__assert(false);
// 		}

// 		lu__assert(false);

// 		return 0;
// 	}

// ///////////////////////////////////////////////////////////////////////////////
// // Lu_N_Column_Node

// 	struct lu_n_column_node {
// 		Lu_N_Column_Node prev;
// 		Lu_N_Cell_Base cell;
// 	};

// 	static inline Lu_N_Column_Node lu_n_column_node__create(Lu_Mem mem, Lu_N_Cell_Base cell, Lu_N_Column_Node prev)
// 	{
// 		Lu_N_Column_Node self = (Lu_N_Column_Node) lu_mem__alloc(mem, sizeof(struct lu_n_column_node));

// 		self->prev = prev;
// 		self->cell = cell;

// 		return self;
// 	}

// 	static void lu_n_column_node__destroy(Lu_N_Column_Node self, Lu_Mem mem);

///////////////////////////////////////////////////////////////////////////////
// Lu_N_Column 


	// // tut bude po inshomu, tut mozhna optymizuvaty
	// // bo naspavdi, ce bude w x h cells
	// // i kozhna vertycalna cell ne bude peretynatys z inshymy, vidpovidno
	// // Lu_N_Column_Node* units; bude okreymyy dlia kozhnoho vertykalna cell
 
	// struct lu_n_column {
	// 	Lu_Mem mem;
	// 	Lu_N_Column_Node* units; // unit might contain more than one node
	// 	lu_size size_in_cells;
	// 	lu_byte cell_type;
	// };

	// //
	// // Create & destroy
	// // 

	// static Lu_N_Column lu_n_column__create(Lu_Mem mem, lu_size size_in_cells, lu_byte cell_type);
	// static void lu_n_column__destroy(Lu_N_Column self);

	// //
	// // Main methods
	// //

	// static inline lu_size lu_n_column__hash_to_index(Lu_N_Column self, lu_size hash)
	// {
	// 	return hash % self->size_in_cells;
	// }

	// static inline Lu_N_Column_Node lu_n_column__cell_add(Lu_N_Column self, lu_size hash, Lu_N_Cell_Base new_cell)
	// {
	// 	lu__debug_assert(self);
	// 	lu__debug_assert(new_cell);
	// 	lu__debug_assert(self->size_in_cells > 0);
	// 	lu__debug_assert(self->units);
	// 	lu__debug_assert(self->mem);
	// 	lu__debug_assert(self->cell_type == new_cell->type);

	// 	lu_size index = lu_n_column__hash_to_index(self, hash);

	// 	Lu_N_Column_Node node = lu_n_column_node__create(self->mem, new_cell, self->units[index]);
	// 	self->units[index] = node;

	// 	return node;
	// }

	// static Lu_N_Column_Node lu_n_column__node_find(Lu_N_Column self, Lu_N_Cell_Base cell, lu_size hash);

	// static void lu_n_column__cell_remove(Lu_N_Column self, lu_size hash, Lu_N_Cell_Base cell);
 
 // 	static Lu_N_Cell_Base lu_n_column__cell_get_1(Lu_N_Column self, lu_size hash, Lu_N_Cell_Base top_left);
 // 	static Lu_N_Cell_Base lu_n_column__cell_get_2(
 // 		Lu_N_Column self, 
 // 		lu_size hash, 
 // 		Lu_N_Cell_Base top_left, 
 // 		Lu_N_Cell_Base top_right
 // 	);
 // 	static Lu_N_Cell_Base lu_n_column__cell_get_3(
 // 		Lu_N_Column self, 
 // 		lu_size hash, 
 // 		Lu_N_Cell_Base top_left, 
 // 		Lu_N_Cell_Base top_right, 
 // 		Lu_N_Cell_Base bottom_left
 // 	);
 // 	static Lu_N_Cell_Base lu_n_column__cell_get_4(
 // 		Lu_N_Column self, 
 // 		lu_size hash, 
 // 		Lu_N_Cell_Base top_left, 
 // 		Lu_N_Cell_Base top_right, 
 // 		Lu_N_Cell_Base bottom_left, 
 // 		Lu_N_Cell_Base bottom_right
 // 	);

	// //
	// // Utility
	// //  

	// static void lu_n_column__print_distribution(Lu_N_Column self);

///////////////////////////////////////////////////////////////////////////////
// Lu_N_Table_Comp
//

	struct lu_n_table_comp {
		Lu_Mem mem;
		lu_size w;
		lu_size h;
		lu_size d;

		// w x h x d, empty by default
		struct lu_n_cell_vp* cells;
	};

	static Lu_N_Table_Comp lu_n_table_comp__create(
		Lu_Config config, 
		Lu_Comp_Calc comp_calc, 
		lu_size width, 
		lu_size height, 
		lu_size depth 
	);

	static void lu_n_table_comp__destroy(Lu_N_Table_Comp self);

	static inline Lu_N_Cell_VP lu_n_table_comp__get_cell(Lu_N_Table_Comp self, lu_size x, lu_size y, lu_size z)
	{
		return &self->cells[z * self->w * self->h + y * self->w + x];
	}


///////////////////////////////////////////////////////////////////////////////
// Lu_N_Cell
//

	struct lu_n_cell {
		lu_size prev_ix;
		// lu_size id; nema smyslu davaty id, yaksho my mozhemu vziaty &lu_n_cell - &cells i bude id

		// index to back links strings (zero limited) in for prev (child) n_table located in this n_table
		lu_size links_ix; 
	};

///////////////////////////////////////////////////////////////////////////////
// Lu_N_String

	#define LU_N_STRING__END LU_SIZE__MAX

	struct lu_n_string {
		lu_size pos;
		lu_p_size p;
	};

	static inline void lu_n_string__init(Lu_N_String self, lu_p_size p)
	{
		lu__debug_assert(self);
		lu__debug_assert(p);

		self->pos = 0;
		self->p = p;
	}

	static inline void lu_n_string__reset(Lu_N_String self)
	{
		lu__debug_assert(self);
		self->p = NULL;
		self->pos = 0;
	}

	static inline lu_size lu_n_string__get(Lu_N_String self)
	{
		// I know it can be rewritten with: return p[pos++]
		lu_size v = self->p[self->pos];
		++self->pos;
		return v;
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_N_Free_Links
//
	struct lu_n_free_links {
		// free (deleted) strings
		// Ce maye buty okrema structura
		lu_p_size *free_1;
		lu_p_size *free_2;
		lu_p_size *free_4;
	};

///////////////////////////////////////////////////////////////////////////////
// Lu_N_Links
// Mozhe buty dlia vsih n_table, chy krashche zrobyty dlia kozhnoho n_column?
// Dlia kozhnoho n_column krashche - maksymalna rozparalezaciya

	struct lu_n_links {
		lu_p_size p;

		//struct lu_n_free_links free_links;
	};

	static Lu_N_Links lu_n_links__init(Lu_Mem mem, lu_size size);
	static void lu_n_links__deinit(Lu_N_Links self, Lu_Mem mem);

	static inline lu_p_size lu_n_links__alloc(Lu_N_Links self, lu_size size)
	{

	}

///////////////////////////////////////////////////////////////////////////////
// Lu_N_Column
// 

	////
	// Having separete columns helps with parallelization in the future, but takes a little bit more memory.
	// my mozhemo vykorystovuvaty columns, ale treba
	// prosto znaty v yakomu poriadku zberihayemo string, sho prosto
	// size parne, 0-size/2 cells, size/2-size - free cells
	struct lu_n_column {
		lu_size size;
		struct lu_n_cell* cells;

		// links size is proportional to cells size
		struct lu_n_links links;
	};

	static Lu_N_Column lu_n_column__init(Lu_Mem mem, lu_size size);
	static void lu_n_column__deinit(Lu_N_Column self, Lu_Mem mem);

///////////////////////////////////////////////////////////////////////////////
// Lu_N_Table

	struct lu_n_table {
		Lu_Mem mem;

		lu_size w;
		lu_size h;

		lu_byte cell_type; // nema smyslu davaty cell_type v komirku koly to vse povtoruyetsia

		struct lu_n_column* columns;
	};

	static Lu_N_Table lu_n_table__create(Lu_Mem mem, lu_size w, lu_size h, lu_byte cell_type);
	static void lu_n_table__destroy(Lu_N_Table self);