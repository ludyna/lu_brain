/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Lu_Rec_Config

 	static Lu_Wave_Config lu_wave_config__init(Lu_Wave_Config self);
 	static inline lu_bool lu_wave_config__is_set(Lu_Wave_Config self) { return self->flags != 0; }

///////////////////////////////////////////////////////////////////////////////
// Lu_Rec_Config Predefined 

	extern struct lu_wave_config lu_g_wc_predefined[LU_WAVE_CONFIG_END];

///////////////////////////////////////////////////////////////////////////////
// Lu_Wave 

	
	enum lu_wave_type {
		LU_WAVE_TYPE__SAVE,
		LU_WAVE_TYPE__FIND,
		LU_WAVE_TYPE__RESTORE
	};

	//
	// One wave is one seq. Create another wave to create another seq.
	//
	struct lu_wave {
		enum lu_wave_type type;

		// user can set it, default 0
		lu_size id;		

		Lu_Mem mem;
		Lu_Brain brain;
		struct lu_wave_config config;

		// virtual destructor
		void (*destroy)(Lu_Wave);

		// virtual methods
		void (*block_begin)(Lu_Wave);
		void (*block_end)(Lu_Wave);

		void (*push)(Lu_Wave, Lu_Rec, lu_value* data);
		void (*push_neu)(Lu_Wave, Lu_Neu); 

		void (*reset)(Lu_Wave);

		void (*step)(Lu_Wave);
		void (*process)(Lu_Wave);
	};

	static inline Lu_Wave lu_wave__init(
		Lu_Wave self, 
		enum lu_wave_type type, 
		lu_size id, 
		Lu_Brain brain, 
		struct lu_wave_config config
	);

	static inline lu_bool lu_wave__is_save(Lu_Wave self) { return self->type == LU_WAVE_TYPE__SAVE; }
	static inline lu_bool lu_wave__is_find(Lu_Wave self) { return self->type == LU_WAVE_TYPE__FIND; }
	static inline lu_bool lu_wave__is_restore(Lu_Wave self) { return self->type == LU_WAVE_TYPE__RESTORE; }

///////////////////////////////////////////////////////////////////////////////
// Lu_Seq_Rg

	struct lu_cell {
		Lu_Layer layer;
		N_Cell_0 n_cell_0;
		lu_value sig;
	};

	// static Lu_Cell lu_cell_create

	struct lu_layer {

		Lu_Cell* cells;
	};

	static Lu_Layer lu_layer__create(Lu_Mem mem);
	static void lu_layer__destroy(Lu_Layer self, Lu_Mem mem);

	struct lu_rec_rg {

		struct lu_layer componentlu_m_layer;
		struct lu_layer pixellu_m_layer;
		struct lu_layer* pyralu_m_layers;
	};

	static Lu_Rec_Rg lu_rec_rg__create(Lu_Mem mem);
	static void lu_rec_rg__destroy(Lu_Rec_Rg self, Lu_Mem mem);

	struct lu_seq_rg {
		Lu_Mem mem;
		Lu_S s;
	
		Lu_Arr recs;

		// block (time) index, we dont save reference to Lu_Block
		// because they might be destroyed and we don't want to copy it
		// (for space/speed performance)
		lu_size seq_index; 	
							
		Lu_Cell cell; // resulting block_layer cell	
	};

	static Lu_Seq_Rg lu_seq_rg__create(Lu_Mem mem, Lu_S s);
	static void lu_seq_rg__destroy(Lu_Seq_Rg self);

///////////////////////////////////////////////////////////////////////////////
// Lu_Save_Wave 

	struct lu_save_wave {
		struct lu_wave super;

		Lu_Seq seq;

		Lu_Lim_List block_layers;

		// max size is lu_lim_list__size(self->block_layers)
		struct lu_layer* block_layer_layers; // !!! WRONG
	};

///////////////////////////////////////////////////////////////////////////////
// Lu_Find_Wave 

	struct lu_find_wave {
		struct lu_wave super;

		Lu_Seq seq;
	};

///////////////////////////////////////////////////////////////////////////////
// Lu_Restore_Wave 

	struct lu_restore_wave {
		struct lu_wave super;

	};