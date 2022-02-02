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

	struct lu_w_space {
		Lu_Mem mem;

		
	};