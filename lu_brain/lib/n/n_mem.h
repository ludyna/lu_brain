/**
	Copyright © 2021 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// N_Mem Config 

	struct n_mem_config {
		lu_size names_size;

		struct hnn_config hnn_config;
	};

	static inline N_Mem_Config lu_n_mem_config_validate(N_Mem_Config self)
	{
		lu_assert(self);
		lu_assert(self->names_size > 0);

		hnn_config_validate(&self->hnn_config);

		return self;
	}

///////////////////////////////////////////////////////////////////////////////
// N_Mem  
	
	struct n_mem {

		struct n_mem_config config;

		// vlasnyk
		Lu_Brain brain;

		Names_List names;

		Hnn hnn;
	};

///////////////////////////////////////////////////////////////////////////////
// N_Mem Create & Destroy

	static N_Mem n_mem_create(Lu_Brain brain, struct n_mem_config config);
	static void n_mem_destroy(N_Mem self);

///////////////////////////////////////////////////////////////////////////////
// N_Mem Utility

	static void n_mem_print_info(N_Mem);
