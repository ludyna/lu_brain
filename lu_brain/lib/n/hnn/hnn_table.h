/**
	Copyright © 2021 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// 
	struct hnn_table_unit {
		Hnn_Table_Unit prev;
		Hnn_Cell cell;
	};

	static inline Hnn_Table_Unit hnn_table_unit_create(Mem mem, Hnn_Cell cell, Hnn_Table_Unit prev)
	{
		Hnn_Table_Unit self = (Hnn_Table_Unit) mem_alloc(mem, sizeof(struct hnn_table_unit));

		self->prev = prev;
		self->cell = cell;

		return self;
	}

	static void hnn_table_unit_destroy(Hnn_Table_Unit self, Mem mem);


///////////////////////////////////////////////////////////////////////////////
// 

	struct hnn_table {
		Mem mem;
		Hnn_Table_Unit* units;
		lu_size size_in_cells;
	};
 
///////////////////////////////////////////////////////////////////////////////
// 
	static Hnn_Table hnn_table_create(Mem mem, lu_size size_in_cells);
	static void hnn_table_destroy(Hnn_Table self);

///////////////////////////////////////////////////////////////////////////////
//  

	static inline Hnn_Table_Unit hnn_table_cell_add(Hnn_Table self, Hnn_Cell cell, lu_size hash)
	{
		lu_assert(self);
		lu_assert(cell);
		lu_assert(self->size_in_cells > 0);
		lu_assert(self->units);
		lu_assert(self->mem);

		lu_size index = hash % self->size_in_cells;
		Hnn_Table_Unit unit;

		unit = hnn_table_unit_create(self->mem, cell, self->units[index]);
		self->units[index] = unit;

		return unit;
	}

	static void hnn_table_cell_remove(Hnn_Table self, Hnn_Cell cell, lu_size hash);
