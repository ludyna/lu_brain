/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Lu_Brain_Config predefined 

	extern struct lu_brain_config lu_g_bc_predefined[LU_BC_END];

///////////////////////////////////////////////////////////////////////////////
// Lu_Brain 

	struct lu_brain {
		Mem 					brain_mem;

		struct lu_brain_config 	config;

		Arr						recs;		// receivers

		S_Mem 					s_mem;
		N_Mem 					n_mem;		
	};	

	static void lu_brain_rec_attach(Lu_Brain self, Lu_Rec rec);
	static void lu_brain_rec_detach(Lu_Brain self, Lu_Rec rec);