/**
	Copyright © 2022 Oleh Ihorovych Novosad 

	Map:													
		(x Y y) = max(x - 1, 1) * max(y - 1, 1)


		"Minimal" start:

		Last level should always have ONE layer.

		4 level3, story(vertically 1-n4)
		3 level2, scene(vertically 1-n3)
		2 level1, event (vertically 1-n2)
		1 layer seq (vertically 1-n1)
		0 layer recs (vertically rec_count)
			1 frame layers (vertically w Y h), base layer is frame layer
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
// Lu_S_View_Comp
//

	// can be v or p
	struct lu_s_view_comp {
		enum lu_s_view_comp_type view_type;

		lu_value 				orig_min;
		lu_value 				orig_max;
		lu_value 				max;

		lu_value 				step;
		lu_value*				steps;  		// preobchysleni kroky
		lu_size 				cells_size;

		// w x h x cells_size_i, empty by default
		Hnn_Cell_Value* cells;
	};

	static Lu_S_View_Comp lu_s_view_comp__init(Lu_S_Layer_Comp, Lu_Mem mem, lu_value min, lu_value max, lu_size cells_size);
	static void lu_s_view_comp__deinit(Lu_S_Layer_Comp self);

	static inline lu_value lu_s_view_comp__norm(Lu_S_Layer_Comp self, lu_value request);
	static inline lu_size lu_s_view_comp__ix(Lu_S_Layer_Comp self, lu_value val);
	static inline struct lu_size_range lu_s_view_comp__ix_range(Lu_S_Layer_Comp self, lu_value val, lu_size nsc);
	static inline lu_value lu_s_view_comp__calc_sig(Lu_S_Layer_Comp self, lu_size val_step_i, lu_value val);
	static inline lu_value lu_s_view_comp__step_norm_dist(Lu_S_Layer_Comp self);

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
	static void lu_s_layer_base__recursive_destroy(Lu_S_Layer_Base layer, Lu_Mem mem);

	//
	// Lu_S_Layer_Comp 
	// 

	struct lu_s_layer_comp {
		struct lu_s_layer_base super;

		struct lu_s_view_comp v_view;
		struct lu_s_view_comp p_view;
	};

	static Lu_S_Layer_Comp lu_s_layer_comp__create(Lu_Mem mem, Lu_S_Layer_Frame frame, Lu_Rec_Comp_Config config);
	static void lu_s_layer_comp__destroy(Lu_S_Layer_Base self, Lu_Mem);

	//
	// Lu_S_Layer_Frame
	//

	struct lu_s_layer_frame {
		struct lu_s_layer_base super;

		Lu_Rec rec;
	};

	static Lu_S_Layer_Frame lu_s_layer_frame__create(Lu_Mem mem, Lu_Rec rec);
	static void lu_s_layer_frame__destroy(Lu_S_Layer_Base self, Lu_Mem mem);

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
// Maps
//

	struct lu_s_map_base {

		enum lu_s_map_type type;

		Lu_Mem mem;

		Lu_Arr apexes;
		Lu_Arr bases;

		Lu_S_Map_Base p;
		Lu_Slot_Base c;

		// virtual destructor
		void (*destroy)(Lu_S_Map_Base);
	};

	static Lu_S_Map_Base lu_s_map_base__init(
		Lu_S_Map_Base self,
		Lu_Mem mem, 
		enum lu_s_map_type type, 
		lu_size apexes_size,
		lu_size bases_size, 
		Lu_S_Map_Base p,
		void (*destroy)(Lu_S_Map_Base)
	);

	static Lu_S_Map_Base lu_s_map_base__init_with_childs(
		Lu_S_Map_Base self,
		Lu_Mem mem, 
		enum lu_s_map_type type, 
		lu_size apexes_size,
		lu_size bases_size, 
		Lu_S_Map_Base p, 
		lu_size childs_size,
		void (*destroy)(Lu_S_Map_Base)
	);

	static void lu_s_map_base__destroy(Lu_S_Map_Base);

	static Lu_S_Layer_Base lu_s_map_base__get_base(Lu_S_Map_Base self);
	static Lu_S_Layer_Base lu_s_map_base__get_apex(Lu_S_Map_Base self);
	static Lu_S_Layer_Frame lu_s_map_base__get_frame(Lu_S_Map_Base self);

	static void lu_s_map_base__connect(Lu_S_Map_Base p, Lu_S_Map_Base c);
	static void lu_s_map_base__recursive_destroy(Lu_S_Map_Base self);

	//
	// Fractals
	//

	static void lu_s_map_base__make_story_fractal(Lu_S_Map_Base self, lu_size recs_layers_size);
	static void lu_s_map_base__make_frame_fractal(Lu_S_Map_Base self, Lu_Rec rec);
	static void lu_s_map_base__unmake_fractal(Lu_S_Map_Base);

	//
	// Story
	//

	struct lu_s_map_story {
		struct lu_s_map_base super;

		lu_size recs_count;
	};

	static Lu_S_Map_Story lu_s_map_story__create(Lu_Mem, lu_size recs_size); 
	static void lu_s_map_story__destroy(Lu_S_Map_Base self);

	//
	// Frame
	//

	struct lu_s_map_frame {
		struct lu_s_map_base super;

		Lu_Rec rec;
	};

	static Lu_S_Map_Frame lu_s_map_frame__create(Lu_Mem, Lu_Rec, Lu_S_Map_Base p);
	static void lu_s_map_frame__destroy(Lu_S_Map_Base self);

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

		Lu_Mem mem;
		Lu_Arr frames;

		Lu_S_Map_Base fractal;

	};

	//
	// (x Y y) = max(max(x - 1, 1) * max(y - 1, 1) - 1, 1)
	// This calculation is only correct for "intersected squares cortex" type or similar 
	// 
	static inline lu_size lu_s__Y(lu_size w, lu_size h)
	{
		lu__assert(w);
		lu__assert(h);

		if (w > 1) --w;
		if (h > 1) --h;

		lu_size Y = w * h;

		// minus one because apex is in the base layer of the next level
		// Highest level should always have one layer.
		if (Y > 1) --Y;

		return Y;
	}

	//
	// S
	//
	
	static Lu_S lu_s__create_intersected_squares_cortex(Lu_Mem mem, struct lu_space_config config, Lu_Arr lu_recs);
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
	static void lu_s__create_component_fractal(Lu_Mem mem, Lu_S_Layer_Frame p, Lu_Arr apexes, Lu_Rec rec);

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

