/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Lu_Rec_Config

 	static Lu_Save_Config lu_wave_config__init(Lu_Save_Config self);
 	static inline lu_bool lu_wave_config__is_set(Lu_Save_Config self) { return self->flags != 0; }

///////////////////////////////////////////////////////////////////////////////
// Lu_Rec_Config Predefined 

	extern struct lu_save_config lu_g_wc_predefined[LU_PROCESS__END];

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
		struct lu_save_config config;

		// virtual destructor
		void (*destroy)(Lu_Wave);

		// virtual methods
		void (*block_begin)(Lu_Wave);
		void (*block_end)(Lu_Wave);

		void (*push)(Lu_Wave, Lu_Rec, lu_value* data, lu_size, lu_size, lu_size);

		void (*reset)(Lu_Wave);

		void (*step)(Lu_Wave, Lu_Save_Config);
		void (*process)(Lu_Wave, Lu_Save_Config);
	};

	static inline Lu_Wave lu_wave__init(
		Lu_Wave self, 
		enum lu_wave_type type, 
		Lu_Brain brain
	);

	static inline lu_bool lu_wave__is_save(Lu_Wave self) { return self->type == LU_WAVE__SAVE; }
	static inline lu_bool lu_wave__is_match(Lu_Wave self) { return self->type == LU_WAVE__MATCH; }
	static inline lu_bool lu_wave__is_restore(Lu_Wave self) { return self->type == LU_WAVE__RESTORE; }

///////////////////////////////////////////////////////////////////////////////
// Lu_Save_Wave 

	struct lu_save_wave {
		struct lu_wave super;

		Lu_Data_Seq seq;
	};

	static inline lu_size lu_save_wave__get_wave_ix(Lu_Save_Wave self)
	{
		return self->super.wave_ix;
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_Match_Wave 

	struct lu_match_wave {
		struct lu_wave super;

		Lu_Data_Seq seq;

		struct lu_w_processor processor;

		struct lu_w_match_cell_mem match_cell_mem;
	};

///////////////////////////////////////////////////////////////////////////////
// Lu_Restore_Wave 

	struct lu_restore_wave {
		struct lu_wave super;

	};

///////////////////////////////////////////////////////////////////////////////
// Lu_Delete_Wave 

	struct lu_delete_wave {
		struct lu_wave super;

	};

