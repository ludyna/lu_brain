/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Nouns


///////////////////////////////////////////////////////////////////////////////
// Lu_Story 
	
	#define STORY_INITIAL_BLOCKS_SIZE 8

	struct lu_story {
		// not resetable
		Lu_Brain 			brain;
		Arr2 				data;

		// resetable
		lu_size				data_y;
		bool 				start_block_on_next_data;
		lu_size 			block_count;
	};

	//
	//	
	//
	static void story_reset(Lu_Story);