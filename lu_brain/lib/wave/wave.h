/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Lu_Wave 

	/*
		One wave is one seq. Create another wave to create another seq.
	*/
	struct lu_wave {
		lu_size wave_id; 			// global wave_id
		lu_size wave_ix;			// wave type specific, can be same number for different wave types
		enum lu_wave_type type;	

		lu_p_byte manager_addr;

		Lu_Mem mem;
		Lu_Brain brain;
	};

	static inline Lu_Wave lu_wave__init(
		Lu_Wave self, 
		enum lu_wave_type type, 
		Lu_Brain brain
	);

	static inline void lu_wave__deinit(Lu_Wave self);

	static inline lu_bool lu_wave__is_save(Lu_Wave self) { return self->type == LU_WAVE__SAVE; }
	static inline lu_bool lu_wave__is_match(Lu_Wave self) { return self->type == LU_WAVE__MATCH; }
	static inline lu_bool lu_wave__is_restore(Lu_Wave self) { return self->type == LU_WAVE__RESTORE; } 


///////////////////////////////////////////////////////////////////////////////
// Lu_Data_Wave (data flow wave)

	struct lu_data_wave {
		struct lu_wave super;

		Lu_Data_Seq seq;
	};

	//
	// Constructor / Destructor
	//

	static void lu_data_wave__init(Lu_Data_Wave self, enum lu_wave_type type, Lu_Brain brain);
	static void lu_data_wave__deinit(Lu_Data_Wave self);

	//
	// Data
	//

	static void lu_data_wave__reset(Lu_Data_Wave);
	static void lu_data_wave__block_begin(Lu_Data_Wave);
	static void lu_data_wave__block_end(Lu_Data_Wave);

	static void lu_data_wave__set_dest_start_pos(Lu_Data_Wave, Lu_Rec, lu_long dest_x, lu_long dest_y);
	static void lu_data_wave__set_src_start_pos(Lu_Data_Wave, Lu_Rec, lu_size src_x, lu_size src_y);
	static void lu_data_wave__set_src_end_pos(Lu_Data_Wave, Lu_Rec, lu_size src_x, lu_size src_y);

///////////////////////////////////////////////////////////////////////////////
// Lu_Save_Wave 

	struct lu_save_wave {
		struct lu_data_wave super;

		struct lu_save_config config;
	};

///////////////////////////////////////////////////////////////////////////////
// Lu_Match_Wave 

	struct lu_match_wave {
		struct lu_data_wave super;

		struct lu_match_config config;

		struct lu_w_match_processor processor;

		struct lu_w_match_cell_mem match_cell_mem;
	};

///////////////////////////////////////////////////////////////////////////////
// Lu_Delete_Wave 

	struct lu_delete_wave {
		struct lu_wave super;

		struct lu_delete_config config;

		struct lu_w_del_processor processor;
	};

///////////////////////////////////////////////////////////////////////////////
// Lu_Restore_Wave 

	struct lu_restore_wave {
		struct lu_wave super;

		struct lu_restore_config config;

		struct lu_w_restore_processor processor;
	};