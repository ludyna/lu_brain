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
		Arr2 				data;

		// Resetable
		lu_size				y;
		bool 				start_block_on_next_data;
		lu_size 			block_count;

		// Attached gate and wave
		Gate 				gate;
		Lu_Wave 			wave;
	};

	//
	//	
	//
	static void story_reset(Lu_Story);

	static void story_wave_attach(Lu_Story self, Gate gate, Lu_Wave wave);
	static void story_wave_detach(Lu_Story self);