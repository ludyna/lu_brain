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

///////////////////////////////////////////////////////////////////////////////
// 

	static Hnn_Cell* hnn_links_connect(Hnn_Links self, Hnn_Cell c1);
	static Hnn_Cell* hnn_links_connect_2(Hnn_Links self, Hnn_Cell c1, Hnn_Cell c2);
	static Hnn_Cell* hnn_links_connect_3(Hnn_Links self, Hnn_Cell c1, Hnn_Cell c2, Hnn_Cell c3);
	static Hnn_Cell* hnn_links_connect_4(Hnn_Links self, Hnn_Cell c1, Hnn_Cell c2, Hnn_Cell c3, Hnn_Cell c4);