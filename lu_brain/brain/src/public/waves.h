/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/
///////////////////////////////////////////////////////////////////////////////
// Nound

	typedef struct save_wave* 			Save_Wave;
	typedef struct save_wave_opts* 		Save_Wave_Opts;

	typedef struct find_wave* 			Find_Wave;
	typedef struct find_wave_opts*  	Find_Wave_Opts;

	typedef struct restore_wave* 		Restore_Wave;
	typedef struct restore_wave_opts*	Restore_Wave_Opts;

///////////////////////////////////////////////////////////////////////////////
// Wave API

	struct wave {
		Story 			story;
	};

	
	struct wave_resp {

	};

///////////////////////////////////////////////////////////////////////////////
// Save 

	struct save_wave_opts
	{

	};

	struct save_wave {
		struct wave 	super;
	};

	struct save_opts {

	};


	struct save_resp {

	};

	static Save_Wave save_wave_create(Mem, Save_Wave_Opts);

	static void save_wave_process(Save_Wave self, Save_Opts);

//////////////////////////7/////////////////////////////////////////////////////
// Find

	struct find_wave_opts
	{

	};

	struct find_wave {
		struct wave 	super;
	};

	struct find_opts {

	};

	struct find_resp {

	};

	static Find_Wave find_wave_create(Mem, Find_Wave_Opts);

	static void find_wave_process(Find_Wave self, Find_Opts);

///////////////////////////////////////////////////////////////////////////////
// Reception API

	struct reception {

	};

///////////////////////////////////////////////////////////////////////////////
// Restore API

	struct restore_wave_opts
	{

	};

	struct restore_wave {
		struct wave 	super;
	};


	struct restore_opts {

	};

	struct restore_resp {

	};


	static Restore_Wave restore_wave_create(Mem, Restore_Wave_Opts);

	static void restore_wave_process(Restore_Wave self, Restore_Opts);