/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Lu_W_Table 

	// always 2D
	struct lu_w_table {
		Lu_Mem mem;
		Lu_Wave wave;
		Lu_Comp_Calc comp_calc;

		lu_size width;
		lu_size height;

		
	};

	static Lu_W_Table lu_w_table__create(Lu_Config config, Lu_Comp_Calc comp_calc, lu_size width, lu_size height);
	static void lu_w_table__destroy(Lu_W_Table self);

	static void lu_w_table__save_data(Lu_W_Table self, lu_size z, Lu_Data data, Lu_Process_Config config);

///////////////////////////////////////////////////////////////////////////////
// Lu_W_Space

	struct lu_w_space {
		Lu_Mem mem;

		Lu_Arr tables;
	};

	static Lu_W_Space lu_w_space__create(Lu_Config config, Lu_Comp_Calc comp_calc, lu_size width, lu_size height);
	static void lu_w_space__destroy(Lu_W_Space self);

	static Lu_W_Table lu_w_space__get_table(Lu_W_Space self, Lu_Wave wave);


///////////////////////////////////////////////////////////////////////////////
// Lu_W_Manager

	struct lu_w_manager {
		Lu_Mem mem;
		Lu_Mem_Table waves;
	};

	static Lu_W_Manager lu_w_manager__create(Lu_Mem mem, lu_size w_waves_size);
	static void lu_w_manager__destroy(Lu_W_Manager self); 

	static bool lu_w_manager__register_wave(Lu_W_Manager self, Lu_Wave wave);
	static void lu_w_manager__unregister_wave(Lu_W_Manager self, Lu_Wave wave);

	static inline bool lu_w_manager__is_empty(Lu_W_Manager self) 
	{
		lu__assert(self);
		lu__assert(self->waves);

		return lu_mem_table__records_count(self->waves) == 0;
	}

	static inline Lu_Wave lu_w_manager__get_wave_by_id(Lu_W_Manager self, lu_size id)
	{
		lu__assert(self);
		lu__assert(self->waves);

		return *((Lu_Wave*) lu_mem_table__get(self->waves, id));
	}
	 