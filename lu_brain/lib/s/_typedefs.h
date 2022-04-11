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

	static inline void lu_s_layer_type__to_str(enum lu_s_layer_type type, char buffer[])
	{
		switch(type)
		{
			case LU_S_LAYER__COMP:
				strcpy(buffer, "COMP");
				break;
			case LU_S_LAYER__REC:
				strcpy(buffer, "REC");
				break;
			case LU_S_LAYER__LAYER:
				strcpy(buffer, "LAYER");
				break;
			default:
				strcpy(buffer, "(!) UNKNOWN");
				break;
		}
	}

	enum lu_s_tag {
		LU_S_TAG__NULL,
		LU_S_TAG__COMP,
		LU_S_TAG__REC,
		LU_S_TAG__FRAME,
		LU_S_TAG__SEQ,
		LU_S_TAG__EVENT,
		LU_S_TAG__SCENE,
		LU_S_TAG__STORY,
		LU_S_TAG__OTHER,
		LU_S_TAG__END
	};

	static inline void lu_s_tag__to_str(enum lu_s_layer_type type, char buffer[])
	{
		switch(type)
		{
			case LU_S_TAG__NULL:
				strcpy(buffer, "NULL");
				break;
			case LU_S_TAG__COMP:
				strcpy(buffer, "COMP");
				break;
			case LU_S_TAG__REC:
				strcpy(buffer, "REC");
				break;
			case LU_S_TAG__FRAME:
				strcpy(buffer, "FRAME");
				break;
			case LU_S_TAG__SEQ:
				strcpy(buffer, "SEQ");
				break;
			case LU_S_TAG__EVENT:
				strcpy(buffer, "EVENT");
				break;
			case LU_S_TAG__SCENE:
				strcpy(buffer, "SCENE");
				break;
			case LU_S_TAG__STORY:
				strcpy(buffer, "STORY");
				break;
			case LU_S_TAG__OTHER:
				strcpy(buffer, "OTHER");
				break;
			default:
				strcpy(buffer, "(!) UNKNOWN");
				break;
		}
	}

	enum lu_s_view_p_type {
		LU_S_VIEW__V,
		LU_S_VIEW__P
	};

	typedef struct lu_s_layer_base* Lu_S_Layer_Base;
	typedef struct lu_s_layer_comp* Lu_S_Layer_Comp;
	typedef struct lu_s_layer_rec* Lu_S_Layer_Rec;
	typedef struct lu_s_layer* Lu_S_Layer;

	//
	// Area
	//

	typedef struct lu_s_area* Lu_S_Area;

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

