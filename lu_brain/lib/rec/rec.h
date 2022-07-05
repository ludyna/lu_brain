/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Lu_Rec_Config predefined 

	extern struct lu_rec_config lu_g_rc_predefined[LU_REC__END];

///////////////////////////////////////////////////////////////////////////////
// Lu_Rec_View config

	struct lu_rec_view {
		// Starting position from which we read data from source
		// src_start_x should be >= 0
		// src_start_y should be >= 0
		// src_end_x should be <= data.width
		// src_end_y should be <= data.height
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

	//
	// Constructors / Destructors
	//

	static inline Lu_Rec_View lu_rec_view__init(Lu_Rec_View self, lu_size w, lu_size h, lu_size d)
	{
		lu__assert(self);

		self->src_start_x = 0;
		self->src_start_y = 0;
		self->src_start_z = 0;
		self->src_end_x = w;
		self->src_end_y = h;
		self->src_end_z = d;

		self->dest_start_x = 0;
		self->dest_start_y = 0;

		return self;
	}

	//
	// Set
	//

	static inline void lu_rec_view__set_dest_start_pos(Lu_Rec_View self, lu_long dest_x, lu_long dest_y)
	{
		lu__assert(self);		

		self->dest_start_x = dest_x;
		self->dest_start_y = dest_y;
	}

	static inline void lu_rec_view__set_src_start_pos(Lu_Rec_View self, lu_size src_x, lu_size src_y)
	{
		lu__assert(self);

		self->src_start_x = src_x;
		self->src_start_y = src_y;
	}

	static inline void lu_rec_view__set_src_end_pos(Lu_Rec_View self, lu_size src_x, lu_size src_y)
	{
		lu__assert(self);

		self->src_end_x = src_x;
		self->src_end_y = src_y;
	}

	static inline void lu_rec_view__set_src_start_z(Lu_Rec_View self, lu_size src_z)
	{
		lu__assert(self);

		self->src_start_z = src_z;
	}

	static inline void lu_rec_view__set_src_end_z(Lu_Rec_View self, lu_size src_z)
	{
		lu__assert(self);

		self->src_end_z = src_z;
	}

	//
	// Methods
	// 

	static inline void lu_rec_view__update_to_dimensions(Lu_Rec_View self, lu_size w, lu_size h, lu_size d)
	{
		lu__assert(self);

		if (self->src_end_x > w) self->src_end_x = w;
		if (self->src_end_y > h) self->src_end_y = h;
		if (self->src_end_z > d) self->src_end_z = d;
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_Rec

	struct lu_rec {
		Lu_Brain 					brain;
		lu_size 					id;

		lu_size  					width;
		lu_size  					height;
		lu_size  					depth;

		struct lu_rec_config 		config; 
		struct lu_rec_view 			view;
	};

	static void lu_rec__destroy(Lu_Rec self, Lu_Mem mem);