/**
	Copyright © 2022 Oleh Ihorovych Novosad 

*/

///////////////////////////////////////////////////////////////////////////////
// S

	typedef struct lu_s_view_p* Lu_S_View_P;
	typedef struct lu_s_view_v* Lu_S_View_V;

	//
	// Layers
	//

	enum lu_s_layer_type {
		LU_S_LAYER__COMP,
		LU_S_LAYER__REC,
		LU_S_LAYER__LAYER,
		LU_S_LAYER__END
	};

	enum lu_s_layer_tag {
		LU_S_TAQ__NULL,
		LU_S_TAG__COMP,
		LU_S_TAG__REC_BASE,
		LU_S_TAG__FRAME_BASE,
		LU_S_TAG__SEQ_BASE,
		LU_S_TAG__EVENT_BASE,
		LU_S_TAG__SCENE_BASE,
		LU_S_TAG__STORY_BASE,
		LU_S_TAG__OTHER_BASE,
		LU_S_TAG__END
	};

	enum lu_s_view_p_type {
		LU_S_VIEW__V,
		LU_S_VIEW__P
	};

	typedef struct lu_s_layer_base* Lu_S_Layer_Base;
	typedef struct lu_s_layer_comp* Lu_S_Layer_Comp;
	typedef struct lu_s_layer_rec* Lu_S_Layer_Rec;
	typedef struct lu_s_layer* Lu_S_Layer;

	// 
	// Map
	// 

	enum lu_s_map_type {
		LU_S_MAP__STORY,
		LU_S_MAP__FRAME
	};

	typedef struct lu_s_map_base* Lu_S_Map_Base;
	typedef struct lu_s_map_story* Lu_S_Map_Story;
	typedef struct lu_s_map_frame* Lu_S_Map_Frame;

	//
	// S
	//
	
	typedef struct lu_s* Lu_S;

