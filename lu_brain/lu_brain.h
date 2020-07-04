/**
	Copyright © 2020 Oleh Ihorovych Novosad
	Ludyna Brain API
*/
#ifndef _LU_BRAIN_PUB_H
#define _LU_BRAIN_PUB_H
 
#include "lu_configs.h"


///////////////////////////////////////////////////////////////////////////////
// Brain

	typedef struct lu_brain_opts* 		Lu_Brain_Opts;
	typedef struct lu_brain* 			Lu_Brain;
	typedef struct lu_rec_opts* 		Lu_Rec_Opts;
	typedef struct lu_rec* 				Lu_Rec;

	///////////////////////////////////////
	// Lu_Brain_Opts

	Lu_Brain_Opts lu_brain_opts_create(lu_size id, lu_size size_in_bytes);
	void lu_brain_opts_destroy(Lu_Brain_Opts);

	///////////////////////////////////////
	// Lu_Rec_Opts

	Lu_Rec_Opts lu_rec_opts_create(
		Lu_Brain_Opts lu_brain_opts, 
		lu_size width, 
		lu_size height, 
		lu_size depth,
		lu_size blocks_size,
		lu_value v_min, 
		lu_value v_max, 
		lu_size v_neu_size
	);

	void lu_rec_opts_v_nsc_set(Lu_Rec_Opts self, lu_size val);
	void lu_rec_opns_p_neu_size_set(Lu_Rec_Opts self, lu_size val);
	void lu_rec_opts_p_nsc_set(Lu_Rec_Opts self, lu_size val);

	void lu_rec_opts_destroy(Lu_Rec_Opts);


	///////////////////////////////////////
	// Lu_Brain

	Lu_Brain lu_brain_create(Lu_Brain_Opts);
	void lu_brain_destroy(Lu_Brain);

	lu_size lu_brain_neuron_count(Lu_Brain);
	Lu_Rec lu_brain_rec_get(Lu_Brain, lu_size index); 


///////////////////////////////////////////////////////////////////////////////
// Lu_Story  

	typedef struct lu_story* 			Lu_Story;

	Lu_Story lu_story_create(Lu_Brain, lu_size);
	void lu_story_destroy(Lu_Story);

	void lu_story_push(Lu_Story, Lu_Rec, lu_value* data);

	void lu_block_begin(Lu_Story);
	void lu_block_end(Lu_Story);

///////////////////////////////////////////////////////////////////////////////
// Lu_Wave 

	typedef struct lu_neu* 				Lu_Neu;
	typedef struct lu_space* 			Lu_Space;
	typedef struct lu_layer* 			Lu_Layer;
	typedef struct lu_net*				Lu_Net;
	typedef struct lu_wave* 			Lu_Wave;

	///////////////////////////////////////
	// Lu_Neu 

	lu_size lu_neu_name_get(Lu_Neu);
	void lu_neu_name_set(Lu_Neu, lu_size);

	///////////////////////////////////////
	// Lu_Space

	Lu_Neu lu_space_winner_get(Lu_Space);

	///////////////////////////////////////
	// Lu_Layer

	Lu_Space lu_layer_space_get(Lu_Layer, lu_size x, lu_size y, lu_size z);

	///////////////////////////////////////
	// Lu_Wave

	Lu_Wave lu_wave_create(Lu_Brain, lu_flags flags, lu_value color, lu_value contrast, lu_value breakpoint);
	void lu_wave_destroy(Lu_Wave);

	Lu_Net lu_wave_save(Lu_Wave, Lu_Story); 
	void lu_wave_save_async(Lu_Wave, Lu_Story);

	Lu_Net lu_wave_find(Lu_Wave, Lu_Story);
	void lu_wave_find_async(Lu_Wave, Lu_Story);

	Lu_Net lu_wave_restore(Lu_Wave, Lu_Neu);
	void lu_wave_restore_async(Lu_Wave, Lu_Story);

	Lu_Net lu_wave_join(Lu_Wave);

	lu_value lu_wave_color_get(Lu_Wave);
	void lu_wave_color_set(Lu_Wave, lu_value);

	lu_value lu_wave_contrast_get(Lu_Wave);
	void lu_wave_contrast_set(Lu_Wave, lu_value);

	lu_value lu_wave_breakpoint_get(Lu_Wave);
	void lu_wave_breakpoint_set(Lu_Wave, lu_value);


	// lu_bool lu_wave_is_working(Lu_Wave);
	// lu_bool lu_wave_cancel(Lu_Wave);
	// lu_size lu_wave_time(Lu_Wave);
	// enum lu_wave_status lu_wave_status(Lu_Wave);
	// lu_size lu_wave_touched_count(Lu_Wave);
	// lu_size lu_wave_excited_count(Lu_Wave);
	// Lu_Wave_Resp lu_wave_response(Lu_Wave);
	// void lu_wave_join(Lu_Wave);


#endif // _LU_BRAIN_API_H
