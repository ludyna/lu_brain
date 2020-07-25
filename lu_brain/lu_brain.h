/**
	Copyright © 2020 Oleh Ihorovych Novosad
	Ludyna Brain API
*/
#ifndef _LU_BRAIN_PUB_H
#define _LU_BRAIN_PUB_H
 
#include "lu_configs.h"

///////////////////////////////////////////////////////////////////////////////
// Nouns

	// Brain related 
	
	typedef struct lu_brain_opts* 		Lu_Brain_Opts;
	typedef struct lu_brain* 			Lu_Brain;
	typedef struct lu_rec_opts* 		Lu_Rec_Opts;
	typedef struct lu_rec* 				Lu_Rec; 

	// Story related

	typedef struct lu_story* 			Lu_Story;

	// Wave related
	typedef struct lu_neu* 				Lu_Neu;
	typedef struct lu_wave_mem*			Lu_Wave_Mem;
	typedef struct lu_wave* 			Lu_Wave;

///////////////////////////////////////////////////////////////////////////////
// Brain related

	// Lu_Brain_Opts

	Lu_Brain_Opts lu_brain_opts_create(lu_size id, lu_size size_in_bytes);
	void lu_brain_opts_destroy(Lu_Brain_Opts);


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

	// Lu_Brain

	Lu_Brain lu_brain_create(Lu_Brain_Opts);
	void lu_brain_destroy(Lu_Brain);

	lu_size lu_brain_neuron_count(Lu_Brain);
	Lu_Rec lu_brain_rec(Lu_Brain, lu_size index); 


///////////////////////////////////////////////////////////////////////////////
// Story related  

	Lu_Story lu_story_create(Lu_Brain, lu_size);
	void lu_story_destroy(Lu_Story);

	void lu_story_push(Lu_Story, Lu_Rec, lu_value* data);

	void lu_block_begin(Lu_Story);
	void lu_block_end(Lu_Story);

	void lu_story_reset(Lu_Story);

///////////////////////////////////////////////////////////////////////////////
// Wave related 

	// Lu_Neu 

	lu_size lu_neu_name(Lu_Neu);
	void lu_neu_name_set(Lu_Neu, lu_size);
	void lu_neu_connect(Lu_Neu, Lu_Neu);


	// Lu_Wave
	Lu_Wave lu_wave_create(Lu_Brain);
	void lu_wave_destroy(Lu_Wave); 

	// Lu_Wave Sync

	Lu_Wave_Mem lu_wave_save(Lu_Wave, Lu_Story); 
	Lu_Wave_Mem lu_wave_save_with_name(Lu_Wave, Lu_Story, lu_size name);
	Lu_Wave_Mem lu_wave_find(Lu_Wave, Lu_Story);
	Lu_Wave_Mem lu_wave_restore(Lu_Wave, Lu_Neu);

	// Lu_Wave Async

	void lu_wave_save_async(Lu_Wave, Lu_Story);
	void lu_wave_find_async(Lu_Wave, Lu_Story);
	void lu_wave_restore_async(Lu_Wave, Lu_Story);
	Lu_Wave_Mem lu_wave_join(Lu_Wave);

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

	// Lu_Wave_Mem

	Lu_Neu lu_wave_mem_name_neu(Lu_Wave_Mem);
	Lu_Neu lu_wave_mem_top_neu(Lu_Wave_Mem);
	Lu_Neu lu_wave_name_find_or_create(Lu_Wave_Mem, lu_size);


#endif // _LU_BRAIN_API_H
