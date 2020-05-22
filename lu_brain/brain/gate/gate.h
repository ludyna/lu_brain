/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Gate
	struct gate_opts {
		lu_size 						w_saves_size;		// max number of save waves that could 
															// run in parallel
		struct w_save_create_opts		w_save_create_opts;

		lu_size							w_finds_size;
		struct w_find_create_opts  		w_find_create_opts;

		lu_size							w_restores_size;
		struct w_restore_create_opts	w_restore_create_opts;
	}; 

	static void gate_opts_init(Gate_Opts self);

	struct gate {
		Lu_Brain brain;

		Arr save_waves;
		Arr find_waves;
		Arr restore_waves;
	};

	static Gate gate_create(Lu_Brain, Gate_Opts);

	static W_Save gate_save_wave_wait(Gate self);
	static W_Find gate_find_wave_wait(Gate self);
	static W_Restore gate_restore_wave_wait(Gate self);

	static void gate_wave_book(Gate self, Lu_Wave wave);
	static void gate_wave_free(Gate self, Lu_Wave wave);