/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/




///////////////////////////////////////////////////////////////////////////////
// Story API
	
	#define STORY_INITIAL_BLOCKS_SIZE 256

	enum story_state {
		SS_BLOCK_STARTED,
		SS_BLOCK_ENDED
	};

	struct story {
		Brain 				brain;

		Arr					blocks;
		enum story_state	state;
	};


///////////////////////////////////////////////////////////////////////////////
// Block API
 
 	struct block {
 		Story 		story;
 	};

 	void block_append(Block self, lu_value* data);