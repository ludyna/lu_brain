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
	// Structure 
	// 

	enum lu_area_tag {
		LU_AREA_TAG__NULL,
		LU_AREA_TAG__COMP,
		LU_AREA_TAG__REC,
		LU_AREA_TAG__FRAME,
		LU_AREA_TAG__SEQ,
		LU_AREA_TAG__EVENT,
		LU_AREA_TAG__SCENE,
		LU_AREA_TAG__STORY,
		LU_AREA_TAG__OTHER,
		LU_AREA_TAG__END
	};

	//
	// Wave 
	// 

	enum lu_wave_type {
		LU_WAVE__SAVE,
		LU_WAVE__MATCH,
		LU_WAVE__RESTORE
	};


	typedef union lu_w_addr* Lu_W_Addr;
	typedef struct lu_w_cell* Lu_W_Cell; 

	typedef struct lu_process_config*	Lu_Process_Config;
	typedef struct lu_wave* 			Lu_Wave; 

	//
	// Label
	//

	typedef struct lu_label* Lu_Label;
	typedef struct lu_la_cell* Lu_La_Cell;

///////////////////////////////////////////////////////////////////////////////
// Lu_Config 

	struct lu_config {
		//
		// Brain level
		//
		Lu_Mem b_mem;								// if NULL initialize to default
		lu_size b_id;								// optional, to identify brain by unique id
		lu_size b_recs_size;						// initial maximum number of recs 
		lu_size b_max_seq_size_in_blocks; 			// max seq size in blocks

		//
		// Space
		//
		Lu_Mem s_mem;								// if NULL initialize to default
		lu_size s_apexes_size;						// initial maximum number of apexes
		lu_size s_areas_size;						// initial number of areas

		//
		// Network 
		//
		Lu_Mem n_mem;								// if NULL initialize to default
		lu_size n_names_size; 						// initial maximum number of names
		lu_size n_size_in_cell_0;
		lu_size n_size_in_cell_1;
		lu_size n_size_in_cell_2;
		lu_size n_size_in_cell_3; 
		lu_size n_size_in_cell_4;
		lu_size s_table_mod;	
		lu_size s_column_w;
		lu_size s_column_h;
		lu_size s_column_d;
		lu_size n_link_mem_size;

		//
		// Waves 
		//
		Lu_Mem w_mem;								// if NULL initialize to default

		//
		// Save wave
		//
		lu_size w_save_waves_size;					// save waves size 
		lu_value w_save_sig_breakpoint;				// [0, 1]

		//
		// Match wave
		//
		lu_size w_match_waves_size;					// match waves size
		lu_value w_match_sig_breakpoint;			// [0, 1]
		lu_size w_match_processor_queue_size;		// 
		lu_size w_match_results_size;				//
		lu_size w_match_cells_size_per_wave;		//			

		//
		// Restore wave 
		//

		lu_size w_restore_waves_size;				// restore waves size

		//
		// Labels
		//
		Lu_Mem la_mem;
		lu_size la_labels_size;
		lu_size la_link_mem_size;
	};

	Lu_Config lu_config__validate(Lu_Config config);

	//
	// Lu_Config predefined 
	//

	enum lu_config_type {
		LU_CONFIG__DEFAULT 	= 0,
		LU_CONFIG__SEMEION = 1,
		LU_CONFIG__END 				
	};

	struct lu_config lu_config__get_by_id(lu_size id);

///////////////////////////////////////////////////////////////////////////////
// Lu_Brain 

	Lu_Brain lu_brain__create(struct lu_config config);
	void lu_brain__destroy(Lu_Brain);

	void lu_brain__print_info(Lu_Brain self);

	void lu_brain__print_areas(Lu_Brain self);
	void lu_brain__print_net_stats(Lu_Brain self);

	Lu_Brain lu_brain__reconfig(Lu_Brain self, struct lu_config config);

	lu_size lu_brain__recs_size(Lu_Brain self); 

	// After you added recs call this method to build or rebuild brain.  
	// Method returns NULL if build failed.
	Lu_Brain lu_brain__build(Lu_Brain self);

	Lu_Wave lu_brain__get_wave_by_ix(Lu_Brain self, lu_size wave_ix, enum lu_wave_type wave_type);

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

	//
	// Setup view 
	//

	void lu_rec__set_src_start_pos(Lu_Rec, lu_size src_x, lu_size src_y);
	void lu_rec__set_src_end_pos(Lu_Rec self, lu_size src_x, lu_size src_y);
	void lu_rec__set_src_start_z(Lu_Rec, lu_size src_z);
	void lu_rec__set_src_end_z(Lu_Rec self, lu_size src_z);

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

		lu_size 				result_labels_size;
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

	Lu_Wave lu_wave__create_save_wave(Lu_Brain); 
	Lu_Wave lu_wave__create_match_wave(Lu_Brain);
	Lu_Wave lu_wave__create_restore_wave(Lu_Brain);

	//
	// Destroy
	//

	void lu_wave__destroy(Lu_Wave); 

	//
	// Wave Reset
	//

	void lu_wave__reset(Lu_Wave);

	//
	// Wave Level
	//

	void lu_wave__start_layer(Lu_Wave, lu_size level);

	//
	// Wave Block
	//

	void lu_wave__block_begin(Lu_Wave);
	void lu_wave__block_end(Lu_Wave);

	//
	// Focus
	//
	void lu_wave__set_dest_start_pos(Lu_Wave, Lu_Rec, lu_long dest_x, lu_long dest_y);

	//
	// Wave Data
	//

	void lu_wave__push(Lu_Wave, Lu_Rec, lu_value* src, lu_size src_width, lu_size src_height, lu_size src_depth);

	//
	// Process
	//

	void lu_wave__step(Lu_Wave, struct lu_process_config);
	void lu_wave__process(Lu_Wave, struct lu_process_config);

	//
	// Get
	//

	struct lu_process_config lu_wave__get_process_config(Lu_Wave);
	lu_size lu_wave__get_id(Lu_Wave);
	lu_size lu_wave__get_ix(Lu_Wave);
	enum lu_wave_type lu_wave__get_type(Lu_Wave);

	//
	// Wave label
	//

	Lu_La_Cell lu_wave__link_to_label(Lu_Wave, lu_size area_ix, lu_size layer_ix, lu_size x, lu_size y, lu_size label); 
	Lu_Label* lu_wave__get_result_labels(Lu_Wave);

	//
	// Match only
	// 

	lu_size lu_wave__get_fired_cells_count(Lu_Wave self);
	void lu_wave__print_match_results(Lu_Wave self);

///////////////////////////////////////////////////////////////////////////////
// Lu_Label

	lu_size lu_label__get_id(Lu_Label self);
	lu_value lu_label__get_sig(Lu_Label self);


#endif // _LU_BRAIN_API_H
