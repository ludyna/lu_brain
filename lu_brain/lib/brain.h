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
	};	

	static lu_size lu_brain__rec_attach(Lu_Brain self, Lu_Rec rec);
	static void lu_brain__rec_detach(Lu_Brain self, Lu_Rec rec);


