/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// lu_values

	void lu_values__print(
		lu_p_value src, 
		lu_size w, 
		lu_size h, 
		lu_size d
	);

	void lu_values__print_symbols(
		lu_p_value src, 
		lu_size w, 
		lu_size h, 
		lu_size d
	);

///////////////////////////////////////////////////////////////////////////////
// Lu_W_Block_Id

	////
	// Structure that uniquely identifies data block (in time)
	struct lu_block_id {
		lu_size wave_id;	// id because not sequential, more random, after 3 next one can be 0
		lu_size block_ix;   // ix because its sequential
	};

	//
	// Constructors / Destructors
	//

	static inline Lu_Block_Id lu_block_id__reset(Lu_Block_Id self)
	{
		lu__assert(self);

		self->wave_id = LU_WAVE_ID__NOT_SET;
		self->block_ix = LU_BLOCK_IX__NOT_SET;

		return self;
	}

	static inline Lu_Block_Id lu_block_id__init(Lu_Block_Id self, lu_size wave_id, lu_size block_ix)
	{
		lu__assert(self);

		self->wave_id = wave_id;
		self->block_ix = block_ix;

		return self;
	}

	//
	// Is
	//

	static inline lu_bool lu_block_id__is_set(Lu_Block_Id self)
	{
		if (self->wave_id == LU_WAVE_ID__NOT_SET) return false;
		if (self->block_ix == LU_BLOCK_IX__NOT_SET) return false;

		return true;
	}

	static inline lu_bool lu_block_id__is_not_set(Lu_Block_Id self)
	{
		return !lu_block_id__is_set(self);
	}

	static inline lu_bool lu_block_id__is_eq(Lu_Block_Id self, Lu_Block_Id block_id)
	{
		return (self->wave_id == block_id->wave_id) && (self->block_ix == block_id->block_ix);
	}

	static inline lu_bool lu_block_id__is_not_eq(Lu_Block_Id self, Lu_Block_Id block_id)
	{
		return !lu_block_id__is_eq(self, block_id);
	}

	//
	// Methods
	//

	static inline void lu_block_id__print(Lu_Block_Id self)
	{
		lu__assert(self);
		lu__debug("[wave_id=%ld, block_ix=%ld]", self->wave_id, self->block_ix);
	}

	static inline void lu_block_id__increase_block_ix(Lu_Block_Id self)
	{
		lu__assert(self);

		if (self->block_ix == LU_BLOCK_IX__NOT_SET)
		{
			self->block_ix = 0;
		}
		else
		{
			++self->block_ix;
		}
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_Data

	enum lu_data_flags {
		LU_DATA_FLAGS__CLEAR = 0,
		LU_DATA_FLAGS__RESET_REC = 1,
		LU_DATA_FLAGS__END
	};

	struct lu_data {
		struct lu_block_id block_id;

		lu_size rec_id;
		lu_flags flags;

		lu_size w;
		lu_size h;
		lu_size d;

		lu_p_value values;

		// Info about how to view/process this data
		struct lu_rec_view view;
	};

	//	
	// Get
	//

	static inline void lu_data__value_set(Lu_Data d, lu_size x, lu_size y, lu_size z, lu_value value) 
	{ 
		lu__assert(x < d->w);
		lu__assert(y < d->h);
		lu__assert(z < d->d);

		lu_macro__value_in_3d_array(d->values, x, y, z, d->w, d->h) = value; 
	}

	static inline lu_value lu_data__get_value(Lu_Data d, lu_size x, lu_size y, lu_size z) 
	{ 
		lu__assert(x < d->w);
		lu__assert(y < d->h);
		lu__assert(z < d->d);

		return lu_macro__value_in_3d_array(d->values, x, y, z, d->w, d->h); 
	}

	static inline lu_bool lu_data__is_empty(Lu_Data self) { return self->values == NULL; }
 
	//
	// Init
	//

	static inline Lu_Data lu_data__set(
		Lu_Data self, 
		struct lu_block_id block_id,
		lu_size rec_id, 
		lu_size w, 
		lu_size h, 
		lu_size d, 
		lu_p_value values, 
		struct lu_rec_view view, 
		lu_flags flags
	)
	{
		self->block_id 	= block_id;
		self->rec_id 	= rec_id;
		self->flags 	= flags;

		self->w 		= w;
		self->h 		= h;
		self->d 		= d;
		self->values 	= values;
		self->view 		= view;

		// Important (!) We receice view from Rec, but data can have smaller dimensions that rec
		lu_rec_view__update_to_dimensions(&self->view, self->w, self->h, self->d);

		return self;
	}

	static inline Lu_Data lu_data__init_default(Lu_Data self)
	{

		struct lu_rec_view view;

		lu_rec_view__init(&view, 0, 0, 0); 

		struct lu_block_id block_id;
		lu_block_id__reset(&block_id);

		lu_data__set(
			self, 
			block_id,
			LU_REC_ID__NOT_SET, 
			0, 
			0, 
			0, 
			NULL,
			view,
			0
		);

		return self;
	}

	#define lu_data__reset(d) lu_data__init_default(d)

	//
	// Create / Destroy
	//

	static inline Lu_Data lu_data__create(Lu_Mem mem, lu_size w, lu_size h, lu_size d)
	{
		lu__assert(mem);
		lu__assert(w > 0);
		lu__assert(h > 0);
		lu__assert(d > 0);

		Lu_Data self = (Lu_Data) lu_mem__alloc(mem, sizeof(struct lu_data));
		lu__assert(self);

		self->w 		= w;
		self->h 		= h;
		self->d 		= d;

		lu_size size = sizeof(lu_value) * self->w * self->h * self->d;

		self->values = (lu_p_value) lu_mem__alloc(mem, size);
		lu__assert(self->values);

		memset(self->values, 0, size);

		return self;
	}

	Lu_Data lu_data__create_via_mem_copy_internal(
		Lu_Mem mem, 
		lu_p_value src, 
		lu_size w, 
		lu_size h, 
		lu_size d, 
		const char* func, 
		const char* file, 
		int line
	);

	#define lu_data__create_via_mem_copy(mem, src, w, h, d) \
		lu_data__create_via_mem_copy_internal(mem, src, w, h, d, __func__, __FILE__, __LINE__)

	Lu_Data lu_data__create_via_deep_copy_internal(Lu_Mem, Lu_Data src, const char* func, const char* file, int line);

	#define lu_data__create_via_deep_copy(mem, src) \
		lu_data__create_via_deep_copy_internal(mem, src, __func__, __FILE__, __LINE__)

	Lu_Data lu_data__shift(
		Lu_Data self, 
		lu_p_value src, 
		lu_size src_w, 
		lu_size src_h, 
		lu_size src_d, 
		lu_int x_shift, 
		lu_int y_shift
	);

	Lu_Data lu_data__create_via_shift_internal(
		Lu_Mem mem, 
		Lu_Data src, 
		lu_int x_shift, 
		lu_int y_shift, 
		const char* func, 
		const char* file, 
		int line
	);

	#define lu_data__create_via_shift(mem, src, x_shift, y_shift) \
		lu_data__create_via_shift_internal(mem, src, x_shift, y_shift,  __func__, __FILE__, __LINE__)

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
		lu_data__set(
			dest, 
			src->block_id, 
			src->rec_id, 
			src->w, 
			src->h, 
			src->d, 
			src->values, 
			src->view, 
			src->flags
		);

		return dest;
	}


	//
	// Methods
	//

	void lu_data__print(Lu_Data);
	void lu_data__print_symbols(Lu_Data);


///////////////////////////////////////////////////////////////////////////////
// Lu_Data_Block 

	enum lu_data_block_flags {
		LU_DATA_BLOCK_FLAGS__CLEAR = 0,
		LU_DATA_BLOCK_FLAGS__RESET_RECS = 1,
		LU_DATA_BLOCK_FLAGS__END
	};

	struct lu_data_block {
		Lu_Mem mem;

		struct lu_block_id block_id;

		lu_size 			datum_size;
		struct lu_data* 	datum; 

		lu_flags flags;
	};

	static Lu_Data_Block lu_data_block__create(Lu_Mem mem, lu_size recs_size, lu_size wave_id, lu_size block_ix);
	static void lu_data_block__destroy(Lu_Data_Block self);

	static inline lu_size lu_data_block__get_size(Lu_Data_Block self) { return self->datum_size; }
	static inline Lu_Data lu_data_block__get_data(Lu_Data_Block self, lu_size index) { return &self->datum[index]; }

///////////////////////////////////////////////////////////////////////////////
// Lu_Data_Seq 

	struct lu_data_seq {
		Lu_Mem 				mem;
		lu_size 			wave_id;

		lu_size 			recs_size;

		Lu_List 			blocks;

		// We have separate count for block_ix. lu_list__count(blocks) will not work because 
		// we reset it every process() call
		lu_size  			blocks_count; 

		lu_bool 			start_block_on_next_data;

		Lu_L_Node 			current_read_pos;
	};

	Lu_Data_Seq lu_data_seq__create(Lu_Mem mem, lu_size wave_id, lu_size recs_size);
	void lu_data_seq__destroy(Lu_Data_Seq self);

	static inline lu_size lu_data_seq__block_count(Lu_Data_Seq self) { return lu_list__count(self->blocks); }

	Lu_Data_Seq lu_data_seq__validate(Lu_Data_Seq);
	Lu_Data_Seq lu_data_seq__prepare(Lu_Data_Seq);

	void lu_data_seq__block_begin(Lu_Data_Seq seq);
	void lu_data_seq__block_end(Lu_Data_Seq seq);

	void lu_data_seq__push(
		Lu_Data_Seq self, 
		Lu_Rec rec, lu_value* values, 
		lu_size w, 
		lu_size h, 
		lu_size d,
		struct lu_rec_view view
	);
	Lu_Data lu_data_seq__data_get(Lu_Data_Seq self, lu_size rec_i, Lu_L_Node node);

	void lu_data_seq__reset(Lu_Data_Seq self);

	static Lu_Data_Block lu_data_seq__block_add(Lu_Data_Seq self);
	static inline lu_bool lu_data_seq__is_empty(Lu_Data_Seq self) { return lu_list__is_blank(self->blocks); }
	static inline lu_size lu_data_seq__recs_count(Lu_Data_Seq self) { return self->recs_size; }
	lu_size lu_data_seq__blocks_count(Lu_Data_Seq self);
	lu_p_value lu_data_seq__get_last_values(Lu_Data_Seq self, lu_size rec_i);
	Lu_Data lu_data_seq__get_last_data(Lu_Data_Seq self, lu_size rec_i);

	// Seq reading

	static Lu_Data_Block lu_data_seq__next_block_get(Lu_Data_Seq self);
