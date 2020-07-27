/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

#ifndef _LU_S_H
#define _LU_S_H

///////////////////////////////////////////////////////////////////////////////
// S Net
// 

	// block_neu
 	#define b_b(n) n->b[0]  
	#define d_d(n) n->d[0]

	// neu
	#define b_vl(n) n->b[0]
	#define b_vp(n) n->b[1]
	#define b_np(n) n->b[2]
	#define b_nl(n) n->b[3]

	#define d_vl(n) n->d[0]
	#define d_vp(n) n->d[1]
	#define d_np(n) n->d[2]
	#define d_nl(n) n->d[3]

	struct s_cell {
		enum s_cell_type    	type;			
		//lu_size 				l_ix;		// nomer v layer

		S_Layer 				layer;
	
		S_Cell*					b;
		S_Cell*					d;
	}; 

	struct s_cell_2 {
		struct s_cell 			super;

		lu_size 				x; 
		lu_size 				y;   		
	};

	struct s_cell_3 {
		struct s_cell_2 		super;

		lu_size 				z;

		S_Layer_Conf 			v_conf;
		N_Cell* 				n_v_cells;

		S_Layer_Conf 			p_conf;
		N_Cell*					n_p_cells;
	};

	static void s_cell_3_save(S_Cell_3 self, lu_value value);

	// s_neu_inits.lu
	static S_Cell s_cell_init(S_Cell self, enum s_cell_type type, S_Layer, lu_size l_ix);
	static S_Cell_2 s_cell_2_init(S_Cell_2 self, enum s_cell_type type, S_Layer layer, lu_size l_ix, lu_size x, lu_size y);
	static S_Cell_3 s_cell_3_init(S_Cell_3 self, Mem mem, S_Layer layer, lu_size l_ix, lu_size x, lu_size y, lu_size z);

	static S_Cell s_component_links_alloc(S_Cell self, S_Rec, Mem mem);
	static S_Cell s_pixel_links_alloc(S_Cell self, S_Rec, Mem mem);
	static S_Cell s_pyra_links_alloc(S_Cell self, S_Rec, Mem mem);
	static S_Cell s_block_links_alloc(S_Cell self, S_Rec, Mem mem); 

	// s_neu_connects.lu
	static void s_pixel_connect(S_Cell_2 self, S_Layer);
	static void s_pyra_connect(S_Cell_2 self, S_Layer);
	static void s_block_connect(S_Cell self, S_Layer);


///////////////////////////////////////////////////////////////////////////////
// S Dopomizhni
//

	struct s_layer_conf {
		lu_value 				orig_min;
		lu_value 				orig_max;
		lu_value 				max;

		lu_value 				step;
		lu_value*				steps;  		// preobchysleni kroky
		lu_size 				cells_size;
		lu_size 				nsc; 			// (tilky dlia poshuku) nei sim count
	};

	static S_Layer_Conf s_layer_conf_init(S_Layer_Conf, Mem mem, lu_value min, lu_value max, lu_size cells_size, lu_size nsc);
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

		lu_size 				cells_count;
		S_Cell* 				cells;

		S_Layer_Conf 			conf;		

		
		lu_size 				n_cells_count; // cells_count potriben shob znayty n_sig dlia n_cell po yoho n_cell->s_ix v wave->w_neu->cells
	};

	static S_Layer s_layer_init(S_Layer self, S_Rec rec, Mem mem, enum s_layer_type type, lu_size l, lu_size w, lu_size h, lu_size d);
	
	static inline void s_layer_neu_set(S_Layer self, lu_size x, lu_size y, lu_size z, S_Cell val) 
	{ 
		lu_user_assert_void(val, "S_Cell is NULL");
		lu_user_assert_void(x < self->w, "x index out of range");
		lu_user_assert_void(y < self->h, "y index out of range");
		lu_user_assert_void(z < self->d, "z index out of range");

		self->cells[z * self->w * self->h + y * self->w + x] = val; 
	}

	static inline S_Cell s_layer_neu_get(S_Layer self, lu_size x, lu_size y, lu_size z) 
	{ 
		lu_user_assert(x < self->w, "x index out of range");
		lu_user_assert(y < self->h, "y index out of range");
		lu_user_assert(z < self->d, "z index out of range");

		return self->cells[z * self->w * self->h + y * self->w + x]; 
	}

	static inline lu_size s_layer_neus_size(S_Layer self) 
	{ 
		return self->w * self->h * self->d; 
	}

	static void s_layer_print_info(S_Layer self);

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

		lu_size 				cells_size;
		lu_size 				cells_count;
		struct s_cell* 			cells;

		lu_size 				cells_2_size;
		lu_size 				cells_2_count;
		struct s_cell_2*		cells_2;

		lu_size 				cells_3_size;
		lu_size 				cells_3_count;
		struct s_cell_3* 		cells_3;

		struct s_layer_conf 	v_conf;	
		struct s_layer_conf 	p_conf;

		lu_size 				data_layers_size;
		struct s_layer* 		data_layers;

		lu_size 				hold_blocks_size;
		lu_size 				block_layers_size;
		struct s_layer* 		block_layers;
	};

	static S_Rec s_rec_create(S_Mem mem, Lu_Rec s_rec);
	
	static S_Cell s_rec_cell_alloc(S_Rec, Mem mem, S_Layer);  
	static S_Cell_2 s_rec_cell_2_alloc(S_Rec self, Mem mem, S_Layer layer, lu_size x, lu_size y);
	static S_Cell_3 s_rec_cell_3_alloc(S_Rec self, Mem mem, S_Layer layer, lu_size x, lu_size y, lu_size z);

	static inline S_Cell s_rec_v_cell_get(S_Rec self, lu_size l, lu_size x, lu_size y, lu_size z)
	{
		S_Layer layer = &self->data_layers[l];
		return s_layer_neu_get(layer, x, y, z);
	}

	// Layers inits
	static void s_rec_components_init(S_Rec self, Mem mem);
	static void s_rec_cells_init(S_Rec self, Mem mem);
	static void s_rec_pyras_init(S_Rec self, Mem mem);

	static void s_rec_print_info(S_Rec self);

	struct s_mem {
		Lu_Brain 				brain;

		Arr 					recs;
	};
	
	static S_Mem s_mem_create(Lu_Brain brain);
	static inline S_Rec s_mem_s_rec_get(S_Mem self, lu_size indx) { return arr_get(self->recs, indx); }
	static void s_mem_print_info(S_Mem self);

#endif // _LU_S_H
