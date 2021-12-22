/**
	Copyright © 2022 Oleh Ihorovych Novosad 

	Map:													
		(x Y y) = max(x - 1, 1) * max(y - 1, 1)


		"Minimal" start:

		4 level3, story(vertically 1-n4)
		3 level2, scene(vertically 1-n3)
		2 level1, event (vertically 1-n2)
		1 layer seq (vertically 1-n1)
		0 layer recs (vertically rec_count)
			2 layer rixels (vertically w Y h)
			1 rixels FRAME (1)
			0 comp1 comp2 comp3 (horizontally comp_count or d)

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

		Lu_S_Layer_Base p;
		Lu_Slot_Base c;

		// n_table

		// virtual destructor
		void (*destroy)(Lu_S_Layer_Base, Lu_Mem);
	};

	static inline Lu_S_Layer_Base lu_s_layer_base__init_with_no_c_slot(
		Lu_S_Layer_Base self, 
		enum lu_s_layer_type type, 
		lu_size level,
		Lu_S_Layer_Base p,
		void (*destroy)(Lu_S_Layer_Base, Lu_Mem)
	);

	static inline Lu_S_Layer_Base lu_s_layer_base__init_with_one_c_slot(
		Lu_S_Layer_Base self, 
		Lu_Mem mem,
		enum lu_s_layer_type type, 
		lu_size level,
		Lu_S_Layer_Base p,
		void (*destroy)(Lu_S_Layer_Base, Lu_Mem)
	);

	static inline Lu_S_Layer_Base lu_s_layer_base__init_with_arr_c_slot(
		Lu_S_Layer_Base self, 
		Lu_Mem mem,
		enum lu_s_layer_type type, 
		lu_size level,
		Lu_S_Layer_Base p,
		lu_size children_count,
		void (*destroy)(Lu_S_Layer_Base, Lu_Mem)
	);

	static inline void lu_s_layer_base__deinit(Lu_S_Layer_Base self, Lu_Mem mem);

	static void lu_s_layer_base__connect(Lu_S_Layer_Base p, Lu_S_Layer_Base c);

	//
	// Lu_S_Comp_Layer 
	// 

	struct lu_s_comp_layer {
		struct lu_s_layer_base super;

		struct lu_s_comp_view v_view;
		struct lu_s_comp_view p_view;
	};

	static Lu_S_Comp_Layer lu_s_comp_layer__create(Lu_Mem mem, Lu_S_Frame_Layer frame, Lu_Rec_Comp_Config config);
	static void lu_s_comp_layer__destroy(Lu_S_Layer_Base self, Lu_Mem);

	//
	// Lu_S_Frame_Layer
	//

	struct lu_s_frame_layer {
		struct lu_s_layer_base super;

		Lu_Rec rec;
	};

	static Lu_S_Frame_Layer lu_s_frame_layer__create(Lu_Mem mem, Lu_Rec rec);
	static void lu_s_frame_layer__destroy(Lu_S_Layer_Base self, Lu_Mem mem);

	//
	// Lu_S_Layer
	//

	struct lu_s_layer {
		struct lu_s_layer_base super;

		Lu_S_Layer_Base child;
	};

	static Lu_S_Layer lu_s_layer__create(Lu_Mem mem, lu_size level, lu_size children_count);
	static void lu_s_layer__destroy(Lu_S_Layer_Base self, Lu_Mem);


///////////////////////////////////////////////////////////////////////////////
// Lu_S_Map 
//

	struct lu_s_map {
		Lu_Mem mem;

		Lu_Arr apexes;
		Lu_Arr bases;

		Lu_S_Map p;
		Lu_Slot_Base c;
	};

	static Lu_S_Map lu_s_map__create_story_fractal_and_map(Lu_Mem);
	static Lu_S_Map lu_s_map__create_frame_fractal_and_map(Lu_Mem, Lu_Rec);
	static void lu_s_map__destroy(Lu_S_Map);

	static Lu_S_Layer_Base lu_s_map__get_base(Lu_S_Map self);
	static Lu_S_Layer_Base lu_s_map__get_apex(Lu_S_Map self);
	static Lu_S_Frame_Layer lu_s_map__get_frame(Lu_S_Map self);

	static void lu_s_map__connect(Lu_S_Map p, Lu_S_Map c);


///////////////////////////////////////////////////////////////////////////////
// Lu_Space_Config 
//

	#define LU_S_CONF__FRAMES_MIN_SIZE 256
	#define LU_S_CONF__APEXES_MIN_SIZE 256

	static inline Lu_Space_Config lu_space_config__validate(Lu_Space_Config self)
	{
		lu__user_assert(
			self->frames_size >= LU_S_CONF__FRAMES_MIN_SIZE, 
			"frames_size is too low in struct lu_space_config"
		);

		lu__user_assert(
			self->apexes_size >= LU_S_CONF__APEXES_MIN_SIZE, 
			"apexes_sixe is too low in struct lu_space_config"
		);

		return self;
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_S
//

	struct lu_s {

		struct lu_space_config config;

		Lu_Mem 					mem;

		Lu_Arr 					frames;
		Lu_Arr 					apexes;

		Lu_S_Map fractal;

	};
	
	static Lu_S lu_s__create(Lu_Mem mem, struct lu_space_config config, Lu_Arr lu_recs);
	static void lu_s__destroy(Lu_S self);

	//
	// S Fractals
	//

	static void lu_s__create_story_fractal(Lu_Mem, Lu_S_Layer p, Lu_Arr apexes, Lu_Arr frames, Lu_Arr recs);
	static void lu_s__create_scene_fractal(Lu_Mem mem, Lu_S_Layer p, Lu_Arr apexes, Lu_Arr frames, Lu_Arr recs);
	static void lu_s__create_event_fractal(Lu_Mem mem, Lu_S_Layer p, Lu_Arr apexes, Lu_Arr frames, Lu_Arr recs);
	static void lu_s__create_seq_fractal(Lu_Mem mem, Lu_S_Layer p, Lu_Arr apexes, Lu_Arr frames, Lu_Arr recs);
	static void lu_s__create_rec_fractal(Lu_Mem mem, Lu_S_Layer p, Lu_Arr apexes, Lu_Arr frames, Lu_Arr recs);
	static void lu_s__create_frame_fractal(Lu_Mem mem, Lu_S_Layer p, Lu_Arr apexes, Lu_Arr frames, Lu_Rec rec);
	static void lu_s__create_component_fractal(Lu_Mem mem, Lu_S_Frame_Layer p, Lu_Arr apexes, Lu_Rec rec);

	static void lu_s__destroy_fractal(Lu_Mem, Lu_S_Layer_Base layer);

	//
	// 
	//

	static void lu_s__add_v_layer(Lu_S self, lu_size level);
	static void lu_s__add_h_layer(Lu_S self, lu_size level);

	static void lu_s__add_rixel_layer(Lu_S self, Lu_Rec rec);
	

	#define lu_s__add_seq(self) lu_s__add_v_layer(self, 0)
	#define lu_s__add_event(self) lu_s__add_v_layer(self, 1)
	#define lu_s__add_chapter(self) lu_s__add_v_layer(self, 2)
	#define lu_s__add_story(self) lu_s__add_v_layer(self, 3)



	static void lu_s__print_info(Lu_S self);

