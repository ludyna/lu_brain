/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Lu_N_Table

	

///////////////////////////////////////////////////////////////////////////////
// Lu_N_Space

	struct lu_n_space {

	};


///////////////////////////////////////////////////////////////////////////////
// Lu_N Config 

	struct lu_n_config {
		lu_size names_size;

		//struct lu_n_config n_config;
	};

	static inline Lu_N_Config lu_n_config__validate(Lu_N_Config self)
	{
		lu__assert(self);
		lu__assert(self->names_size > 0);

		//n_config_validate(&self->n_config);

		return self;
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_N  
	
	struct lu_n { 

		struct lu_n_config config;
		Lu_Mem mem;

		Names_List names;

		//Hnn hnn;
	};

///////////////////////////////////////////////////////////////////////////////
// Lu_N Create & Destroy

	static Lu_N lu_n__create(Lu_Mem mem, struct lu_n_config config);
	static void lu_n__destroy(Lu_N self);

///////////////////////////////////////////////////////////////////////////////
// Lu_N Utility

	static void lu_n__print_info(Lu_N);
