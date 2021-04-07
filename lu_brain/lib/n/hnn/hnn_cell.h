/**
	Copyright © 2021 Oleh Ihorovych Novosad 
*/

struct hnn_cell {
	lu_byte type;

	Hnn_Cell top_left;
};

static lu_bool hnn_cell_equal(Hnn_Cell self, Hnn_Cell other);

struct hnn_cell_2 {
	struct hnn_cell super;

	Hnn_Cell top_right;
};

static lu_bool hnn_cell_2_equal(Hnn_Cell_2 self, Hnn_Cell_2 other);

struct hnn_cell_3 {
	struct hnn_cell_2 super;

	Hnn_Cell bottom_left;

};

static lu_bool hnn_cell_3_equal(Hnn_Cell_3 self, Hnn_Cell_3 other);

struct hnn_cell_4 {
	struct hnn_cell_3 super;

	Hnn_Cell bottom_right;
};

static lu_bool hnn_cell_4_equal(Hnn_Cell_4 self, Hnn_Cell_4 other);

#define hnn_cell_type_get(c) (((Hnn_Cell)c)->type)
#define hnn_cell_top_left_get(c) (((Hnn_Cell)c)->top_left)
#define hnn_cell_top_right_get(c) (((Hnn_Cell_2)c)->top_right)
#define hnn_cell_bottom_left_get(c) (((Hnn_Cell_3)c)->bottom_left)
#define hnn_cell_bottom_right_get(c) (((Hnn_Cell_4)c)->bottom_right)