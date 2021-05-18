/**
	Copyright © 2021 Oleh Ihorovych Novosad
	Ludyna Brain API
*/
#ifndef _LU_BRAIN_PUB_H
#define _LU_BRAIN_PUB_H

#include "lu_types.h"

///////////////////////////////////////////////////////////////////////////////
// Typedefs

	// Brain  
	
	typedef struct lu_brain_config* 	Lu_Brain_Config;
	typedef struct lu_brain* 			Lu_Brain;	
	typedef struct lu_rec_config*		Lu_Rec_Config;
	typedef struct lu_rec* 				Lu_Rec; 

	// Story 
	
	typedef struct lu_data* 			Lu_Data;
	typedef struct lu_story* 			Lu_Story;

	// Wave 
	
	typedef struct lu_neu* 				Lu_Neu;
	typedef struct lu_wave_config*		Lu_Wave_Config;
	typedef struct lu_wave* 			Lu_Wave;

///////////////////////////////////////////////////////////////////////////////
// Lu_Brain_Config 

	struct lu_net_config {
		lu_size names_size; 		// initial maximum number of names

		lu_size size_in_cell_0;
		lu_size size_in_cell_1;
		lu_size size_in_cell_2;
		lu_size size_in_cell_3; 
		lu_size size_in_cell_4;

		lu_size hnn_table_mod;
	};
	
	struct lu_brain_config {
		lu_size id;							// optional, to identify brain by unique id

		lu_size recs_size;					// initial maximum number of recs 

		struct lu_net_config net;
	};

	Lu_Brain_Config lu_brain_config_validate(Lu_Brain_Config config);

	// Lu_Brain_Config predefined 

	enum lu_bc_predefined_type {
		LU_BC_DEFAULT 	= 0,
		LU_BC_END 				
	};

	Lu_Brain_Config lu_brain_config_predefined_get(lu_size id);

///////////////////////////////////////////////////////////////////////////////
// Lu_Brain 

	Lu_Brain lu_brain_create_from_predefined(lu_size size_in_bytes, lu_size predefined_config_id);
	Lu_Brain lu_brain_create(struct lu_brain_config config);
	void lu_brain_destroy(Lu_Brain);

	void lu_brain_print_info(Lu_Brain self);

	struct lu_brain_config lu_brain_config_get(Lu_Brain self);
	Lu_Brain lu_brain_reconfigure(Lu_Brain self, struct lu_brain_config config);

	lu_size lu_brain_recs_size(Lu_Brain self);

///////////////////////////////////////////////////////////////////////////////
// Rec  

	// Lu_Rec_Config 

	enum lu_trans_algorithm {
		LU_TA_NONE = 0,
		LU_TA_STATIC_IMAGE = 1
	};

	struct lu_rec_config {
		lu_size 		width;
		lu_size 		height;
		lu_size 		depth;

		lu_size 		max_blocks_size;
		lu_size 		hold_blocks_size;
		lu_size 		transf_algorithm;

		lu_value 		v_min;
		lu_value 		v_max;
		lu_size			v_neu_size;
		lu_size 		v_nsc;

		lu_size 		p_neu_size;
		lu_size 		p_nsc;  	// nei sim count	
	};

	Lu_Rec_Config lu_rec_config_validate(Lu_Rec_Config self);

	// Lu_Rec_Config predefined 

	enum lu_rc_predefined_type {
		LU_RC_MONOCHROME1_IMAGE = 0,
		LU_RC_MONOCHROME8_IMAGE,
		LU_RC_RBG8_IMAGE,
		LU_RC_RBG16_IMAGE, 
		LU_RC_RBG32_IMAGE,
		LU_RC_TEST1,
		LU_RC_END 				
	};

	Lu_Rec_Config lu_rec_config_predefined_get(lu_size id);

	// Lu_Rec 

	Lu_Rec lu_rec_create_from_predefined(
		Lu_Brain brain, 
		lu_size width, 
		lu_size height, 
		lu_size predefined_config_id
	);		

	Lu_Rec lu_rec_create(Lu_Brain brain, struct lu_rec_config config);
	void lu_rec_destroy(Lu_Rec self);

///////////////////////////////////////////////////////////////////////////////
// Story   

	Lu_Story lu_story_create(Lu_Brain);
	void lu_story_destroy(Lu_Story);

	void lu_story_push(Lu_Story, Lu_Rec, lu_value* data);

	void lu_block_begin(Lu_Story);
	void lu_block_end(Lu_Story);

	void lu_story_reset(Lu_Story); 
	lu_size lu_story_blocks_count(Lu_Story self);
	lu_p_value lu_story_last_values(Lu_Story self, lu_size rec_i);
	Lu_Data lu_story_last_data(Lu_Story self, lu_size rec_i);


///////////////////////////////////////////////////////////////////////////////
// Wave  

	// Lu_Neu 

	lu_size lu_neu_name(Lu_Neu);
	void lu_neu_name_set(Lu_Neu, lu_size);
	void lu_neu_connect(Lu_Neu, Lu_Neu);

	// Lu_Wave

	Lu_Wave lu_wave_create(Lu_Brain brain);
	void lu_wave_destroy(Lu_Wave); 
	Lu_Wave lu_wave_reset(Lu_Wave);

	// Lu_Wave_Config 

	struct lu_wave_config {
		lu_flags 				flags;						// 0 oznachaye not set
		lu_value 				contrast_vs_color;			// blyzhche do 1 ce contrast
		lu_value 				fire_breakpoint;
	};

	Lu_Wave_Config lu_wave_config_validate(Lu_Wave_Config self);

	Lu_Wave lu_wave_config_set(Lu_Wave, struct lu_wave_config);
	struct lu_wave_config lu_wave_config_get(Lu_Wave);
	
	// Lu_Wave_Config Predefined

	enum lu_wc_predefined_type {
		LU_WC_SAVE_DEFAULT = 0,
		LU_WC_FIND_FULL_CONTRAST, 
		LU_WC_FIND_FULL_COLOR,
		LU_WC_END			
	};
	
	Lu_Wave lu_wave_config_predefined_set(Lu_Wave, lu_size id);

	// Lu_Wave Sync

	Lu_Wave lu_wave_save(Lu_Wave, Lu_Story); 
	Lu_Wave lu_wave_save_with_name(Lu_Wave, Lu_Story, lu_size name);
	Lu_Wave lu_wave_find(Lu_Wave, Lu_Story);
	Lu_Wave lu_wave_restore(Lu_Wave, Lu_Neu);

	// Lu_Wave Async

	void lu_wave_save_async(Lu_Wave, Lu_Story);
	void lu_wave_find_async(Lu_Wave, Lu_Story);
	void lu_wave_restore_async(Lu_Wave, Lu_Story);
	Lu_Wave lu_wave_join(Lu_Wave);

	// Lu_Wave Properties

	lu_flags lu_wave_flags(Lu_Wave);
	void lu_wave_flags_set(Lu_Wave, lu_flags);
	void lu_wave_flags_remove(Lu_Wave self, lu_flags flags);

	lu_value lu_wave_color(Lu_Wave);
	void lu_wave_color_set(Lu_Wave, lu_value);

	lu_value lu_wave_contrast(Lu_Wave);
	void lu_wave_contrast_set(Lu_Wave, lu_value);

	lu_value lu_wave_breakpoint(Lu_Wave);
	void lu_wave_breakpoint_set(Lu_Wave, lu_value);

	Lu_Neu lu_wave_top_name_get(Lu_Wave);
	Lu_Neu lu_wave_top_neu_get(Lu_Wave);

	Lu_Neu lu_wave_name_find_or_create(Lu_Wave, lu_size);

#endif // _LU_BRAIN_API_H
