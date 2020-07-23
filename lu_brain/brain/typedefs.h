/**
	Copyright © 2020 Oleh Ihorovych Novosad 
	Internal typedefs not defined in lu_brain.h

	Only app specific. Lib and basic typedefs should not be here.
*/

///////////////////////////////////////////////////////////////////////////////
// Gate
	typedef struct data* 		Data;

///////////////////////////////////////////////////////////////////////////////
// Gate

	typedef struct gate_opts* 	Gate_Opts;
	typedef struct gate* 		Gate;

///////////////////////////////////////////////////////////////////////////////
// S

	enum s_neu_type {
		SNT_COMPONENT,
		SNT_CELL, 
		SNT_DATA,
		SNT_BLOCK
	};

 	typedef struct s_neu* 		S_Neu;
	
	// Helpers

	enum s_layer_type {
		SLT_COMPONENTS,
		SLT_CELLS,
		SLT_DATUM,
		SLT_BLOCKS
	};
	
	typedef struct s_layer_conf*	S_Layer_Conf;
	typedef struct s_layer* 		S_Layer;
	typedef struct s_rec*			S_Rec;
	typedef struct s_mem* 			S_Mem;

///////////////////////////////////////////////////////////////////////////////
// N

	#define IX_NULL 0

	enum n_com_type {
		NCT_VALUE = 0,
		NCT_NAME = 1,

		NCT_SIZE
	};
 	
 	typedef struct n_com* 		N_Com;
	typedef struct n_lin* 		N_Lin;
	typedef struct n_neu*		N_Neu;
	typedef struct n_mem_opts*  N_Mem_Opts;
	typedef struct n_mem* 		N_Mem;


