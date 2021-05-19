/**
	Copyright © 2021 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Hnn_Table_Node

	struct hnn_table_node {
		Hnn_Table_Node prev;
		Hnn_Cell_0 cell;
	};

	static inline Hnn_Table_Node hnn_table_node_create(Lu_Mem mem, Hnn_Cell_0 cell, Hnn_Table_Node prev)
	{
		Hnn_Table_Node self = (Hnn_Table_Node) mem_alloc(mem, sizeof(struct hnn_table_node));

		self->prev = prev;
		self->cell = cell;

		return self;
	}

	static void hnn_table_unit_destroy(Hnn_Table_Node self, Lu_Mem mem);


///////////////////////////////////////////////////////////////////////////////
// Hnn_Table 

	struct hnn_table {
		Lu_Mem mem;
		Hnn_Table_Node* units; // unit might contain more than one cell 
		lu_size size_in_cells;
		lu_byte cell_type;
	};
 
///////////////////////////////////////////////////////////////////////////////
// Hnn_Table Create And Destroy

	static Hnn_Table hnn_table_create(Lu_Mem mem, lu_size size_in_cells, lu_byte cell_type);
	static void hnn_table_destroy(Hnn_Table self);

///////////////////////////////////////////////////////////////////////////////
// Hnn_Table Main Methods

	static inline lu_size hnn_table_hash_to_index(Hnn_Table self, lu_size hash)
	{
		return hash % self->size_in_cells;
	}

	static inline Hnn_Table_Node hnn_table_cell_add(Hnn_Table self, lu_size hash, Hnn_Cell_0 new_cell)
	{
		lu_assert(self);
		lu_assert(new_cell);
		lu_assert(self->size_in_cells > 0);
		lu_assert(self->units);
		lu_assert(self->mem);
		lu_assert(self->cell_type == new_cell->type);

		lu_size index = hnn_table_hash_to_index(self, hash);

		Hnn_Table_Node node = hnn_table_node_create(self->mem, new_cell, self->units[index]);
		self->units[index] = node;

		return node;
	}

	static Hnn_Table_Node hnn_table_node_find(Hnn_Table self, Hnn_Cell_0 cell, lu_size hash);

	static void hnn_table_cell_remove(Hnn_Table self, lu_size hash, Hnn_Cell_0 cell);
 
 	static Hnn_Cell_0 hnn_table_cell_get_1(Hnn_Table self, lu_size hash, Hnn_Cell_0 top_left);
 	static Hnn_Cell_0 hnn_table_cell_get_2(Hnn_Table self, lu_size hash, Hnn_Cell_0 top_left, Hnn_Cell_0 top_right);
 	static Hnn_Cell_0 hnn_table_cell_get_3(Hnn_Table self, lu_size hash, Hnn_Cell_0 top_left, Hnn_Cell_0 top_right, Hnn_Cell_0 bottom_left);
 	static Hnn_Cell_0 hnn_table_cell_get_4(Hnn_Table self, lu_size hash, Hnn_Cell_0 top_left, Hnn_Cell_0 top_right, Hnn_Cell_0 bottom_left, Hnn_Cell_0 bottom_right);

///////////////////////////////////////////////////////////////////////////////
// Hnn_Table Utility    

	static void hnn_table_print_distribution(Hnn_Table self);