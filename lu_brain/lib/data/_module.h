/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

	struct data {
		lu_size w;
		lu_size h;
		lu_size d;

		lu_p_value values;
	};

	
	static inline Data data_init(Data self, lu_size w, lu_size h, lu_size d, lu_p_value values)
	{
		self->w 		= w;
		self->h 		= h;
		self->d 		= d;
		self->values 	= values;
	}

	static inline void data_reset(Data self)
	{
		self->w 		= 0;
		self->h 		= 0;
		self->d 		= 0;
		self->values 	= NULL;
	}

	static inline void data_shallow_copy(Data dest, Data src)
	{
		dest->w 		= src->w;
		dest->h 		= src->h;
		dest->d 		= src->d;
		dest->values 	= src->values;
	}

	static inline void data_set(Data d, lu_size x, lu_size y, lu_size z, lu_value value) { d->values[z * d->w * d->h + y * d->w + x] = value; }
	static inline lu_value data_get(Data d, lu_size x, lu_size y, lu_size z) { return d->values[z * d->w * d->h + y * d->w + x]; }

	static void data_debug(Data);