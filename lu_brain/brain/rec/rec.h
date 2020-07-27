/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Lu_Rec_Opts

	struct lu_rec_opts {
		Lu_Brain_Opts  	brain_opts;

		lu_size 		width;
		lu_size 		height;
		lu_size			hold_blocks_size;
		lu_size 		max_blocks_size;
		
		lu_size 		depth;

		lu_value 		v_min;
		lu_value 		v_max;
		lu_size			v_neu_size;
		lu_size 		v_nsc;

		lu_size 		p_neu_size;
		lu_size 		p_nsc;  	// nei sim count		
	};

///////////////////////////////////////////////////////////////////////////////
// Lu_Rec

	struct lu_rec {
		Lu_Brain 		brain;
		lu_size 		id;

		lu_size 		width;
		lu_size 		height;
		lu_size 		hold_blocks_size;
		lu_size 		max_blocks_size;

		lu_size 		depth;

		lu_value 		v_min;
		lu_value 		v_max;
		lu_size			v_neu_size;
		lu_size 		v_nsc;

		lu_size 		p_neu_size;
		lu_size 		p_nsc;  	// nei sim count
	};

	static inline lu_value rec_data_get(Lu_Rec rec, lu_p_value data, lu_size x, lu_size y, lu_size z)
	{
		return data[z * rec->width * rec->height + y * rec->width + x];
	}

	static inline void rec_data_set(Lu_Rec rec, lu_p_value data, lu_size x, lu_size y, lu_size z, lu_value value)
	{
		data[z * rec->width * rec->height + y * rec->width + x] = value;
	}