/**
	Copyright © 2021 Oleh Ihorovych Novosad 

*/

///////////////////////////////////////////////////////////////////////////////
// S

	enum s_cell_type {
		SCT_CELL_3,
		SCT_CELL_2, 
		SCT_CELL
	};

 	typedef struct s_cell* 				S_Cell;
 	typedef struct s_cell_2* 			S_Cell_2;
 	typedef struct s_cell_3* 			S_Cell_3;
	
	// Helpers

	enum s_layer_type {
		SLT_COMPONENTS,
		SLT_PIXELS, 	
		SLT_PYRAS,
		SLT_BLOCKS
	};
	
	typedef struct s_layer_conf*		S_Layer_Conf;
	typedef struct s_layer* 			S_Layer;
	typedef struct s_rec*				S_Rec;
	typedef struct s_mem* 				S_Mem;

