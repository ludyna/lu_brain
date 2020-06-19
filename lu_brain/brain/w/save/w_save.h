/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Save 

	struct w_save_create_opts
	{
		lu_size 				blocks_max_size;
	};

	static void save_wave_create_opts_init(W_Save_Create_Opts);

	struct lu_save_opts {	
		lu_size 				cont_create_x_radius;
		lu_size 				cont_create_y_radius;
		lu_size 				cont_create_t_radius;

		lu_value 				contrast;
		lu_value 				color_influence;
	};

	struct w_save {
		struct lu_wave 			super;
		struct lu_save_opts 	save_opts;

		// tymchasove zberezhenia linkiv na prev data 
		// vidsutnist danyh oznachaye povtoruvanist danyh
		lu_p_value* 			fill_data;
	}; 
	
	struct lu_save_resp {

	};

	static void w_save_init(W_Save, Lu_Story, Lu_Save_Opts);
	static void w_save_data_send(W_Save self, Lu_Save_Opts opts, S_Rec s_rec, lu_p_value data, lu_size block_i);
	static void w_save_rec_progress(W_Save self, S_Rec s_rec, lu_size block_i);
	static void w_save_block_progress(W_Save self, lu_size block_i); 
