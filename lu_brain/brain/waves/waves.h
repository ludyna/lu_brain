/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Nouns
	typedef struct sig* 						Sig;

	typedef struct w_col* 						W_Col;
	typedef struct w_rec*						W_Rec;

	typedef struct save_wave_create_opts* 		Save_Wave_Create_Opts;
	typedef struct save_wave* 					Save_Wave;

	typedef struct find_wave_create_opts*  		Find_Wave_Create_Opts;
	typedef struct find_wave* 					Find_Wave;

	typedef struct restore_wave_create_opts*	Restore_Wave_Create_Opts;
	typedef struct restore_wave* 				Restore_Wave;

	// typedef here to break cyclic dependency
	typedef struct gate* 						Gate;

///////////////////////////////////////////////////////////////////////////////
// Sig

	struct sig {
		lu_size 	neu_ent;
		lu_value 	p;
	};

///////////////////////////////////////////////////////////////////////////////
// W_Col

	struct w_col
	{
		lu_p_size sigs;
	};

	static W_Col w_col_create(Mem mem, lu_size component_size);

///////////////////////////////////////////////////////////////////////////////
// W_Rec 

	struct w_rec
	{
		lu_size component_size;

		lu_size w_cols_w;
		lu_size w_cols_h;
		W_Col* w_cols;
	};

	static W_Rec w_rec_create(Mem mem, lu_size w, lu_size h, lu_size component_size);

	static void w_rec_sig_send(W_Rec self, lu_size x, lu_size y, lu_size neu_ent);

	static inline void w_rec_w_cols_set(W_Rec self, lu_size x, lu_size y, W_Col w_col) { self->w_cols[y * self->w_cols_w + x] = w_col; }
	static inline W_Col w_rec_w_cols_get(W_Rec self, lu_size x, lu_size y) { return self->w_cols[y * self->w_cols_w + x]; }

///////////////////////////////////////////////////////////////////////////////
// Lu_Wave

	struct lu_wave {
		Gate 					gate;
		Lu_Story 				story;

		Arr						w_recs;
	};

	static void wave_init(Lu_Wave self, Gate gate); 
	static W_Rec wave_rec_get(Lu_Wave self, lu_size id);

///////////////////////////////////////////////////////////////////////////////
// Lu_Wave_Resp

	struct lu_wave_resp {
		
	};

///////////////////////////////////////////////////////////////////////////////
// Save 

	struct save_wave_create_opts
	{
		lu_size 				max_story_size_in_blocks;
	};

	static void save_wave_create_opts_init(Save_Wave_Create_Opts);

	struct lu_save_opts {	
		lu_size 				cont_create_x_radius;
		lu_size 				cont_create_y_radius;
		lu_size 				cont_create_t_radius;
	};

	struct save_wave {
		struct lu_wave 			super;
		struct lu_save_opts 	save_opts;

		// tymchasove zberezhenia linkiv na prev data 
		// vidsutnist danyh oznachaye povtoruvanist danyh
		lu_p_value* 			fill_data;
	};

	struct lu_save_resp {

	};

	typedef struct n_rec* N_Rec; // to break dep loop

	static void save_wave_init(Save_Wave, Lu_Story, Lu_Save_Opts);
	static void save_wave_data_send(Save_Wave self, N_Rec n_rec, lu_p_value data, lu_size block_i);
	static void save_wave_rec_progress(Save_Wave self, N_Rec n_rec, lu_size block_i);
	static void save_wave_block_progress(Save_Wave self, lu_size block_i); 

//////////////////////////7/////////////////////////////////////////////////////
// Find

	struct find_wave_create_opts
	{

	};

	static void find_wave_create_opts_init(Find_Wave_Create_Opts);

	struct lu_find_opts {
		lu_size 				cont_exc_x_radius;
		lu_size 				cont_exc_y_radius;
		lu_size 				cont_exc_t_radius;

		lu_size 				color_exc_x_radius;
		lu_size 				color_exc_y_radius;
		lu_size 				color_exc_val_radius;
	};

	struct find_wave {
		struct lu_wave 			super;
		struct lu_find_opts 	find_opts;
		Lu_Story 				story;
	};

	struct lu_find_resp {

	};

	static void find_wave_init(Find_Wave, Lu_Story, Lu_Find_Opts);

	static void find_wave_process(Find_Wave self);

///////////////////////////////////////////////////////////////////////////////
// Restore API

	struct restore_wave_create_opts
	{

	};

	static void restore_wave_create_opts_init(Restore_Wave_Create_Opts);

	struct lu_restore_opts {

	};

	struct restore_wave {
		struct lu_wave 			super;
		struct lu_restore_opts 	restore_opts;
		Lu_Brain 				brain;
	};

	struct lu_restore_resp {

	};

	static void restore_wave_init(Restore_Wave, Lu_Brain, Lu_Restore_Opts);

	static void restore_wave_process(Restore_Wave self);