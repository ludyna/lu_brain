/**
	Copyright © 2021 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Cells
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

	struct lu_s_cell_1 {
		enum lu_s_cell_type type;			
		//lu_size l_ix;		// nomer v layer

		Lu_S_Layer layer;
	
		Lu_S_Cell_1* b;
		Lu_S_Cell_1* d;
	}; 

	struct lu_s_cell_2 {
		struct lu_s_cell_1 super;

		lu_size x; 
		lu_size y;   		
	};

	struct lu_s_cell_values {
		Lu_S_Layer_Conf conf;
		Hnn_Cell_Value* cells;
	};

	static Lu_S_Cell_Values lu_s_cell_values_create(Lu_Mem mem, Lu_S_Layer_Conf conf);
	static void lu_s_cell_values_destroy(Lu_S_Cell_Values self, Lu_Mem mem);

	struct lu_s_cell_3 {
		struct lu_s_cell_2 super;

		lu_size z;

		Lu_S_Cell_Values v;
		Lu_S_Cell_Values p;
	};

	//
	// s_neu_inits.lu
	//

	static Lu_S_Cell_1 lu_s_cell_1_init(Lu_S_Cell_1 self, enum lu_s_cell_type type, Lu_S_Layer, lu_size l_ix);
	static Lu_S_Cell_2 lu_s_cell_2_init(Lu_S_Cell_2 self, enum lu_s_cell_type type, Lu_S_Layer layer, lu_size l_ix, lu_size x, lu_size y);
	
	static Lu_S_Cell_3 lu_s_cell_3_init(
		Lu_S_Cell_3 self, 
		Lu_S_Layer layer, 
		lu_size l_ix, 
		lu_size x, 
		lu_size y, 
		lu_size z, 
		Lu_S_Layer_Conf v_conf, 
		Lu_S_Layer_Conf p_conf
	);
	static void lu_s_cell_3_deinit(Lu_S_Cell_3 self);

	static Lu_S_Cell_1 s_component_links_alloc(Lu_S_Cell_1 self);
	static Lu_S_Cell_1 s_pixel_links_alloc(Lu_S_Cell_1 self, lu_size cells_d);
	static Lu_S_Cell_1 s_pyra_links_alloc(Lu_S_Cell_1 self);
	static Lu_S_Cell_1 s_block_links_alloc(Lu_S_Cell_1 self); 
	static void lu_s_cell_links_free(Lu_S_Cell_1 self);

	//
	// s_neu_connects.lu
	//

	static void s_pixel_connect(Lu_S_Cell_2 self, Lu_S_Layer);
	static void s_pyra_connect(Lu_S_Cell_2 self, Lu_S_Layer);
	static void s_block_connect(Lu_S_Cell_1 self, Lu_S_Layer);


///////////////////////////////////////////////////////////////////////////////
// Lu_S_Layer_Conf
//

	struct lu_s_layer_conf {
		lu_value 				orig_min;
		lu_value 				orig_max;
		lu_value 				max;

		lu_value 				step;
		lu_value*				steps;  		// preobchysleni kroky
		lu_size 				cells_size;
	};

	// lu_s_layer_conf.lu
	static Lu_S_Layer_Conf lu_s_layer_conf_init(Lu_S_Layer_Conf, lu_value min, lu_value max, lu_size cells_size);
	static void lu_s_layer_conf_deinit(Lu_S_Layer_Conf self);

	static inline lu_value lu_s_layer_conf_norm(Lu_S_Layer_Conf self, lu_value request);
	static inline lu_size lu_s_layer_conf_ix(Lu_S_Layer_Conf self, lu_value val);
	static inline struct lu_size_range lu_s_layer_conf_ix_range(Lu_S_Layer_Conf self, lu_value val, lu_size nsc);
	static inline lu_value lu_s_layer_conf_calc_sig(Lu_S_Layer_Conf self, lu_size val_step_i, lu_value val);
	static inline lu_value lu_s_layer_conf_step_norm_dist(Lu_S_Layer_Conf self);

///////////////////////////////////////////////////////////////////////////////
// Lu_S_Layer
//

	struct lu_s_layer {

		enum lu_s_layer_type type;

		lu_size l;
		lu_size w;
		lu_size h;
		lu_size d;				// components 

		lu_size cells_count;
		Lu_S_Cell_1* cells;

		Lu_S_Layer_Conf conf;		

		lu_size n_cells_count; 	// cells_count potriben shob znayty n_sig dlia n_cell po yoho n_cell->s_ix v wave->w_neu->cells
	};

	static inline void lu_s_layer_cell_set(Lu_S_Layer self, lu_size x, lu_size y, lu_size z, Lu_S_Cell_1 val) 
	{
		lu_user_assert_void(val, "Lu_S_Cell_1 is NULL");
		lu_user_assert_void(x < self->w, "x index out of range");
		lu_user_assert_void(y < self->h, "y index out of range");
		lu_user_assert_void(z < self->d, "z index out of range");

		self->cells[z * self->w * self->h + y * self->w + x] = val; 
	}

	static inline Lu_S_Cell_1 lu_s_layer_cell_get(Lu_S_Layer self, lu_size x, lu_size y, lu_size z) 
	{ 
		lu_user_assert(x < self->w, "x index out of range");
		lu_user_assert(y < self->h, "y index out of range");
		lu_user_assert(z < self->d, "z index out of range");

		return self->cells[z * self->w * self->h + y * self->w + x]; 
	}

	static inline lu_size lu_s_layer_cells_size(Lu_S_Layer self) 
	{ 
		return self->w * self->h * self->d; 
	}

	// lu_s_layer.lu
	static Lu_S_Layer lu_s_layer_base_init(Lu_S_Layer self, enum lu_s_layer_type type, lu_size l, lu_size w, lu_size h, lu_size d);
	static void lu_s_layer_base_deinit(Lu_S_Layer self);

	static void lu_s_layer_component_cells_init(
		Lu_S_Layer self, 
		Lu_S_Cell_Mem cell_mem, 
		Lu_S_Layer_Conf v_conf, 
		Lu_S_Layer_Conf p_conf
	);
	static void lu_s_layer_component_cells_deinit(Lu_S_Layer self, Lu_S_Cell_Mem cell_mem);

	static void lu_s_layer_pixel_cells_init(Lu_S_Layer self, Lu_S_Layer b_layer, Lu_S_Cell_Mem cell_mem, lu_size cells_d);
	static void lu_s_layer_pixel_cells_deinit(Lu_S_Layer self, Lu_S_Cell_Mem cell_mem);

	static void lu_s_layer_pyra_cells_init(Lu_S_Layer self, Lu_S_Layer b_layer, Lu_S_Cell_Mem cell_mem);
	static void lu_s_layer_pyra_cells_deinit(Lu_S_Layer self, Lu_S_Cell_Mem cell_mem);

	static void lu_s_layer_story_cells_init(Lu_S_Layer self, Lu_S_Layer b_layer, Lu_S_Cell_Mem cell_mem);
	static void lu_s_layer_story_cells_deinit(Lu_S_Layer self, Lu_S_Cell_Mem cell_mem);

	static void lu_s_layer_print_info(Lu_S_Layer self);

///////////////////////////////////////////////////////////////////////////////
// Lu_S_Cell_Mem
//

	struct lu_s_cell_mem {

		Lu_Mem mem;

		lu_size 				cells_1_size;
		lu_size 				cells_1_count;
		struct lu_s_cell_1* 	cells_1;

		lu_size 				cells_2_size;
		lu_size 				cells_2_count;
		struct lu_s_cell_2*		cells_2;

		lu_size 				cells_3_size;
		lu_size 				cells_3_count;
		struct lu_s_cell_3* 	cells_3;

	};

	//
	// Create and Destroy
	// 

	static Lu_S_Cell_Mem lu_s_cell_mem_create(Lu_Mem mem);
	static void lu_s_cell_mem_destroy(Lu_S_Cell_Mem self);

	// 
	// Size increments
	//

	static inline lu_size lu_s_cell_mem_cell_1_size_inc(Lu_S_Cell_Mem self, lu_size s) 
	{
		self->cells_1_size += s;
		return self->cells_1_size;
	}

	static inline lu_size lu_s_cell_mem_cell_2_size_inc(Lu_S_Cell_Mem self, lu_size s) 
	{
		self->cells_2_size += s;
		return self->cells_2_size;
	}

	static inline lu_size lu_s_cell_mem_cell_3_size_inc(Lu_S_Cell_Mem self, lu_size s) 
	{
		self->cells_3_size += s;
		return self->cells_3_size;
	}

	//
	// Allocate cells
	// 

	static void lu_s_cell_mem_alloc_cells(Lu_S_Cell_Mem self);

	//
	// Cells assign and retract
	//

	static Lu_S_Cell_1 lu_s_cell_mem_cell_1_assign(Lu_S_Cell_Mem, Lu_S_Layer);   
	static void lu_s_cell_mem_cell_1_retract(Lu_S_Cell_Mem self, Lu_S_Cell_1 cell); 

	static Lu_S_Cell_2 lu_s_cell_mem_cell_2_assign(Lu_S_Cell_Mem self, Lu_S_Layer layer, lu_size x, lu_size y);
	static void lu_s_cell_mem_cell_2_retract(Lu_S_Cell_Mem self, Lu_S_Cell_2 cell);

	static Lu_S_Cell_3 lu_s_cell_mem_cell_3_assign(
		Lu_S_Cell_Mem self, 
		Lu_S_Layer layer, 
		lu_size x, 
		lu_size y, 
		lu_size z,
		Lu_S_Layer_Conf v_conf, 
		Lu_S_Layer_Conf p_conf
	);
	static void lu_s_cell_mem_cell_3_retract(Lu_S_Cell_Mem self, Lu_S_Cell_3 cell);


///////////////////////////////////////////////////////////////////////////////
// Lu_S_Rec_Rg
//

	// velyki masyvy v lu_s_rec_rg shob vykorystaty perevahu cpu keshuvania
	struct lu_s_rec_rg {
		
		// Lu_Rec 
		Lu_Rec 					rec;			
		lu_size 				id;

		// Dimensions
		lu_size 				cells_w;
		lu_size 				cells_h; 
		lu_size 				cells_d;		

		Lu_S_Cell_Mem 			cell_mem;

		// v and p configs
		struct lu_s_layer_conf 	v_conf;	
		struct lu_s_layer_conf 	p_conf;
 		
 		// Layers
		lu_size 				layers_size;
		struct lu_s_layer* 		layers;
	};

	static inline Lu_S_Cell_1 lu_s_rec_rg_v_cell_get(Lu_S_Rec_Rg self, lu_size l, lu_size x, lu_size y, lu_size z)
	{
		Lu_S_Layer layer = &self->layers[l];
		return lu_s_layer_cell_get(layer, x, y, z);
	}

	//
	// lu_s_rec_rg.lu
	//

	static Lu_S_Rec_Rg lu_s_rec_rg_create(Lu_Rec lu_s_rec_rg, Lu_S_Cell_Mem cell_mem);
	static void lu_s_rec_rg_destroy(Lu_S_Rec_Rg self);
	
	//
	// lu_s_rec_rg_layer_inits.lu
	//

	static void lu_s_rec_rg_layers_init(Lu_S_Rec_Rg self);
	static void lu_s_rec_rg_layers_deinit(Lu_S_Rec_Rg self);
	
	static void lu_s_rec_rg_component_layer_connect(Lu_S_Rec_Rg self);
	static void lu_s_rec_rg_component_layer_disconnect(Lu_S_Rec_Rg self);
	
	static void lu_s_rec_rg_pixel_layer_connect(Lu_S_Rec_Rg self); 
	static void lu_s_rec_rg_pixel_layer_disconnect(Lu_S_Rec_Rg self); 

	static void lu_s_rec_rg_pyras_layers_connect(Lu_S_Rec_Rg self); 
	static void lu_s_rec_rg_pyras_layers_disconnect(Lu_S_Rec_Rg self);

	static void lu_s_rec_rg_print_info(Lu_S_Rec_Rg self);

///////////////////////////////////////////////////////////////////////////////
// Lu_S_Story_Rg
//

	struct lu_s_story_rg {
		Lu_S_Cell_Mem 			cell_mem;
		lu_size 				max_blocks_size;
		lu_size 				recs_size;
		lu_size 				layers_size;
		struct lu_s_layer* 		layers;
	};

	static Lu_S_Story_Rg lu_s_story_rg_create(Lu_S_Cell_Mem cell_mem, lu_size max_blocks_size, lu_size recs_size);
	static void lu_s_story_rg_destroy(Lu_S_Story_Rg self);

	static void lu_s_story_rg_layers_connect(Lu_S_Story_Rg self, Lu_S_Layer last_data_layer);
	static void lu_s_story_rg_layers_disconnect(Lu_S_Story_Rg self);

///////////////////////////////////////////////////////////////////////////////
// Lu_S
//

	struct lu_s {
		Lu_Brain 				brain;

		Lu_S_Cell_Mem  			cell_mem;

		Lu_Arr 					recs;

		Lu_S_Story_Rg 			story;
	};
	
	// s.lu
	static Lu_S lu_s_create(Lu_Brain brain);
	static void lu_s_destroy(Lu_S self);

	static void lu_s_print_info(Lu_S self);
