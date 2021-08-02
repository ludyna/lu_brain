/**
	Copyright © 2021 Oleh Ihorovych Novosad 

*/

///////////////////////////////////////////////////////////////////////////////
// S

	enum lu_s_slot_type {
		LU_SST_SLOT_1,
		LU_SST_SLOT_2,
		LU_SST_SLOT_3,
		LU_SST_SLOT_4
	};

	typedef struct lu_s_slot_1* Lu_S_Slot_1;
	typedef struct lu_s_slot_2* Lu_S_Slot_2;
	typedef struct lu_s_slot_3* Lu_S_Slot_3;
	typedef struct lu_s_slot_4* Lu_S_Slot_4;

	enum lu_s_cell_type {
		LU_SCT_CELL_3,
		LU_SCT_CELL_2, 
		LU_SCT_CELL
	};

 	typedef struct lu_s_cell_1* 			Lu_S_Cell_1;
 	typedef struct lu_s_cell_2* 			Lu_S_Cell_2;
 	typedef struct lu_s_cell_values*  		Lu_S_Cell_Values;
 	typedef struct lu_s_cell_3* 			Lu_S_Cell_3;
	
	// Helpers

	enum lu_s_layer_type {
		LU_SLT_COMPONENTS,
		LU_SLT_PIXELS, 	
		LU_SLT_PYRAS,
		LU_SLT_STORY
	};
	
	typedef struct lu_s_layer_conf*		Lu_S_Layer_Conf;
	typedef struct lu_s_layer* 			Lu_S_Layer;
	typedef struct lu_s_cell_mem*   	Lu_S_Cell_Mem;
	typedef struct lu_s_rec_rg*			Lu_S_Rec_Rg;
	typedef struct lu_s_story_rg*  		Lu_S_Story_Rg;
	typedef struct lu_s* 				Lu_S;

