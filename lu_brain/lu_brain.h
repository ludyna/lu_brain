/**
	Copyright © 2020 Oleh Ihorovych Novosad
	Ludyna Brain API
*/
#ifndef _LU_BRAIN_PUB_H
#define _LU_BRAIN_PUB_H

#include "lu_types.h"

///////////////////////////////////////////////////////////////////////////////
// Nouns

	// Brain  
	
	typedef struct lu_brain_config* 	Lu_Brain_Config;
	typedef struct lu_brain* 			Lu_Brain;	
	typedef struct lu_rec_config*		Lu_Rec_Config;
	typedef struct lu_rec* 				Lu_Rec; 

	// Story 

	typedef struct lu_story* 			Lu_Story;

	// Wave 
	
	typedef struct lu_neu* 				Lu_Neu;
	typedef struct lu_wave* 			Lu_Wave;

///////////////////////////////////////////////////////////////////////////////
// Brain 

	// Lu_Brain_Config predefined 

	Lu_Brain_Config lu_brain_config_predefined_get(lu_size id);

	// Lu_Brain_Config 

	Lu_Brain_Config lu_brain_config_validate(Lu_Brain_Config config);

	// Lu_Brain 

	Lu_Brain lu_brain_create_from_predefined(lu_size size_in_bytes, lu_size predefined_config_id);
	Lu_Brain lu_brain_create(struct lu_brain_config config);
	void lu_brain_destroy(Lu_Brain);

	void lu_brain_print_info(Lu_Brain self);

///////////////////////////////////////////////////////////////////////////////
// Rec  

	// Lu_Rec_Config predefined 

	Lu_Rec_Config lu_rec_config_predefined_get(lu_size id);

	// Lu_Rec_Config 

	Lu_Rec_Config lu_rec_config_validate(Lu_Rec_Config self);

	// Lu_Rec 

	Lu_Rec lu_rec_create_from_predefined(
		Lu_Brain brain, 
		lu_size width, 
		lu_size height, 
		lu_size predefined_config_id
	);		

	Lu_Rec lu_rec_create(Lu_Brain brain, struct lu_rec_config config);
	void lu_rec_destory(Lu_Rec self);

///////////////////////////////////////////////////////////////////////////////
// Story   

	Lu_Story lu_story_create(Lu_Brain, lu_size);
	void lu_story_destroy(Lu_Story);

	void lu_story_push(Lu_Story, Lu_Rec, lu_value* data);

	void lu_block_begin(Lu_Story);
	void lu_block_end(Lu_Story);

	void lu_story_reset(Lu_Story);

///////////////////////////////////////////////////////////////////////////////
// Wave  

	// Lu_Neu 

	lu_size lu_neu_name(Lu_Neu);
	void lu_neu_name_set(Lu_Neu, lu_size);
	void lu_neu_connect(Lu_Neu, Lu_Neu);

	// Lu_Wave

	Lu_Wave lu_wave_create(Lu_Brain brain);
	void lu_wave_destroy(Lu_Wave); 

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
