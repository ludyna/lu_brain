/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Nouns

	typedef struct gate* 	Gate;

///////////////////////////////////////////////////////////////////////////////
// Gate

	struct gate {
		Arr save_waves;
		Arr find_waves;
		Arr restore_waves;
	};

	static Gate gate_create(Mem, Brain_Opts);

	static Save_Wave gate_save_wave_wait(Gate self);
	static Find_Wave gate_find_wave_wait(Gate self);
	static Restore_Wave gate_restore_wave_wait(Gate self);