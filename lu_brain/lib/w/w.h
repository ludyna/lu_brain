/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Lu_Cell 

	struct lu_cell {
		Lu_N_Cell_Base n_cell_0;
		lu_value sig;
		lu_size wave_id;
	};

///////////////////////////////////////////////////////////////////////////////
//  

	struct lu_w_cell_p {
		struct lu_cell super;

	};

	static inline void lu_w_cell_p__register(
		Lu_W_Cell_P self, 
		lu_size wave_id, 
		lu_value value, 
		Lu_Process_Config config
	)
	{
		// if (self->wave_id != wave_id)
		// {
		// 	self->wave_id
		// }
	}

	struct lu_w_cell_v {

	};

///////////////////////////////////////////////////////////////////////////////
//  

	struct lu_w_table_p {
		lu_size w;
		lu_size h;

		// always "2D"
		struct lu_cell* cells;
	};

	static inline Lu_W_Cell_P lu_w_table_p__get_cell(Lu_W_Table_P self, lu_size x, lu_size y)
	{

	}

	static inline void lu_w_table_p__register(
		Lu_W_Table_P self, 
		lu_size wave_id,
		lu_size x, 
		lu_size y, 
		lu_value v, 
		Lu_Process_Config config
	)
	{
		Lu_W_Cell_P cell_p = lu_w_table_p__get_cell(self, x, y);
		lu__assert(cell_p);

		lu_w_cell_p__register(cell_p, wave_id, v, config);
	}

	static inline lu_bool lu_w_table_p__is_ready(Lu_W_Table_P self, lu_size wave_id, lu_size x, lu_size y)
	{
		return true;
	}

	static inline void lu_w_table_p__save(
		Lu_W_Table_P self, 
		lu_size wave_id, 
		lu_size x, 
		lu_size y,
		Lu_Process_Config config
	)
	{

	} 



///////////////////////////////////////////////////////////////////////////////
//  

	struct lu_w_table_v {
		lu_size w;
		lu_size h;

		// always "2D"
		struct lu_cell* cells;
	};

	static inline void lu_w_table_v__register(
		Lu_W_Table_V self, 
		lu_size wave_id,
		lu_size x, 
		lu_size y, 
		lu_value v, 
		Lu_Process_Config config
	)
	{

	}

	static inline lu_bool lu_w_table_v__is_ready(Lu_W_Table_V self, lu_size wave_id, lu_size x, lu_size y)
	{
		return true;
	}

	static inline void lu_w_table_v__save(
		Lu_W_Table_V self, 
		lu_size wave_id, 
		lu_size x, 
		lu_size y,
		Lu_Process_Config config
	)
	{

	} 

///////////////////////////////////////////////////////////////////////////////
// Lu_W_Table 

	struct lu_w_table_comp {
		Lu_Mem mem;
		Lu_Wave wave;
		Lu_Comp_Calc comp_calc;

		lu_size w;
		lu_size h;

		// always "2D"
		struct lu_cell* cells;
	};

	static Lu_W_Table lu_w_table_comp__create(
		Lu_Config config, 
		Lu_Comp_Calc comp_calc, 
		lu_size width, 
		lu_size height
	);

	static void lu_w_table_comp__destroy(Lu_W_Table self);

	
	static void lu_w_table_comp__save_p(
		Lu_W_Table self, 
		lu_size z, 
		Lu_W_Table v_w_table, 
		Lu_Data data, 
		Lu_Process_Config config
	);

	static void lu_w_table_comp__save(
		Lu_W_Table self, 
		lu_size z, 
		Lu_W_Table p_w_table, 
		Lu_Data d, 
		Lu_Process_Config config
	);

///////////////////////////////////////////////////////////////////////////////
// Lu_W_Space

	struct lu_w_space {
		Lu_Mem mem;

		Lu_Arr tables;
	};

	static Lu_W_Space lu_w_space__create(
		Lu_Config config, 
		Lu_Comp_Calc comp_calc, 
		lu_size width, 
		lu_size height
	);
	static void lu_w_space__destroy(Lu_W_Space self);

	static inline Lu_W_Table lu_w_space__get_w_table(Lu_W_Space self, lu_size ix)
	{
		lu__assert(self);
		lu__assert(self->tables);
		lu__assert(ix < lu_arr__count(self->tables));

		return (Lu_W_Table) lu_arr__get(self->tables, ix);
	}

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
	 