/**
	Copyright © 2021 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Cnn Cell

	struct n_cell {
		enum n_cell_type 		type;
		Lu_S_Cell 					s_cell;
		lu_size 				sl_ix;   	// nomer v lu_s_layer

		N_Lin 					b_l; 		
		lu_value 				b_count;

		N_Lin  					d_l;		
	
	};

	struct n_cell_2 {
		struct n_cell 			super;

		lu_value 				value;
	};

	struct n_cell_3 {
		struct n_cell 			super;

		lu_size 				name;
	};