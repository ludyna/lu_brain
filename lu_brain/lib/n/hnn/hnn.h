/**
	Copyright © 2021 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// 

	struct hnn_config {
		lu_size size_in_cell_1;
		lu_size size_in_cell_2;
		lu_size size_in_cell_3; 
		lu_size size_in_cell_4;
		lu_size t1_size;
		lu_size t2_size;
		lu_size t3_size;
		lu_size t4_size;
	};

	struct hnn {

		Mem mem;
		Hnn_Cell_Allocator cell_allocator;
		Hnn_Links links;

	};

///////////////////////////////////////////////////////////////////////////////
// 

	Hnn hnn_create(Mem mem, struct hnn_config config);
	void hnn_destroy(Hnn self);


///////////////////////////////////////////////////////////////////////////////
// 

	Hnn_Cell hnn_cell_spawn(Hnn self, lu_byte type);
	void hnn_cell_die(Hnn self, Hnn_Cell cell);

	Hnn_Cell hnn_connect_2(Hnn self, Hnn_Cell c1, Hnn_Cell c2);
	Hnn_Cell hnn_connect_3(Hnn self, Hnn_Cell c1, Hnn_Cell c2, Hnn_Cell c3);
	Hnn_Cell hnn_connect_4(Hnn self, Hnn_Cell c1, Hnn_Cell c2, Hnn_Cell c3, Hnn_Cell c4);


