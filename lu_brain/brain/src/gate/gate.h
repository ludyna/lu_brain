/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Nouns

	typedef struct gate* 	Gate;

///////////////////////////////////////////////////////////////////////////////
// Gate

	struct gate {

	};

	Save_Wave gate_save_wave_wait(Gate self);
	Find_Wave gate_find_wave_wait(Gate self);
	Restore_Wave gate_restore_wave_wait(Gate self);