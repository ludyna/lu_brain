/**
	Copyright © 2020 Oleh Ihorovych Novosad 
	Internal typedefs not defined in lu_brain.h

	Only app specific. Lib and basic typedefs should not be here.
*/

///////////////////////////////////////////////////////////////////////////////
// Gate

	typedef struct gate_opts* 	Gate_Opts;
	typedef struct gate* 		Gate;

///////////////////////////////////////////////////////////////////////////////
// N

	typedef struct n_ent* 		N_Ent;
	typedef struct n_base* 		N_Base;
	typedef struct n_name* 		N_Name;

///////////////////////////////////////////////////////////////////////////////
// S

	enum n_col_type {
		NCT_FIRST,
		NCT_COL, 			
		NCT_PER_HOR, 
		NCT_PER_VER,
		NCT_PER_DIAG, 
		NCT_LAST
	};


	typedef struct lin_ent* 	Lin_Ent;
	typedef struct lin_b* 		Lin_B;

	typedef struct val_layer* 	Val_Layer;

	typedef struct s_cb* 		S_Cb;
	typedef struct s_col* 		S_Col;
	typedef struct s_rec*		S_Rec;
	typedef struct s_mem* 		S_Mem;


///////////////////////////////////////////////////////////////////////////////
// W

	typedef struct sig* 						Sig;

	typedef struct w_col* 						W_Col;
	typedef struct w_rec*						W_Rec;

	typedef struct save_wave_create_opts* 		Save_Wave_Create_Opts;
	typedef struct save_wave* 					Save_Wave;

	typedef struct find_wave_create_opts*  		Find_Wave_Create_Opts;
	typedef struct find_wave* 					Find_Wave;

	typedef struct restore_wave_create_opts*	Restore_Wave_Create_Opts;
	typedef struct restore_wave* 				Restore_Wave; 