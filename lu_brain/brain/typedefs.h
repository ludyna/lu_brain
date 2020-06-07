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

	typedef struct n_col* 		N_Col;
	typedef struct n_cell* 		N_Cell;
	typedef struct n_cb* 		N_Cb;
	typedef struct n_mem* 		N_Mem;

	typedef struct n_ent* 		N_Ent;
	typedef struct n_base* 		N_Base;
	typedef struct n_name* 		N_Name;

	typedef struct lin_ent* 	Lin_Ent;
	typedef struct lin_b* 		Lin_B;

///////////////////////////////////////////////////////////////////////////////
// S

	enum s_type {
		S_MEM, 
		S_REC, 
		S_COL, 
		S_CB,
		S_NAME
	};

	typedef struct s_layer* 	S_Layer;
 	typedef struct s_base* 		S_Base;
 	typedef struct s_col_conf*	S_Col_Conf;
	typedef struct s_col* 		S_Col;
	typedef struct s_v_cell* 	S_V_Cell;
	typedef struct s_cb* 		S_Cb;
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