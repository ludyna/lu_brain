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

	enum lu_s_layer_tag {
		LU_S_TAG__NULL,
		LU_S_TAG__COMP,
		LU_S_TAG__REC_BASE,
		LU_S_TAG__REC_STEP,
		LU_S_TAG__FRAME_BASE,
		LU_S_TAG__FRAME_STEP,
		LU_S_TAG__SEQ_BASE,
		LU_S_TAG__SEQ_STEP,
		LU_S_TAG__EVENT_BASE,
		LU_S_TAG__EVENT_STEP,
		LU_S_TAG__SCENE_BASE,
		LU_S_TAG__SCENE_STEP,
		LU_S_TAG__STORY_BASE,
		LU_S_TAG__STORY_STEP,
		LU_S_TAG__OTHER_BASE,
		LU_S_TAG__OTHER_STEP,
		LU_S_TAG__END
	};

	static inline void lu_s_layer_tag__to_str(enum lu_s_layer_type type, char buffer[])
	{
		switch(type)
		{
			case LU_S_TAG__NULL:
				strcpy(buffer, "NULL");
				break;
			case LU_S_TAG__COMP:
				strcpy(buffer, "COMP");
				break;
			case LU_S_TAG__REC_BASE:
				strcpy(buffer, "REC_BASE");
				break;
			case LU_S_TAG__REC_STEP:
				strcpy(buffer, "REC_STEP");
				break;
			case LU_S_TAG__FRAME_BASE:
				strcpy(buffer, "FRAME_BASE");
				break;
			case LU_S_TAG__FRAME_STEP:
				strcpy(buffer, "FRAME_STEP");
				break;
			case LU_S_TAG__SEQ_BASE:
				strcpy(buffer, "SEQ_BASE");
				break;
			case LU_S_TAG__SEQ_STEP:
				strcpy(buffer, "SEQ_STEP");
				break;
			case LU_S_TAG__EVENT_BASE:
				strcpy(buffer, "EVENT_BASE");
				break;
			case LU_S_TAG__EVENT_STEP:
				strcpy(buffer, "EVENT_STEP");
				break;
			case LU_S_TAG__SCENE_BASE:
				strcpy(buffer, "SCENE_BASE");
				break;
			case LU_S_TAG__SCENE_STEP:
				strcpy(buffer, "SCENE_STEP");
				break;
			case LU_S_TAG__STORY_BASE:
				strcpy(buffer, "STORY_BASE");
				break;
			case LU_S_TAG__STORY_STEP:
				strcpy(buffer, "STORY_STEP");
				break;
			case LU_S_TAG__OTHER_BASE:
				strcpy(buffer, "OTHER_BASE");
				break;
			case LU_S_TAG__OTHER_STEP:
				strcpy(buffer, "OTHER_STEP");
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

