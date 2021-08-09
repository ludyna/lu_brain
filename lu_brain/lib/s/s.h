/**
	Copyright © 2021 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Slots
//
	struct lu_s_slot_1 {
		Lu_S_Base_Cell one;
	};

	struct lu_s_slot_4 {
		Lu_S_Base_Cell one;
		Lu_S_Base_Cell two;
		Lu_S_Base_Cell three;
		Lu_S_Base_Cell four;
	};

	struct lu_s_slot_2 {
		Lu_S_Base_Cell one;
		Lu_S_Base_Cell two;
	};

	//
	// Slot inits
	//

	static inline Lu_S_Slot_1 lu_s_slot_1_init(Lu_S_Slot_1 self) 
	{
		self->one = NULL;
		return self;
	}

	static inline Lu_S_Slot_2 lu_s_slot_2_init(Lu_S_Slot_2 self) 
	{
		self->one = NULL;
		self->two = NULL;
		return self;
	} 

	static inline Lu_S_Slot_4 lu_s_slot_4_init(Lu_S_Slot_4 self) 
	{
		self->one = NULL;
		self->two = NULL;
		self->three = NULL;
		self->four = NULL;
		return self;
	}

///////////////////////////////////////////////////////////////////////////////
// Cells
// 
// Plan:
// component_v (1) ==>
// component_p (1) ==> pixel (w x h) ==> pyra (w - 1 x h - 1) ... pyra (1) = pyra(w) 
// ==> seq (w - 1) ... seq (1)
//

	struct lu_s_base_cell {
		enum lu_s_cell_type type;			

		Lu_S_Base_Layer layer;

		// for S and W it is always one child
		struct lu_s_slot_1 c; 
	}; 

	struct lu_s_component_cell {
		struct lu_s_base_cell super;

		Hnn_Cell_Value* cells;
	};

	// nertex
	struct lu_s_pixel_cell {
		struct lu_s_base_cell super;

 		// for pixe always one p
		struct lu_s_slot_2 p;

		lu_size x; 
		lu_size y;   		
	};

	struct lu_s_rec_cell {
		struct lu_s_base_cell super;

		struct lu_s_slot_4 p;
	};

	// nertex
	struct lu_s_seq_nx_cell {
		struct lu_s_base_cell super;

		struct lu_s_slot_4 p;
		Lu_Rec rec;
	};

	struct lu_s_seq_cell {
		struct lu_s_base_cell super;

		struct lu_s_slot_2 p;
	};

	// nertex
	struct lu_s_story_nx_cell {
		struct lu_s_base_cell super;

		struct lu_s_slot_2 p;
	};

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

	struct lu_s_base_layer {
		enum lu_s_layer_type type;

		// layer number, starting from bottom, starting from zero 
		// layer number resets for every layer type
		lu_size number; 				
		lu_size w;
		lu_size h;
	};

	// v an p layers are instances of this layer
	// We can make algorithm a bit more complicated but save memory for components 
 	// but for MVP it is not important (if ever)
	struct lu_s_component_layer {
		struct lu_s_base_layer super;
		struct lu_s_layer_conf conf;

		Lu_S_Component_Cell* cells;
	};

	// nertex
	struct lu_s_pixel_layer {
		struct lu_s_base_layer super;

		lu_size cells_count;
		Lu_S_Pixel_Cell* cells;
	};

	// pyra
	struct lu_s_rec_layer {
		struct lu_s_base_layer super;

		lu_size cells_count;
		Lu_S_Rec_Cell* cells;
	};

	// nertex
	struct lu_s_seq_nx_layer {
		struct lu_s_base_layer super;

		lu_size cells_count;
		Lu_S_Seq_Nx_Cell* cells;
	};

	// pyra
	struct lu_s_seq_layer {
		struct lu_s_base_layer super;

		lu_size cells_count;
		Lu_S_Seq_Cell* cells;
	};

	// nertex
	struct lu_s_story_nx_layer {
		struct lu_s_base_layer super;

		lu_size cells_count;
		Lu_S_Story_Nx_Cell* cells;
	};


	// static inline void lu_s_layer_cell_set(Lu_S_Layer self, lu_size x, lu_size y, lu_size z, Lu_S_Base_Cell val) 
	// {
	// 	lu_user_assert_void(val, "Lu_S_Base_Cell is NULL");
	// 	lu_user_assert_void(x < self->w, "x index out of range");
	// 	lu_user_assert_void(y < self->h, "y index out of range");
	// 	lu_user_assert_void(z < self->d, "z index out of range");

	// 	self->cells[z * self->w * self->h + y * self->w + x] = val; 
	// }

	// static inline Lu_S_Base_Cell lu_s_layer_cell_get(Lu_S_Layer self, lu_size x, lu_size y, lu_size z) 
	// { 
	// 	lu_user_assert(x < self->w, "x index out of range");
	// 	lu_user_assert(y < self->h, "y index out of range");
	// 	lu_user_assert(z < self->d, "z index out of range");

	// 	return self->cells[z * self->w * self->h + y * self->w + x]; 
	// }

	// static inline lu_size lu_s_layer_cells_size(Lu_S_Layer self) 
	// { 
	// 	return self->w * self->h * self->d; 
	// }

	// // lu_s_layer.lu
	// static Lu_S_Layer lu_s_layer_base_init(Lu_S_Layer self, enum lu_s_layer_type type, lu_size l, lu_size w, lu_size h, lu_size d);
	// static void lu_s_layer_base_deinit(Lu_S_Layer self);

	// static void lu_s_layer_component_cells_init(
	// 	Lu_S_Layer self, 
	// 	Lu_S_Cell_Mem cell_mem, 
	// 	Lu_S_Layer_Conf v_conf, 
	// 	Lu_S_Layer_Conf p_conf
	// );
	// static void lu_s_layer_component_cells_deinit(Lu_S_Layer self, Lu_S_Cell_Mem cell_mem);

	// static void lu_s_layer_pixel_cells_init(Lu_S_Layer self, Lu_S_Layer b_layer, Lu_S_Cell_Mem cell_mem, lu_size cells_d);
	// static void lu_s_layer_pixel_cells_deinit(Lu_S_Layer self, Lu_S_Cell_Mem cell_mem);

	// static void lu_s_layer_rec_cells_init(Lu_S_Layer self, Lu_S_Layer b_layer, Lu_S_Cell_Mem cell_mem);
	// static void lu_s_layer_rec_cells_deinit(Lu_S_Layer self, Lu_S_Cell_Mem cell_mem);

	// static void lu_s_layer_seq_cells_init(Lu_S_Layer self, Lu_S_Layer b_layer, Lu_S_Cell_Mem cell_mem);
	// static void lu_s_layer_seq_cells_deinit(Lu_S_Layer self, Lu_S_Cell_Mem cell_mem);

	// static void lu_s_layer_print_info(Lu_S_Layer self);

///////////////////////////////////////////////////////////////////////////////
// Lu_S_Cell_Mem
//

	struct lu_s_cell_mem {

		Lu_Mem mem;

		lu_size component_cells_size;
		lu_size component_cells_count;
		struct lu_s_component_cell* component_cells;

		lu_size pixel_cells_size;
		lu_size pixel_cells_count;
		struct lu_s_pixel_cell* pixel_cells;

		lu_size rec_cells_size;
		lu_size rec_cells_count;
		struct lu_s_rec_cell* rec_cells;

		lu_size seq_nx_cells_size;
		lu_size seq_nx_cells_count;
		struct lu_s_seq_nx_cell* seq_nx_cells;

		lu_size seq_cells_size;
		lu_size seq_cells_count;
		struct lu_s_seq_cell* seq_cells;

		lu_size story_nx_cells_size;
		lu_size story_nx_cells_count;
		struct lu_s_story_nx_cell* story_nx_cells;
	};

	//
	// Create and Destroy
	// 

	static Lu_S_Cell_Mem lu_s_cell_mem_create(Lu_Mem mem);
	static void lu_s_cell_mem_destroy(Lu_S_Cell_Mem self);

	//
	// Allocate cells
	// 

	static void lu_s_cell_mem_alloc_cells(Lu_S_Cell_Mem self);

	//
	// Cells assign and retract
	//

	// static Lu_S_Cell_1 lu_s_cell_mem_cell_1_assign(Lu_S_Cell_Mem, Lu_S_Layer);   
	// static void lu_s_cell_mem_cell_1_retract(Lu_S_Cell_Mem self, Lu_S_Cell_1 cell); 

	// static Lu_S_Cell_2 lu_s_cell_mem_cell_2_assign(Lu_S_Cell_Mem self, Lu_S_Layer layer, lu_size x, lu_size y);
	// static void lu_s_cell_mem_cell_2_retract(Lu_S_Cell_Mem self, Lu_S_Cell_2 cell);

	// static Lu_S_Cell_3 lu_s_cell_mem_cell_3_assign(
	// 	Lu_S_Cell_Mem self, 
	// 	Lu_S_Layer layer, 
	// 	lu_size x, 
	// 	lu_size y, 
	// 	lu_size z,
	// 	Lu_S_Layer_Conf v_conf, 
	// 	Lu_S_Layer_Conf p_conf
	// );
	// static void lu_s_cell_mem_cell_3_retract(Lu_S_Cell_Mem self, Lu_S_Cell_3 cell);


	// 
	// Print
	//

	static void lu_s_cell_mem_print_info(Lu_S_Cell_Mem self);

///////////////////////////////////////////////////////////////////////////////
// Lu_S_Rec_Rg
//

	// Reason we have different rgs instead of putting every layer into the same 
	// structure is that we can different number of instances of each rg.
	// For example, we need rec_rg for ever rec, while we need one seq_rg.
	struct lu_s_rec_rg {
		
		// Lu_Rec 
		Lu_Rec 					rec;			
		lu_size 				id;

		// Dimensions
		lu_size 				cells_w;
		lu_size 				cells_h; 
		lu_size 				cells_d;		

		Lu_S_Cell_Mem 			cell_mem;

		//
 		// Layers
 		//

		struct lu_s_component_layer v_layer;
		struct lu_s_component_layer p_layer;

		struct lu_s_pixel_layer pixel_layer;

		lu_size rec_layers_size;
		struct lu_s_rec_layer* rec_layers;
	};

	// static inline Lu_S_Cell_1 lu_s_rec_rg_v_cell_get(Lu_S_Rec_Rg self, lu_size l, lu_size x, lu_size y, lu_size z)
	// {
	// 	Lu_S_Layer layer = &self->layers[l];
	// 	return lu_s_layer_cell_get(layer, x, y, z);
	// }

	// static inline Lu_S_Layer lu_s_rec_rg_top_layer_get(Lu_S_Rec_Rg self)
	// {
	// 	return &self->layers[self->layers_size - 1];
	// }

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
// Lu_S_Seq_Rg
//

	struct lu_s_seq_rg {
		Lu_S_Cell_Mem 			cell_mem;
		lu_size 				max_blocks_size;
		lu_size 				recs_size;

		// 
		// Layers
		//

		struct lu_s_seq_nx_layer seq_nx_layer;

		lu_size seq_layers_size;
		struct lu_s_seq_layer* seq_layers;

	};

	// static inline Lu_S_Layer lu_s_seq_rg_base_layer_get(Lu_S_Seq_Rg self) 
	// {
	// 	return &self->layers[0];
	// }

	static Lu_S_Seq_Rg lu_s_seq_rg_create(Lu_S_Cell_Mem cell_mem, lu_size recs_size);
	static void lu_s_seq_rg_destroy(Lu_S_Seq_Rg self);

	static void lu_s_seq_rg_layers_connect(Lu_S_Seq_Rg self);
	static void lu_s_seq_rg_layers_disconnect(Lu_S_Seq_Rg self);


///////////////////////////////////////////////////////////////////////////////
// Lu_S_Seq_Rg
//

	struct lu_s_story_rg {
		Lu_S_Cell_Mem cell_mem;

		//
		// Layers
		//

		struct lu_s_story_nx_layer story_nx_layer;
	};

///////////////////////////////////////////////////////////////////////////////
// Lu_S
//

	struct lu_s {
		Lu_Brain 				brain;

		Lu_S_Cell_Mem  			cell_mem;

		//
		// Regions
		//

		Lu_Arr 					recs;

		Lu_S_Seq_Rg 			seq;

		Lu_S_Story_Rg  			story;
	};
	
	// s.lu
	static Lu_S lu_s_create(Lu_Brain brain);
	static void lu_s_destroy(Lu_S self);

	static void lu_s_print_info(Lu_S self);
