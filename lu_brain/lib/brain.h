/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Lu_Config predefined 

	extern struct lu_config lu_g_bc_predefined[LU_CONFIG__END];

	static void lu_config__set_defaults(Lu_Config self);

///////////////////////////////////////////////////////////////////////////////
// Lu_Brain 

	struct lu_brain {
		struct lu_config config;

		Lu_Arr	recs; // receivers

		Lu_S s;	

		Lu_W_Manager w_manager;

		struct lu_la_column la_column;
	};	

	//
	// Get
	// 

	static inline Lu_S lu_brain__get_s(Lu_Brain self)
	{
		return self->s;
	}

	//
	// Methods
	//

	static lu_size lu_brain__rec_attach(Lu_Brain self, Lu_Rec rec);
	static void lu_brain__rec_detach(Lu_Brain self, Lu_Rec rec);


