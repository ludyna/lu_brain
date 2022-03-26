/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/	

///////////////////////////////////////////////////////////////////////////////
// 

	struct lu_comp_calc {
		Lu_Mem mem;

		lu_value 				orig_min;
		lu_value 				orig_max;
		lu_value 				max;

		lu_value 				step;
		lu_value*				steps;  		// preobchysleni kroky
		lu_size 				cells_size;
	};

	//
	// Init & deinit
	// 

	Lu_Comp_Calc lu_comp_calc__init(
		Lu_Comp_Calc self,  
		Lu_Mem mem,
		lu_value min, 
		lu_value max, 
		lu_size cells_size
	);

	void lu_comp_calc__deinit(Lu_Comp_Calc self);


	//
	// Inline 
	//

	static inline lu_value lu_comp_calc__norm(Lu_Comp_Calc self, lu_value request)
	{
		lu_value val = request - self->orig_min;
		val < 0 && (val = 0);
		val > self->max && (val = self->max);

		return val;
	}

	static inline lu_size lu_comp_calc__ix(Lu_Comp_Calc self, lu_value norm_val)
	{
		lu_size ix = (lu_size) lu_floor(norm_val / self->step);
		ix >= self->cells_size && (ix = ix - 1);

		lu__debug_assert(ix < self->cells_size);

		return ix;
	}

	static inline struct lu_size_range lu_comp_calc__ix_range(Lu_Comp_Calc self, lu_value val, lu_size nsc)
	{
		lu_size orig_i = lu_comp_calc__ix(self, val);

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

	static inline lu_value lu_comp_calc__calc_sig(Lu_Comp_Calc self, lu_size val_step_i, lu_value val)
	{ 
		return 1.0 - lu_value_abs(self->steps[val_step_i] - val) / self->max;
	}

	static inline lu_value lu_comp_calc__step_norm_dist(Lu_Comp_Calc self)
	{
		return 1.0 / self->cells_size;
	}

	static inline lu_value lu_comp_calc__digitalize_value(Lu_Comp_Calc self, lu_value v)
	{
		v = lu_comp_calc__norm(self, v);

		lu_size ix = lu_comp_calc__ix(self, v);

		return self->steps[ix];
	}

	//
	//
	//

	void lu_comp_calc__digitalize_data(Lu_Comp_Calc self, Lu_Data data, lu_size z);

	void lu_comp_calc__debug(Lu_Comp_Calc self);