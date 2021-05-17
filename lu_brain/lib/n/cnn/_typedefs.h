/**
	Copyright © 2021 Oleh Ihorovych Novosad 
*/


	#define IX_NULL 0

	enum n_cell_type {
		NCT_NORMAL = 0, 
		NCT_VALUE,
		NCT_NAME,
		NCT_SIZE
	};

	typedef struct n_cell*				N_Cell;
	typedef struct n_cell_2* 			N_Cell_2;
	typedef struct n_cell_3* 			N_Cell_3;
	typedef struct n_lin* 				N_Lin;