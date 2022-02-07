/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Lu_W_Table 

	// always 2D
	struct lu_w_table {
		Lu_Mem mem;


	};

	static Lu_W_Table lu_w_table__create(Lu_Mem mem);
	static void lu_w_table__destroy(Lu_W_Table self);

	static void lu_w_table__save_data(Lu_W_Table self, lu_size z, Lu_Data data, Lu_Process_Config config);

///////////////////////////////////////////////////////////////////////////////
// Lu_W_Space

	struct lu_w_space {
		Lu_Mem mem;

		Lu_Wave wave;
		Lu_Arr w_comp_tables;
	};

	static Lu_W_Table lu_w_space__get_table(Lu_W_Space self, Lu_Wave wave);