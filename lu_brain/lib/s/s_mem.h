/**
	Copyright © 2021 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// S_Layer_Conf
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

	// s_layer_conf.lu
	static S_Layer_Conf s_layer_conf_init(S_Layer_Conf, lu_value min, lu_value max, lu_size cells_size, lu_size nsc);
	static void s_layer_conf_deinit(S_Layer_Conf self);

	static inline lu_value s_layer_conf_norm(S_Layer_Conf self, lu_value request);
	static inline lu_size s_layer_conf_ix(S_Layer_Conf self, lu_value val);
	static inline struct lu_size_range s_layer_conf_ix_range(S_Layer_Conf self, lu_value val);
	static inline lu_value s_layer_conf_calc_sig(S_Layer_Conf self, lu_size val_step_i, lu_value val);
	static inline lu_value s_layer_conf_step_norm_dist(S_Layer_Conf self);

///////////////////////////////////////////////////////////////////////////////
// S_Layer
//

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

	static inline void s_layer_cell_set(S_Layer self, lu_size x, lu_size y, lu_size z, S_Cell val) 
	{
		lu_user_assert_void(val, "S_Cell is NULL");
		lu_user_assert_void(x < self->w, "x index out of range");
		lu_user_assert_void(y < self->h, "y index out of range");
		lu_user_assert_void(z < self->d, "z index out of range");

		self->cells[z * self->w * self->h + y * self->w + x] = val; 
	}

	static inline S_Cell s_layer_cell_get(S_Layer self, lu_size x, lu_size y, lu_size z) 
	{ 
		lu_user_assert(x < self->w, "x index out of range");
		lu_user_assert(y < self->h, "y index out of range");
		lu_user_assert(z < self->d, "z index out of range");

		return self->cells[z * self->w * self->h + y * self->w + x]; 
	}

	static inline lu_size s_layer_cells_size(S_Layer self) 
	{ 
		return self->w * self->h * self->d; 
	}

	// s_layer.lu
	static S_Layer s_layer_base_init(S_Layer self, S_Rec rec, enum s_layer_type type, lu_size l, lu_size w, lu_size h, lu_size d);
	static void s_layer_base_deinit(S_Layer self);

	static void s_layer_component_cells_init(S_Layer self);
	static void s_layer_component_cells_deinit(S_Layer self);

	static void s_layer_pixel_cells_init(S_Layer self, S_Layer b_layer);
	static void s_layer_pixel_cells_deinit(S_Layer self);

	static void s_layer_pyra_cells_init(S_Layer self, S_Layer b_layer);
	static void s_layer_pyra_cells_deinit(S_Layer self);

	static void s_layer_block_cells_init(S_Layer self, S_Layer b_layer);
	static void s_layer_block_cells_deinit(S_Layer self);

	static void s_layer_print_info(S_Layer self);

///////////////////////////////////////////////////////////////////////////////
// S_Rec
//

	// velyki masyvy v s_rec shob vykorystaty perevahu cpu keshuvania
	struct s_rec {
		
		// Vlasnyk

		S_Mem 					mem; 			

		// Lu_Rec related

		Lu_Rec 					rec;			
		lu_size 				id;

		// Cells

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
 
 		// Layers

		struct s_layer_conf 	v_conf;	
		struct s_layer_conf 	p_conf;

		lu_size 				data_layers_size;
		struct s_layer* 		data_layers;
 
		lu_size 				max_blocks_size;
		lu_size 				block_layers_size;
		struct s_layer* 		block_layers;
	};

	static inline S_Cell s_rec_v_cell_get(S_Rec self, lu_size l, lu_size x, lu_size y, lu_size z)
	{
		S_Layer layer = &self->data_layers[l];
		return s_layer_cell_get(layer, x, y, z);
	}

	// s_rec.lu
	static S_Rec s_rec_create(S_Mem mem, Lu_Rec s_rec);
	static void s_rec_destroy(S_Rec self);
	
	static S_Cell s_rec_cell_assign(S_Rec, S_Layer);   
	static void s_rec_cell_retract(S_Rec self, S_Cell cell); 

	static S_Cell_2 s_rec_cell_2_assign(S_Rec self, S_Layer layer, lu_size x, lu_size y);
	static void s_rec_cell_2_retract(S_Rec self, S_Cell_2 cell);

	static S_Cell_3 s_rec_cell_3_assign(S_Rec self, S_Layer layer, lu_size x, lu_size y, lu_size z);
	static void s_rec_cell_3_retract(S_Rec self, S_Cell_3 cell);

	// s_rec_layer_inits.lu
	static void s_rec_layers_init(S_Rec self);
	static void s_rec_layers_deinit(S_Rec self);
	
	static void s_rec_components_init(S_Rec self);
	static void s_rec_components_deinit(S_Rec self);
	
	static void s_rec_pixels_init(S_Rec self); 
	static void s_rec_pixels_deinit(S_Rec self); 

	static void s_rec_pyras_init(S_Rec self); 
	static void s_rec_pyras_deinit(S_Rec self);

	static void s_rec_blocks_init(S_Rec self);
	static void s_rec_blocks_deinit(S_Rec self);

	static void s_rec_print_info(S_Rec self);

///////////////////////////////////////////////////////////////////////////////
// S_Mem
//

	struct s_mem {
		Lu_Brain 				brain;

		Arr 					recs;
	};
	
	static inline S_Rec s_mem_s_rec_get(S_Mem self, lu_size indx) { return arr_get(self->recs, indx); }

	// s_mem.lu
	static S_Mem s_mem_create(Lu_Brain brain);
	static void s_mem_destroy(S_Mem self);

	static void s_mem_print_info(S_Mem self);

	static void s_mem_rec_create(S_Mem self, Lu_Rec rec);
	static void s_mem_rec_destroy(S_Mem self, Lu_Rec rec);
