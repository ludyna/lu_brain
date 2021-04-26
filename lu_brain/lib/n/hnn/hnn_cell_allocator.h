/**
	Copyright © 2021 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// 

	struct hnn_cell_allocator {

		Mem mem;
		Mem_Table 	mt_cell_0;
		Mem_Table 	mt_cell_1;
		Mem_Table	mt_cell_2;
		Mem_Table 	mt_cell_3;
		Mem_Table 	mt_cell_4;

	};

///////////////////////////////////////////////////////////////////////////////
// 

	Hnn_Cell_Allocator hnn_cell_allocator_create(
		Mem mem, 
		lu_size size_in_cell_0,
		lu_size size_in_cell_1,
		lu_size size_in_cell_2,
		lu_size size_in_cell_3, 
		lu_size size_in_cell_4
	);

	void hnn_cell_allocator_destroy(Hnn_Cell_Allocator self);

///////////////////////////////////////////////////////////////////////////////
// Cell Allocators

	Hnn_Cell hnn_cell_alloc_0(Hnn_Cell_Allocator self);
	void hnn_cell_free_0(Hnn_Cell_Allocator self, Hnn_Cell cell);

	Hnn_Cell hnn_cell_alloc_1(Hnn_Cell_Allocator self);
	void hnn_cell_free_1(Hnn_Cell_Allocator self, Hnn_Cell cell);

	Hnn_Cell_2 hnn_cell_2_alloc(Hnn_Cell_Allocator self);
	void hnn_cell_2_free(Hnn_Cell_Allocator self, Hnn_Cell_2 cell);

	Hnn_Cell_3 hnn_cell_3_alloc(Hnn_Cell_Allocator self);
	void hnn_cell_3_free(Hnn_Cell_Allocator self, Hnn_Cell_3 cell);

	Hnn_Cell_4 hnn_cell_4_alloc(Hnn_Cell_Allocator self);
	void hnn_cell_4_free(Hnn_Cell_Allocator self, Hnn_Cell_4 cell);

///////////////////////////////////////////////////////////////////////////////
// Shifts

	static inline lu_size hnn_cell_shift_0(Hnn_Cell_Allocator self, Hnn_Cell cell)
	{
		lu_assert(self);
		lu_assert(cell);

		return mem_table_record_shift(self->mt_cell_0, (lu_p_byte) cell);
	}

	static inline lu_size hnn_cell_shift_1(Hnn_Cell_Allocator self, Hnn_Cell cell)
	{
		lu_assert(self);
		lu_assert(cell);

		return mem_table_record_shift(self->mt_cell_1, (lu_p_byte) cell);
	}

	static inline lu_size hnn_cell_2_shift(Hnn_Cell_Allocator self, Hnn_Cell_2 cell)
	{
		lu_assert(self);
		lu_assert(cell);

		return mem_table_record_shift(self->mt_cell_2, (lu_p_byte) cell);
	}

	static inline lu_size hnn_cell_3_shift(Hnn_Cell_Allocator self, Hnn_Cell_3 cell)
	{
		lu_assert(self);
		lu_assert(cell);

		return mem_table_record_shift(self->mt_cell_3, (lu_p_byte) cell);
	}

	static inline lu_size hnn_cell_4_shift(Hnn_Cell_Allocator self, Hnn_Cell_4 cell)
	{
		lu_assert(self);
		lu_assert(cell);

		return mem_table_record_shift(self->mt_cell_4, (lu_p_byte) cell);
	}