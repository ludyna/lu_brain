/**
	Copyright © 2022 Oleh Ihorovych Novosad
	Lu_Brain Public Interface
*/
#ifndef _LU_BRAIN_PUB_H
#define _LU_BRAIN_PUB_H

#include "lu_types.h"

///////////////////////////////////////////////////////////////////////////////
// Header

	//
	// Mem
	//

	typedef struct lu_mem*  			Lu_Mem;

	//
	// Brain  
	//
 
	typedef struct lu_config* 			Lu_Config;
	typedef struct lu_brain_net_stats*	Lu_Brain_Net_Stats;

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
		LU_WAVE__RESTORE,
		LU_WAVE__DELETE
	};

	typedef struct lu_wave* 			Lu_Wave; 

	typedef struct lu_save_config* 		Lu_Save_Config;
	typedef struct lu_save_wave* 		Lu_Save_Wave;

	typedef struct lu_match_config* 	Lu_Match_Config;
	typedef struct lu_match_wave* 		Lu_Match_Wave;

	typedef struct lu_restore_config* 	Lu_Restore_Config;
	typedef struct lu_restore_wave* 	Lu_Restore_Wave;

	typedef struct lu_delete_config*  	Lu_Delete_Config;
	typedef struct lu_delete_wave*		Lu_Delete_Wave;

	//
	// Label
	//

	typedef struct lu_label* Lu_Label;
	typedef struct lu_la_cell* Lu_La_Cell;

	//
	// Lu_N_Addr
	// 

	#define LU_N_CELL_IX__SIZE 16
	#define LU_N_COLUMN_IX__SIZE 24
	#define LU_N_LAYER_IX__SIZE 16
	#define LU_N_AREA_IX__SIZE 8

	union lu_n_addr {
		struct {
			lu_size cell_ix : LU_N_CELL_IX__SIZE;
			lu_size column_ix: LU_N_COLUMN_IX__SIZE;
			lu_size layer_ix: LU_N_LAYER_IX__SIZE;
			lu_size area_ix: LU_N_AREA_IX__SIZE;
		};
		lu_size value;
	};

	typedef union lu_n_addr* Lu_N_Addr;

	//
	// Brain Config
	// 

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
		// Delete wave
		//

		lu_size w_delete_waves_size;

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
		LU_CONFIG__SEMEION_01 = 1,
		LU_CONFIG__SEMEION_02 = 2,
		LU_CONFIG__END 				
	};

	struct lu_config lu_config__get_by_id(lu_size id);

	//
	// Brain stats
	// 

	struct lu_brain_net_stats {

		// to be expanded later..

		lu_size n_cells_count;
		lu_size n_cells_size;
		lu_size n_links_count;
		lu_size n_links_size;
	};

///////////////////////////////////////////////////////////////////////////////
// Lu_Brain 

	Lu_Brain lu_brain__create(struct lu_config config);
	void lu_brain__destroy(Lu_Brain);

	void lu_brain__print_info(Lu_Brain self);

	void lu_brain__print_areas(Lu_Brain self);
	void lu_brain__print_net_stats(Lu_Brain self);
	struct lu_brain_net_stats lu_brain__get_net_stats(Lu_Brain self);

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

	Lu_Rec lu_brain__add_rec(
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
// Lu_Wave  

	struct lu_save_config lu_wave__get_process_config(Lu_Wave);
	lu_size lu_wave__get_id(Lu_Wave);
	lu_size lu_wave__get_ix(Lu_Wave);
	enum lu_wave_type lu_wave__get_type(Lu_Wave);

///////////////////////////////////////////////////////////////////////////////
// Lu_Save_Wave 

	// 
	// Save Config
	// 
	struct lu_save_config {
		// lu_flags 				flags;						// 0 oznachaye not set

		// lu_value 				p_potency;					// "contrast" potency
		// lu_value 				v_potency;					// value potency

		// lu_value 				min_potency;				// ignore potencies below this value
		// lu_value 				min_fire_potency;			// fire neurons with potency above this value
		
		// lu_size 				block_layers_size;			// How many wave block_layers should we hold.
		// 													// Oldest ones are destroyed once limit is reached (FIFO).

		// lu_size 				result_labels_size;
	};

	extern struct lu_save_config LU_SAVE_CONFIG__DEFAULT;

	//
	// Constructor / Destructor
	// 

	Lu_Save_Wave lu_save_wave__create(Lu_Brain); 
	void lu_save_wave__destroy(Lu_Save_Wave);

	//
	// Focus
	//

	void lu_save_wave__set_dest_start_pos(Lu_Save_Wave, Lu_Rec, lu_long dest_x, lu_long dest_y);
	void lu_save_wave__set_src_start_pos(Lu_Save_Wave, Lu_Rec, lu_size src_x, lu_size src_y);
	void lu_save_wave__set_src_end_pos(Lu_Save_Wave, Lu_Rec, lu_size src_x, lu_size src_y);

	//
	// Data
	//

	

	void lu_save_wave__block_begin(Lu_Save_Wave);
	void lu_sace_wave__block_end(Lu_Save_Wave);

	void lu_save_wave__push(Lu_Save_Wave, Lu_Rec, lu_value* src, lu_size src_width, lu_size src_height, lu_size src_depth);

	void lu_save_wave__save_step(Lu_Save_Wave, struct lu_save_config);
	void lu_save_wave__save(Lu_Save_Wave, struct lu_save_config);

	Lu_La_Cell lu_save_wave__link_to_label(Lu_Save_Wave, lu_size area_ix, lu_size layer_ix, lu_size x, lu_size y, lu_size label); 

	//
	// Fractal
	//

	void lu_save_wave__start_layer(Lu_Save_Wave, lu_size level);

	//
	// Other
	// 

	void lu_save_wave__reset_2(Lu_Save_Wave);

///////////////////////////////////////////////////////////////////////////////
// Lu_Match_Wave   

	//
	// Match Config
	//

	struct lu_match_config {
		lu_size w_match_results_size;
	};

	extern struct lu_match_config LU_MATCH_CONFIG__DEFAULT;

	Lu_Match_Config lu_match_config__validate(Lu_Match_Config self);

	//
	// Constructor / Destructor
	// 

	Lu_Match_Wave lu_match_wave__create(Lu_Brain); 
	void lu_match_wave__destroy(Lu_Match_Wave);

	//
	// Focus
	//

	void lu_match_wave__set_dest_start_pos(Lu_Match_Wave, Lu_Rec, lu_long dest_x, lu_long dest_y);
	void lu_match_wave__set_src_start_pos(Lu_Match_Wave, Lu_Rec, lu_size src_x, lu_size src_y);
	void lu_match_wave__set_src_end_pos(Lu_Match_Wave, Lu_Rec, lu_size src_x, lu_size src_y);

	//
	// Data
	//

	void lu_match_wave__block_begin(Lu_Match_Wave);
	void lu_match_wave__block_end(Lu_Match_Wave);

	void lu_match_wave__push(Lu_Match_Wave, Lu_Rec, lu_value* src, lu_size src_width, lu_size src_height, lu_size src_depth);

	void lu_match_wave__match_step(Lu_Match_Wave, struct lu_match_config);
	void lu_match_wave__match(Lu_Match_Wave, struct lu_match_config); 

	lu_size lu_match_wave__get_fired_cells_count(Lu_Match_Wave self);
	Lu_Label* lu_match_wave__get_result_labels(Lu_Match_Wave);
	void lu_match_wave__print_results(Lu_Match_Wave self);

	//
	// Other
	//

	void lu_match_wave__reset(Lu_Match_Wave);

///////////////////////////////////////////////////////////////////////////////
// Lu_Delete_Wave  

	//
	// Delete Config
	//

	struct lu_delete_config {
		lu_bool include_children;
		lu_size processor_list_size;
	};

	extern struct lu_delete_config LU_DELETE_CONFIG__DEFAULT;

	//
	// Constructor / Destructor
	// 

	Lu_Delete_Wave lu_delete_wave__create(Lu_Brain, struct lu_delete_config config); 
	void lu_delete_wave__destroy(Lu_Delete_Wave);

	//
	// Methods
	//

	void lu_delete_wave__delete_label(Lu_Delete_Wave, lu_size label);
	void lu_delete_wave__delete_neuron(Lu_Delete_Wave, union lu_n_addr);

///////////////////////////////////////////////////////////////////////////////
// Lu_Restore_Wave  

	//
	// Restore Config
	//

	struct lu_restore_config {
		lu_size processor_list_size;
	};

	extern struct lu_restore_config LU_RESTORE_CONFIG__DEFAULT;

	//
	// Constructor / Destructor
	// 

	Lu_Restore_Wave lu_restore_wave__create(Lu_Brain, struct lu_restore_config); 
	void lu_restore_wave__destroy(Lu_Restore_Wave);

	//
	// Methods
	//

	void lu_restore_wave__restore_from_label(Lu_Restore_Wave, lu_size label);
	void lu_restore_wave__restore_from_neuron(Lu_Restore_Wave, union lu_n_addr);

	// temporary solution
	lu_p_value lu_restore_wave__get_values_temp(Lu_Restore_Wave);

///////////////////////////////////////////////////////////////////////////////
// Lu_Label

	lu_size lu_label__get_id(Lu_Label self);
	lu_value lu_label__get_sig(Lu_Label self);


#endif // _LU_BRAIN_API_H
