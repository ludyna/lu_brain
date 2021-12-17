/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Lu_Brain_Config predefined 

	extern struct lu_brain_config lu_g_bc_predefined[LU_BRAIN_CONFIG_END];

///////////////////////////////////////////////////////////////////////////////
// Lu_Brain 

	struct lu_brain {
		// config copy
		struct lu_brain_config config;

		// Mems
		Lu_Mem brain_mem;
		Lu_Mem s_mem;
		Lu_Mem n_mem;
		Lu_Mem lu_w;

		Lu_Arr	recs; // receivers

		Lu_S s;
		Lu_N n;		
	};	

	static lu_size lu_brain__rec_attach(Lu_Brain self, Lu_Rec rec);
	static void lu_brain__rec_detach(Lu_Brain self, Lu_Rec rec);

	