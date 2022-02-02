/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Lu_Data

	struct lu_data {
		lu_size w;
		lu_size h;
		lu_size d;

		lu_p_value values;
	};

	//	
	// Properties
	//

	static inline void lu_data__value_set(Lu_Data d, lu_size x, lu_size y, lu_size z, lu_value value) { d->values[z * d->w * d->h + y * d->w + x] = value; }
	static inline lu_value lu_data__value_get(Lu_Data d, lu_size x, lu_size y, lu_size z) { return d->values[z * d->w * d->h + y * d->w + x]; }
	static inline lu_bool lu_data__is_empty(Lu_Data self) { return self->values == NULL; }
 
	//
	// Init
	//

	static inline Lu_Data lu_data_set(Lu_Data self, lu_size w, lu_size h, lu_size d, lu_p_value values)
	{
		self->w 		= w;
		self->h 		= h;
		self->d 		= d;
		self->values 	= values;

		return self;
	}

	static inline Lu_Data lu_data__init_default(Lu_Data self)
	{
		lu_data_set(self, 0, 0, 0, NULL);

		return self;
	}

	static inline void lu_data__reset(Lu_Data self)
	{
		lu_data_set(self, 0, 0, 0, NULL);
	}

	//
	// Create, destroy
	//

	static Lu_Data lu_data__create_via_deep_copy_internal(Lu_Mem, Lu_Data src, const char* func, const char* file, int line);

	#define lu_data__create_via_deep_copy(mem, src) lu_data__create_via_deep_copy_internal(mem, src, __func__, __FILE__, __LINE__)

	Lu_Data lu_data__create_via_shift_internal(Lu_Mem mem, Lu_Data src, lu_int x_shift, lu_int y_shift, const char* func, const char* file, int line);

	#define lu_data__create_via_shift(mem, src, x_shift, y_shift) lu_data__create_via_shift_internal(mem, src, x_shift, y_shift,  __func__, __FILE__, __LINE__)

	void lu_data__destroy(Lu_Data, Lu_Mem);

	//
	// Validators
	//

	static inline Lu_Data lu_data__validate_exists(Lu_Data self)
	{
		lu__assert(self);
		lu__assert(self->values);
		lu__assert(self->w > 0);
		lu__assert(self->h > 0);
		lu__assert(self->d > 0);

		return self;
	}

	//
	// Copy
	//

	static inline Lu_Data lu_data__shallow_copy(Lu_Data dest, Lu_Data src)
	{
		lu_data_set(dest, src->w, src->h, src->d, src->values);

		return dest;
	}


	//
	// Debug
	//

	void lu_data__debug(Lu_Data);


///////////////////////////////////////////////////////////////////////////////
// Lu_Data_Block 

	struct lu_data_block {
		Lu_Mem mem;
		lu_size 			datum_size;

		// Using "struct lu_data*" here istead of Lu_Data to point out that 
		// datum is array of "struct lu_data"
		struct lu_data* 	datum;

	};

	static Lu_Data_Block lu_data_block__create(Lu_Mem mem, lu_size recs_size);
	static void lu_data_block__destroy(Lu_Data_Block self);

	static inline Lu_Data lu_data_block__data_get(Lu_Data_Block self, lu_size index) { return &self->datum[index]; }

///////////////////////////////////////////////////////////////////////////////
// Lu_Data_Seq 

	struct lu_data_seq {
		Lu_Mem 				mem;
		lu_size 			recs_size;

		Lu_List 			blocks;

		lu_bool 			start_block_on_next_data;

		Lu_L_Node 			current_read_pos;
	};

	static inline lu_size lu_data_seq__block_count(Lu_Data_Seq self) { return lu_list__count(self->blocks); }

	Lu_Data_Seq lu_data_seq__create(Lu_Mem mem, lu_size recs_size);
	void lu_data_seq__destroy(Lu_Data_Seq self);

	Lu_Data_Seq lu_data_seq__validate(Lu_Data_Seq);
	Lu_Data_Seq lu_data_seq__prepare(Lu_Data_Seq);

	void lu_data_seq__block_begin(Lu_Data_Seq seq);
	void lu_data_seq__block_end(Lu_Data_Seq seq);

	void lu_data_seq__push(Lu_Data_Seq self, Lu_Rec rec, lu_value* values);
	Lu_Data lu_data_seq__data_get(Lu_Data_Seq self, lu_size rec_i, Lu_L_Node node);

	void lu_data_seq__reset(Lu_Data_Seq self);

	static Lu_Data_Block lu_data_seq__block_add(Lu_Data_Seq self);
	static inline lu_bool lu_data_seq__is_empty(Lu_Data_Seq self) { return lu_list__is_empty(self->blocks); }
	static inline lu_size lu_data_seq__recs_count(Lu_Data_Seq self) { return self->recs_size; }
	lu_size lu_data_seq__blocks_count(Lu_Data_Seq self);
	lu_p_value lu_data_seq__last_values(Lu_Data_Seq self, lu_size rec_i);
	Lu_Data lu_data_seq__last_data(Lu_Data_Seq self, lu_size rec_i);

	// Seq reading

	static Lu_Data_Block lu_data_seq__next_block_get(Lu_Data_Seq self);
