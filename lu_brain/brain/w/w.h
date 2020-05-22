/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// W_Sig

	struct w_sig {
		lu_size 	n_ent;
		lu_value 	p;
	};

///////////////////////////////////////////////////////////////////////////////
// W_Col

	struct w_col
	{
		W_Rec 				w_rec; 		// vlasnyk

		enum n_col_type 	type;

		lu_size 			x;
		lu_size 			y; 

		lu_p_value 			curr_vals;
		lu_p_value 			p_vals; 	// for t
		lu_p_size 			prev_neus;
	};

	static W_Col w_col_create(Mem mem, W_Rec w_rec, S_Col s_col);

///////////////////////////////////////////////////////////////////////////////
// W_Rec 

	struct w_rec
	{
		lu_size 			component_size;

		lu_size 			w_cols_w;
		lu_size 			w_cols_h;
		W_Col* 				w_cols;

		Arr					pers;
		Arr 				pers_active; // or t-neus?
	};

	static W_Rec w_rec_create(Mem mem, S_Rec s_rec);
	static void w_rec_debug_print(W_Rec self);

	static void w_rec_sig_send(W_Rec self, lu_size x, lu_size y, lu_size n_ent);

	///////////////////////////
	// Accessors

	static inline void w_rec_w_cols_set(W_Rec self, lu_size x, lu_size y, W_Col w_col) { self->w_cols[y * self->w_cols_w + x] = w_col; }
	static inline W_Col w_rec_w_cols_get(W_Rec self, lu_size x, lu_size y) { return self->w_cols[y * self->w_cols_w + x]; }

///////////////////////////////////////////////////////////////////////////////
// Lu_Wave

	struct lu_wave {
		Gate 				gate;
		Lu_Story 			story;
		S_Mem 				s_mem; 

		Arr 				w_recs;
	};

	static void wave_init(Lu_Wave self, Gate gate); 

	static inline W_Rec wave_w_rec_get(Lu_Wave self, lu_size id) { return (W_Rec) arr_get(self->w_recs, id); }

///////////////////////////////////////////////////////////////////////////////
// Lu_Wave_Resp

	struct lu_wave_resp {
		
	};

///////////////////////////////////////////////////////////////////////////////
// Save 

	struct w_save_create_opts
	{
		lu_size 				max_blocks_size;
	};

	static void save_wave_create_opts_init(W_Save_Create_Opts);

	struct lu_save_opts {	
		lu_size 				cont_create_x_radius;
		lu_size 				cont_create_y_radius;
		lu_size 				cont_create_t_radius;

		lu_value 				contrast;
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

///////////////////////////////////////////////////////////////////////////////
// Restore API

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