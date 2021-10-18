/**
	Copyright © 2021 Oleh Ihorovych Novosad 

	Map:
		comp (d) 
			comp_cell component_v x n(cells_size_i, empty by default) ==>
			comp_cell component_p x n(cells_size_i, empty by default) ==> 

			pixel_nx (w Y h)
				pixel (w - 1 Y h - 1)
					...
						rec_nx (recs_count Y t)
							rec(recs_count - 1 Y t - 1)
								...
									seq_nx (seq_count)
										seq(seq_count - 1)
											...
												event_nx (event_count)
													event_nx (event_count - 1)
														...
															scene_nx (chapter_count)
																..
																	story_nx (story_count)

														

	(x Y y) = max(x - 1, 1) * max(y - 1, 1)


	"Minimal" start:

	level3, story(1)
	level2, scene(1)
	level1, event (1)
	seq (1)
	rec (rec_count)
	pixel(w Y h)
	comp1 comp2 comp3


	r1 r2 r3 r4
	r1 r2 r3 r4
	r1 r2 r3 r4

	r1 r2 r3 r4

	
	Koly my dobavliayemo novyy sequence to my mozhemo chy ce novyy event, chy ce nova scena 
	Faktychno sequence ce zavzhdy vyznacheno. Novi rivni poza seq ce vhe problemy avtora (programista).
	Vin maye maty mozhlyvist dobavliaty yih stilky skilky zahoche i nazyvaty yih yak zahoche 
	(slova, rechenia, abzacy, storinky i td).
	Yaksho programist kazhe startuyem novyy level3, ce ozanachaye avtomatychno novyy level 2 and level 1.
*/

///////////////////////////////////////////////////////////////////////////////
// Slots
//

	struct lu_s_slot_1 {
		Lu_S_Cell_Base one;
	};

	struct lu_s_slot_4 {
		Lu_S_Cell_Base one;
		Lu_S_Cell_Base two;
		Lu_S_Cell_Base three;
		Lu_S_Cell_Base four;
	};

	struct lu_s_slot_2 {
		Lu_S_Cell_Base one;
		Lu_S_Cell_Base two;
	};

	//
	// Slot inits
	//

	static inline Lu_S_Slot_1 lu_s_slot_1__init(Lu_S_Slot_1 self) 
	{
		self->one = NULL;
		return self;
	}

	static inline Lu_S_Slot_2 lu_s_slot_2__init(Lu_S_Slot_2 self) 
	{
		self->one = NULL;
		self->two = NULL;
		return self;
	} 

	static inline Lu_S_Slot_4 lu_s_slot_4__init(Lu_S_Slot_4 self) 
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

	struct lu_s_cell_base {
		enum lu_s_cell_type type;			

		// for S and W it is always one parent
		struct lu_s_slot_1 p; 
	}; 

	struct lu_s_cell_2 {
		struct lu_s_cell_base super;

		struct lu_s_slot_2 c;
	};

	// struct lu_s_cell_4 {
	// 	struct lu_s_cell_base super;

	// 	struct lu_s_slot_2
	// }

	// can be v or p
	struct lu_s_comp_cell {
		struct lu_s_cell_base super;

		lu_value 				orig_min;
		lu_value 				orig_max;
		lu_value 				max;

		lu_value 				step;
		lu_value*				steps;  		// preobchysleni kroky
		lu_size 				cells_size;

		// w x h x cells_size_i, empty by default
		Hnn_Cell_Value* cells;
	};

	static Lu_S_Comp_Cell lu_s_comp_cell__init(Lu_S_Comp_Cell, Lu_Mem mem, lu_value min, lu_value max, lu_size cells_size);
	static void lu_s_comp_cell__deinit(Lu_S_Comp_Cell self);

	static inline lu_value lu_s_comp_cell__norm(Lu_S_Comp_Cell self, lu_value request);
	static inline lu_size lu_s_comp_cell__ix(Lu_S_Comp_Cell self, lu_value val);
	static inline struct lu_size_range lu_s_comp_cell__ix_range(Lu_S_Comp_Cell self, lu_value val, lu_size nsc);
	static inline lu_value lu_s_comp_cell__calc_sig(Lu_S_Comp_Cell self, lu_size val_step_i, lu_value val);
	static inline lu_value lu_s_comp_cell__step_norm_dist(Lu_S_Comp_Cell self);


///////////////////////////////////////////////////////////////////////////////
// Lu_S_Cell_Mem
//
	struct lu_s_cell_mem_config {
		lu_size component_cells_size;

	};

	static inline Lu_S_Cell_Mem_Config lu_s_cell_mem_config__init(Lu_S_Cell_Mem_Config self)
	{
		lu__assert(self);

		self->component_cells_size = 0;


		return self;
	}

	static inline Lu_S_Cell_Mem_Config lu_s_cell_mem_config__validate(Lu_S_Cell_Mem_Config self)
	{
		lu__assert(self);

		lu__assert(self->component_cells_size > 0);

		return self;
	}

	struct lu_s_cell_mem {
		Lu_Mem mem;

		struct lu_s_cell_mem_config config;

		lu_size component_cells_count;
		struct lu_s_comp_cell* component_cells;


	};

	//
	// Create and Destroy
	// 

	static Lu_S_Cell_Mem lu_s_cell_mem__create(Lu_Mem mem, struct lu_s_cell_mem_config config);
	static void lu_s_cell_mem__destroy(Lu_S_Cell_Mem self);

	//
	// Allocate cells
	// 

	static void lu_s_cell_mem__alloc_cells(Lu_S_Cell_Mem self, struct lu_s_cell_mem_config config);

	// 
	// Print
	//

	static void lu_s_cell_mem__print_info(Lu_S_Cell_Mem self);

///////////////////////////////////////////////////////////////////////////////
// Lu_S_Layer
//

	struct lu_s_layer_base {

	};
 
	struct lu_s_layer {
		struct lu_s_layer_base super;
	};

///////////////////////////////////////////////////////////////////////////////
// Lu_S
//

	struct lu_s {

		Lu_Mem 					mem;
		Lu_S_Cell_Mem  			cell_mem;


		Lu_S_Layer 				top;
		Lu_S_Layer 				seq;

	};
	
	static Lu_S lu_s__create(Lu_Mem mem, Lu_Arr lu_recs);
	static void lu_s__destroy(Lu_S self);

	static void lu_s__add_layer(Lu_S self, lu_size level);
	
	#define lu_s__add_seq(self) lu_s__add_layer(self, 0)
	#define lu_s__add_event(self) lu_s__add_layer(self, 1)
	#define lu_s__add_chapter(self) lu_s__add_layer(self, 2)
	#define lu_s__add_story(self) lu_s__add_layer(self, 3)

	static void lu_s__add_rec(Lu_S self, Lu_Rec rec);

	static void lu_s__print_info(Lu_S self);

