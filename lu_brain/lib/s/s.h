/**
	Copyright © 2021 Oleh Ihorovych Novosad 

	Map:

		story_nx_layer 
			story_nx_cell(1)

			seq_layer ...
				seq_cell (n-1) ...
				seq_nx_layer
					seq_nx_cell (n)



						rec_layer ...
							rec_cell (w - 1 x h - 1) ... 

						pixel_layer 
							pixel_cell (w x h) ==>  

							comp_layer
								comp_cell component_v (d) x n(w x h x cells_size_i, empty by default) ==>
								comp_cell component_p (d) x n(w x h x cells_size_i, empty by default) ==> 


	
	abstract_cell(1) (self expanding)
		abstract_cell (2)
			...
			story_cell (1) (self expanding)
				seq_cell (2)
					... 
					seq_cell (rec_count * self expanding)
						rec_cell 



	Stvoruvaty znyzu duzhe vazhko, i potrebuye dodatkovyh structur taki yak layery.
	Yaksho stvoruvaty zverhu, dostatnio prost komirok.

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

	struct lu_s_base_cell {
		enum lu_s_cell_type type;			

		// for S and W it is always one child
		struct lu_s_slot_1 c; 
	}; 

	// can be v or p
	struct lu_s_comp_cell {
		struct lu_s_base_cell super;

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
// Lu_M
//

	struct lu_m {

		Lu_Mem 					mem;
		Lu_S_Cell_Mem  			cell_mem;


	};
	
	static Lu_M lu_s__create(Lu_Mem mem, Lu_Arr lu_recs);
	static void lu_s__destroy(Lu_M self);

	static void lu_s__print_info(Lu_M self);
