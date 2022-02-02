/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/	

typedef struct lu_n_config* 		Lu_N_Config;
typedef struct lu_n* 				Lu_N;

enum n_cell_type {
	N_CT__0,
	N_CT__VALUE,
	N_CT__1,
	N_CT__2,
	N_CT__3,
	N_CT__4,
	N_CT__END
};

typedef struct lu_n_cell_0* N_Cell_0; 
typedef struct lu_n_cell_value* N_Cell_Value;
typedef struct lu_n_cell_1* N_Cell_1;
typedef struct lu_n_cell_2* N_Cell_2; 
typedef struct lu_n_cell_3* N_Cell_3;
typedef struct lu_n_cell_4* N_Cell_4;
typedef struct lu_n_cell_allocator* N_Cell_Allocator;

typedef struct lu_n_table_node* N_Table_Node;
typedef struct lu_n_table* N_Table;
typedef struct lu_n_links* N_Links;

typedef struct lu_n_space* Lu_N_Space;

// typedef struct lu_n_config* N_Config;
// typedef struct lu_n* N;
