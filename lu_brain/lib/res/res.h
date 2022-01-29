/**
	Copyright © 2022 Oleh Ihorovych Novosad 

	System resources
*/

///////////////////////////////////////////////////////////////////////////////
// 

	struct lu_res {
		Lu_Mem brain_mem;
		Lu_Mem s_mem;
		Lu_Mem n_mem;
		Lu_Mem w_mem;
	};

	static Lu_Res lu_res__init(
		Lu_Res self,
		Lu_Mem brain_mem,
		Lu_Mem s_mem,
		Lu_Mem n_mem,
		Lu_Mem w_mem
	);

	static void lu_res__deinit(Lu_Res self);
