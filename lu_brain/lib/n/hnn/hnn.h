/**
	Copyright © 2021 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// 

	struct hnn_config {

	};

	struct hnn {

		Hnn_Cell_Allocator cell_allocator;
		
	};

///////////////////////////////////////////////////////////////////////////////
// 

	Hnn_Cell hnn_cell_spawn(Hnn self, lu_byte type);
	void hnn_cell_die(Hnn self, Hnn_Cell cell);

	Hnn_Cell hnn_connect_2(Hnn self, Hnn_Cell c1, Hnn_Cell c2);
	Hnn_Cell hnn_connect_3(Hnn self, Hnn_Cell c1, Hnn_Cell c2, Hnn_Cell c3);
	Hnn_Cell hnn_connect_4(Hnn self, Hnn_Cell c1, Hnn_Cell c2, Hnn_Cell c3, Hnn_Cell c4);


