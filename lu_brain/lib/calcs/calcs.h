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

	static Lu_Comp_Calc lu_comp_calc__init(
		Lu_Comp_Calc self,  
		Lu_Mem mem,
		lu_value min, 
		lu_value max, 
		lu_size cells_size
	);

	static void lu_comp_calc__deinit(Lu_Comp_Calc self);

	static inline lu_value lu_comp_calc__norm(Lu_Comp_Calc self, lu_value request);
	static inline lu_size lu_comp_calc__ix(Lu_Comp_Calc self, lu_value val);
	static inline struct lu_size_range lu_comp_calc__ix_range(Lu_Comp_Calc self, lu_value val, lu_size nsc);
	static inline lu_value lu_comp_calc__calc_sig(Lu_Comp_Calc self, lu_size val_step_i, lu_value val);
	static inline lu_value lu_comp_calc__step_norm_dist(Lu_Comp_Calc self);