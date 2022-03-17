/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Lu_Rec_Config predefined 

	extern struct lu_rec_config lu_g_rc_predefined[LU_REC__END];

///////////////////////////////////////////////////////////////////////////////
// Lu_Rec

	struct lu_rec {
		Lu_Brain 					brain;
		lu_size 					id;

		lu_size  					width;
		lu_size  					height;
		lu_size  					depth;

		struct lu_rec_config 		config;	
	};

	static void lu_rec__destroy(Lu_Rec self, Lu_Mem mem);