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

	// 
	// Cell_Mem
	//

	typedef struct lu_s_cell_mem_config* Lu_S_Cell_Mem_Config;
	typedef struct lu_s_cell_mem*   	Lu_S_Cell_Mem;


	//
	// S
	//
	
	typedef struct lu_s* 				Lu_S;

