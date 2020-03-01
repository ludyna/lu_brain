/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Nouns

	typedef struct block* 		Block;
	typedef struct rec_input* 	Rec_Input;

///////////////////////////////////////////////////////////////////////////////
// Story 
	
	#define STORY_INITIAL_BLOCKS_SIZE 256
	#define BLOCK_INITIAL_REC_INPUTS_SIZE 16

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
// Block 
 
 	struct block {
 		Story 		story;

 		Arr 		rec_inputs;
 	};

 	void block_append(Block self, Rec rec, lu_p_value data);

 ///////////////////////////////////////////////////////////////////////////////
// Rec_Input

 	struct rec_input {
 		Rec 		rec;
 		lu_p_value 	data;
 	};