/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Nouns

	typedef struct gate_opts* 	Gate_Opts;
	typedef struct gate* 		Gate;

///////////////////////////////////////////////////////////////////////////////
// Gate
	struct gate_opts {
		lu_size 					save_waves_size;		// max number of save waves that could 
															// run in parallel
		struct save_wave_create_opts		save_wave_create_opts;

		lu_size						find_waves_size;
		struct find_wave_create_opts  		find_wave_create_opts;

		lu_size						restore_waves_size;
		struct restore_wave_create_opts	restore_wave_create_opts;
	}; 

	static void gate_opts_init(Gate_Opts self);

	struct gate {
		Lu_Brain brain;

		Arr save_waves;
		Arr find_waves;
		Arr restore_waves;
	};

	static Gate gate_create(Lu_Brain, Gate_Opts);

	static Save_Wave gate_save_wave_wait(Gate self);
	static Find_Wave gate_find_wave_wait(Gate self);
	static Restore_Wave gate_restore_wave_wait(Gate self);