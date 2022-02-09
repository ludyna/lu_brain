/**
	Copyright © 2022 Oleh Ihorovych Novosad 

*/

///////////////////////////////////////////////////////////////////////////////
// S

	typedef struct lu_s_comp_view* Lu_S_Comp_View;

	//
	// Layers
	//

	enum lu_s_layer_type {
		LU_S_LT__COMP,
		LU_S_LT__FRAME,
		LU_S_LT__LAYER,
		LU_S_LT__END
	};

	enum lu_s_comp_view_type {
		LU_S_CVT__V,
		LU_S_CVT__P
	};

	typedef struct lu_s_layer_base_config* Lu_S_Layer_Base_Config;

	typedef struct lu_s_layer_base* Lu_S_Layer_Base;
	typedef struct lu_s_layer_comp* Lu_S_Layer_Comp;
	typedef struct lu_s_layer_frame* Lu_S_Layer_Frame;
	typedef struct lu_s_layer* Lu_S_Layer;

	// 
	// Map
	// 

	enum lu_s_map_type {
		LU_S_MT__STORY,
		LU_S_MT__FRAME
	};

	typedef struct lu_s_map_base* Lu_S_Map_Base;
	typedef struct lu_s_map_story* Lu_S_Map_Story;
	typedef struct lu_s_map_frame* Lu_S_Map_Frame;

	//
	// S
	//
	
	typedef struct lu_s* 				Lu_S;

