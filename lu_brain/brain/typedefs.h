/**
	Copyright © 2020 Oleh Ihorovych Novosad 
	Internal typedefs not defined in lu_brain.h
*/

///////////////////////////////////////////////////////////////////////////////
// Waves

	typedef struct sig* 						Sig;

	typedef struct w_col* 						W_Col;
	typedef struct w_rec*						W_Rec;

	typedef struct save_wave_create_opts* 		Save_Wave_Create_Opts;
	typedef struct save_wave* 					Save_Wave;

	typedef struct find_wave_create_opts*  		Find_Wave_Create_Opts;
	typedef struct find_wave* 					Find_Wave;

	typedef struct restore_wave_create_opts*	Restore_Wave_Create_Opts;
	typedef struct restore_wave* 				Restore_Wave; 


///////////////////////////////////////////////////////////////////////////////
// Gate

	typedef struct gate_opts* 	Gate_Opts;
	typedef struct gate* 		Gate;

///////////////////////////////////////////////////////////////////////////////
// N_Mem

	typedef struct neu_ent* 	Neu_Ent;
	typedef struct neu_b* 		Neu_B;
	typedef struct neu_name* 	Neu_Name;

	typedef struct lin_ent* 	Lin_Ent;
	typedef struct lin_b* 		Lin_B;

	typedef struct val_layer* 	Val_Layer;

	typedef struct n_col* 		N_Col;
	typedef struct n_rec*		N_Rec;
	typedef struct n_mem* 		N_Mem;