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

		Lu_S_Table_Comp n_comp_table;
		Lu_Arr w_save_tables;
		Lu_Arr w_match_tables;
		Lu_Arr w_restore_data;
	};

	static Lu_S_View_P lu_s_view_p__init(
		Lu_S_View_P, 
		Lu_Config config, 
		enum lu_s_view_p_type view_type,
		lu_size width, 
		lu_size height, 
		lu_value min, 
		lu_value max, 
		lu_size cells_size,
		lu_size layer_ix,
		lu_size area_ix
	);
	
	static void lu_s_view_p__deinit(Lu_S_View_P self);

	static inline Lu_W_Table_P lu_s_view_p__get_w_save_table(Lu_S_View_P self, lu_size wave_ix)
	{
		lu__assert(self);
		lu__assert(self->w_save_tables);
		lu__assert(wave_ix < lu_arr__count(self->w_save_tables));

		return (Lu_W_Table_P) lu_arr__get(self->w_save_tables, wave_ix);
	}

	static inline Lu_W_Table_P lu_s_view_p__get_w_match_table(Lu_S_View_P self, lu_size wave_ix)
	{
		lu__assert(self);
		lu__assert(self->w_match_tables);
		lu__assert(wave_ix < lu_arr__count(self->w_match_tables));

		return (Lu_W_Table_P) lu_arr__get(self->w_match_tables, wave_ix);
	}

	static inline Lu_W_Table_P lu_s_view_p__get_w_table(Lu_S_View_P self, lu_size wave_ix, enum lu_wave_type wave_type)
	{
		lu__assert(self);

		switch(wave_type)
		{
			case LU_WAVE__SAVE:
				return lu_s_view_p__get_w_save_table(self, wave_ix);
				break;
			case LU_WAVE__MATCH:
				return lu_s_view_p__get_w_match_table(self, wave_ix);
				break;
			default:
				lu__assert(false);
		}

		return NULL;
	}

	static inline void lu_s_view_p__print_net_stats(Lu_S_View_P self)
	{
		
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_S_View_V
//

	struct lu_s_view_v {
		enum lu_s_view_p_type view_type;

		struct lu_comp_calc comp_calc;

		Lu_S_Table_Comp n_comp_table;
		Lu_Arr w_save_tables;
	};

	static Lu_S_View_V lu_s_view_v__init(
		Lu_S_View_V, 
		Lu_Config config, 
		enum lu_s_view_p_type view_type,
		lu_size width, 
		lu_size height, 
		lu_value min, 
		lu_value max, 
		lu_size cells_size,
		lu_size layer_ix,
		lu_size area_ix
	);
	
	static void lu_s_view_v__deinit(Lu_S_View_V self);


///////////////////////////////////////////////////////////////////////////////
// Lu_S_Layer_Base
//

	struct lu_s_layer_base {
		enum lu_s_layer_type type;
		enum lu_area_tag tag;
		lu_size layer_ix;
		lu_size area_ix;

		Lu_Mem s_mem;
		Lu_Mem n_mem;
		Lu_Mem w_mem;

		Lu_S_Layer_Base p;
		Lu_Slot_Base c;

		// virtual destructor
		void (*destroy)(Lu_S_Layer_Base);
	};

	//
	// Constructors / Destructors
	//
	static inline Lu_S_Layer_Base lu_s_layer_base__init(
		Lu_S_Layer_Base self, 
		Lu_S_Layer_Base p,
		Lu_Config config,
		enum lu_s_layer_type type,
		lu_size layer_ix,
		lu_size area_ix,
		void (*destroy)(Lu_S_Layer_Base),
		enum lu_area_tag tag
	);

	static inline Lu_S_Layer_Base lu_s_layer_base__init_with_one_c_slot(
		Lu_S_Layer_Base self, 
		Lu_S_Layer_Base p,
		Lu_Config config,
		enum lu_s_layer_type type,
		lu_size layer_ix,
		lu_size area_ix,
		void (*destroy)(Lu_S_Layer_Base),
		enum lu_area_tag tag
	);

	static inline Lu_S_Layer_Base lu_s_layer_base__init_with_arr_c_slot(
		Lu_S_Layer_Base self, 
		Lu_S_Layer_Base p,
		lu_size children_count,
		Lu_Config config,
		enum lu_s_layer_type type,
		lu_size layer_ix,
		lu_size area_ix,
		void (*destroy)(Lu_S_Layer_Base),
		enum lu_area_tag tag
	);

	static inline void lu_s_layer_base__deinit(Lu_S_Layer_Base self);

	//
	// Is
	//

	static inline lu_bool lu_s_layer_base__is_n_cell_layer(Lu_S_Layer_Base self)
	{
		// LU_S_LAYER__REC is also LU_S_LAYER__LAYER
		return self->type == LU_S_LAYER__LAYER || self->type == LU_S_LAYER__REC;
	}

	//
	// Methosd
	//

	static void lu_s_layer_base__connect(Lu_S_Layer_Base p, Lu_S_Layer_Base c);
	static void lu_s_layer_base__recursive_destroy(Lu_S_Layer_Base layer);

	static void lu_s_layer_base__create_s_table(
		Lu_S_Layer_Base self, 
		Lu_Mem n_mem, 
		lu_size size_in_cells, 
		lu_byte cell_type
	);

	static void lu_s_layer_base__destroy_s_table(Lu_S_Layer_Base self);

	static inline enum lu_s_layer_type lu_s_layer_base__get_type(Lu_S_Layer_Base self)
	{
		lu__debug_assert(self);

		return self->type;
	}

	static inline void lu_s_layer_base__print(Lu_S_Layer_Base self)
	{
		char buffer[50];
		lu_s_layer_type__to_str(self->type, buffer);
		lu__debug("\n 		layer_ix: %d, type: %s", self->layer_ix, buffer);
	}

	static inline void lu_s_layer_base__print_basic_info(Lu_S_Layer_Base self)
	{
		lu__assert(self);

		char type[50];
		char tag[50];

		lu_s_layer_type__to_str(self->type, type);
		lu_area_tag__to_str(self->tag, tag);

		lu__debug("%s:%s A=%ld, L=%ld", tag, type, self->area_ix, self->layer_ix);
	}

	static inline void lu_s_layer_base__print_net_stats(Lu_S_Layer_Base self, Lu_S_Area_Net_Stats area_ns)
	{
		lu__debug("\n\t");
		lu_s_layer_base__print_basic_info(self);
	}

	static inline void lu_s_layer_base__get_net_stats(Lu_S_Layer_Base self, Lu_S_Area_Net_Stats area_ns)
	{

	}

///////////////////////////////////////////////////////////////////////////////
// Lu_S_Layer_Comp
//

	struct lu_s_layer_comp {
		struct lu_s_layer_base super;

		struct lu_s_view_p p_view;
		struct lu_s_view_v v_view;
	};

	//
	// Constructors / Destructors
	//

	static Lu_S_Layer_Comp lu_s_layer_comp__create(
		Lu_Config config, 
		Lu_S_Layer_Rec frame, 
		Lu_Rec_Comp_Config rc_config,
		lu_size layer_ix,
		lu_size area_ix
	);

	static void lu_s_layer_comp__destroy(Lu_S_Layer_Base self);

	//
	// Get
	//

	static inline Lu_Data lu_s_layer_comp__get_p_restore_data(Lu_S_Layer_Comp self, lu_size wave_ix)
	{
		lu__assert(self);

		return (Lu_Data) lu_arr__get(self->p_view.w_restore_data, wave_ix);
	}

	static inline void lu_s_layer_comp__get_net_stats(Lu_S_Layer_Comp self, Lu_S_Area_Net_Stats area_ns)
	{
		lu_s_layer_base__print_net_stats(&self->super, area_ns);
		lu_s_layer_base__get_net_stats(&self->super, area_ns);
	}

	//
	// Methods
	//

	static inline void lu_s_layer_comp__print_net_stats(Lu_S_Layer_Comp self, Lu_S_Area_Net_Stats area_ns)
	{
		lu_s_layer_base__print_net_stats(&self->super, area_ns);

		// struct lu_s_layer_net_stats layer_ns;

		// lu_s_layer_net_stats__reset(&layer_ns);

		// lu_s_table__print_net_stats(&self->s_table, &layer_ns);

		// lu_s_area_net_stats__collect(area_ns, &layer_ns);
	}

	static inline void lu_s_layer_comp__find_n_cell_and_s_column(
		Lu_S_Layer_Comp self, 
		union lu_n_addr addr, 
		Lu_N_Located_Cell located_cell
	)
	{ 
		// 
		Lu_S_Column_Comp s_column_comp = lu_s_table_comp__get_column_by_ix(self->p_view.n_comp_table, addr.column_ix);

		located_cell->n_cell_type = LU_N_CELL__VP;
		located_cell->s_column_comp = s_column_comp;
		located_cell->s_layer_comp = self;

		lu_s_column_comp__find_n_cell(s_column_comp, addr, &located_cell->n_cell_vp);
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_S_Layer
//

	struct lu_s_layer {
		struct lu_s_layer_base super;

		struct lu_s_table s_table;
		Lu_Arr w_save_tables;
	};

	//
	// Constructors / Destructors
	//

	static Lu_S_Layer lu_s_layer__init(
		Lu_S_Layer self, 
		Lu_Config config, 
		enum lu_s_layer_type type,
		lu_size layer_ix, 
		lu_size area_ix,
		lu_size children_count,
		void (*destroy)(Lu_S_Layer_Base),
		lu_size n_w,
		lu_size n_h,
		lu_size n_h_max,
		enum lu_area_tag tag
	);

	static void lu_s_layer__deinit(Lu_S_Layer self);

	static Lu_S_Layer lu_s_layer__create(
		Lu_Config config, 
		lu_size layer_ix, 
		lu_size area_ix,
		lu_size children_count,
		lu_size n_w,
		lu_size n_h,
		lu_size n_h_max,
		enum lu_area_tag tag
	);
	static void lu_s_layer__destroy(Lu_S_Layer_Base self);

	//
	// Get
	//

	static inline lu_size lu_s_layer__get_layer_ix(Lu_S_Layer self)
	{
		return self->super.layer_ix;
	} 

	static inline lu_size lu_s_layer__get_area_ix(Lu_S_Layer self)
	{
		return self->super.area_ix;
	}

	static inline enum lu_s_layer_type lu_s_layer__get_type(Lu_S_Layer self)
	{
		return self->super.type;
	}

	static inline enum lu_area_tag lu_s_layer__get_tag(Lu_S_Layer self)
	{
		return self->super.tag;
	}

	static inline Lu_S_Layer_Base lu_s_layer__get_parent_layer(Lu_S_Layer self)
	{
		lu__debug_assert(self);

		return self->super.p;
	}

	static inline Lu_S_Table lu_s_layer__get_s_table(Lu_S_Layer self)
	{
		lu__debug_assert(self);

		return &self->s_table;
	}

	static inline Lu_W_Table lu_s_layer__get_save_w_table(Lu_S_Layer self,  lu_size wave_ix)
	{
		lu__debug_assert(self);
		lu__debug_assert(self->w_save_tables);
		lu__debug_assert(wave_ix < lu_arr__count(self->w_save_tables));

		return lu_arr__get(self->w_save_tables, wave_ix);
	}

	static inline Lu_W_Table lu_s_layer__get_w_table(Lu_S_Layer self, enum lu_wave_type wave_type, lu_size wave_ix)
	{
		lu__debug_assert(self);
		lu__debug_assert(self->w_save_tables);

		switch(wave_type)
		{
			case LU_WAVE__SAVE:
				return lu_s_layer__get_save_w_table(self, wave_ix);
				break;
			case LU_WAVE__MATCH:
				lu__assert(false);
				break;
			default:
				lu__assert(false);
		}
	}

	static inline Lu_S_Layer lu_s_layer__get_parent(Lu_S_Layer self)
	{
		Lu_S_Layer_Base layer_base = self->super.p;
		lu__assert(layer_base->type == LU_S_LAYER__LAYER);

		return (Lu_S_Layer) layer_base;
	}

	static inline Lu_N_Cell lu_s_layer__get_n_cell(Lu_S_Layer self, union lu_n_addr n_addr)
	{
		return lu_s_table__get_n_cell(&self->s_table, n_addr);
	}

	//
	// Methods
	//


	static Lu_W_Table lu_s_layer__save(
		Lu_S_Layer self, 
		Lu_Save_Wave save_wave,
		struct lu_block_id block_id,
		Lu_W_Table prev_w_table,
		Lu_Save_Config config
	);

	static inline lu_bool lu_s_layer__expand(Lu_S_Layer self)
	{
		lu__assert(self);

		return lu_s_table__expand(&self->s_table);
	}

	static inline void lu_s_layer__find_n_cell_and_s_column(
		Lu_S_Layer self, 
		union lu_n_addr addr, 
		Lu_N_Located_Cell located_cell
	)
	{
		Lu_S_Column s_column = lu_s_table__get_column_by_ix(&self->s_table, addr.column_ix);

		located_cell->n_cell_type = LU_N_CELL__N;
		located_cell->s_column = s_column;

		lu_s_column__find_n_cell(s_column, addr, &located_cell->n_cell);
	}

	static inline void lu_s_layer__print_basic_info(Lu_S_Layer self)
	{
		lu_s_layer_base__print_basic_info(&self->super);
	}

	static inline void lu_s_layer__print_net_stats(Lu_S_Layer self, Lu_S_Area_Net_Stats area_ns)
	{
		lu_s_layer_base__print_net_stats(&self->super, area_ns);

		struct lu_s_layer_net_stats layer_ns;

		lu_s_layer_net_stats__reset(&layer_ns);

		lu_s_table__print_net_stats(&self->s_table, &layer_ns);

		lu_s_area_net_stats__collect(area_ns, &layer_ns);
	}

	static inline void lu_s_layer__get_net_stats(Lu_S_Layer self, Lu_S_Area_Net_Stats area_ns)
	{
		lu_s_layer_base__print_net_stats(&self->super, area_ns);

		struct lu_s_layer_net_stats layer_ns;

		lu_s_layer_net_stats__reset(&layer_ns);

		lu_s_table__get_net_stats(&self->s_table, &layer_ns);

		lu_s_area_net_stats__collect(area_ns, &layer_ns);
	}


///////////////////////////////////////////////////////////////////////////////
// Lu_S_Layer_Rec
//

	struct lu_s_layer_rec {
		struct lu_s_layer super;

		Lu_Rec rec;

		struct lu_w_rec* save_w_recs;
		lu_size save_w_recs_size;

		struct lu_w_rec* match_w_recs; 
		lu_size match_w_recs_size;
		
		// w_match_tables are needed to start match process, we don't need
		// w_match_tables in higher layers (Lu_S_Layer)
		Lu_Arr w_match_tables;
	};

	//
	// Costructors / Destructors
	//

	static Lu_S_Layer_Rec lu_s_layer_rec__create(Lu_Config config, Lu_Rec rec, lu_size layer_ix, lu_size area_ix);
	static void lu_s_layer_rec__destroy(Lu_S_Layer_Base self);

	//
	// Get
	//

	static inline Lu_W_Rec lu_s_layer_rec__get_save_w_rec(Lu_S_Layer_Rec self, lu_size wave_ix)
	{
		lu__assert(self);
		lu__assert(wave_ix < self->save_w_recs_size);

		return &self->save_w_recs[wave_ix];
	}

	static inline Lu_W_Rec lu_s_layer_rec__get_match_w_rec(Lu_S_Layer_Rec self, lu_size wave_ix)
	{
		lu__assert(self);
		lu__assert(wave_ix < self->match_w_recs_size);

		return &self->match_w_recs[wave_ix];
	}

	static inline Lu_W_Rec lu_s_layer_rec__get_w_rec(Lu_S_Layer_Rec self, lu_size wave_ix, enum lu_wave_type wave_type)
	{
		switch(wave_type)
		{
			case LU_WAVE__SAVE:
				return lu_s_layer_rec__get_save_w_rec(self, wave_ix);
				break;
			case LU_WAVE__MATCH:
				return lu_s_layer_rec__get_match_w_rec(self, wave_ix);
				break;
			default:
				lu__assert(false);
		}

		return NULL;
	}

	static inline Lu_S_Table lu_s_layer_rec__get_s_table(Lu_S_Layer_Rec self)
	{
		return &self->super.s_table;
	}

	static inline Lu_S_Layer_Base lu_s_layer_rec__get_parent(Lu_S_Layer_Rec self)
	{
		return self->super.super.p;
	}

	static inline Lu_S_Layer_Comp lu_s_layer_rec__get_layer_comp(Lu_S_Layer_Rec self, lu_size ix)
	{
		Lu_S_Layer_Base base = (Lu_S_Layer_Base) self;

		Lu_Slot_Base slot_base = base->c;
		lu__assert(slot_base);
		lu__assert(slot_base->type == LU_SLOT__ARR);

		Lu_Slot_Arr slot_arr = (Lu_Slot_Arr) slot_base;

		Lu_S_Layer_Comp comp = (Lu_S_Layer_Comp) lu_arr__get(slot_arr->items, ix);
		lu__assert(comp->super.type == LU_S_LAYER__COMP);

		return comp;
	}

	static inline Lu_W_Table lu_s_layer_rec__get_match_w_table(Lu_S_Layer_Rec self, lu_size wave_ix)
	{
		lu__assert(self);
		lu__assert(self->w_match_tables);
		lu__debug_assert(wave_ix < lu_arr__count(self->w_match_tables));

		return lu_arr__get(self->w_match_tables, wave_ix);
	}

	static inline Lu_W_Table lu_s_layer_rec__get_w_table(
		Lu_S_Layer_Rec self, 
		enum lu_wave_type wave_type, 
		lu_size wave_ix
	)
	{
		switch(wave_type)
		{
			case LU_WAVE__SAVE:
				return lu_s_layer__get_save_w_table(&self->super, wave_ix);
				break;
			case LU_WAVE__MATCH:
				return lu_s_layer_rec__get_match_w_table(self, wave_ix);
				break;
			default:
				lu__assert(false);
		}

		return NULL;
	}

	//
	// Methods
	// 

	static Lu_W_Table lu_s_layer_rec__save(
		Lu_S_Layer_Rec self, 
		Lu_Save_Wave save_wave,
		lu_size rec_id, 
		Lu_Data data,
		Lu_Save_Config config
	);

	static enum lu_w_rec_state lu_s_layer_rec__match(
		Lu_S_Layer_Rec self, 
		Lu_Match_Wave match_wave,
		lu_size rec_id, 
		Lu_Data data,
		Lu_Match_Config config,
		Lu_W_Match_Processor processor
	);

	static inline void lu_s_layer_rec__print_comp_w_tables(
		Lu_S_Layer_Rec self, 
		lu_size wave_ix, 
		enum lu_wave_type wave_type,
		lu_size src_start_z, 
		lu_size src_end_z
	)
	{
		Lu_S_Layer_Comp comp;
		Lu_S_View_P s_view_p;
		Lu_W_Table_P w_table_p;

		for (lu_size src_z = src_start_z; src_z < src_end_z; src_z++)
		{
			comp = lu_s_layer_rec__get_layer_comp(self, src_z);
			lu__assert(comp->super.type == LU_S_LAYER__COMP);

			s_view_p = &comp->p_view;

			w_table_p = lu_s_view_p__get_w_table(s_view_p, wave_ix, wave_type);
			lu__assert(w_table_p);

			lu_w_table_p__print(w_table_p);
		}
	}

	static inline void lu_s_layer_rec__print_net_stats(Lu_S_Layer_Rec self, Lu_S_Area_Net_Stats area_ns)
	{
		lu_s_layer__print_net_stats(&self->super, area_ns);
	}

	static inline void lu_s_layer_rec__get_net_stats(Lu_S_Layer_Rec self, Lu_S_Area_Net_Stats area_ns)
	{
		lu_s_layer__get_net_stats(&self->super, area_ns);
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_S_Area
//

	struct lu_s_area {
		enum lu_area_tag tag;
		Lu_Config config;
		lu_size area_ix;

		Lu_S_Layer_Base *layers;
		lu_size layers_size;
		lu_size layers_count;
	};

	//
	// Constructors / Destructors
	//

	static Lu_S_Area lu_s_area__create(Lu_Config config, lu_size area_ix, lu_size size, enum lu_area_tag tag);
	static void lu_s_area__destroy(Lu_S_Area self);

	//
	// Get
	//

	static inline Lu_W_Cell lu_s_area__get_w_cell_from_save_w_table(
		Lu_S_Area self, 
		lu_size wave_ix, 
		lu_size layer_ix, 
		lu_size x, 
		lu_size y
	)
	{
		lu__assert(self);
		lu__assert(layer_ix < self->layers_count);

		Lu_S_Layer_Base layer_base = self->layers[layer_ix];
		lu__assert(layer_base);

		// We can have access to Lu_W_Cell(s) in LU_S_LAYER__LAYER(s) only atm
		if (layer_base->type != LU_S_LAYER__LAYER) return NULL;

		Lu_S_Layer layer = (Lu_S_Layer) layer_base;

		lu__assert(lu_s_layer__get_layer_ix(layer) == layer_ix);

		Lu_W_Table w_table = lu_s_layer__get_save_w_table(layer, wave_ix);
		lu__assert(w_table);

		return lu_w_table__get_w_cell(w_table, x, y);
	}

	static inline Lu_S_Layer_Base lu_s_area__get_last_layer(Lu_S_Area self)
	{
		if (self->layers_count == 0) return NULL;

		return self->layers[self->layers_count - 1];
	}

	static inline Lu_S_Layer_Base lu_s_area__get_layer_by_ix(Lu_S_Area self, lu_size layer_ix)
	{
		lu__assert(self);
		lu__assert(layer_ix < self->layers_count);

		return self->layers[layer_ix];
	}

	static inline Lu_N_Cell lu_s_area__get_n_cell(Lu_S_Area self, union lu_n_addr n_addr)
	{
		lu__assert(n_addr.layer_ix < self->layers_count);

		Lu_S_Layer_Base layer_base = self->layers[n_addr.layer_ix];

		lu__assert(layer_base->type == LU_S_LAYER__LAYER);

		Lu_S_Layer layer = (Lu_S_Layer) layer_base;

		return lu_s_layer__get_n_cell(layer, n_addr);
	}


	//
	// Methods
	//

	static inline Lu_S_Layer_Base lu_s_area__register_layer(Lu_S_Area self, Lu_S_Layer_Base layer)
	{
		lu__debug_assert(self);
		lu__debug_assert(layer);
		//lu__debug_assert(layers_count < layers_size);

		self->layers[self->layers_count] = (Lu_S_Layer_Base) layer;
		++self->layers_count;

		return layer;
	}
	
	static Lu_S_Layer_Comp lu_s_area__create_layer_comp(
		Lu_S_Area self, 
		Lu_S_Layer_Rec frame, 
		Lu_Rec_Comp_Config rc_config
	);

	static Lu_S_Layer lu_s_area__create_layer(
		Lu_S_Area self,  
		lu_size children_count,
		lu_size n_w,
		lu_size n_h,
		lu_size n_h_max
	);

	static Lu_S_Layer_Rec lu_s_area__create_layer_rec(Lu_S_Area self, Lu_Rec rec);

	static inline void lu_s_area__print(Lu_S_Area self, lu_bool short_version)
	{
		char buffer[50];
		lu_area_tag__to_str(self->tag, buffer);

		lu__debug("\n\tarea_ix: %d, tag: %s", self->area_ix, buffer);

		if (short_version) return;

		Lu_S_Layer_Base layer ;
		for (lu_size i = 0; i < self->layers_count; i++)
		{
			layer = self->layers[i];

			if (layer == NULL) break;

			lu_s_layer_base__print_basic_info(layer);
		}
	}

	static inline void lu_s_area__print_net_stats(Lu_S_Area self, Lu_S_Net_Stats s_ns)
	{
		lu__assert(self);
		lu__assert(s_ns);

		char buffer[50];
		lu_area_tag__to_str(self->tag, buffer);

		lu__debug("\narea_ix: %d, tag: %s", self->area_ix, buffer);

		Lu_S_Layer_Base layer ;
		struct lu_s_area_net_stats area_ns;

		lu_s_area_net_stats__reset(&area_ns);

		for (lu_size i = 0; i < self->layers_count; i++)
		{
			layer = self->layers[i];

			if (layer == NULL) break;

			switch(layer->type)
			{
				case LU_S_LAYER__COMP:
					lu_s_layer_comp__print_net_stats((Lu_S_Layer_Comp) layer, &area_ns);
					break;
				case LU_S_LAYER__REC:
					lu_s_layer_rec__print_net_stats((Lu_S_Layer_Rec) layer, &area_ns);
					break;
				case LU_S_LAYER__LAYER:
					lu_s_layer__print_net_stats((Lu_S_Layer) layer, &area_ns);
					break;
				default:
					lu__assert(false);
			}
		}

		lu_s_net_stats__collect(s_ns, &area_ns);
	}

	static inline void lu_s_area__get_net_stats(Lu_S_Area self, Lu_S_Net_Stats s_ns)
	{
		lu__assert(self);
		lu__assert(s_ns);

		Lu_S_Layer_Base layer ;
		struct lu_s_area_net_stats area_ns;

		lu_s_area_net_stats__reset(&area_ns);

		for (lu_size i = 0; i < self->layers_count; i++)
		{
			layer = self->layers[i];

			if (layer == NULL) break;

			switch(layer->type)
			{
				case LU_S_LAYER__COMP:
					lu_s_layer_comp__get_net_stats((Lu_S_Layer_Comp) layer, &area_ns);
					break;
				case LU_S_LAYER__REC:
					lu_s_layer_rec__get_net_stats((Lu_S_Layer_Rec) layer, &area_ns);
					break;
				case LU_S_LAYER__LAYER:
					lu_s_layer__get_net_stats((Lu_S_Layer) layer, &area_ns);
					break;
				default:
					lu__assert(false);
			}
		}

		lu_s_net_stats__collect(s_ns, &area_ns);
	}

	static inline void lu_s_area__find_n_cell_and_s_column(
		Lu_S_Area self, 
		union lu_n_addr addr, 
		Lu_N_Located_Cell located_cell
	)
	{
		Lu_S_Layer_Base s_layer_base = lu_s_area__get_layer_by_ix(self, addr.layer_ix);

		switch (s_layer_base->type)
		{
			case LU_S_LAYER__LAYER:
			case LU_S_LAYER__REC:
				lu_s_layer__find_n_cell_and_s_column((Lu_S_Layer) s_layer_base, addr, located_cell);
				break;
			case LU_S_LAYER__COMP:
				lu_s_layer_comp__find_n_cell_and_s_column((Lu_S_Layer_Comp) s_layer_base, addr, located_cell);
				break;
			default:
				lu__assert(false);
		}

		
	}

	static lu_bool lu_s_area__expand(Lu_S_Area self);

	static Lu_W_Table lu_s_area__save_rec(
		Lu_S_Area self, 
		Lu_Save_Wave save_wave,
		lu_size rec_id, 
		Lu_Data data, 
		Lu_Save_Config config
	);

	static Lu_W_Table lu_s_area__save_frame(
		Lu_S_Area self, 
		Lu_Save_Wave save_wave, 
		struct lu_block_id block_id, 
		Lu_W_Table curr_w_table, 
		Lu_Save_Config config
	);

	static Lu_W_Table lu_s_area__save_seq(
		Lu_S_Area self, 
		Lu_Save_Wave save_wave,
		struct lu_block_id block_id, 
		Lu_W_Table curr_w_table, 
		Lu_Save_Config config
	);

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

	static void lu_s_map_base__make_story_fractal(Lu_S_Map_Base self, lu_size recs_layers_size, Lu_S s);
	static void lu_s_map_base__make_rec_fractal(Lu_S_Map_Base self, Lu_Rec rec, Lu_S s);
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

	// Maximum number of layers
	#define LU_S__LAYERS_SIZE (2^LU_N_LAYER_IX__SIZE)

	////
	// Space structure for memory fractals and space layers factory.
	// 
	struct lu_s {

		Lu_Config config;
		
		Lu_Arr v_recs;
		Lu_Arr p_recs;

		Lu_S_Map_Base fractal;

		Lu_S_Area* areas;
		lu_size areas_size;
		lu_size areas_count;

		Lu_S_Area* tag_to_area;
	};

	//
	// Get
	// 

	static inline Lu_S_Area lu_s__get_area(Lu_S self, lu_size area_ix)
	{
		lu__assert(self);
		lu__assert(area_ix < self->areas_count);

		return self->areas[area_ix];
	}

	static inline Lu_S_Layer_Rec lu_s__get_v_rec(Lu_S self, lu_size rec_id)
	{
		lu__assert(self);
		lu__assert(self->v_recs);

		return (Lu_S_Layer_Rec) lu_arr__get(self->v_recs, rec_id);
	}

	static inline Lu_W_Cell lu_s__get_w_cell_from_save_w_table( 
		Lu_S self, 
		lu_size wave_ix, 
		lu_size area_ix,
		lu_size layer_ix, 
		lu_size x, 
		lu_size y
	)
	{
		Lu_S_Area area = lu_s__get_area(self, area_ix);
		if (area == NULL) return NULL;

		return lu_s_area__get_w_cell_from_save_w_table(area, wave_ix, layer_ix, x, y);
	}

	struct lu_n_cell_info {

	};

	static inline Lu_N_Cell lu_s__get_n_cell(Lu_S self, union lu_n_addr n_addr)
	{
		Lu_S_Area area = lu_s__get_area(self, n_addr.area_ix);
		if (area == NULL) return NULL;

		return lu_s_area__get_n_cell(area, n_addr);
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
	// Lu_S Area Factory
	//

	static inline Lu_S_Area lu_s__create_area(Lu_S self, Lu_Config config, lu_size size, enum lu_area_tag tag);

	static inline Lu_S_Area lu_s__register_area(Lu_S self, Lu_S_Area area)
	{
		lu__debug_assert(self);
		lu__debug_assert(area);
		lu__debug_assert(self->areas_count < self->areas_size);

		self->areas[self->areas_count] = area;
		++self->areas_count;

		lu__assert(self->tag_to_area[area->tag] == NULL);

		self->tag_to_area[area->tag] = area;

		return area;
	}

	static inline Lu_S_Area lu_s__get_area_by_tag(Lu_S self, enum lu_area_tag tag)
	{
		lu__assert(self);

		return self->tag_to_area[tag];
	}

	//
	// Methods
	// 

	static void lu_s__print_info(Lu_S self);
	static void lu_s__print_areas(Lu_S self);
	static void lu_s__print_net_stats(Lu_S self);

	static inline void lu_s__find_n_cell_and_s_column(		
		Lu_S self,
		union lu_n_addr addr,
		Lu_N_Located_Cell located_cell
	)
	{
		Lu_S_Area s_area = lu_s__get_area(self, addr.area_ix);

		return lu_s_area__find_n_cell_and_s_column(s_area, addr, located_cell);
	}

	static void lu_s__get_net_stats(Lu_S self, Lu_Brain_Net_Stats b_ns)
	{
		lu__assert(self);

		Lu_S_Area area;
		struct lu_s_net_stats ns;

		lu_s_net_stats__reset(&ns);

		for (lu_size i = LU_N_AREA__SPECIAL_AREA_SKIP; i < self->areas_count; i++)
		{
			area = self->areas[i];

			if (area == NULL) break;

			lu_s_area__get_net_stats(area, &ns);
		}

		lu_brain_net_stats__collect(b_ns, &ns);
	}

