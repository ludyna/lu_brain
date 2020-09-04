/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Typedefs


///////////////////////////////////////////////////////////////////////////////
// Lu_Story 

	struct lu_story {
		// Not resetable
		Lu_Brain 			brain;

		lu_size 			datum_w;  	// recs
		lu_size 			datum_h;	// time
		struct data* 		datum;

		Lu_List 				blocks;

		// Resetable
		lu_size				y;  
		lu_bool 			start_block_on_next_data;
		lu_size 			blocks_count;
	};

	static inline Data lu_story_data_get(Lu_Story self, lu_size rec_i, lu_size block_i) { return &self->datum[block_i * self->datum_w + rec_i]; }
	static Lu_Story lu_story_validate(Lu_Story);
	static Lu_Story lu_story_prepare(Lu_Story);