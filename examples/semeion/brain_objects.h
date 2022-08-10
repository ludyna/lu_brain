/**
	Copyright © 2022 Oleh Ihorovych Novosad 

	NOTE: Variation of functionality here (basically focus emulation) will be fully integrated into Lu_Brain later.
**/

	#include "semeion.h"
	#include "semeion.c"


	enum focus_type {
		FOCUS_TYPE__TL,
		FOCUS_TYPE__TR,
		FOCUS_TYPE__BL,
		FOCUS_TYPE__BR,
		FOCUS_TYPE__TOP,
		FOCUS_TYPE__BOTTOM,
		FOCUS_TYPE__END
	};

///////////////////////////////////////////////////////////////////////////////
// Brain_Objects
//

	struct brain_objects {
		Lu_Brain brain;
		Lu_Rec rec;
		Lu_Wave save_wave;
		Lu_Wave match_wave;
	};

	typedef struct brain_objects* Brain_Objects;

	static inline void brain_objects__init( 
		Brain_Objects self,
		struct lu_config config
	)
	{
		self->brain = lu_brain__create(config);
		lu__assert(self->brain);
		
		self->rec = lu_brain__rec_add(
			/*belongs to*/			self->brain, 
			/*width*/				8, 
			/*height*/				8, 
			/*depth*/				1,
			/*predefined config */ 	lu_rec_config__get_by_id(LU_REC__MONO1_IMAGE)
		);	
		lu__assert(self->rec);

		// After we added all recs we need to build/rebuild brain
		lu_brain__build(self->brain);

		// Create save_wave
		
		self->save_wave = lu_wave__create_save_wave(self->brain);
		lu__assert(self->save_wave);  

		self->match_wave = lu_wave__create_match_wave(self->brain);
		lu__assert(self->match_wave);
	}

	static inline void brain_objects__deinit(
		Brain_Objects self
	)	
	{
		lu__assert(self->brain);
		lu__assert(self->save_wave);
		lu__assert(self->match_wave);
		
		lu_wave__destroy(self->match_wave);
		lu_wave__destroy(self->save_wave);
		lu_brain__destroy(self->brain);
	}

	static inline void brain_objects__learn(Brain_Objects self, Smn_Digit d, enum focus_type focus_type)
	{
		lu_wave__push(self->save_wave, self->rec, smn_blank_pixels, 8, 8, 1);

		switch(focus_type)
		{
			case FOCUS_TYPE__TL:
				lu_wave__set_src_start_pos(self->save_wave, self->rec, 0, 0);
				lu_wave__set_src_end_pos(self->save_wave, self->rec, 8, 8);
				break;
			case FOCUS_TYPE__TR:
				lu_wave__set_src_start_pos(self->save_wave, self->rec, 8, 0);
				lu_wave__set_src_end_pos(self->save_wave, self->rec, 16, 8);
				break;
			case FOCUS_TYPE__BL:
				lu_wave__set_src_start_pos(self->save_wave, self->rec, 0, 8);
				lu_wave__set_src_end_pos(self->save_wave, self->rec, 8, 16);
				break;
			case FOCUS_TYPE__BR:
				lu_wave__set_src_start_pos(self->save_wave, self->rec, 8, 8);
				lu_wave__set_src_end_pos(self->save_wave, self->rec, 16, 16);
				break;
			default:
				lu__assert(false);
		} 

		lu_wave__push(self->save_wave, self->rec, d->pixels, 16, 16, 1);
		lu_wave__process(self->save_wave, lu_process_config__get_by_id(LU_PROCESS__SAVE_DEFAULT));

		Lu_La_Cell la_cell = lu_wave__link_to_label(self->save_wave, 2, 0, 0, 0, d->name);
		lu__assert(la_cell);

	}

	static inline void brain_objects__match(Brain_Objects self, Smn_Digit d, enum focus_type focus_type)
	{
		lu_wave__push(self->match_wave, self->rec, smn_blank_pixels, 8, 8, 1);

		switch(focus_type)
		{
			case FOCUS_TYPE__TR:
				lu_wave__set_src_start_pos(self->save_wave, self->rec, 0, 0);
				break;
			case FOCUS_TYPE__TL:
				lu_wave__set_src_start_pos(self->save_wave, self->rec, 8, 0);
				break;
			case FOCUS_TYPE__BL:
				lu_wave__set_src_start_pos(self->save_wave, self->rec, 0, 8);
				break;
			case FOCUS_TYPE__BR:
				lu_wave__set_src_start_pos(self->save_wave, self->rec, 8, 8);
				break;
			default:
				lu__assert(false);
		}

		lu_wave__push(self->match_wave, self->rec, d->pixels, 8, 8, 1);
		lu_wave__process(self->match_wave, lu_process_config__get_by_id(LU_PROCESS__MATCH_DIFF_ONLY));
	}


///////////////////////////////////////////////////////////////////////////////
// Focuses
//

	#define FOCUSES_SIZE 4
	struct brain_objects focuses[FOCUSES_SIZE];

	static inline void focuses__create(struct lu_config config)
	{
		for (lu_size i = 0; i < FOCUSES_SIZE; i++)
		{	
			config.b_id = i;

			brain_objects__init(&focuses[i], config);
		}
	}

	static inline void focuses__destroy()
	{
		for (lu_size i = 0; i < FOCUSES_SIZE; i++)
		{	
			brain_objects__deinit(&focuses[i]);
		}
	}

 	static inline void focuses__learn_samples()
 	{
 		Smn_Group group;
 		Smn_Digit digit;

 		size_t i;
 		for (size_t learnt_count = 0; learnt_count < 151; learnt_count++)
 		{
	 		for (i = 0; i < SMN_DIGIT__VALUE_COUNT; i++)
	 		{
	 			group = &smn_groups[i];
	 			lu__assert(group);

	 			if (learnt_count < group->training_size)
	 			{
	 				digit = group->training_samples[learnt_count];
	 				lu__assert(digit);

	 				brain_objects__learn(&focuses[0], digit, FOCUS_TYPE__TL);
	 				brain_objects__learn(&focuses[1], digit, FOCUS_TYPE__TR);
	 				brain_objects__learn(&focuses[2], digit, FOCUS_TYPE__BL);
	 				brain_objects__learn(&focuses[3], digit, FOCUS_TYPE__BR);
	 			}
	 		}
 		}
 	}

 	static inline void focuses__net_stats()
 	{
 		for (lu_size i = 0; i < FOCUSES_SIZE; i++)
 		{
 			lu_brain__print_net_stats(focuses[i].brain);
 		}
 	}