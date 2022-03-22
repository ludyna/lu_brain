/**
	Copyright © 2022 Oleh Ihorovych Novosad 

	Map:													
		(x Y y) = max(x - 1, 1) * max(y - 1, 1)

 
		"Minimal" start:

		Last level should always have ONE layer.

		4 level3, story(vertically 1-n4)
		3 level2, scene(vertically 1-n3)
		2 level1, event (vertically 1-n2)
		1 layer seq (vertically 1-n1) (de n1 ce kilkist kadrykiv v sequence)
		0 layer frames (vertically rec_count) (t1, t2, etc. nema v S, tilky virtnualno v N)
			1 PV rec layers (vertically w Y h) base layer is rec layer, apex layer is "pixel" in frames
				0 P_comp1 P_comp2 P_comp3 (horizontally comp_count or d), connected to "pixel" in rec
				0 V_comp1 V_comp2 V_comp3 (horizontally comp_count or d), connected to "pixel" in rec

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
// Lu_S_View_P
//

	struct lu_s_view_p {
		enum lu_s_view_p_type view_type;

		struct lu_comp_calc comp_calc;

		Lu_N_Table_Comp n_comp_table;
		Lu_Arr w_tables;
	};

	static Lu_S_View_P lu_s_view_p__init(
		Lu_S_View_P, 
		Lu_Config config, 
		enum lu_s_view_p_type view_type,
		lu_size width, 
		lu_size height, 
		lu_value min, 
		lu_value max, 
		lu_size cells_size
	);
	
	static void lu_s_view_p__deinit(Lu_S_View_P self);

	static void lu_s_view_p__register(Lu_S_View_P self, lu_size z, Lu_Data data, lu_size wave_id);

	static Lu_W_Table_P lu_s_view_p__get_w_table(Lu_S_View_P self, lu_size wave_id);

///////////////////////////////////////////////////////////////////////////////
// Lu_S_View_V
//

	struct lu_s_view_v {
		enum lu_s_view_p_type view_type;

		struct lu_comp_calc comp_calc;

		Lu_N_Table_Comp n_comp_table;
		Lu_Arr w_tables;
	};

	static Lu_S_View_V lu_s_view_v__init(
		Lu_S_View_V, 
		Lu_Config config, 
		enum lu_s_view_p_type view_type,
		lu_size width, 
		lu_size height, 
		lu_value min, 
		lu_value max, 
		lu_size cells_size
	);
	
	static void lu_s_view_v__deinit(Lu_S_View_V self);

	static Lu_W_Table_V lu_s_view_v__get_w_table(Lu_S_View_V self, lu_size wave_id);

	
///////////////////////////////////////////////////////////////////////////////
// Lu_S_Layer_Base
//

	struct lu_s_layer_base {
		enum lu_s_layer_type type;
		lu_size level;

		Lu_Mem s_mem;

		Lu_S_Layer_Base p;
		Lu_Slot_Base c;

		Lu_N_Table n_table;
		Lu_Arr w_tables;

		// virtual destructor
		void (*destroy)(Lu_S_Layer_Base);
	};

	static inline Lu_S_Layer_Base lu_s_layer_base__init(
		Lu_S_Layer_Base self, 
		Lu_S_Layer_Base p,
		Lu_Config config,
		enum lu_s_layer_type type,
		lu_size level,
		void (*destroy)(Lu_S_Layer_Base)
	);

	static inline Lu_S_Layer_Base lu_s_layer_base__init_with_one_c_slot(
		Lu_S_Layer_Base self, 
		Lu_S_Layer_Base p,
		Lu_Config config,
		enum lu_s_layer_type type,
		lu_size level,
		void (*destroy)(Lu_S_Layer_Base)
	);

	static inline Lu_S_Layer_Base lu_s_layer_base__init_with_arr_c_slot(
		Lu_S_Layer_Base self, 
		Lu_S_Layer_Base p,
		lu_size children_count,
		Lu_Config config,
		enum lu_s_layer_type type,
		lu_size level,
		void (*destroy)(Lu_S_Layer_Base)
	);

	static inline void lu_s_layer_base__deinit(Lu_S_Layer_Base self);

	static void lu_s_layer_base__connect(Lu_S_Layer_Base p, Lu_S_Layer_Base c);
	static void lu_s_layer_base__recursive_destroy(Lu_S_Layer_Base layer);

	static void lu_s_layer_base__create_n_table(
		Lu_S_Layer_Base self, 
		Lu_Mem n_mem, 
		lu_size size_in_cells, 
		lu_byte cell_type
	);

	static void lu_s_layer_base__destroy_n_table(Lu_S_Layer_Base self);

	static inline Lu_W_Table lu_s_layer_base__get_w_table(Lu_S_Layer_Base self, lu_size wave_id)
	{
		lu__debug_assert(self);
		lu__debug_assert(self->w_tables);
		lu__debug_assert(wave_id < lu_arr__size(self->w_tables));

		return lu_arr__get(self->w_tables, wave_id);
	}

///////////////////////////////////////////////////////////////////////////////
// Layers
//

	//
	// Lu_S_Layer_Comp 
	//

	struct lu_s_layer_comp {
		struct lu_s_layer_base super;

		struct lu_s_view_p p_view;
		struct lu_s_view_v v_view;
	};

	static Lu_S_Layer_Comp lu_s_layer_comp__create(Lu_Config config, Lu_S_Layer_Rec frame, Lu_Rec_Comp_Config rc_config);
	static void lu_s_layer_comp__destroy(Lu_S_Layer_Base self);

	//
	// Lu_S_Layer_Rec
	//

	struct lu_s_layer_rec {
		struct lu_s_layer_base super;

		Lu_Rec rec;
	};

	static Lu_S_Layer_Rec lu_s_layer_rec__create(Lu_Config config, Lu_Rec rec);
	static void lu_s_layer_rec__destroy(Lu_S_Layer_Base self);

	static void lu_s_layer_rec__save_data(
		Lu_S_Layer_Rec self, 
		Lu_Wave wave, 
		lu_size rec_id, 
		Lu_Data data,
		Lu_Process_Config config
	);

	//
	// Lu_S_Layer
	//

	struct lu_s_layer {
		struct lu_s_layer_base super;


		Lu_S_Layer_Base child;
	};

	static Lu_S_Layer lu_s_layer__create(Lu_Config config, lu_size level, lu_size children_count);
	static void lu_s_layer__destroy(Lu_S_Layer_Base self);


///////////////////////////////////////////////////////////////////////////////
// Maps
//

	struct lu_s_map_base {

		enum lu_s_map_type type;

		Lu_Config config;

		Lu_Arr apexes;
		Lu_Arr bases;

		Lu_S_Map_Base p;
		Lu_Slot_Base c;

		// virtual destructor
		void (*destroy)(Lu_S_Map_Base);
	};

	static Lu_S_Map_Base lu_s_map_base__init(
		Lu_S_Map_Base self,
		enum lu_s_map_type type, 
		Lu_Config config,
		Lu_S_Map_Base p,
		void (*destroy)(Lu_S_Map_Base)
	);

	static Lu_S_Map_Base lu_s_map_base__init_with_childs(
		Lu_S_Map_Base self,
		enum lu_s_map_type type, 
		Lu_Config config,
		Lu_S_Map_Base p, 
		lu_size childs_size,
		void (*destroy)(Lu_S_Map_Base)
	);

	static void lu_s_map_base__destroy(Lu_S_Map_Base);

	static Lu_S_Layer_Base lu_s_map_base__get_base(Lu_S_Map_Base self);
	static Lu_S_Layer_Base lu_s_map_base__get_apex(Lu_S_Map_Base self);
	static Lu_S_Layer_Rec lu_s_map_base__get_frame(Lu_S_Map_Base self);

	static void lu_s_map_base__connect(Lu_S_Map_Base p, Lu_S_Map_Base c);
	static void lu_s_map_base__recursive_destroy(Lu_S_Map_Base self);

	//
	// Fractals
	//

	static void lu_s_map_base__make_story_fractal(Lu_S_Map_Base self, lu_size recs_layers_size);
	static void lu_s_map_base__make_rec_fractal(Lu_S_Map_Base self, Lu_Rec rec);
	static void lu_s_map_base__unmake_fractal(Lu_S_Map_Base);

	//
	// Story
	//

	struct lu_s_map_story {
		struct lu_s_map_base super;

		lu_size recs_count;
	};

	static Lu_S_Map_Story lu_s_map_story__create(lu_size recs_size, Lu_Config config); 
	static void lu_s_map_story__destroy(Lu_S_Map_Base self);

	//
	// Frame
	//

	struct lu_s_map_frame {
		struct lu_s_map_base super;

		Lu_Rec rec;
	};

	static Lu_S_Map_Frame lu_s_map_frame__create(Lu_Rec, Lu_S_Map_Base p, Lu_Config config);
	static void lu_s_map_frame__destroy(Lu_S_Map_Base self);


///////////////////////////////////////////////////////////////////////////////
// Lu_S
//

	struct lu_s {

		Lu_Config config;
		
		Lu_Arr v_recs;
		Lu_Arr p_recs;

		Lu_S_Map_Base fractal;

	};

	//
	// Utility
	//

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
	// Properties
	//

	static inline Lu_S_Layer_Rec lu_s__get_v_rec(Lu_S self, lu_size rec_id)
	{
		lu__assert(self);
		lu__assert(self->v_recs);

		return (Lu_S_Layer_Rec) lu_arr__get(self->v_recs, rec_id);
	}

	//
	// Create and destroy
	//
	
	static Lu_S lu_s__create_intersected_squares_cortex(
		Lu_Config config, 
		Lu_Arr lu_recs
	);

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
	static void lu_s__create_component_fractal(Lu_Mem mem, Lu_S_Layer_Rec p, Lu_Arr apexes, Lu_Rec rec);

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

	//
	//
	// 

	static void lu_s__print_info(Lu_S self);

	//
	//
	//

	static void lu_s__save_data(Lu_S self, Lu_Wave wave, lu_size rec_id, Lu_Data data, Lu_Process_Config);