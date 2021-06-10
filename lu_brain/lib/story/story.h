/**
	Copyright © 2021 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Lu_Block 

	struct lu_block {
		Lu_Mem mem;
		lu_size 			datum_size;

		// Using "struct lu_data*" here istead of Lu_Data to point out that 
		// datum is array of "struct lu_data"
		struct lu_data* 	datum;

	};

	static Lu_Block lu_block_create(Lu_Mem mem, lu_size recs_size);
	static void lu_block_destroy(Lu_Block self);

	static inline Lu_Data lu_block_data_get(Lu_Block self, lu_size index) { return &self->datum[index]; }

///////////////////////////////////////////////////////////////////////////////
// Lu_Story 

	struct lu_story {
		Lu_Mem 				mem;
		lu_size 			recs_size;

		Lu_List 			blocks;

		lu_bool 			start_block_on_next_data;
	};

	Lu_Story lu_story_create(Lu_Mem mem, lu_size recs_size);
	void lu_story_destroy(Lu_Story self);

	void lu_story_block_start(Lu_Story story);
	void lu_story_block_end(Lu_Story story);

	Lu_Data lu_story_data_get(Lu_Story self, lu_size rec_i, Lu_L_Node node);
	Lu_Story lu_story_validate(Lu_Story);
	Lu_Story lu_story_prepare(Lu_Story);
	static Lu_Block lu_story_block_add(Lu_Story self);
	static inline lu_bool lu_story_is_empty(Lu_Story self) { return lu_list_is_empty(self->blocks); }
	static inline lu_size lu_story_recs_count(Lu_Story self) { return self->recs_size; }