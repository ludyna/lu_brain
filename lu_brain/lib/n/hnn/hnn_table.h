/**
	Copyright © 2021 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// 
	struct hnn_table_node {
		Hnn_Table_Node prev;
		Hnn_Cell cell;
	};

	static inline Hnn_Table_Node hnn_table_node_create(Mem mem, Hnn_Cell cell, Hnn_Table_Node prev)
	{
		Hnn_Table_Node self = (Hnn_Table_Node) mem_alloc(mem, sizeof(struct hnn_table_node));

		self->prev = prev;
		self->cell = cell;

		return self;
	}

	static void hnn_table_unit_destroy(Hnn_Table_Node self, Mem mem);


///////////////////////////////////////////////////////////////////////////////
// 

	struct hnn_table {
		Mem mem;
		Hnn_Table_Node* units;
		lu_size size_in_cells;
		lu_byte cell_type;
	};
 
///////////////////////////////////////////////////////////////////////////////
// 
	static Hnn_Table hnn_table_create(Mem mem, lu_size size_in_cells, lu_byte cell_type);
	static void hnn_table_destroy(Hnn_Table self);

///////////////////////////////////////////////////////////////////////////////
//   

	static inline lu_size hnn_table_hash_to_index(Hnn_Table self, lu_size hash)
	{
		return hash % self->size_in_cells;
	}

	static inline Hnn_Table_Node hnn_table_cell_add(Hnn_Table self, Hnn_Cell cell, lu_size hash)
	{
		lu_assert(self);
		lu_assert(cell);
		lu_assert(self->size_in_cells > 0);
		lu_assert(self->units);
		lu_assert(self->mem);
		lu_assert(self->cell_type == cell->type);

		lu_size index = hnn_table_hash_to_index(self, hash);
		Hnn_Table_Node node;

		node = hnn_table_node_create(self->mem, cell, self->units[index]);
		self->units[index] = node;

		return node;
	}

	static Hnn_Table_Node hnn_table_node_find(Hnn_Table self, Hnn_Cell cell, lu_size hash);

	static void hnn_table_cell_remove(Hnn_Table self, Hnn_Cell cell, lu_size hash);
 
 	static Hnn_Cell hnn_table_cell_get(Hnn_Table self, lu_size hash, Hnn_Cell top_left);
 	static Hnn_Cell hnn_table_cell_get_2(Hnn_Table self, lu_size hash, Hnn_Cell top_left, Hnn_Cell top_right);
 	static Hnn_Cell hnn_table_cell_get_3(Hnn_Table self, lu_size hash, Hnn_Cell top_left, Hnn_Cell top_right, Hnn_Cell bottom_left);
 	static Hnn_Cell hnn_table_cell_get_4(Hnn_Table self, lu_size hash, Hnn_Cell top_left, Hnn_Cell top_right, Hnn_Cell bottom_left, Hnn_Cell bottom_right);