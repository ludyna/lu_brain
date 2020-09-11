/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/


///////////////////////////////////////////////////////////////////////////////
// Lu_Rec_Config

	struct lu_rec_config {
		lu_size 		width;
		lu_size 		height;
		lu_size 		depth;

		lu_size 		max_blocks_size;
		lu_size 		hold_blocks_size;

		lu_value 		v_min;
		lu_value 		v_max;
		lu_size			v_neu_size;
		lu_size 		v_nsc;

		lu_size 		p_neu_size;
		lu_size 		p_nsc;  	// nei sim count	

	};

///////////////////////////////////////////////////////////////////////////////
// Lu_Rec_Config predefined 

	enum lu_rc_predefined_type {
		LU_RC_MONOCHROME1_IMAGE = 0,
		LU_RC_MONOCHROME8_IMAGE,
		LU_RC_RBG8_IMAGE,
		LU_RC_RBG16_IMAGE, 
		LU_RC_RBG32_IMAGE,
		LU_RC_TEST1,
		LU_RC_END 				
	};

	extern struct lu_rec_config lu_g_rc_predefined[LU_RC_END];

///////////////////////////////////////////////////////////////////////////////
// Lu_Rec

	struct lu_rec {
		Lu_Brain 					brain;
		lu_size 					id;

		struct lu_rec_config 	config;	
	};

	static void lu_rec_attach_to_brain(Lu_Rec self, Lu_Brain brain);
	static void lu_rec_detach_from_brain(Lu_Rec self);
