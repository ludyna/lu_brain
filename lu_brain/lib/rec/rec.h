/**
	Copyright © 2021 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Lu_Rec_Config predefined 

	extern struct lu_rec_config lu_g_rc_predefined[LU_RC_END];

///////////////////////////////////////////////////////////////////////////////
// Lu_Rec

	struct lu_rec {
		Lu_Brain 					brain;
		lu_size 					id;

		struct lu_rec_config 	config;	
	};
