/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Typedefs

	typedef struct simple_hash* 		Simple_Hash;

///////////////////////////////////////////////////////////////////////////////
// Very Simple_Hash

	// extremely simple, might be updated later
	struct simple_hash {
		lu_p_void* 		table;
		lu_size 		table_size;
	};

	Simple_Hash simple_hash_create(Mem mem, lu_size size);
	void simple_hash_destroy(Simple_Hash self, Mem mem);

	void simple_hash_set(Simple_Hash self, lu_size key, lu_p_void value);
	lu_p_void simple_hash_get(Simple_Hash self, lu_size key);

