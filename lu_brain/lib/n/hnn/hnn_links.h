/**
	Copyright © 2021 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// 

	struct hnn_links {

		Mem mem;
		Hnn_Table table_1;
		Hnn_Table table_2;
		Hnn_Table table_3;
		Hnn_Table table_4;

	};

///////////////////////////////////////////////////////////////////////////////
// 

	static Hnn_Links hnn_links_create(Mem mem, lu_size t1_size, lu_size t2_size, lu_size t3_size, lu_size t4_size);
	static void hnn_links_destroy(Hnn_Links self);