/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/	
  
	typedef struct lu_n_pos* Lu_N_Pos;
	typedef struct lu_n_pos_3d* Lu_N_Pos_3d;
	typedef union lu_n_ix* Lu_N_Ix;

	enum lu_n_cell_special {
		LU_N_CELL__NULL = 0,
		LU_N_CELL__INACTIVE = 1,
		LU_N_CELL__SPEIAL_CELLS_SKIP
	};
	
	#define LU_N_CELL__LINKS_MAX 5

	enum n_cell_type {
		LU_N_CELL__0,
		LU_N_CELL_VP, // for p and v
		LU_N_CELL__1,
		LU_N_CELL__2,
		LU_N_CELL__3,
		LU_N_CELL__4,
		LU_N_CELL__N,
		LU_N_CELL__END
	};

	typedef struct lu_n_cell_vp* Lu_N_Cell_VP;
	typedef struct lu_n_cell* Lu_N_Cell;
	typedef struct lu_n_strings* Lu_N_Strings;
	typedef struct lu_n_cells* Lu_N_Cells;
	typedef struct lu_n_column* Lu_N_Column;
	typedef struct lu_n_table_comp* Lu_N_Table_Comp;
	typedef struct lu_n_table* Lu_N_Table;

