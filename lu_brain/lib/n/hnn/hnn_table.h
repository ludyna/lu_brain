/**
	Copyright © 2021 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// 
	struct hnn_table_unit {
		Hnn_Table_Unit next;
		Hnn_Cell cell;
	};

	static inline Hnn_Table_Unit hnn_table_unit_init(Hnn_Table_Unit self)
	{
		lu_assert(self);

		self->next = NULL;
		self->cell = NULL;

		return self;
	}

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

	// static Hnn_Table_Unit hnn_table_get_1(Hnn_Table self, lu_size sh_1);
	// static Hnn_Table_Unit hnn_table_get_2(Hnn_Table self, lu_size shift_1, lu_size shift_2);
	// static Hnn_Table_Unit hnn_table_get_3(Hnn_Table self, lu_size sh_1, lu_size sh_2, lu_size sh_3);
	// static Hnn_Table_Unit hnn_table_get_4(Hnn_Table self, lu_size sh_1, lu_size sh_2, lu_size sh_3, lu_size sh_4);

	// 	static Hnn_Table_Unit hnn_table_get_1(Hnn_Table self, lu_size sh_1);
	// static Hnn_Table_Unit hnn_table_get_2(Hnn_Table self, lu_size shift_1, lu_size shift_2);
	// static Hnn_Table_Unit hnn_table_get_3(Hnn_Table self, lu_size sh_1, lu_size sh_2, lu_size sh_3);
	// static Hnn_Table_Unit hnn_table_get_4(Hnn_Table self, lu_size sh_1, lu_size sh_2, lu_size sh_3, lu_size sh_4);

