/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

#ifndef _LU_S_H
#define _LU_S_H

///////////////////////////////////////////////////////////////////////////////
// S

	struct s_base {
		enum s_type 			type;

		lu_size 				t;
		lu_size 				l;
		lu_size 				x;
		lu_size 				y;
	};

	// neu i a_neu
	struct s_neu {
		struct s_base 			super;

		enum s_type				p_type;
		s_neu_ix 				p[4];

		enum s_type 			c_type;
		s_neu_ix 				c[4];

	};

	struct s_col_conf {
		lu_value 				orig_min;
		lu_value 				orig_max;
		lu_value 				max;

		lu_value 				step;
		lu_value*				steps;  		// preobchysleni kroky
		lu_size 				neu_size;
		lu_size 				nsc; 			// (tilky dlia poshuku) nei sim count
	};

	static inline lu_value s_col_conf_norm(S_Col_Conf self, lu_value request);
	static inline lu_size s_col_conf_indx(S_Col_Conf self, lu_value val);
	static inline struct lu_size_range s_col_conf_indx_range(S_Col_Conf self, lu_value val);
	static inline lu_value s_col_conf_calc_sig(S_Col_Conf self, lu_size val_step_i, lu_value val);
	static inline lu_value s_col_conf_step_norm_dist(S_Col_Conf self);

	struct s_col {
		struct s_base 			super;	

		// conf 
		S_Col_Conf 				conf;

		n_neu_ix*					neus; 	
		//N_V_Neu 				t1neu; // stop ce maye buty v w_v_col, i ce bude w_v_neu chy shos take
	};

	static inline S_Col s_col_create(Mem mem, S_Cell s_cell, S_Col_Conf s_col_conf);
	// tilky w_save mozhe stvoruvaty neu (lock vseredyni cioho methoda yakyy lokaye tilky dlia cioho input_val - tochnishe val index)
	static inline N_Neu s_col_n_get(S_Col self, lu_value input_val);

	struct s_p_cell {
		struct s_base 			super;

		S_Col 					col;
	};

	// p or v cell
	struct s_v_cell {
		struct s_base 			super;
		
		Arr 					cols;    	
	};

	static inline S_Col s_v_cell_col_get(S_Cell self, lu_size indx) { return (S_Col) arr_get(self->s_cols, indx); }

	struct s_rec {
		// vlasnyk
		S_Mem 					mem; 			

		// poviazanyy z rec
		Lu_Rec 					rec;			

		lu_size 				id;

		lu_size 				cells_w;
		lu_size 				cells_h; 
		S_Cell* 				cells;	

		// Ci dani spilni dlia vsih cells i s_col
		// i odnakovi dlia znachen i perepadiv
		lu_size 				component_size; 

		struct s_col_conf 		v_conf;
		struct s_col_conf 		p_conf;
	};

	static S_Rec s_rec_create(S_Mem mem, Lu_Rec s_rec);

	static inline void s_rec_s_cell_set(S_Rec self, lu_size x, lu_size y, S_Cell s_cell) { self->cells[y * self->cells_w + x] = s_cell; }
	static inline S_Cell s_rec_s_cell_get(S_Rec self, lu_size x, lu_size y) { return self->cells[y * self->cells_w + x]; }

	static void s_rec_debug_print(S_Rec self);

	struct s_mem {
		Lu_Brain 				brain;

		Arr 					s_recs;
	};
	
	static S_Mem s_mem_create(Lu_Brain brain);

	//static N_Col s_mem_n_col_create(S_Mem self, S_Col s_col);
	static inline S_Rec s_mem_s_rec_get(S_Mem self, lu_size indx) { return arr_get(self->s_recs, indx); }

#endif // _LU_S_H
