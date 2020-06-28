/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

#ifndef _LU_S_H
#define _LU_S_H

///////////////////////////////////////////////////////////////////////////////
// S Net
// 

	// a_neu
 	#define b_l(n) n->b[0]
	#define b_p(n) n->b[0]
	
	#define d_l(n) n->d[0]
	#define d_p(n) n->d[1]

	// neu
	#define b_vl(n) n->b[0]
	#define b_vp(n) n->b[1]
	#define b_np(n) n->b[2]
	#define b_nl(n) n->b[3]

	#define d_vl(n) n->d[0]
	#define d_vp(n) n->d[1]
	#define d_np(n) n->d[2]
	#define d_nl(n) n->d[3]

	// ce ne neu, ce lohichnyy prostir dlia neus (odnoho i bilshe neu)
	struct s_neu {
		enum s_neu_type    		type;			

		S_Layer 				layer;
		lu_size 				x;    		// bude t index dlia a_neu
		lu_size 				y;
		lu_size 				z;

		S_Neu*					b;
		S_Neu*					d;
		S_Neu  	 				t;			// zviazok po t		

		lu_size 				neus_count; // neus_count potriben shob znayty n_sig dlia n_neu po yoho n_neu->sid v wave->w_neu->neus
		N_Neu* 					neus;		// mozhe buty NULL abo odyn abo bilshe neu sho podiliayut prostir

		// she maye buty zviazok z s_neu z inshyh s_rec na tyh rivniah de ce 
		// mozhlyvo
	}; 

	static S_Neu s_neu_init(S_Neu self, enum s_neu_type type, S_Layer, lu_size x, lu_size y, lu_size z);
	static void s_component_b_layer_connect(S_Neu d, S_Layer b_layer);
	static void s_cell_b_layer_connect(S_Neu self, S_Layer);
	static void s_neu_b_layer_connect(S_Neu self, S_Layer);
	static void s_a_neu_b_layer_connect(S_Neu self, S_Layer);
	static inline void s_neu_t_connect(S_Neu v_neu, S_Neu p_neu) 
	{
		v_neu->t = p_neu;
		p_neu->t = v_neu;
	}

///////////////////////////////////////////////////////////////////////////////
// S Dopomizhni
//

	struct s_layer_conf {
		lu_value 				orig_min;
		lu_value 				orig_max;
		lu_value 				max;

		lu_value 				step;
		lu_value*				steps;  		// preobchysleni kroky
		lu_size 				neus_size;
		lu_size 				nsc; 			// (tilky dlia poshuku) nei sim count
	};

	static S_Layer_Conf s_layer_conf_init(S_Layer_Conf, Mem mem, lu_value min, lu_value max, lu_size neus_size, lu_size nsc);
	static inline lu_value s_layer_conf_norm(S_Layer_Conf self, lu_value request);
	static inline lu_size s_layer_conf_ix(S_Layer_Conf self, lu_value val);
	static inline struct lu_size_range s_layer_conf_ix_range(S_Layer_Conf self, lu_value val);
	static inline lu_value s_layer_conf_calc_sig(S_Layer_Conf self, lu_size val_step_i, lu_value val);
	static inline lu_value s_layer_conf_step_norm_dist(S_Layer_Conf self);

	struct s_layer {
		// vlasnyk
		S_Rec 					rec;

		enum s_layer_type 		type;

		lu_size 				l;
		lu_size 				w;
		lu_size 				h;
		lu_size 				d;				// komponenty v pershomu layer

		S_Neu* 					neus;

		S_Layer_Conf 			conf;		
	};

	static S_Layer s_layer_init(S_Layer self, S_Rec rec, Mem mem, enum s_layer_type type, lu_size l, lu_size w, lu_size h, lu_size d);
	static inline void s_layer_neu_set(S_Layer self, lu_size x, lu_size y, lu_size z, S_Neu val) { self->neus[z * self->w * self->h + y * self->w + x] = val; }
	static inline S_Neu s_layer_neu_get(S_Layer self, lu_size x, lu_size y, lu_size z) { return self->neus[z * self->w * self->h + y * self->w + x]; }
	static void s_layer_cells_create(S_Layer self, Mem mem, S_Layer_Conf conf);

	// velyki masyvy v s_rec shob vykorystaty perevahu cpu keshuvania
	struct s_rec {
		// vlasnyk
		S_Mem 					mem; 			

		// poviazanyy z rec
		Lu_Rec 					rec;			

		lu_size 				id;

		lu_size 				cells_w;
		lu_size 				cells_h; 
		lu_size 				cells_d;		

		lu_size 				neus_size;
		lu_size 				neus_count;
		struct s_neu* 			neus;

		lu_size 				vp_layers_size;
		struct s_layer_conf 	v_conf;	
		struct s_layer* 		v_layers;
		struct s_layer_conf 	p_conf;
		struct s_layer* 		p_layers;

		lu_size 				blocks_size;
		lu_size 				a_layers_size;
		struct s_layer* 		av_layers;
		struct s_layer* 		ap_layers;
	};

	static S_Rec s_rec_create(S_Mem mem, Lu_Rec s_rec);

	static inline S_Neu s_rec_v_cell_get(S_Rec self, lu_size l, lu_size x, lu_size y, lu_size z)
	{
		S_Layer layer = &self->v_layers[l];
		return s_layer_neu_get(layer, x, y, z);
	}

	// Layers inits
	static void s_rec_val_layers_init(S_Rec self, S_Layer v_layer, S_Layer p_layer, Mem mem);
	static void s_rec_comp_layers_init(S_Rec self, S_Layer v_layer, S_Layer p_layer, S_Layer b_v_layer, S_Layer b_p_layer, Mem mem);
	static void s_rec_cell_layers_init(S_Rec self, S_Layer v_layer, S_Layer p_layer, S_Layer b_v_layer, S_Layer b_p_layer, Mem mem);
	static void s_rec_neu_layers_init(S_Rec self, S_Layer v_layer, S_Layer p_layer, S_Layer b_v_layer, S_Layer b_p_layer, Mem mem, lu_size w, lu_size h, lu_size layer_ix);

	// Neu inits
	static S_Neu s_rec_neu_init(S_Rec, Mem mem, enum s_neu_type type, S_Layer, lu_size x, lu_size y, lu_size z); 
	static S_Neu s_rec_val_init(S_Rec, Mem mem, S_Neu neu);
	static S_Neu s_rec_component_init(S_Rec, Mem mem, S_Neu neu);
	static S_Neu s_rec_cell_init(S_Rec self, Mem mem, S_Neu neu);
	static S_Neu s_rec_mid_tier_neu_init(S_Rec self, Mem mem, S_Neu neu);
	static S_Neu s_rec_a_neu_init(S_Rec self, Mem mem, S_Neu neu);

	struct s_mem {
		Lu_Brain 				brain;

		Arr 					recs;
	};
	
	static S_Mem s_mem_create(Lu_Brain brain);
	static inline S_Rec s_mem_s_rec_get(S_Mem self, lu_size indx) { return arr_get(self->recs, indx); }

#endif // _LU_S_H
