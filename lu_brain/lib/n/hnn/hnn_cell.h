/**
	Copyright © 2021 Oleh Ihorovych Novosad 
*/

struct hnn_cell {
	lu_byte type;

	Hnn_Cell top_left;
};

struct hnn_cell_2 {
	struct hnn_cell super;

	Hnn_Cell top_right;
};

struct hnn_cell_3 {
	struct hnn_cell_2 super;

	Hnn_Cell bottom_left;

};

struct hnn_cell_4 {
	struct hnn_cell_3 super;

	Hnn_Cell bottom_right;
};