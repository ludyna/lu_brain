/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Nouns


///////////////////////////////////////////////////////////////////////////////
// Lu_Story 
	
	#define STORY_INITIAL_BLOCKS_SIZE 8

	struct lu_story {
		// Not resetable
		Lu_Brain 			brain;
		//Arr2 				data;
		struct data* 		datum;
		lu_size 			datum_w;  	// recs
		lu_size 			datum_h;	// time


		// Resetable
		lu_size				y;  
		lu_bool 			start_block_on_next_data;
		lu_size 			blocks_count;

		// Attached gate and wave
		Gate 				gate;
		Lu_Wave 			wave;
	};

	static inline Data story_data_get(Lu_Story self, lu_size rec_i, lu_size block_i) { return &self->datum[block_i * self->datum_w + rec_i]; }

	//
	//	
	//
	static void story_reset(Lu_Story);

	static void story_wave_attach(Lu_Story self, Gate gate, Lu_Wave wave);
	static void story_wave_detach(Lu_Story self);