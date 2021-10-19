/**
	Copyright © 2021 Oleh Ihorovych Novosad 

	Map:													
		(x Y y) = max(x - 1, 1) * max(y - 1, 1)


		"Minimal" start:

		level3, story(vertically 1-n4)
		level2, scene(vertically 1-n3)
		level1, event (vertically 1-n2)
		seq (vertically 1-n1)
		rec (vertically rec_count)
		pixel(vertically w Y h)
		comp1 comp2 comp3 (horizontally comp_count or d)

	r1 r2 r3 r4
	r1 r2 r3 r4
	r1 r2 r3 r4

	r1 r2 r3 r4

	
	Koly my dobavliayemo novyy sequence to my mozhemo chy ce novyy event, chy ce nova scena 
	Faktychno sequence ce zavzhdy vyznacheno. Novi rivni poza seq ce vhe problemy avtora (programista).
	Vin maye maty mozhlyvist dobavliaty yih stilky skilky zahoche i nazyvaty yih yak zahoche 
	(slova, rechenia, abzacy, storinky i td).
	Yaksho programist kazhe startuyem novyy level3, ce ozanachaye avtomatychno novyy level 2 and level 1.

	There will not be horizontal growing fro S, only vertical, except for comps layers.
	No need for S cells. No need for S slots.

	S and W wil be very similar.

	We build not from top and not from bottom, we build from pixel layer.
*/


///////////////////////////////////////////////////////////////////////////////
// Lu_S_Layer
//

	//
	// Base
	//

	struct lu_s_layer_base {
		enum lu_s_layer_type type;
		lu_size level;
	};

	static inline Lu_S_Layer_Base lu_s_layer_base__init(Lu_S_Layer_Base self, enum lu_s_layer_type type, lu_size level)
	{
		lu__assert(self);
		lu__assert(type < LU_S_LT_END);

		self->type = type;
		self->level = level;

		return self;
	}
	
	//
	// Comp_Layer
	//

	// can be v or p
	struct lu_s_comp_layer {

		struct lu_s_layer_base 	super;

		lu_value 				orig_min;
		lu_value 				orig_max;
		lu_value 				max;

		lu_value 				step;
		lu_value*				steps;  		// preobchysleni kroky
		lu_size 				cells_size;

		// w x h x cells_size_i, empty by default
		Hnn_Cell_Value* cells;
	};

	static Lu_S_Comp_Layer lu_s_comp_layer__init(Lu_S_Comp_Layer, Lu_Mem mem, lu_value min, lu_value max, lu_size cells_size);
	static void lu_s_comp_layer__deinit(Lu_S_Comp_Layer self);

	static inline lu_value lu_s_comp_layer__norm(Lu_S_Comp_Layer self, lu_value request);
	static inline lu_size lu_s_comp_layer__ix(Lu_S_Comp_Layer self, lu_value val);
	static inline struct lu_size_range lu_s_comp_layer__ix_range(Lu_S_Comp_Layer self, lu_value val, lu_size nsc);
	static inline lu_value lu_s_comp_layer__calc_sig(Lu_S_Comp_Layer self, lu_size val_step_i, lu_value val);
	static inline lu_value lu_s_comp_layer__step_norm_dist(Lu_S_Comp_Layer self);



	//
	// Pixel_Layer
	//

	struct lu_s_pixel_layer {
		struct lu_s_layer_base super;
	};

	//
	// Layer_4
	//

	struct lu_s_layer_4 {
		struct lu_s_layer_base super;
	};

	//
	// Layer_2
	//

	struct lu_s_layer_2 {
		struct lu_s_layer_base super;
	};



///////////////////////////////////////////////////////////////////////////////
// Lu_S_Layer_Mem
//
	struct lu_s_layer_mem_config {
		lu_size component_cells_size;

	};

	static inline Lu_S_Layer_Mem_Config lu_s_cell_mem_config__init(Lu_S_Layer_Mem_Config self)
	{
		lu__assert(self);

		self->component_cells_size = 0;


		return self;
	}

	static inline Lu_S_Layer_Mem_Config lu_s_cell_mem_config__validate(Lu_S_Layer_Mem_Config self)
	{
		lu__assert(self);

		lu__assert(self->component_cells_size > 0);

		return self;
	}

	struct lu_s_layer_mem {
		Lu_Mem mem;

		struct lu_s_layer_mem_config config;

		lu_size component_cells_count;
		struct lu_s_comp_layer* component_cells;


	};

	//
	// Create and Destroy
	// 

	static Lu_S_Layer_Mem lu_s_cell_mem__create(Lu_Mem mem, struct lu_s_layer_mem_config config);
	static void lu_s_cell_mem__destroy(Lu_S_Layer_Mem self);

	//
	// Allocate cells
	// 

	static void lu_s_cell_mem__alloc_cells(Lu_S_Layer_Mem self, struct lu_s_layer_mem_config config);

	// 
	// Print
	//

	static void lu_s_cell_mem__print_info(Lu_S_Layer_Mem self);


///////////////////////////////////////////////////////////////////////////////
// Lu_S
//


	struct lu_s {

		Lu_Mem 					mem;
		Lu_S_Layer_Mem  		cell_mem;


		Lu_S_Layer_Base 		apex;
		Lu_S_Layer_Base 		seq;

	};
	
	static Lu_S lu_s__create(Lu_Mem mem, Lu_Arr lu_recs);
	static void lu_s__destroy(Lu_S self);

	static void lu_s__add_rec(Lu_S self, Lu_Rec rec);
	static void lu_s__add_layer(Lu_S self, lu_size level);
	#define lu_s__add_seq(self) lu_s__add_layer(self, 0)
	#define lu_s__add_event(self) lu_s__add_layer(self, 1)
	#define lu_s__add_chapter(self) lu_s__add_layer(self, 2)
	#define lu_s__add_story(self) lu_s__add_layer(self, 3)



	static void lu_s__print_info(Lu_S self);

