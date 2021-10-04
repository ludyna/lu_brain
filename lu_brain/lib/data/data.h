/**
	Copyright © 2021 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Lu_Data

	struct lu_data {
		lu_size w;
		lu_size h;
		lu_size d;

		lu_p_value values;
	};


///////////////////////////////////////////////////////////////////////////////
// Properties

	static inline void lu_data_value_set(Lu_Data d, lu_size x, lu_size y, lu_size z, lu_value value) { d->values[z * d->w * d->h + y * d->w + x] = value; }
	static inline lu_value lu_data_value_get(Lu_Data d, lu_size x, lu_size y, lu_size z) { return d->values[z * d->w * d->h + y * d->w + x]; }
	static inline lu_bool lu_data_is_empty(Lu_Data self) { return self->values == NULL; }
 
///////////////////////////////////////////////////////////////////////////////
// Init

	static inline Lu_Data lu_data_set(Lu_Data self, lu_size w, lu_size h, lu_size d, lu_p_value values)
	{
		self->w 		= w;
		self->h 		= h;
		self->d 		= d;
		self->values 	= values;

		return self;
	}

	static inline Lu_Data lu_data_init_default(Lu_Data self)
	{
		lu_data_set(self, 0, 0, 0, NULL);

		return self;
	}

	static inline void lu_data_reset(Lu_Data self)
	{
		lu_data_set(self, 0, 0, 0, NULL);
	}

///////////////////////////////////////////////////////////////////////////////
// Create, detsroy

	static Lu_Data lu_data_create_via_deep_copy_internal(Lu_Mem, Lu_Data src, const char* func, const char* file, int line);

	#define lu_data_create_via_deep_copy(mem, src) lu_data_create_via_deep_copy_internal(mem, src, __func__, __FILE__, __LINE__)

	Lu_Data lu_data_create_via_shift_internal(Lu_Mem mem, Lu_Data src, lu_int x_shift, lu_int y_shift, const char* func, const char* file, int line);

	#define lu_data_create_via_shift(mem, src, x_shift, y_shift) lu_data_create_via_shift_internal(mem, src, x_shift, y_shift,  __func__, __FILE__, __LINE__)

	void lu_data_destroy(Lu_Data, Lu_Mem);

///////////////////////////////////////////////////////////////////////////////
// Validators

	static inline Lu_Data lu_data_validate_exists(Lu_Data self)
	{
		lu__assert(self);
		lu__assert(self->values);
		lu__assert(self->w > 0);
		lu__assert(self->h > 0);
		lu__assert(self->d > 0);

		return self;
	}

///////////////////////////////////////////////////////////////////////////////
// Copy

	static inline Lu_Data lu_data_shallow_copy(Lu_Data dest, Lu_Data src)
	{
		lu_data_set(dest, src->w, src->h, src->d, src->values);

		return dest;
	}


///////////////////////////////////////////////////////////////////////////////
// Debug

	void lu_data_debug(Lu_Data);