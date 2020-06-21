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
		lu_value 				color_influence; 	// ce maye znachenia pry find
		lu_bool 				auto_save;		 	// auto save data if its new
		lu_size					winner_count;
		lu_value 				fire_breakpoint;	// [0,1]			
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
