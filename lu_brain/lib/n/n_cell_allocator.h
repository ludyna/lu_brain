/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/

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

	N_Cell_Allocator n_cell_allocator_create(
		Lu_Mem mem, 
		lu_size size_in_cell_0,
		lu_size size_in_cell_1,
		lu_size size_in_cell_2,
		lu_size size_in_cell_3, 
		lu_size size_in_cell_4
	);

	void n_cell_allocator_destroy(N_Cell_Allocator self);

///////////////////////////////////////////////////////////////////////////////
// Cell Allocators

	N_Cell_0 n_cell__alloc_0(N_Cell_Allocator self);
	void n_cell__free_0(N_Cell_Allocator self, N_Cell_0 cell);

	N_Cell_1 n_cell__alloc_1(N_Cell_Allocator self);
	void n_cell__free_1(N_Cell_Allocator self, N_Cell_0 cell);

	N_Cell_2 n_cell__alloc_2(N_Cell_Allocator self);
	void n_cell__free_2(N_Cell_Allocator self, N_Cell_2 cell);

	N_Cell_3 n_cell__alloc_3(N_Cell_Allocator self);
	void n_cell__free_3(N_Cell_Allocator self, N_Cell_3 cell);

	N_Cell_4 n_cell__alloc_4(N_Cell_Allocator self);
	void n_cell__free_4(N_Cell_Allocator self, N_Cell_4 cell);

///////////////////////////////////////////////////////////////////////////////
// Shifts

	static inline lu_size n_cell__shift_0(N_Cell_Allocator self, N_Cell_0 cell)
	{
		lu__assert(self);
		lu__assert(cell);

		return lu_mem_table__record_shift(self->mt_cell_0, (lu_p_byte) cell);
	}

	static inline lu_size n_cell__shift_1(N_Cell_Allocator self, N_Cell_0 cell)
	{
		lu__assert(self);
		lu__assert(cell);

		return lu_mem_table__record_shift(self->mt_cell_1, (lu_p_byte) cell);
	}

	static inline lu_size n_cell__shift_2(N_Cell_Allocator self, N_Cell_2 cell)
	{
		lu__assert(self);
		lu__assert(cell);

		return lu_mem_table__record_shift(self->mt_cell_2, (lu_p_byte) cell);
	}

	static inline lu_size n_cell__shift_3(N_Cell_Allocator self, N_Cell_3 cell)
	{
		lu__assert(self);
		lu__assert(cell);

		return lu_mem_table__record_shift(self->mt_cell_3, (lu_p_byte) cell);
	}

	static inline lu_size n_cell__shift_4(N_Cell_Allocator self, N_Cell_4 cell)
	{
		lu__assert(self);
		lu__assert(cell);

		return lu_mem_table__record_shift(self->mt_cell_4, (lu_p_byte) cell);
	}

	static inline lu_size n_cell__shift(N_Cell_Allocator self, N_Cell_0 cell)
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
				return n_cell__shift_2(self, (N_Cell_2) cell);
			case N_CT__3:
				return n_cell__shift_3(self, (N_Cell_3) cell);
			case N_CT__4:
				return n_cell__shift_4(self, (N_Cell_4) cell);			
			default:
				lu__assert(false);
		}

		lu__assert(false);

		return 0;
	}