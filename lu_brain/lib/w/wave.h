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

		Lu_Brain brain;
		struct lu_wave_config config;
	};

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