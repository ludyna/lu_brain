/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/	


///////////////////////////////////////////////////////////////////////////////
//  lu_calc__

	static inline lu_size lu_calc__hash_comb(lu_size seed, lu_size value)
	{
	    seed ^= value + 0x9e3779b9 + (seed<<6) + (seed>>2);
	    return seed;
	}

	//
	// (x Y y) = max(max(x - 1, 1) * max(y - 1, 1) - 1, 1)
	// This calculation is only correct for "intersected squares cortex" type or similar 
	// 
	static inline lu_size lu_calc__layers_count(lu_size w, lu_size h)
	{
		lu__assert(w > 0);
		lu__assert(h > 0);

		if (w > 1) --w;
		if (h > 1) --h;

		lu_size Y = w * h;

		// minus one because apex is in the base layer of the next level
		// Highest level should always have one layer.
		if (Y > 1) --Y;

		return Y;
	}

	static inline lu_size lu_calc__expected_child_size(lu_size w, lu_size h)
	{
		lu__assert(w > 0);
		lu__assert(h > 0);

		if (w == 1 && h == 1)
		{
			return 1;
		}
		else if (w == 1 || h == 1)
		{
			return 2;
		}
		else
		{
			return 4;
		}
	}

	static inline lu_bool lu_calc__is_last_layer(lu_size w, lu_size h)
	{
		lu__assert(w);
		lu__assert(h);

		return lu_calc__expected_child_size(w, h) == (w * h);
	}

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
		
		#pragma GCC diagnostic ignored "-Wunused-value"
			val < 0 && (val = 0);
			val > self->max && (val = self->max);
		#pragma GCC diagnostic pop

		return val;
	}

	static inline lu_size lu_comp_calc__ix(Lu_Comp_Calc self, lu_value norm_val)
	{
		lu_size ix = (lu_size) lu_floor(norm_val / self->step);

		#pragma GCC diagnostic ignored "-Wunused-value"
			ix >= self->cells_size && (ix = ix - 1);
		#pragma GCC diagnostic pop

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