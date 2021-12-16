/**
	Copyright © 2021 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Names_List

	struct names_list {
		Lu_Mem mem;
		lu_size names_size;
		Lu_Simple_Hash	hash;
	};

///////////////////////////////////////////////////////////////////////////////
// Names_List Create & Destroy

	static Names_List names_list_create(Lu_Mem mem, lu_size names_size);
	static void names_list_destroy(Names_List self);

