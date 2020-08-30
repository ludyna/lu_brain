/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Lu_Rec_Opts

	struct lu_rec_opts {
		Lu_Brain_Opts  				brain_opts;

		lu_size 					width;
		lu_size 					height;

		struct lu_rec_opts_config 	config;	
	};

///////////////////////////////////////////////////////////////////////////////
// Lu_Rec_Opts_Config

	static Lu_Rec_Opts_Config lu_rec_opts_config_validate(Lu_Rec_Opts_Config self);

///////////////////////////////////////////////////////////////////////////////
// Lu_Rec

	struct lu_rec {
		Lu_Brain 					brain;
		lu_size 					id;

		struct lu_rec_opts_config 	config;	
	};
