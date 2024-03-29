/**
	Copyright © 2022 Oleh Ihorovych Novosad 

*/

///////////////////////////////////////////////////////////////////////////////
// S typedefs

	enum lu_s_layer_type {
		LU_S_LAYER__COMP,
		LU_S_LAYER__REC,
		LU_S_LAYER__LAYER,
		LU_S_LAYER__END
	};

	//
	// Columns
	//

	typedef struct lu_s_column* Lu_S_Column;
	typedef struct lu_s_column* Lu_S_Column;
	typedef struct lu_s_column_comp* Lu_S_Column_Comp;

	//
	// Tables
	//

	typedef struct lu_s_table_comp* Lu_S_Table_Comp;

	typedef struct lu_s_table* Lu_S_Table;
	static inline Lu_S_Layer_Base lu_s_table__get_layer(Lu_S_Table self);