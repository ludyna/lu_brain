/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

	struct lu_data {
		lu_size w;
		lu_size h;
		lu_size d;

		lu_p_value values;
	};

	static inline Lu_Data lu_data_init(Lu_Data self, lu_size w, lu_size h, lu_size d, lu_p_value values)
	{
		self->w 		= w;
		self->h 		= h;
		self->d 		= d;
		self->values 	= values;

		return self;
	}

	static inline Lu_Data lu_data_init_default(Lu_Data self)
	{
		self->w 		= 0;
		self->h 		= 0;
		self->d 		= 0;
		self->values 	= NULL;

		return self;
	}

	static inline void lu_data_reset(Lu_Data self)
	{
		self->w 		= 0;
		self->h 		= 0;
		self->d 		= 0;
		self->values 	= NULL;
	}

	static inline Lu_Data lu_data_shallow_copy(Lu_Data dest, Lu_Data src)
	{
		dest->w 		= src->w;
		dest->h 		= src->h;
		dest->d 		= src->d;
		dest->values 	= src->values;

		return dest;
	}

	static Lu_Data lu_data_deep_copy(Lu_Data dest, Lu_Data src);

	static inline void lu_data_set(Lu_Data d, lu_size x, lu_size y, lu_size z, lu_value value) { d->values[z * d->w * d->h + y * d->w + x] = value; }
	static inline lu_value lu_data_get(Lu_Data d, lu_size x, lu_size y, lu_size z) { return d->values[z * d->w * d->h + y * d->w + x]; }

	static void lu_data_debug(Lu_Data);