/**
	Copyright © 2021 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// 

	static inline Lu_S_Layer_Conf lu_s_layer_conf_init(Lu_S_Layer_Conf self, Lu_Mem mem, lu_value min, lu_value max, lu_size cells_size)
	{
		lu__assert(self);
		lu__assert(mem);

		self->mem 				= mem;
		self->cells_size  		= cells_size; // value depth in indexes
		self->orig_min 			= min;
		self->orig_max 			= max;
		self->max 				= self->orig_max - self->orig_min;
		self->step 				= self->max / (lu_value) self->cells_size;
		//self->nsc 				= nsc; //(lu_size) lu_value_round(self->max_val * rec->val_nsc / self->step); // nsc in indexes

	 	// Kroky preobchysleni
		self->steps 		= (lu_value*) lu_mem__alloc(self->mem, sizeof(lu_value) * self->cells_size);
		lu__assert(self->steps);
	
		lu_size i;
		for (i = 0; i < self->cells_size; i++)
			self->steps[i] = (lu_value)i * self->step;

		return self;
	}

	static inline void lu_s_layer_conf_deinit(Lu_S_Layer_Conf self)
	{
		lu__assert(self);

		lu_mem__free(self->mem, (lu_p_byte) self->steps);
		self->steps = NULL;
	}

	static inline lu_value lu_s_layer_conf_norm(Lu_S_Layer_Conf self, lu_value request)
	{
		lu_value val = request - self->orig_min;
		if (val < 0) val = 0;
		if (val > self->max) val = self->max;

		return val;
	}

	static inline lu_size lu_s_layer_conf_ix(Lu_S_Layer_Conf self, lu_value val)
	{
		return (lu_size) lu_value_round(val / self->step);
	}

	static inline struct lu_size_range lu_s_layer_conf_ix_range(Lu_S_Layer_Conf self, lu_value val, lu_size nsc)
	{
		lu_size orig_i = lu_s_layer_conf_ix(self, val);

		long begin, end;

		begin = orig_i - nsc;
		if (begin < 0) begin = 0;

		end = orig_i + nsc;
		if (end > (self->cells_size - 1)) end = self->cells_size - 1; 

		struct lu_size_range r;
		r.begin = (lu_size) begin;
		r.end = (lu_size) end;
		return r;
	}

	static inline lu_value lu_s_layer_conf_calc_sig(Lu_S_Layer_Conf self, lu_size val_step_i, lu_value val)
	{ 
		return 1.0 - lu_value_abs(self->steps[val_step_i] - val) / self->max;
	}

	static inline lu_value lu_s_layer_conf_step_norm_dist(Lu_S_Layer_Conf self)
	{
		return 1.0 / self->cells_size;
	}