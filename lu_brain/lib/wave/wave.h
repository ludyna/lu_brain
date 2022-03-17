/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Lu_Rec_Config

 	static Lu_Process_Config lu_wave_config__init(Lu_Process_Config self);
 	static inline lu_bool lu_wave_config__is_set(Lu_Process_Config self) { return self->flags != 0; }

///////////////////////////////////////////////////////////////////////////////
// Lu_Rec_Config Predefined 

	extern struct lu_process_config lu_g_wc_predefined[LU_PROCESS__END];

///////////////////////////////////////////////////////////////////////////////
// Lu_Wave 

	
	enum lu_wave_type {
		LU_WAVE__SAVE,
		LU_WAVE__MATCH,
		LU_WAVE__RESTORE
	};

	/*
		One wave is one seq. Create another wave to create another seq.
	*/
	struct lu_wave {
		enum lu_wave_type type;

		lu_size wave_id;
		lu_p_byte manager_addr;

		Lu_Mem mem;
		Lu_Brain brain;
		struct lu_process_config config;

		// virtual destructor
		void (*destroy)(Lu_Wave);

		// virtual methods
		void (*block_begin)(Lu_Wave);
		void (*block_end)(Lu_Wave);

		void (*push)(Lu_Wave, Lu_Rec, lu_value* data);
		void (*push_neu)(Lu_Wave, Lu_Neu); 

		void (*reset)(Lu_Wave);

		void (*step)(Lu_Wave, Lu_Process_Config);
		void (*process)(Lu_Wave, Lu_Process_Config);
	};

	static inline Lu_Wave lu_wave__init(
		Lu_Wave self, 
		enum lu_wave_type type, 
		Lu_Brain brain
	);

	static inline lu_bool lu_wave__is_save(Lu_Wave self) { return self->type == LU_WAVE__SAVE; }
	static inline lu_bool lu_wave__is_find(Lu_Wave self) { return self->type == LU_WAVE__MATCH; }
	static inline lu_bool lu_wave__is_restore(Lu_Wave self) { return self->type == LU_WAVE__RESTORE; }


///////////////////////////////////////////////////////////////////////////////
// Lu_Save_Wave 

	struct lu_save_wave {
		struct lu_wave super;

		Lu_Data_Seq seq;
	};

///////////////////////////////////////////////////////////////////////////////
// Lu_Find_Wave 

	struct lu_find_wave {
		struct lu_wave super;

		Lu_Data_Seq seq;
	};

///////////////////////////////////////////////////////////////////////////////
// Lu_Restore_Wave 

	struct lu_restore_wave {
		struct lu_wave super;

	};

