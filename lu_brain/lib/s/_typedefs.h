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
		LU_SCT_SEQ_ELEMENT,
		LU_SCT_SEQ,
		LU_SCT_STORY_ELEMENT
	};

 	typedef struct lu_s_base_cell* 				Lu_S_Base_Cell;
 	typedef struct lu_s_component_cell* 		Lu_S_Component_Cell;
 	typedef struct lu_s_pixel_cell* 			Lu_S_Pixel_Cell;
 	typedef struct lu_s_rec_cell* 				Lu_S_Rec_Cell;
 	typedef struct lu_s_seq_element_cell* 		Lu_S_Seq_Element_Cell;
 	typedef struct lu_s_seq_cell* 				Lu_S_Seq_Cell;
 	typedef struct lu_s_story_element_cell* 	Lu_S_Story_Element_Cell;

	//
	// Layes
	//

	enum lu_s_layer_type {
		LU_SLT_COMPONENT,
		LU_SLT_PIXEL, 	
		LU_SLT_REC,
		LU_SLT_SEQ_ELEMENT,
		LU_SLT_SEQ,
		LU_SLT_STORY_ELEMENT
	};
	
	typedef struct lu_s_layer_conf*		Lu_S_Layer_Conf;
	typedef struct lu_s_layer* 			Lu_S_Layer;

	// 
	// Cell_Mem
	//

	typedef struct lu_s_cell_mem*   	Lu_S_Cell_Mem;

	// 
	// Regions
	//

	typedef struct lu_s_rec_rg*			Lu_S_Rec_Rg;
	typedef struct lu_s_seq_rg*  		Lu_S_Seq_Rg;

	//
	// S
	//
	
	typedef struct lu_s* 				Lu_S;

