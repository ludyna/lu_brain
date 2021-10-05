/**
	Copyright © 2021 Oleh Ihorovych Novosad 

*/

///////////////////////////////////////////////////////////////////////////////
// S

	// 
	// Slots
	// 

	typedef struct lu_s_slot_1* Lu_S_Slot_1;
	typedef struct lu_s_slot_2* Lu_S_Slot_2;
	typedef struct lu_s_slot_4* Lu_S_Slot_4;

	//
	// Cells
	//

	enum lu_s_cell_type {
		LU_SCT_COMPONTENT,
		LU_SCT_PIXEL,
		LU_SCT_REC,
		LU_SCT_SEQ_NX,
		LU_SCT_SEQ,
		LU_SCT_STORY_NX
	};

 	typedef struct lu_s_base_cell* 				Lu_S_Base_Cell;
 	typedef struct lu_s_comp_cell* 				Lu_S_Comp_Cell;
 	typedef struct lu_s_pixel_cell* 			Lu_S_Pixel_Cell;
 	typedef struct lu_s_rec_cell* 				Lu_S_Rec_Cell;
 	typedef struct lu_s_seq_nx_cell* 			Lu_S_Seq_Nx_Cell;
 	typedef struct lu_s_seq_cell* 				Lu_S_Seq_Cell;
 	typedef struct lu_s_story_nx_cell* 			Lu_S_Story_Nx_Cell;

	//
	// Layers
	//

	enum lu_s_layer_type {
		LU_SLT_COMPONENT,
		LU_SLT_PIXEL, 	
		LU_SLT_REC,
		LU_SLT_SEQ_NX,
		LU_SLT_SEQ,
		LU_SLT_STORY_NX,
		LU_SLT_END
	};

	typedef struct lu_s_base_layer* 		Lu_S_Base_Layer;
	typedef struct lu_s_comp_layer* 		Lu_S_Comp_Layer;
	typedef struct lu_s_pixel_layer*  		Lu_S_Pixel_Layer;
	typedef struct lu_s_rec_layer*  		Lu_S_Rec_Layer;
	typedef struct lu_s_seq_nx_layer*  		Lu_S_Seq_Nx_Layer;
	typedef struct lu_s_seq_layer* 			Lu_S_Seq_Layer;
	typedef struct lu_s_story_nx_layer*   	Lu_S_Story_Nx_Layer;

	// 
	// Cell_Mem
	//

	typedef struct lu_s_cell_mem_config* Lu_S_Cell_Mem_Config;
	typedef struct lu_s_cell_mem*   	Lu_S_Cell_Mem;

	// 
	// Regions
	//

	typedef struct lu_s_base_rg*  		Lu_S_Base_Rg;
	typedef struct lu_s_rec_rg*			Lu_S_Rec_Rg;
	typedef struct lu_s_seq_rg*  		Lu_S_Seq_Rg;
	typedef struct lu_s_story_rg* 		Lu_S_Story_Rg;

	//
	// S
	//
	
	typedef struct lu_s* 				Lu_S;

