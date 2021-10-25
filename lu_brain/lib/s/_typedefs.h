/**
	Copyright © 2021 Oleh Ihorovych Novosad 

*/

///////////////////////////////////////////////////////////////////////////////
// S

	typedef struct lu_s_comp_view* Lu_S_Comp_View;
	
	//
	// Layer
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
	// Layer_Mem
	//

	typedef struct lu_s_layer_mem_config* Lu_S_Layer_Mem_Config;
	typedef struct lu_s_layer_mem* Lu_S_Layer_Mem;

	//
	// S
	//
	
	typedef struct lu_s* 				Lu_S;

