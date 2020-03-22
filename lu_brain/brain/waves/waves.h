/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Nouns

	typedef struct save_wave_create_opts* 		Save_Wave_Create_Opts;
	typedef struct save_wave* 					Save_Wave;

	typedef struct find_wave_create_opts*  		Find_Wave_Create_Opts;
	typedef struct find_wave* 					Find_Wave;

	typedef struct restore_wave_create_opts*	Restore_Wave_Create_Opts;
	typedef struct restore_wave* 				Restore_Wave;


///////////////////////////////////////////////////////////////////////////////
// Wave API

	struct wave {

	};

	
	struct wave_resp {

	};

///////////////////////////////////////////////////////////////////////////////
// Save 

	struct save_wave_create_opts
	{
		lu_size 			block_neus_size;
	};

	static void save_wave_create_opts_init(Save_Wave_Create_Opts);

	struct save_opts {

	};

	struct save_wave {
		struct wave 		super;
		struct save_opts 	save_opts;
		Story 				story;

		Arr2				percs;
	};

	struct save_resp {

	};

	static Save_Wave save_wave_create(Mem, Save_Wave_Create_Opts);

	static void save_wave_init(Save_Wave, Story, Save_Opts);

	static void save_wave_process(Save_Wave self);

//////////////////////////7/////////////////////////////////////////////////////
// Find

	struct find_wave_create_opts
	{

	};

	static void find_wave_create_opts_init(Find_Wave_Create_Opts);

	struct find_opts {

	};

	struct find_wave {
		struct wave 		super;
		struct find_opts 	find_opts;
		Story 				story;
	};

	struct find_resp {

	};

	static Find_Wave find_wave_create(Mem, Find_Wave_Create_Opts);

	static void find_wave_init(Find_Wave, Story, Find_Opts);

	static void find_wave_process(Find_Wave self);

///////////////////////////////////////////////////////////////////////////////
// Perc API

lu_p_void perc_cont_create(Rec rec, lu_p_void prev, lu_p_void curr, lu_p_void next);

///////////////////////////////////////////////////////////////////////////////
// Restore API

	struct restore_wave_create_opts
	{

	};

	static void restore_wave_create_opts_init(Restore_Wave_Create_Opts);

	struct restore_opts {

	};

	struct restore_wave {
		struct wave 			super;
		struct restore_opts 	restore_opts;
		Brain 					brain;
	};

	struct restore_resp {

	};


	static Restore_Wave restore_wave_create(Mem, Restore_Wave_Create_Opts);

	static void restore_wave_init(Restore_Wave, Brain, Restore_Opts);

	static void restore_wave_process(Restore_Wave self);