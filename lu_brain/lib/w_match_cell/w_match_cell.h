/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/


///////////////////////////////////////////////////////////////////////////////
//  Lu_W_Addr

	#define LU_W_CELL_IX__SIZE 40

	union lu_w_addr {
		struct {
			lu_size cell_ix: LU_W_CELL_IX__SIZE;
			lu_size layer_ix: LU_N_LAYER_IX__SIZE;
			lu_size area_ix: LU_N_AREA_IX__SIZE;
		};
		lu_size value;
	};

	// NULL addr
	extern const union lu_w_addr LU_W_ADDR__NULL; 

	static inline lu_bool lu_w_addr__is_blank(Lu_W_Addr self)
	{
		return (self->value == 0);
	}

	static inline lu_bool lu_w_addr__is_present(Lu_W_Addr self)
	{
		return (self->value != 0);
	}

	static inline void lu_w_addr__set_to_null(Lu_W_Addr self)
	{
		self->value = 0;
	}

	static inline lu_bool lu_w_addr__is_eq(Lu_W_Addr self, Lu_W_Addr b)
	{
		return self->value == b->value;
	}

	static inline void lu_w_addr__print(Lu_W_Addr self)
	{
		lu__debug("%d:%d:%d", self->area_ix, self->layer_ix, self->cell_ix);
	}


///////////////////////////////////////////////////////////////////////////////
//  Lu_W_Match_Addr

	////
	// Using as an index in Lu_W_Match_Cell_Mem so reallocation will not break pointer
	union lu_w_match_addr {
		lu_size value;
	};


///////////////////////////////////////////////////////////////////////////////
//  Lu_W_Match_Cell 

	struct lu_w_match_cell {
		lu_value sig;
		lu_size wave_id;
	};	


///////////////////////////////////////////////////////////////////////////////
//  Lu_W_Match_Cell_Mem

	struct lu_w_match_cell_mem {

	};