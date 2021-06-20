/**
	Copyright © 2021 Oleh Ihorovych Novosad
	Ludyna Brain API
*/
#ifndef _LU_BRAIN_PUB_H
#define _LU_BRAIN_PUB_H

#include "lu_types.h"
	// #include "lib/lib/mem_abstractors/_module.h"
	// #include "lib/lib/mem_debuggers/_module.h"

///////////////////////////////////////////////////////////////////////////////
// Typedefs

	// Mem

	typedef struct lu_mem*  			Lu_Mem;

	// Brain  
	
	typedef struct lu_brain_config* 	Lu_Brain_Config;
	typedef struct lu_brain* 			Lu_Brain;	
	typedef struct lu_rec_config*		Lu_Rec_Config;
	typedef struct lu_rec* 				Lu_Rec; 

	// Wave 
	
	typedef struct lu_data* 			Lu_Data;
	typedef struct lu_neu* 				Lu_Neu;
	typedef struct lu_wave_config*		Lu_Wave_Config;
	typedef struct lu_wave* 			Lu_Wave;

///////////////////////////////////////////////////////////////////////////////
// Lu_Brain_Config 

	struct lu_net_config {
		lu_size names_size; 				// initial maximum number of names

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

		struct lu_net_config net;			// initial values
	};

	Lu_Brain_Config lu_brain_config_validate(Lu_Brain_Config config);

	// Lu_Brain_Config predefined 

	enum lu_bc_predefined_type {
		LU_BC_DEFAULT 	= 0,
		LU_BRAIN_CONFIG_END 				
	};

	struct lu_brain_config lu_brain_config_get_by_id(lu_size id);

///////////////////////////////////////////////////////////////////////////////
// Lu_Brain 

	Lu_Brain lu_brain_create(Lu_Mem, struct lu_brain_config config);
	void lu_brain_destroy(Lu_Brain);

	void lu_brain_print_info(Lu_Brain self);

	Lu_Brain lu_brain_reconfigure(Lu_Brain self, struct lu_brain_config config);

	lu_size lu_brain_recs_size(Lu_Brain self);

///////////////////////////////////////////////////////////////////////////////
// Lu_Rec  

	// Lu_Rec_Config 

	enum lu_trans_algorithm {
		LU_TA_NONE = 0,
		LU_TA_STATIC_IMAGE = 1
	};

	struct lu_rec_config {
		lu_size 		max_blocks_size;
		lu_size 		hold_blocks_size;
		lu_size 		transf_algorithm;

		lu_value 		v_min;
		lu_value 		v_max;
		lu_size			v_neu_size;
		lu_size 		p_neu_size;
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
		LU_REC_CONFIG_END 				
	};

	struct lu_rec_config lu_rec_config_get_by_id(lu_size id);

	// Lu_Rec 

	Lu_Rec lu_brain_rec_add(
		Lu_Brain brain, 
		lu_size width, 
		lu_size height, 
		lu_size depth,
		struct lu_rec_config config
	);		

	// MVP out of scope
	// void lu_brain_rec_remove(Lu_Rec self);

	Lu_Rec lu_brain_rec_get_by_id(Lu_Brain brain, lu_size rec_id);

///////////////////////////////////////////////////////////////////////////////
// Lu_Wave_Config 

	struct lu_wave_config {
		lu_flags 				flags;						// 0 oznachaye not set
		lu_value 				contrast_vs_color;			// blyzhche do 1 ce contrast
		lu_value 				fire_breakpoint;
	};

	Lu_Wave_Config lu_wave_config_validate(Lu_Wave_Config self);
	
	// Lu_Wave_Config Predefined

	enum lu_wc_predefined_type {
		LU_WC_SAVE_DEFAULT = 0,
		LU_WC_FIND_FULL_CONTRAST, 
		LU_WC_FIND_FULL_COLOR,
		LU_WAVE_CONFIG_END			
	};

	struct lu_wave_config lu_wave_config_get_by_id(lu_size id);

///////////////////////////////////////////////////////////////////////////////
// Wave  

	// Sync Create

	Lu_Wave lu_save_wave_create(Lu_Mem, Lu_Brain, struct lu_wave_config); 
	Lu_Wave lu_find_wave_create(Lu_Mem, Lu_Brain, struct lu_wave_config);
	Lu_Wave lu_restore_wave_create(Lu_Mem, Lu_Brain, struct lu_wave_config);

	// Destroy
	void lu_wave_destroy(Lu_Wave); 

	// Wave Story

	void lu_wave_block_begin(Lu_Wave);
	void lu_wave_block_end(Lu_Wave);

	void lu_wave_push(Lu_Wave, Lu_Rec, lu_value* data);
	void lu_wave_push_neu(Lu_Wave, Lu_Neu); 

	void lu_wave_reset(Lu_Wave);

	// lu_size lu_wave_block_count(Lu_Wave);
	// Lu_Data lu_wave_last_data(Lu_Wave, Lu_Rec);

	// Process

	void lu_wave_process(Lu_Wave);
	void lu_wave_step(Lu_Wave);

	// Process Async (IMPLEMENT LATER)
	// void lu_wave_process_async(Lu_Wave, Lu_Story);
	// void lu_wave_restore_process_async(Lu_Wave, Lu_Neu);
	// void lu_wave_step_async(Lu_Wave, Lu_Story);
	// void lu_wave_restore_step_async(Lu_Wave, Lu_Story);
	// void lu_wave_join(Lu_Wave);

	// Properties

	struct lu_wave_config lu_wave_config_get(Lu_Wave);

///////////////////////////////////////////////////////////////////////////////
// Lu_Neu 

	lu_size lu_neu_name(Lu_Neu);
	void lu_neu_name_set(Lu_Neu, lu_size);
	void lu_neu_connect(Lu_Neu, Lu_Neu);

#endif // _LU_BRAIN_API_H
