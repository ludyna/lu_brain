/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Nouns


///////////////////////////////////////////////////////////////////////////////
// Story 
	
	#define STORY_INITIAL_BLOCKS_SIZE 8

	struct story {
		// not resetable
		Brain 				brain;
		Arr2 				data;

		// resetable
		lu_size				data_y;
		bool 				start_block_on_next_data;
		lu_size 			block_count;
	};

	//
	//	
	//
	static void story_reset(Story);