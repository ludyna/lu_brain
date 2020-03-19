/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Nouns

	typedef struct block* 		Block;
	typedef struct rec_datum* 	Rec_Datum;

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

		// lu_p_value* 		data;
		// lu_size				data_size;
		// lu_size				data_count;

		Arr2 				data;
		lu_size				data_y;
	};


///////////////////////////////////////////////////////////////////////////////
// Block 
 
 	struct block {
 		Story 		story;

 		Arr 		rec_data;
 	};

 	static void block_append(Block self, Rec rec, lu_p_value data);
 	// static Rec_Datum block_rec_datum_get(Block, Rec);

 ///////////////////////////////////////////////////////////////////////////////
// Rec_Datum

 	struct rec_datum {
 		Rec 		rec;
 		lu_p_value 	data;
 	};

 	// static void rec_datum_save(Rec_Datum, Rec_Datum, Rec_Datum, Save_Wave);