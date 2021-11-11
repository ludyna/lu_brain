/**
	Copyright © 2021 Oleh Ihorovych Novosad 

*/

///////////////////////////////////////////////////////////////////////////////
// S

	typedef struct lu_s_comp_view* Lu_S_Comp_View;

	//
	// Slots
	//

	enum lu_s_slot_type {
		LU_S_ST_SINGLE,
		LU_S_ST_MULTI,
		LU_S_ST_END
	};

	typedef struct lu_s_slot_base* Lu_S_Slot_Base;
	
	//
	// Layers
	//

	enum lu_s_layer_type {
		LU_S_LT_COMP,
		LU_S_LT_FRAME,
		LU_S_LT_LAYER,
		LU_S_LT_END
	};

	enum lu_s_comp_view_type {
		LU_S_VLT_V,
		LU_S_VLT_P
	};

	typedef struct lu_s_layer_base* Lu_S_Layer_Base;
	typedef struct lu_s_comp_layer* Lu_S_Comp_Layer;
	typedef struct lu_s_frame_layer* Lu_S_Frame_Layer;
	typedef struct lu_s_layer* Lu_S_Layer;

	// 
	// Apexes
	//

	enum lu_s_apex_type {
		LU_S_AT_SINGLE,
		LU_S_AT_MULTI,
		LU_S_AT_END
	};

	typedef struct lu_s_apex_base* Lu_S_Apex_Base;
	typedef struct lu_s_apex_single* Lu_S_Apex_Single;
	typedef struct lu_s_apex_multi* Lu_S_Apex_Multi;

	//
	// S
	//
	
	typedef struct lu_s* 				Lu_S;

