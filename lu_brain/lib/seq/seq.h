/**
	Copyright © 2022 Oleh Ihorovych Novosad 
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

	static Lu_Block lu_block__create(Lu_Mem mem, lu_size recs_size);
	static void lu_block__destroy(Lu_Block self);

	static inline Lu_Data lu_block__data_get(Lu_Block self, lu_size index) { return &self->datum[index]; }

///////////////////////////////////////////////////////////////////////////////
// Lu_Seq 

	struct lu_seq {
		Lu_Mem 				mem;
		lu_size 			recs_size;

		Lu_List 			blocks;

		lu_bool 			start_block_on_next_data;

		Lu_L_Node 			current_read_pos;
	};

	static inline lu_size lu_seq_block__count(Lu_Seq self) { return lu_list__count(self->blocks); }

	Lu_Seq lu_seq__create(Lu_Mem mem, lu_size recs_size);
	void lu_seq__destroy(Lu_Seq self);

	Lu_Seq lu_seq__validate(Lu_Seq);
	Lu_Seq lu_seq__prepare(Lu_Seq);

	void lu_seq__block_begin(Lu_Seq seq);
	void lu_seq__block_end(Lu_Seq seq);

	void lu_seq__push(Lu_Seq self, Lu_Rec rec, lu_value* values);
	Lu_Data lu_seq__data_get(Lu_Seq self, lu_size rec_i, Lu_L_Node node);

	void lu_seq__reset(Lu_Seq self);

	static Lu_Block lu_seq__block_add(Lu_Seq self);
	static inline lu_bool lu_seq__is_empty(Lu_Seq self) { return lu_list__is_empty(self->blocks); }
	static inline lu_size lu_seq__recs_count(Lu_Seq self) { return self->recs_size; }
	lu_size lu_seq__blocks_count(Lu_Seq self);
	lu_p_value lu_seq__last_values(Lu_Seq self, lu_size rec_i);
	Lu_Data lu_seq__last_data(Lu_Seq self, lu_size rec_i);

	// Seq reading

	static Lu_Block lu_seq__next_block_get(Lu_Seq self);
