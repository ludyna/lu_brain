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
// S

	enum s_net_type {
		SNT_CELL, 
		SNT_NEU,
		SNT_A_NEU
	};

	typedef lu_size s_neu_ix;

 	typedef struct s_base* 		S_Base;
 	typedef struct s_neu* 		S_Neu;
	typedef struct s_cell* 		S_Cell;
	
	// Helpers
	typedef struct s_col_conf*	S_Col_Conf;
	typedef struct s_col* 		S_Col;
	typedef struct s_rec*		S_Rec;
	typedef struct s_mem* 		S_Mem;

///////////////////////////////////////////////////////////////////////////////
// N

	#define IX_NULL 0

	typedef lu_size n_h_lin_ix;
	typedef lu_size n_v_lin_ix;
	typedef lu_size n_neu_ix;
	typedef lu_size n_com_ix;

	enum n_com_type {
		NCI_VALUE = 0,
		NCI_NAME = 1,

		NCI_SIZE
	};

	typedef struct n_neu*		N_Neu;
	typedef struct n_v_lin* 	N_V_Lin;
	typedef struct n_h_lin* 	N_H_Lin;
	typedef struct n_mem* 		N_Mem;


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