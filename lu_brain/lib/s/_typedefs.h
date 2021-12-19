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

	typedef struct lu_s_layer_base* Lu_S_Layer_Base;
	typedef struct lu_s_comp_layer* Lu_S_Comp_Layer;
	typedef struct lu_s_rexel_layer* Lu_S_Rexel_Layer;
	typedef struct lu_s_layer* Lu_S_Layer;

	//
	// S
	//
	
	typedef struct lu_s* 				Lu_S;

