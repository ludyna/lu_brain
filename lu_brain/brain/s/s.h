/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

#ifndef _LU_S_H
#define _LU_S_H

///////////////////////////////////////////////////////////////////////////////
// S

 	struct s_pos {
		lu_size 	lvl;
		lu_size 	x;
		lu_size 	y; 
	};

	struct s_cb_links {
		S_Cb 	tl;
		S_Cb 	tr;
		S_Cb 	bl;
		S_Cb 	br;
	};

	struct s_v_cell_links {
		S_V_Cell	tl;
		S_V_Cell	tr;
		S_V_Cell 	bl;
		S_V_Cell	br;
	};

	union s_cb_parents {
		struct s_cb_links cbs;
		struct s_v_cell_links cols;
	};

	struct s_col_conf {
		lu_value 			orig_min;
		lu_value 			orig_max;
		lu_value 			max;

		lu_value 			step;
		lu_value*			steps;  		// preobchysleni kroky
		lu_size 			neu_size;
		lu_size 			nsc; 			// (tilky dlia poshuku) nei sim count
	};

 	// n_cols dlia kolioru i perp
	struct s_col {
		// vlasnyk
		S_V_Cell				s_v_cell;		

		// conf 
		S_Col_Conf 			conf;

		// kolekciya vsih neu i generator neu
		S_Mem 				s_mem;

		N_Col*				n_cols; 	

		// odyn s_cb mozhe braty uchast tilky v 4roh child s_cb
	};

	static inline S_Col s_col_create(Mem mem, S_V_Cell s_v_cell, S_Col_Conf s_col_conf);
	static inline lu_value s_col_norm(S_Col self, lu_value request);
	static inline lu_size s_col_indx(S_Col self, lu_value val);
	static inline struct lu_size_range s_col_indx_range(S_Col self, lu_value val);
	static inline lu_value s_col_calc_sig(S_Col self, lu_size val_step_i, lu_value val);
	static inline lu_value s_col_step_norm_dist(S_Col self);

	// tilky w_save mozhe stvoruvaty neu (w_save_n_col_create(), w_save kontroluye lock yaksho treba), vony stvoruyutsia v n_mem ale 
	// zyednani z s_col
	static inline N_Col s_col_n_get(S_Col self, lu_value input_val);

	struct s_p_cell {

	};

	// p or v cell
	struct s_v_cell {
		// vlasnyk
		S_Rec 				s_rec; 		

		// s_v_cell ye na 0 lvl
		struct s_pos 		pos; 		

		Arr 				s_cols;    	
	};

	static S_V_Cell s_v_cell_create(Mem mem, S_Rec rec, lu_size x, lu_size y);
	static inline S_Col s_v_cell_s_col_get(S_V_Cell self, lu_size indx) { return (S_Col) arr_get(self->s_cols, indx); }
	
	static N_Cell s_v_cell_n_get(S_V_Cell, lu_p_value components);

	struct s_cb_first {

		
	};

	struct s_cb {


		lu_flags			flags;

		union s_cb_parents 	parents;

		// odyn s_cb mozhe braty uchast tilky v 4roh child s_cb
		struct s_cb_links 	children; 

		struct s_pos 		pos;
	};

	struct s_rec {
		// vlasnyk
		S_Mem 				s_mem; 			

		// poviazanyy z rec
		Lu_Rec 				rec;			

		lu_size 			id;

		lu_size 			s_v_cells_w;
		lu_size 			s_v_cells_h; 
		S_V_Cell* 			s_v_cells;	

		// Ci dani spilni dlia vsih s_v_cells i s_col
		// i odnakovi dlia znachen i perepadiv
		lu_size 			component_size; 

		struct s_col_conf 	v_conf;
		struct s_col_conf 	p_conf;
	};

	static S_Rec s_rec_create(S_Mem s_mem, Lu_Rec s_rec);

	static inline void s_rec_s_v_cell_set(S_Rec self, lu_size x, lu_size y, S_V_Cell s_v_cell) { self->s_v_cells[y * self->s_v_cells_w + x] = s_v_cell; }
	static inline S_V_Cell s_rec_s_v_cell_get(S_Rec self, lu_size x, lu_size y) { return self->s_v_cells[y * self->s_v_cells_w + x]; }

	static void s_rec_debug_print(S_Rec self);

	struct s_mem {
		Lu_Brain 			brain;

		Arr 				s_recs;
	};
	
	static S_Mem s_mem_create(Lu_Brain brain);

	//static N_Col s_mem_n_col_create(S_Mem self, S_Col s_col);
	static inline S_Rec s_mem_s_rec_get(S_Mem self, lu_size indx) { return arr_get(self->s_recs, indx); }

#endif // _LU_S_H
