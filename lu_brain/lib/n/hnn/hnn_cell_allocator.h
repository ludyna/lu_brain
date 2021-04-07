/**
	Copyright © 2021 Oleh Ihorovych Novosad 
*/

struct hnn_cell_allocator {

	Mem_Table 	mt_cell;
	Mem_Table	mt_cell_2;
	Mem_Table 	mt_cell_3;
	Mem_Table 	mt_cell_4;

};

static Hnn_Cell_Allocator hnn_cell_allocator_create(
	lu_size size_in_cell_1,
	lu_size size_in_cell_2,
	lu_size size_in_cell_3, 
	lu_size size_in_cell_4
);

static void hnn_cell_allocator_destroy(Hnn_Cell_Allocator self);