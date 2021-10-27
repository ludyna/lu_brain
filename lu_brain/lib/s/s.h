/**
	Copyright © 2021 Oleh Ihorovych Novosad 

	Map:													
		(x Y y) = max(x - 1, 1) * max(y - 1, 1)


		"Minimal" start:

		level3, story(vertically 1-n4)
		level2, scene(vertically 1-n3)
		level1, event (vertically 1-n2)
		layer seq (vertically 1-n1)
		layer recs (vertically rec_count)
		layer frames (vertically w Y h)
		frame(1)
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

	We build not from top and not from bottom, we build from frame layer.

	CE SHO NYZHCHE VIDNOSYTSIA DO rozpiznavannia i ne maye niyakoho vidnoshennia do save
	v = GREEN
	p = 1 
	- NIYAKOHO VIDNOSHENIA do VIEW vono ne maye  		

	p i c ce objectyvni rechi, tobto vovy zavzhdy budut maty vyznachennyy neuron
	Ya dumayu my mayemo maty kilka gradientiv mixu p i c:
	p 100% c 0% frame view (perspective)
	p 0% c 100% frame view (perspective)
	p 50% c 50% frame view
	p 25% c 75%
	p 75% c 25% 
	etc.

	Odyn i toy samyy frame mozhe buty predstavlenyy bahatma perspektyvamy PRY ROZPIZNAVANI,
	i dostatnio maty odyn paratemer dlia cioho (lu_value v_vs_p)

	C rahuyetsia vidnosno poperednioho frame.
	Tobto potribno yak minimum 2 frame z shiftom shob maty C.
*/


///////////////////////////////////////////////////////////////////////////////
// Lu_S_Comp_View
//

	// can be v or p
	struct lu_s_comp_view {
		enum lu_s_comp_view_type view_type;

		lu_value 				orig_min;
		lu_value 				orig_max;
		lu_value 				max;

		lu_value 				step;
		lu_value*				steps;  		// preobchysleni kroky
		lu_size 				cells_size;

		// w x h x cells_size_i, empty by default
		Hnn_Cell_Value* cells;
	};

	static Lu_S_Comp_View lu_s_comp_view__init(Lu_S_Comp_Layer, Lu_Mem mem, lu_value min, lu_value max, lu_size cells_size);
	static void lu_s_comp_view__deinit(Lu_S_Comp_Layer self);

	static inline lu_value lu_s_comp_view__norm(Lu_S_Comp_Layer self, lu_value request);
	static inline lu_size lu_s_comp_view__ix(Lu_S_Comp_Layer self, lu_value val);
	static inline struct lu_size_range lu_s_comp_view__ix_range(Lu_S_Comp_Layer self, lu_value val, lu_size nsc);
	static inline lu_value lu_s_comp_view__calc_sig(Lu_S_Comp_Layer self, lu_size val_step_i, lu_value val);
	static inline lu_value lu_s_comp_view__step_norm_dist(Lu_S_Comp_Layer self);


///////////////////////////////////////////////////////////////////////////////
// Layers
//

	//
	// Base
	//

	struct lu_s_layer_base {
		enum lu_s_layer_type type;
		lu_size level;

		Lu_S_Layer_Base parent;
	};

	static inline Lu_S_Layer_Base lu_s_layer_base__init(
		Lu_S_Layer_Base self, 
		enum lu_s_layer_type type, 
		lu_size level,
		Lu_S_Layer_Base parent
	)
	{
		lu__assert(self);
		lu__assert(type < LU_S_LT_END);

		self->type = type;
		self->level = level;
		self->parent = parent;

		return self;
	}

	//
	// Lu_S_Comp_Layer 
	// 

	struct lu_s_comp_layer {
		struct lu_s_layer_base super;

		struct lu_s_comp_view v_view;
		struct lu_s_comp_view p_view;
	};

	static Lu_S_Comp_Layer lu_s_comp_layer__create(Lu_Mem mem, Lu_S_Frame_Layer frame);
	static void lu_s_comp_layer__destroy(Lu_S_Comp_Layer self, Lu_Mem);

	//
	// Lu_S_Frame_Layer
	//

	struct lu_s_frame_layer {
		struct lu_s_layer_base super;

		Lu_Rec rec;

		struct lu_list children;
		// n_table
	};

	static inline Lu_S_Frame_Layer lu_s_frame_layer__init(
		Lu_S_Frame_Layer self, 
		Lu_Mem mem
	)
	{
		lu__assert(self);
		lu__assert(mem);

		lu_list__init(&self->children, mem);

		return self;
	}

	static Lu_S_Frame_Layer lu_s_frame_layer__create(Lu_Mem mem, Lu_Rec rec);
	static void lu_s_frame_layer__destroy(Lu_S_Frame_Layer self, Lu_Mem mem);

	//
	// Lu_S_Layer
	//

	struct lu_s_layer {
		struct lu_s_layer_base super;

		Lu_S_Layer_Base child;

		// n_table
	};

	static Lu_S_Layer lu_s_layer__create(
		Lu_Mem mem,
		enum lu_s_layer_type type, 
		lu_size level,
		Lu_S_Layer_Base parent,
		Lu_S_Layer_Base child
	);

	static void lu_s_layer__destroy(Lu_S_Layer self, Lu_Mem);

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
// Lu_Space_Config 
//

	static inline Lu_Space_Config lu_space_config__validate(Lu_Space_Config self)
	{
		lu__assert(self->frames_size >= 256);
		lu__assert(self->apexes_size >= 256);

		return self;
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_S
//

	struct lu_s {

		struct lu_space_config config;

		Lu_Mem 					mem;
		Lu_S_Layer_Mem  		cell_mem;

		Lu_Arr 					frames;
		Lu_Arr 					apexes;

	};
	
	static Lu_S lu_s__create(Lu_Mem mem, struct lu_space_config config, Lu_Arr lu_recs);
	static void lu_s__destroy(Lu_S self);

	static void lu_s__add_rec(Lu_S self, Lu_Rec rec);
	static void lu_s__add_layer(Lu_S self, lu_size level);
	#define lu_s__add_seq(self) lu_s__add_layer(self, 0)
	#define lu_s__add_event(self) lu_s__add_layer(self, 1)
	#define lu_s__add_chapter(self) lu_s__add_layer(self, 2)
	#define lu_s__add_story(self) lu_s__add_layer(self, 3)



	static void lu_s__print_info(Lu_S self);

