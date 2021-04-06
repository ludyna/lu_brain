

struct hnn_cell {
	lu_byte type;
	
	Hnn_Cell top_left;
	Hnn_Cell top_right;
};

struct hnn_cell_4 {
	struct hnn_cell super;

	Hnn_Cell bottom_left;
	Hnn_Cell bottom_right;
};