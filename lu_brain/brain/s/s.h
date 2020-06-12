/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

#ifndef _LU_S_H
#define _LU_S_H

///////////////////////////////////////////////////////////////////////////////
// S Net
//

	struct s_net_base {
		enum s_net_type    		type;

		S_Layer 				layer;
		lu_size 				x;
		lu_size 				y;
	};

	static inline S_Net_Base s_base_init(S_Net_Base self, enum s_net_type type, S_Layer layer, lu_size x, lu_size y)
	{
		self->type 				= type;
		self->layer 			= layer;
		self->x 				= x;
		self->y 				= y;

		return self;
	}

	// neu i a_neu
	struct s_neu {
		struct s_net_base 		super;

		enum s_net_type			p_type;
		s_neu_ix 				p[4];

		enum s_net_type 		c_type;
		s_neu_ix 				c[4];

		enum s_net_type 		t_type;
		s_neu_ix 				t;			

		// she maye buty zviazok z s_neu z inshyh s_rec na tyh rivniah de ce 
		// mozhlyvo
	}; 

	static S_Neu s_neu_create(Mem mem, S_Layer, lu_size x, lu_size y);
	static void s_neu_pc_connect(S_Neu neu, S_Layer* layers);

	struct s_a_neu {
		struct s_net_base 		super;

		enum s_net_type			p_type;
		s_neu_ix 				p[2];

		enum s_net_type 		c_type;
		s_neu_ix 				c[2];
	};

	struct s_cell {
		struct s_net_base 		super;
		
		Arr 					cols;    	

		enum s_net_type 		c_type;
		s_neu_ix 				c[4];
	};

	static S_Cell s_cell_create(Mem mem, S_Layer, S_Col_Conf conf, lu_size x, lu_size y);
	static inline S_Col s_cell_col_get(S_Cell self, lu_size indx) { return (S_Col) arr_get(self->cols, indx); }

///////////////////////////////////////////////////////////////////////////////
// S Dopomizhni
//

	struct s_col_conf {
		lu_size 				component_size;
		lu_value 				orig_min;
		lu_value 				orig_max;
		lu_value 				max;

		lu_value 				step;
		lu_value*				steps;  		// preobchysleni kroky
		lu_size 				neu_size;
		lu_size 				nsc; 			// (tilky dlia poshuku) nei sim count
	};

	static S_Col_Conf s_col_conf_init(S_Col_Conf, Mem mem, lu_size component_size, lu_value min, lu_value max, lu_size neu_size, lu_size nsc);
	static inline lu_value s_col_conf_norm(S_Col_Conf self, lu_value request);
	static inline lu_size s_col_conf_indx(S_Col_Conf self, lu_value val);
	static inline struct lu_size_range s_col_conf_indx_range(S_Col_Conf self, lu_value val);
	static inline lu_value s_col_conf_calc_sig(S_Col_Conf self, lu_size val_step_i, lu_value val);
	static inline lu_value s_col_conf_step_norm_dist(S_Col_Conf self);

	struct s_col {
		S_Cell 					cell;

		// conf 
		S_Col_Conf 				conf;

		n_neu_ix*				neus; 	
	};

	static inline S_Col s_col_create(Mem mem, S_Cell s_cell, S_Col_Conf s_col_conf);
	static inline N_Neu s_col_n_get(S_Col self, lu_value input_val);

	struct s_layer {
		// vlasnyk
		S_Rec 					rec;

		lu_size 				l;
		lu_size 				w;
		lu_size 				h;

		s_neu_ix* 				neus;
	};

	static S_Layer s_layer_create(S_Rec rec, Mem mem, lu_size l, lu_size w, lu_size h);
	static inline void s_layer_neu_ix_set(S_Layer self, lu_size x, lu_size y, s_neu_ix val) { self->neus[y * self->w + x] = val; }
	static inline s_neu_ix s_layer_neu_ix_get(S_Layer self, lu_size x, lu_size y) { return self->neus[y * self->w + x]; }
	static void s_layer_cells_create(S_Layer self, Mem mem, S_Col_Conf conf);

	struct s_rec {
		// vlasnyk
		S_Mem 					mem; 			

		// poviazanyy z rec
		Lu_Rec 					rec;			

		lu_size 				id;

		lu_size 				cells_w;
		lu_size 				cells_h; 
		lu_size 				cells_size;
		lu_size 				cells_count;
		S_Cell* 				cells;	

		lu_size 				neus_size;
		lu_size 				neu_count;
		S_Neu* 					neus;
		lu_size 				layers_size;
		
		struct s_col_conf 		v_conf;	
		S_Layer* 				v_layers;

		struct s_col_conf 		p_conf;
		S_Layer* 				p_layers;
	};

	static S_Rec s_rec_create(S_Mem mem, Lu_Rec s_rec);
	static S_Neu s_rec_neu_create(S_Rec, Mem mem, S_Layer, lu_size x, lu_size y);
 
 	// static inline s_neu_ix s_rec_cell_ix(S_Rec self, lu_size x, lu_size y) { return y * self->cells_w + x; }
	//static inline void s_rec_v_cell_set(S_Rec self, lu_size x, lu_size y, S_Cell s_cell) {  s_layer_neus_cell; }
	static inline S_Cell s_rec_v_cell_get(S_Rec self, lu_size x, lu_size y) { return self->cells[s_layer_neu_ix_get(self->v_layers[0], x, y)]; }
	//static inline void s_rec_p_cell_set(S_Rec self, lu_size x, lu_size y, S_Cell s_cell) { self->p_cells[s_rec_cell_ix(self, x, y)] = s_cell; }
	static inline S_Cell s_rec_p_cell_get(S_Rec self, lu_size x, lu_size y) { return self->cells[s_layer_neu_ix_get(self->p_layers[0], x, y)]; }

	struct s_mem {
		Lu_Brain 				brain;

		Arr 					recs;
	};
	
	static S_Mem s_mem_create(Lu_Brain brain);
	static inline S_Rec s_mem_s_rec_get(S_Mem self, lu_size indx) { return arr_get(self->recs, indx); }

#endif // _LU_S_H
