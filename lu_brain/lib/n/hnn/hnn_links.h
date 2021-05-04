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
// Cell Add 

	static Hnn_Table_Node hnn_links_cell_add_1(Hnn_Links self, lu_size hash, Hnn_Cell_0 new_cell);
	static Hnn_Table_Node hnn_links_cell_add_2(Hnn_Links self, lu_size hash, Hnn_Cell_0 new_cell);
	static Hnn_Table_Node hnn_links_cell_add_3(Hnn_Links self, lu_size hash, Hnn_Cell_0 new_cell);
	static Hnn_Table_Node hnn_links_cell_add_4(Hnn_Links self, lu_size hash, Hnn_Cell_0 new_cell);

///////////////////////////////////////////////////////////////////////////////
// Cell Remove  

	static void hnn_links_cell_remove_1(Hnn_Links self, lu_size hash, Hnn_Cell_0 cell);
	static void hnn_links_cell_remove_2(Hnn_Links self, lu_size hash, Hnn_Cell_0 cell);
	static void hnn_links_cell_remove_3(Hnn_Links self, lu_size hash, Hnn_Cell_0 cell);
	static void hnn_links_cell_remove_4(Hnn_Links self, lu_size hash, Hnn_Cell_0 cell);

///////////////////////////////////////////////////////////////////////////////
// Cell Get  

	static Hnn_Cell_0 hnn_links_cell_get_1(Hnn_Links self, lu_size hash, Hnn_Cell_0 top_left);
	static Hnn_Cell_0 hnn_links_cell_get_2(Hnn_Links self, lu_size hash, Hnn_Cell_0 top_left, Hnn_Cell_0 top_right);
	static Hnn_Cell_0 hnn_links_cell_get_3(Hnn_Links self, lu_size hash, Hnn_Cell_0 top_left, Hnn_Cell_0 top_right, Hnn_Cell_0 bottom_left);
	static Hnn_Cell_0 hnn_links_cell_get_4(Hnn_Links self, lu_size hash, Hnn_Cell_0 top_left, Hnn_Cell_0 top_right, Hnn_Cell_0 bottom_left, Hnn_Cell_0 bottom_right);