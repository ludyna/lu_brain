/**
	Copyright © 2021 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// 

	struct hnn_config {
		lu_size size_in_cell_0;
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
// Cell Spawn & Die 

	Hnn_Cell_0 hnn_cell_spawn(Hnn self, lu_byte type);
	void hnn_cell_die(Hnn self, Hnn_Cell_0 cell);

///////////////////////////////////////////////////////////////////////////////
// Cell Get 

	Hnn_Cell_0 hnn_cell_get_1(Hnn self, Hnn_Cell_0 c1);
	Hnn_Cell_0 hnn_cell_get_2(Hnn self, Hnn_Cell_0 c1, Hnn_Cell_0 c2);
	Hnn_Cell_0 hnn_cell_get_3(Hnn self, Hnn_Cell_0 c1, Hnn_Cell_0 c2, Hnn_Cell_0 c3);
	Hnn_Cell_0 hnn_cell_get_4(Hnn self, Hnn_Cell_0 c1, Hnn_Cell_0 c2, Hnn_Cell_0 c3, Hnn_Cell_0 c4);

///////////////////////////////////////////////////////////////////////////////
// Cell Spawn Connect 

	Hnn_Cell_1 hnn_cell_spawn_connect_1(Hnn self, Hnn_Cell_0 c1);
	Hnn_Cell_2 hnn_cell_spawn_connect_2(Hnn self, Hnn_Cell_0 c1, Hnn_Cell_0 c2);
	Hnn_Cell_3 hnn_cell_spawn_connect_3(Hnn self, Hnn_Cell_0 c1, Hnn_Cell_0 c2, Hnn_Cell_0 c3);
	Hnn_Cell_4 hnn_cell_spawn_connect_4(Hnn self, Hnn_Cell_0 c1, Hnn_Cell_0 c2, Hnn_Cell_0 c3, Hnn_Cell_0 c4);

///////////////////////////////////////////////////////////////////////////////
// Utility

	void hnn_print_distribution(Hnn self, lu_size type);
