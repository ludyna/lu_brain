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

	typedef struct w_sig* 						W_Sig;

	typedef struct w_col* 						W_Col;
	typedef struct w_rec*						W_Rec;

	typedef struct w_save_create_opts* 			W_Save_Create_Opts;
	typedef struct w_save* 						W_Save;

	typedef struct w_find_create_opts*  		W_Find_Create_Opts;
	typedef struct w_find* 						W_Find;

	typedef struct w_restore_create_opts*		W_Restore_Create_Opts;
	typedef struct w_restore* 					W_Restore; 