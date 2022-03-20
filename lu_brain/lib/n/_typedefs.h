/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/	

// typedef struct lu_n_config* 		Lu_N_Config;
// typedef struct lu_n* 				Lu_N;

enum n_cell_type {
	LU_N_CELL__0,
	LU_N_CELL_VP, // for p and v
	LU_N_CELL__1,
	LU_N_CELL__2,
	LU_N_CELL__3,
	LU_N_CELL__4,
	LU_N_CELL__END
};

typedef struct lu_n_cell_base* Lu_N_Cell_Base; 
typedef struct lu_n_cell_vp* Lu_N_Cell_VP;
typedef struct lu_n_cell_1* Lu_N_Cell_1;
typedef struct lu_n_cell_2* Lu_N_Cell_2; 
typedef struct lu_n_cell_3* Lu_N_Cell_3;
typedef struct lu_n_cell_4* Lu_N_Cell_4;
typedef struct lu_n_cell_allocator* Lu_N_Cell_Allocator;

typedef struct lu_n_column_node* Lu_N_Column_Node;
typedef struct lu_n_column* Lu_N_Column;
typedef struct lu_n_links* Lu_N_Links;

typedef struct lu_n_table_comp* Lu_N_Table_Comp;

typedef struct lu_n_cell* Lu_N_Cell;
typedef struct lu_n_links* Lu_N_Links;
typedef struct lu_n_free_links* Lu_N_Free_Links;
typedef struct lu_n_string* Lu_N_String;
typedef struct lu_n_table* Lu_N_Table;

