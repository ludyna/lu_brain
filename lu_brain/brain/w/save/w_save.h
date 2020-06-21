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
		lu_value 				contrast;
		lu_bool 				ignore_color;
	};

	struct w_save {
		struct lu_wave 			super;
		struct lu_save_opts 	save_opts;


	}; 
	
	static W_Save w_save_create(Gate gate, S_Mem s_mem, N_Mem n_mem, W_Save_Create_Opts opts);
	static void w_save_init_and_reset(W_Save, Lu_Story, Lu_Save_Opts);
	static void w_save(W_Save self, Lu_Save_Opts opts, S_Rec s_rec, Data data, lu_size block_i);



	struct lu_save_resp {

	};
