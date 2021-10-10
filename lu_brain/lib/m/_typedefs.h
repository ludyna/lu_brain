/**
	Copyright © 2021 Oleh Ihorovych Novosad 

*/

///////////////////////////////////////////////////////////////////////////////
// S

	// 
	// Slots
	// 

	typedef struct lu_m_slot_1* Lu_M_Slot_1;
	typedef struct lu_m_slot_2* Lu_M_Slot_2;
	typedef struct lu_m_slot_4* Lu_M_Slot_4;

	//
	// Cells
	//

	enum lu_m_cell_type {
		LU_SCT_COMPONTENT,
		LU_SCT_PIXEL,
		LU_SCT_REC,
		LU_SCT_SEQ_NX,
		LU_SCT_SEQ,
		LU_SCT_STORY_NX
	};

 	typedef struct lu_m_base_cell* 				Lu_M_Base_Cell;
 	typedef struct lu_m_comp_cell* 				Lu_M_Comp_Cell;

	// 
	// Cell_Mem
	//

	typedef struct lu_m_cell_mem_config* Lu_M_Cell_Mem_Config;
	typedef struct lu_m_cell_mem*   	Lu_M_Cell_Mem;


	//
	// S
	//
	
	typedef struct lu_m* 				Lu_M;

