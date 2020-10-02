/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

	struct lu_data {
		lu_size w;
		lu_size h;
		lu_size d;

		lu_p_value values;
	};

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

	static inline Lu_Data lu_data_shallow_copy(Lu_Data dest, Lu_Data src)
	{
		lu_data_set(dest, src->w, src->h, src->d, src->values);

		return dest;
	}

	static Lu_Data lu_data_deep_copy(Lu_Data dest, Lu_Data src);

	static inline void lu_data_value_set(Lu_Data d, lu_size x, lu_size y, lu_size z, lu_value value) { d->values[z * d->w * d->h + y * d->w + x] = value; }
	static inline lu_value lu_data_value_get(Lu_Data d, lu_size x, lu_size y, lu_size z) { return d->values[z * d->w * d->h + y * d->w + x]; }

	static void lu_data_debug(Lu_Data);