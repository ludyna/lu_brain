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

		lu_size 					width;
		lu_size 					height;

		struct lu_rec_opts_config 	config;	
	};

	static inline lu_value rec_data_get(Lu_Rec rec, lu_p_value data, lu_size x, lu_size y, lu_size z)
	{
		return data[z * rec->width * rec->height + y * rec->width + x];
	}

	static inline void rec_data_set(Lu_Rec rec, lu_p_value data, lu_size x, lu_size y, lu_size z, lu_value value)
	{
		data[z * rec->width * rec->height + y * rec->width + x] = value;
	}