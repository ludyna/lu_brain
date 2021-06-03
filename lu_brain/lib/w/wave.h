/**
	Copyright © 2021 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Lu_Wave 

	
	enum lu_wave_type {
		LU_WAVE_TYPE_SAVE,
		LU_WAVE_TYPE_FIND,
		LU_WAVE_TYPE_RESTORE
	};

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
		void (*block_start)(Lu_Wave);
		void (*block_end)(Lu_Wave);

		void (*push)(Lu_Wave, Lu_Rec, lu_value* data);
		void (*push_neu)(Lu_Wave, Lu_Neu); 

		void (*reset)(Lu_Wave);
	};

	static inline Lu_Wave lu_wave_init(
		Lu_Wave self, 
		enum lu_wave_type type, 
		lu_size id, 
		Lu_Mem mem, 
		Lu_Brain brain, 
		struct lu_wave_config config,
		void (*wave_destroy)(Lu_Wave)
	)
	{
		self->type = type;
		self->id = id;
		self->mem = mem;
		self->brain = brain;
		self->config = config;
		self->destroy = wave_destroy;
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_Save_Wave 


	struct lu_save_wave {
		struct lu_wave super;

		Lu_Story story;
	};

///////////////////////////////////////////////////////////////////////////////
// Lu_Find_Wave 

	struct lu_find_wave {
		struct lu_wave super;

		Lu_Story story;
	};

///////////////////////////////////////////////////////////////////////////////
// Lu_Restore_Wave 

	struct lu_restore_wave {
		struct lu_wave super;

	};