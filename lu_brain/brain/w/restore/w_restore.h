/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Restore

	struct lu_wave_resp {
		
	};

	struct w_restore_create_opts
	{

	};

	static void w_restore_create_opts_init(W_Restore_Create_Opts);

	struct lu_restore_opts {

	};

	struct w_restore {
		struct lu_wave 			super;
		struct lu_restore_opts 	restore_opts;
		Lu_Brain 				brain;
	};

	struct lu_restore_resp {

	};

	static void w_restore_init(W_Restore, Lu_Brain, Lu_Restore_Opts);

	static void w_restore_process(W_Restore self);