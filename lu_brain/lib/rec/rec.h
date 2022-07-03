/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Lu_Rec_Config predefined 

	extern struct lu_rec_config lu_g_rc_predefined[LU_REC__END];

///////////////////////////////////////////////////////////////////////////////
// Lu_Rec

	struct lu_rec {
		Lu_Brain 					brain;
		lu_size 					id;

		lu_size  					width;
		lu_size  					height;
		lu_size  					depth;

		struct lu_rec_config 		config;	

		//
		// View config
		// 

		// Starting position from which we read data from source
		// src_start_x should be >= 0
		// src_start_y should be >= 0
		// src_end_x should be <= width
		// src_end_y should be <= height
		lu_size src_start_x; 
		lu_size src_start_y;
		lu_size src_start_z;
		lu_size src_end_x;
		lu_size src_end_y;
		lu_size src_end_z;

		// Starting positing into which we write data from source
		// it could be below 0, only part that of src that intersects with
		// dest rectangle will be written (if any)
		lu_long dest_start_x; 
		lu_long dest_start_y;
	};

	static void lu_rec__destroy(Lu_Rec self, Lu_Mem mem);