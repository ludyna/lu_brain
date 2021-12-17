/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Very Lu_Simple_Hash

	// extremely simple, might be updated later
	struct lu_simple_hash {
		lu_p_void* 		table;
		lu_size 		table_size;
	};

	Lu_Simple_Hash lu_simple_hash__create(Lu_Mem mem, lu_size size);
	void lu_simple_hash__destroy(Lu_Simple_Hash self, Lu_Mem mem);

	void lu_simple_hash__set(Lu_Simple_Hash self, lu_size key, lu_p_void value);
	lu_p_void lu_simple_hash__get(Lu_Simple_Hash self, lu_size key);

