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

	typedef lu_size lin_ix;
	typedef lu_size neu_ix;

	enum n_comp_type {
		NCI_VALUE = 0,
		NCI_NAME = 1,

		NCI_SIZE
	};

	// batko => dytyna
	enum n_lin_type {
		NLT_V_TO_P,
		NLT_P_TO_CB,
		NLT_CB_TO_NAME
	};

	typedef struct n_neu*		N_Neu;
	typedef struct n_lin* 		N_Lin;
	typedef struct n_mem* 		N_Mem;

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
	typedef struct s_v_col* 	S_Col;
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