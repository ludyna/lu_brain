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
		void (*block_begin)(Lu_Wave);
		void (*block_end)(Lu_Wave);

		void (*push)(Lu_Wave, Lu_Rec, lu_value* data);
		void (*push_neu)(Lu_Wave, Lu_Neu); 

		void (*reset)(Lu_Wave);

		void (*step)(Lu_Wave);
		void (*process)(Lu_Wave);
	};

	static inline Lu_Wave lu_wave_init(
		Lu_Wave self, 
		enum lu_wave_type type, 
		lu_size id, 
		Lu_Mem mem, 
		Lu_Brain brain, 
		struct lu_wave_config config
	)
	{
		self->type = type;
		self->id = id;
		self->mem = mem;
		self->brain = brain;
		self->config = config;

		self->destroy = NULL;
		self->block_begin = NULL;
		self->block_end = NULL;
		self->push = NULL;
		self->push_neu = NULL;
		self->reset = NULL;
		self->step = NULL;
		self->process = NULL;
	}

	static inline lu_bool lu_wave_is_save(Lu_Wave self) { return self->type == LU_WAVE_TYPE_SAVE; }
	static inline lu_bool lu_wave_is_find(Lu_Wave self) { return self->type == LU_WAVE_TYPE_FIND; }
	static inline lu_bool lu_wave_is_restore(Lu_Wave self) { return self->type == LU_WAVE_TYPE_RESTORE; }

///////////////////////////////////////////////////////////////////////////////
// Lu_Snapshot

	struct lu_cell {
		Lu_Layer layer;
		Hnn_Cell_0 hnn_cell_0;
		lu_value sig;
	};

	struct lu_layer {
		S_Layer s_layer;

		Lu_Cell* cells;
	};

	struct lu_snapshot_rec {
		S_Rec s_rec;
	};

	struct lu_snapshot {
		Lu_S s;
		Lu_Arr recs;
	};

	static Lu_Snapshot lu_snapshot_create(Lu_Mem mem, Lu_S s);
	static void lu_snapshot_destroy(Lu_Snapshot self, Lu_Mem mem);

///////////////////////////////////////////////////////////////////////////////
// Lu_Save_Wave 

	struct lu_save_wave {
		struct lu_wave super;

		Lu_Story story;

		Lu_List snapshots;
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