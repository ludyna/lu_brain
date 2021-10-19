/**
	Copyright © 2021 Oleh Ihorovych Novosad 

*/

///////////////////////////////////////////////////////////////////////////////
// S

	//
	// Layer
	//

	enum lu_s_layer_type {
		LU_S_LT_COMP_V,
		LU_S_LT_COMP_P,
		LU_S_LT_PIXEL,
		LU_S_LT_4,
		LU_S_LT_2,
		LU_S_LT_END
	};

	typedef struct lu_s_layer_base* Lu_S_Layer_Base;
	typedef struct lu_s_layer* Lu_S_Layer;
	typedef struct lu_s_comp_layer* Lu_S_Comp_Layer;


	// 
	// Layer_Mem
	//

	typedef struct lu_s_layer_mem_config* Lu_S_Layer_Mem_Config;
	typedef struct lu_s_layer_mem* Lu_S_Layer_Mem;

	//
	// S
	//
	
	typedef struct lu_s* 				Lu_S;

