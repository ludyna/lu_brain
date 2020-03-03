/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/
///////////////////////////////////////////////////////////////////////////////
// Nound

	typedef struct save_wave* 		Save_Wave;
	typedef struct find_wave* 		Find_Wave;
	typedef struct restore_wave* 	Restore_Wave;

///////////////////////////////////////////////////////////////////////////////
// Wave API

	struct wave {
		Story 			story;
	};

	
	struct wave_resp {

	};

///////////////////////////////////////////////////////////////////////////////
// Save 

	struct save_wave {
		struct wave 	super;
	};

	struct save_opts {

	};


	struct save_resp {

	};

	static void save_wave_process(Save_Wave self);

//////////////////////////7/////////////////////////////////////////////////////
// Find

	struct find_wave {
		struct wave 	super;
	};

	struct find_opts {

	};

	struct find_resp {

	};

	static void find_wave_process(Find_Wave self);

///////////////////////////////////////////////////////////////////////////////
// Reception API

	struct reception {

	};

///////////////////////////////////////////////////////////////////////////////
// Restore API

	struct restore_wave {
		struct wave 	super;
	};


	struct restore_opts {

	};

	struct restore_resp {

	};

	static void restore_wave_process(Restore_Wave self);