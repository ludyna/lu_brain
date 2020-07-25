/**
	Copyright © 2020 Oleh Ihorovych Novosad 
	Internal typedefs not defined in lu_brain.h

	Only app specific. Lib and basic typedefs should not be here.
*/

///////////////////////////////////////////////////////////////////////////////
// Gate
	typedef struct data* 		Data;

///////////////////////////////////////////////////////////////////////////////
// S

	enum s_cell_type {
		SCT_CELL_3,
		SCT_CELL_2, 
		SCT_CELL
	};

 	typedef struct s_cell* 			S_Cell;
 	typedef struct s_cell_2* 		S_Cell_2;
 	typedef struct s_cell_3* 		S_Cell_3;
	
	// Helpers

	enum s_layer_type {
		SLT_COMPONENTS,
		SLT_PIXELS, 	
		SLT_PYRAS,
		SLT_BLOCKS
	};
	
	typedef struct s_layer_conf*	S_Layer_Conf;
	typedef struct s_layer* 		S_Layer;
	typedef struct s_rec*			S_Rec;
	typedef struct s_mem* 			S_Mem;

///////////////////////////////////////////////////////////////////////////////
// N

	#define IX_NULL 0

	enum n_cell_type {
		NCT_NORMAL = 0, 
		NCT_VALUE,
		NCT_NAME,
		NCT_SIZE
	};

	typedef struct n_cell*		N_Cell;
	typedef struct n_cell_2* 	N_Cell_2;
	typedef struct n_cell_3* 	N_Cell_3;
	typedef struct n_lin* 		N_Lin;
	typedef struct n_mem_opts*  N_Mem_Opts;
	typedef struct n_mem* 		N_Mem;


