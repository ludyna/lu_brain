/**
	Copyright © 2022 Oleh Ihorovych Novosad
	Lu_Brain Public Interface
*/
#ifndef _LU_BRAIN_PUB_H
#define _LU_BRAIN_PUB_H

#include "lu_types.h"

///////////////////////////////////////////////////////////////////////////////
// Typedefs

	//
	// Mem
	//

	typedef struct lu_mem*  			Lu_Mem;

	//
	// Brain  
	//
 
	typedef struct lu_config* 			Lu_Config;

	typedef struct lu_brain* 			Lu_Brain;	
	
	typedef struct lu_rec_comp_config*  Lu_Rec_Comp_Config;
	typedef struct lu_rec_config*		Lu_Rec_Config;
	typedef struct lu_rec* 				Lu_Rec; 

	//
	// Wave 
	//

	typedef struct lu_data* 			Lu_Data;
	typedef struct lu_neu* 				Lu_Neu;
	typedef struct lu_process_config*	Lu_Process_Config;
	typedef struct lu_wave* 			Lu_Wave;

///////////////////////////////////////////////////////////////////////////////
// Lu_Config 

	struct lu_config {
		//
		// Brain level
		//
		Lu_Mem b_mem;						// if NULL initialize to default
		lu_size b_id;						// optional, to identify brain by unique id
		lu_size b_recs_size;				// initial maximum number of recs 
		lu_size b_max_seq_size_in_blocks; 	// max seq size in blocks

		//
		// Structure level
		//
		Lu_Mem s_mem;						// if NULL initialize to default
		lu_size s_frames_size; 				// initial maximum number of frames
		lu_size s_apexes_size;				// initial maximum number of apexes

		//
		// Network level
		//
		Lu_Mem n_mem;						// if NULL initialize to default
		lu_size n_names_size; 				// initial maximum number of names
		lu_size n_size_in_cell_0;
		lu_size n_size_in_cell_1;
		lu_size n_size_in_cell_2;
		lu_size n_size_in_cell_3; 
		lu_size n_size_in_cell_4;
		lu_size n_table_mod;	
		lu_size n_column_w;
		lu_size n_column_h;
		lu_size n_column_d;

		//
		// Waves level
		//
		Lu_Mem w_mem;						// if NULL initialize to default
		lu_size w_waves_size;				// waves size
	};

	Lu_Config lu_config__validate(Lu_Config config);

	//
	// Lu_Config predefined 
	//

	enum lu_config_type {
		LU_CONFIG__DEFAULT 	= 0,
		LU_CONFIG__END 				
	};

	struct lu_config lu_config__get_by_id(lu_size id);

///////////////////////////////////////////////////////////////////////////////
// Lu_Brain 

	Lu_Brain lu_brain__create(struct lu_config config);
	void lu_brain__destroy(Lu_Brain);

	void lu_brain__print_info(Lu_Brain self);

	Lu_Brain lu_brain__reconfig(Lu_Brain self, struct lu_config config);

	lu_size lu_brain__recs_size(Lu_Brain self); 

	// After you added recs call this method to build or rebuild brain.  
	// Method returns NULL if build failed.
	Lu_Brain lu_brain__build(Lu_Brain self);

	Lu_Wave lu_brain__get_wave_by_id(Lu_Brain self, lu_size id);

///////////////////////////////////////////////////////////////////////////////
// Lu_Rec  

	//
	// Lu_Rec_Comp_Config 
	// Rec component config.
	//

	struct lu_rec_comp_config {
		// At this moment every component will use the same v and p config
		// but we can easily change it in future (s architecture already supports this)
		lu_value 		v_min;
		lu_value 		v_max;
		lu_size			v_neu_size;
		lu_size 		p_neu_size;
	};

	Lu_Rec_Comp_Config lu_rec_comp_config__validate(Lu_Rec_Comp_Config self);

	//
	// Lu_Rec_Config 
	//

	enum lu_trans_algorithm {
		LU_ALGORITHM__NONE = 0,
		LU_ALGORITHM__IMAGE = 1
	};

	struct lu_rec_config {
		// lu_size 		max_blocks_size; // !!! should be in seq not here

		lu_size 		hold_blocks_size;
		lu_size 		transf_algorithm;

		struct lu_rec_comp_config comp_config;
	};

	Lu_Rec_Config lu_rec_config__validate(Lu_Rec_Config self);
	Lu_Rec_Comp_Config lu_rec_config__get_comp_config(Lu_Rec_Config self, lu_size comp_index);

	//
	// Lu_Rec_Config predefined 
	//

	enum lu_rec_config_type {
		LU_REC__MONO1_IMAGE = 0,
		LU_REC__MONO8_IMAGE,
		LU_REC__RBG8_IMAGE,
		LU_REC__RBG16_IMAGE, 
		LU_REC__RBG32_IMAGE,
		LU_REC__TEST1,
		LU_REC__END 				
	};

	struct lu_rec_config lu_rec_config__get_by_id(lu_size id);

	//
	// Lu_Rec 
	//

	Lu_Rec lu_brain__rec_add(
		Lu_Brain brain, 
		lu_size width, 
		lu_size height, 
		lu_size depth,
		struct lu_rec_config config
	);		

	// MVP out of scope
	// void lu_brain__rec_remove(Lu_Rec self);
 
	lu_size lu_rec__get_id(Lu_Rec self);

	Lu_Rec lu_brain__get_rec_by_id(Lu_Brain brain, lu_size rec_id);

///////////////////////////////////////////////////////////////////////////////
// Lu_Process_Config 

	struct lu_process_config {
		lu_flags 				flags;						// 0 oznachaye not set

		lu_value 				p_potency;					// "contrast" potency
		lu_value 				v_potency;					// value potency

		lu_value 				min_potency;				// ignore potencies below this value
		lu_value 				min_fire_potency;			// fire neurons with potency above this value
		
		lu_size 				block_layers_size;			// How many wave block_layers should we hold.
															// Oldest ones are destroyed once limit is reached (FIFO).
	};

	Lu_Process_Config lu_process_config__validate(Lu_Process_Config self);
	
	//
	// Lu_Process_Config Predefined
	//

	enum lu_process_config_type {
		LU_PROCESS__SAVE_DEFAULT = 0,
		LU_PROCESS__MATCH_DIFF_ONLY, 
		LU_PROCESS__MATCH_VALUE_ONLY,
		LU_PROCESS__END			
	};

	struct lu_process_config lu_process_config__get_by_id(lu_size id);

///////////////////////////////////////////////////////////////////////////////
// Lu_Wave  

	//
	// Sync Create
	//

	Lu_Wave lu_save_wave__create(Lu_Brain); 
	Lu_Wave lu_match_wave__create(Lu_Brain);
	Lu_Wave lu_restore_wave__create(Lu_Brain);

	//
	// Destroy
	//

	void lu_wave__destroy(Lu_Wave); 


	// Wave Level

	void lu_wave__start_layer(Lu_Wave, lu_size level);

	//
	// Wave Seq
	// Same as lu_wave__start_level(wave, 0)
	//

	#define lu_wave__start_seq(self) lu_wave__start_layer(self, 0)
	#define lu_wave__start_event(self) lu_wave__start_layer(self, 1)
	#define lu_wave__start_chapter(self) lu_wave__start_layer(self, 2)
	#define lu_wave__start_story(self) lu_wave__start_layer(self, 3)

	// Wave Block

	void lu_wave__block_begin(Lu_Wave);
	void lu_wave__block_end(Lu_Wave);

	// Wave Data

	void lu_wave__push(Lu_Wave, Lu_Rec, lu_value* data);
	void lu_wave__push_neu(Lu_Wave, Lu_Neu); 


	// lu_size lu_wave_block_count(Lu_Wave);
	// Lu_Data lu_wave_last_data(Lu_Wave, Lu_Rec);

	//
	// Process
	//

	void lu_wave__step(Lu_Wave, struct lu_process_config);
	void lu_wave__process(Lu_Wave, struct lu_process_config);

	// Process Async (IMPLEMENT LATER)
	// void lu_wave_process_async(Lu_Wave, Lu_Data_Seq);
	// void lu_wave_restore_process_async(Lu_Wave, Lu_Neu);
	// void lu_wave_step_async(Lu_Wave, Lu_Data_Seq);
	// void lu_wave_restore_step_async(Lu_Wave, Lu_Data_Seq);
	// void lu_wave_join(Lu_Wave);

	//
	// Properties
	//

	struct lu_process_config lu_wave__get_process_config(Lu_Wave);
	lu_size lu_wave__get_id(Lu_Wave);

///////////////////////////////////////////////////////////////////////////////
// Lu_Neu 

	lu_size lu_neu__name(Lu_Neu);
	void lu_neu__name_set(Lu_Neu, lu_size);
	void lu_neu__connect(Lu_Neu, Lu_Neu);

#endif // _LU_BRAIN_API_H
