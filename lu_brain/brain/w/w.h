/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/
 
#include "basic/w_basic.h"
#include "save/w_save.h"
#include "find/w_find.h"
#include "restore/w_restore.h"




///////////////////////////////////////////////////////////////////////////////
// 

	struct w_sig {
		N_Neu 					neu;
		lu_value 				p;
	};

	// asociyuyetsia do s_neu, a ne n_neu
	struct w_neu {
		W_Sig 					sigs; 	// velykyy masyv, de sigs[n_neu_1->sid] vidpovidaye za w_sig dlia n_neu_1
										// kozhne vykorystania n_neu miniaye misciamy n_neu->sid z vyshchym n_neu->sid
										// takym chynom my mozhemo vyddaliaty neu z sid sho perevyshchuye pevne znachennia (starinnia neuroniv)

		W_Sig 					w;		// peremozhec
	};

	struct w_layer {
		lu_size 				w;
		lu_size 				h;

		W_Neu* 					neus;  // asociyuyutsia z s_neu
	};

	struct lu_wave {
		Gate 					gate;
		S_Mem 					s_mem; 
		N_Mem 					n_mem;
		Lu_Story 				story;

		struct w_layer 			la_1;
		struct w_layer 			la_2;


	};

	static Lu_Wave wave_init(Lu_Wave self, Gate gate, S_Mem s_mem, N_Mem n_mem);

///////////////////////////////////////////////////////////////////////////////
// Save 

	struct w_save_create_opts
	{
		lu_size 				blocks_max_size; // ce ne maye vidnoshenia do save , ce maye vidnochenia do rec i s_rec
	};

	static void save_wave_create_opts_init(W_Save_Create_Opts);

	struct lu_save_opts {	
		lu_value 				contrast;
		lu_bool 				ignore_color;
	};

	struct w_save {
		struct lu_wave 			super;
		struct lu_save_opts 	opts;


	}; 
	
	static W_Save w_save_create(Gate gate, S_Mem s_mem, N_Mem n_mem, W_Save_Create_Opts opts);
	static void w_save_init_and_reset(W_Save, Lu_Story, Lu_Save_Opts);
	static void w_save_process(W_Save self, S_Rec s_rec, Data data, lu_size block_i);

	struct lu_save_resp {
		lu_size test;
	};

//////////////////////////7/////////////////////////////////////////////////////
// Find

	struct w_find_create_opts
	{

	};

	static void w_find_create_opts_init(W_Find_Create_Opts);

	struct lu_find_opts {
		lu_value 				color_influence; 	// ce maye znachenia pry find i save i restore 
		lu_bool 				auto_save;		 	// auto save data if its new (zavzhdy 1 dlia save)
		lu_value 				fire_breakpoint;	// [0,1] ce maye znachenia pry find i save i restore	
		lu_value 				contrast;			// ce maye znachenia pry save i find

		// wave ye wave i ne maye znachenia zvidky my yiyi puskayemo
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