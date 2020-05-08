/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

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
		W_Rec 				w_rec; 		// vlasnyk

		enum n_col_type 	type;

		lu_size 			x;
		lu_size 			y; 

		lu_p_value curr_vals;
		lu_p_value p_vals;
		lu_p_value prev_vals;
	};

	static W_Col w_col_create(Mem mem, W_Rec w_rec, N_Col n_col);

///////////////////////////////////////////////////////////////////////////////
// W_Rec 

	struct w_rec
	{
		lu_size 			component_size;

		lu_size 			w_cols_w;
		lu_size 			w_cols_h;
		W_Col* 				w_cols;

		lu_size 			colors_w;
		lu_size 			colors_h;
		W_Col*				colors;
	};

	static W_Rec w_rec_create(Mem mem, N_Rec n_rec);

	static void w_rec_sig_send(W_Rec self, lu_size x, lu_size y, lu_size neu_ent);

	static inline void w_rec_w_cols_set(W_Rec self, lu_size x, lu_size y, W_Col w_col) { self->w_cols[y * self->w_cols_w + x] = w_col; }
	static inline W_Col w_rec_w_cols_get(W_Rec self, lu_size x, lu_size y) { return self->w_cols[y * self->w_cols_w + x]; }

	static inline void w_rec_colors_set(W_Rec self, lu_size x, lu_size y, W_Col w_col) { self->colors[x + y * self->colors_w] = w_col; }
	static inline W_Col w_rec_colors_get(W_Rec self, lu_size x, lu_size y) { return self->colors[x + y * self->colors_w]; }

///////////////////////////////////////////////////////////////////////////////
// Lu_Wave

	struct lu_wave {
		Gate 					gate;
		Lu_Story 				story;
		N_Mem 					n_mem; 

		Arr 					w_recs;
	};

	static void wave_init(Lu_Wave self, Gate gate); 

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
	static void save_wave_c_neu_fire(Save_Wave self, lu_size neu_ent, lu_value value);	
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