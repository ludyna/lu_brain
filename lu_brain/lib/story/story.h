/**
	Copyright © 2021 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Lu_Block 

	struct lu_block {
		Lu_Story 			story;
		lu_size 			datum_size;
		struct lu_data* 	datum;
	};

	static Lu_Block lu_block_create(Lu_Story story);
	static void lu_block_destroy(Lu_Block self);

	static inline Lu_Data lu_block_data_get(Lu_Block self, lu_size index) { return &self->datum[index]; }

///////////////////////////////////////////////////////////////////////////////
// Lu_Story 

	struct lu_story {
		// Not resetable
		Lu_Brain 			brain;

		Lu_List 			blocks;

		// Resetable
		lu_bool 			start_block_on_next_data;
	};

	Lu_Data lu_story_data_get(Lu_Story self, lu_size rec_i, Lu_L_Node node);
	Lu_Story lu_story_validate(Lu_Story);
	Lu_Story lu_story_prepare(Lu_Story);
	static Lu_Block lu_story_block_add(Lu_Story self);
	static inline lu_bool lu_story_is_empty(Lu_Story self) { return lu_list_is_empty(self->blocks); }
	static inline lu_size lu_story_recs_count(Lu_Story self) { return lu_brain_recs_size(self->brain); }