/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Lu_N_Addr


	//
	// Global variables
	//

	extern union lu_n_addr LU_N_ADDR__NULL; 
	extern const union lu_n_addr LU_N_ADDR__INACTIVE;

	//
	// Constructors / Destructors
	//

	static inline Lu_N_Addr lu_n_addr__init(
		Lu_N_Addr self, 
		lu_size cell_ix, 
		lu_size column_ix, 
		lu_size layer_ix, 
		lu_size area_ix
	)
	{
		lu__debug_assert(self);

		self->cell_ix = cell_ix;
		self->column_ix = column_ix;
		self->layer_ix = layer_ix;
		self->area_ix = area_ix;

		return self;
	}

	//
	// Get
	//

	static inline lu_size lu_n_addr__get_cell_ix(Lu_N_Addr self)
	{
		lu__assert(self);
		return self->cell_ix;
	}

	//
	// Is 
	//

	static inline lu_bool lu_n_addr__is_blank(Lu_N_Addr self)
	{
		return (self->value == 0);
	}

	static inline lu_bool lu_n_addr__is_present(Lu_N_Addr self)
	{
		return (self->value != 0);
	}

	static inline lu_bool lu_n_addr__is_eq(Lu_N_Addr self, Lu_N_Addr b)
	{
		return self->value == b->value;
	}

	////
	// space equal ignores cell_ix
	static inline lu_bool lu_n_addr__is_space_eq(union lu_n_addr a, union lu_n_addr b)
	{
		a.cell_ix = 0;
		b.cell_ix = 0;

		return a.value == b.value;
	}

	static inline lu_bool lu_n_addr__is_space_not_eq(union lu_n_addr a, union lu_n_addr b)
	{
		a.cell_ix = 0;
		b.cell_ix = 0;

		return a.value != b.value;
	}

	//
	// Methods
	//

	static inline void lu_n_addr__print(Lu_N_Addr self)
	{
		lu__debug("CELL: %ld (AREA: %ld LAYER: %ld)", self->cell_ix, self->area_ix, self->layer_ix);
	}

	static inline void lu_n_addr__reset(Lu_N_Addr self)
	{
		self->value = 0;
	}