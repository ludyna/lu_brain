/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// N_Table_Node

	struct lu_n_table_node {
		N_Table_Node prev;
		N_Cell_0 cell;
	};

	static inline N_Table_Node n_table_node__create(Lu_Mem mem, N_Cell_0 cell, N_Table_Node prev)
	{
		N_Table_Node self = (N_Table_Node) lu_mem__alloc(mem, sizeof(struct lu_n_table_node));

		self->prev = prev;
		self->cell = cell;

		return self;
	}

	static void n_table_node__destroy(N_Table_Node self, Lu_Mem mem);

///////////////////////////////////////////////////////////////////////////////
// N_Table 

	struct lu_n_table {
		Lu_Mem mem;
		N_Table_Node* units; // unit might contain more than one node
		lu_size size_in_cells;
		lu_byte cell_type;
	};
 
///////////////////////////////////////////////////////////////////////////////
// N_Table Create And Destroy

	static N_Table n_table__create(Lu_Mem mem, lu_size size_in_cells, lu_byte cell_type);
	static void n_table__destroy(N_Table self);

///////////////////////////////////////////////////////////////////////////////
// N_Table Main Methods

	static inline lu_size n_table__hash_to_index(N_Table self, lu_size hash)
	{
		return hash % self->size_in_cells;
	}

	static inline N_Table_Node n_table__cell_add(N_Table self, lu_size hash, N_Cell_0 new_cell)
	{
		lu__assert(self);
		lu__assert(new_cell);
		lu__assert(self->size_in_cells > 0);
		lu__assert(self->units);
		lu__assert(self->mem);
		lu__assert(self->cell_type == new_cell->type);

		lu_size index = n_table__hash_to_index(self, hash);

		N_Table_Node node = n_table_node__create(self->mem, new_cell, self->units[index]);
		self->units[index] = node;

		return node;
	}

	static N_Table_Node n_table__node_find(N_Table self, N_Cell_0 cell, lu_size hash);

	static void n_table__cell_remove(N_Table self, lu_size hash, N_Cell_0 cell);
 
 	static N_Cell_0 n_table__cell_get_1(N_Table self, lu_size hash, N_Cell_0 top_left);
 	static N_Cell_0 n_table__cell_get_2(N_Table self, lu_size hash, N_Cell_0 top_left, N_Cell_0 top_right);
 	static N_Cell_0 n_table__cell_get_3(N_Table self, lu_size hash, N_Cell_0 top_left, N_Cell_0 top_right, N_Cell_0 bottom_left);
 	static N_Cell_0 n_table__cell_get_4(N_Table self, lu_size hash, N_Cell_0 top_left, N_Cell_0 top_right, N_Cell_0 bottom_left, N_Cell_0 bottom_right);

///////////////////////////////////////////////////////////////////////////////
// N_Table Utility    

	static void n_table__print_distribution(N_Table self);