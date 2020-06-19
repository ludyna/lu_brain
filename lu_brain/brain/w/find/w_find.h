/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

//////////////////////////7/////////////////////////////////////////////////////
// Find

	struct w_find_create_opts
	{

	};

	static void w_find_create_opts_init(W_Find_Create_Opts);

	struct lu_find_opts {
		lu_size 				cont_exc_x_radius;
		lu_size 				cont_exc_y_radius;
		lu_size 				cont_exc_t_radius;

		lu_size 				color_exc_x_radius;
		lu_size 				color_exc_y_radius;
		lu_size 				color_exc_val_radius;
	};

	struct w_find {
		struct lu_wave 			super;
		struct lu_find_opts 	find_opts;
		Lu_Story 				story;
	};

	struct lu_find_resp {

	};

	static void w_find_init(W_Find, Lu_Story, Lu_Find_Opts);

	static void w_find_progress(W_Find self);
