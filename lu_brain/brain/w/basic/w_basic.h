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

		lu_size 			x;
		lu_size 			y; 

		lu_p_value 			curr_vals;
		lu_p_value 			p_vals; 	// for t
		lu_p_size 			prev_neus;
	};

	static W_Col w_col_create(Mem mem, W_Rec w_rec, S_Col s_col);

///////////////////////////////////////////////////////////////////////////////
// W_Cb

	// vony musiat buty zaasayneni dlia kozhnoho s_cb
	// ne znayu chy nam treba she shos krim w_cb (w_rec i w_col mozhut buty 
	// ne potribni)
	struct w_cb
	{
		
	};

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


