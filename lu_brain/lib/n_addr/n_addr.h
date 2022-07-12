/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Lu_N_Addr

	#define LU_N_CELL_IX__SIZE 16
	#define LU_N_COLUMN_IX__SIZE 24
	#define LU_N_LAYER_IX__SIZE 16
	#define LU_N_AREA_IX__SIZE 8

	union lu_n_addr {
		struct {
			lu_size cell_ix : LU_N_CELL_IX__SIZE;
			lu_size column_ix: LU_N_COLUMN_IX__SIZE;
			lu_size layer_ix: LU_N_LAYER_IX__SIZE;
			lu_size area_ix: LU_N_AREA_IX__SIZE;
		};
		lu_size value;
	};

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