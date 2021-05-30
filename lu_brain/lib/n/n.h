/**
	Copyright © 2021 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Lu_N Config 

	struct lu_n_config {
		lu_size names_size;

		struct hnn_config hnn_config;
	};

	static inline Lu_N_Config lu_n_mem_config_validate(Lu_N_Config self)
	{
		lu_assert(self);
		lu_assert(self->names_size > 0);

		hnn_config_validate(&self->hnn_config);

		return self;
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_N  
	
	struct lu_n {

		struct lu_n_config config;

		// vlasnyk
		Lu_Brain brain;

		Names_List names;

		Hnn hnn;
	};

///////////////////////////////////////////////////////////////////////////////
// Lu_N Create & Destroy

	static Lu_N n_mem_create(Lu_Brain brain, struct lu_n_config config);
	static void n_mem_destroy(Lu_N self);

///////////////////////////////////////////////////////////////////////////////
// Lu_N Utility

	static void n_mem_print_info(Lu_N);
