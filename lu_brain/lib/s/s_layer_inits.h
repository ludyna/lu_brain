/**
	Copyright © 2021 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Layers Inline Inits

	//
	// Lu_S_Base_Layer
	//

	static inline Lu_S_Base_Layer lu_s_base_layer__init(
		Lu_S_Base_Layer self, 
		Lu_Mem mem,
		enum lu_s_layer_type type, 
		lu_size number, 
		lu_size w, 
		lu_size h
	)
	{
		lu__assert(self);
		lu__assert(mem);
		lu__assert(w > 0);
		lu__assert(h > 0);
		lu__assert(type >= 0 && type < LU_SLT_END);

		self->mem = mem;
		self->type = type;
		self->number = number;
		self->w = w;
		self->h = h;

		return self;
	}

	static inline void lu_s_base_layer__deinit(Lu_S_Base_Layer self)
	{
		lu__assert(self);

		self->mem = NULL;
		self->type = LU_SLT_END;
		self->number = 0;
		self->w = 0;
		self->h = 0;
	}

	//
	// Lu_S_Comp_Layer
	//

	static inline Lu_S_Comp_Layer lu_s_comp_layer__init(
		Lu_S_Comp_Layer self, 
		Lu_Mem mem, 
		lu_size w, 
		lu_size h,
		lu_size d,
		lu_value min_val,
		lu_value max_val,
		lu_size cells_size 
	)
	{
		lu__assert(self);
		lu__assert(mem);
		lu__assert(w > 0);
		lu__assert(h > 0);
		lu__assert(d > 0);

		lu_s_base_layer__init(&self->super, mem, LU_SLT_COMPONENT, 0, w, h);

		self->d = d;
		lu_s_comp_cell__init(&self->conf, mem, min_val, max_val, cells_size);

		self->cells_size = w * h * d;
		self->cells = (Lu_S_Comp_Cell*) lu_mem__alloc(mem, sizeof(Lu_S_Comp_Cell) * self->cells_size);
		lu__assert(self->cells);

		return self;
	} 

	static inline void lu_s_comp_layer__deinit(Lu_S_Comp_Layer self)
	{
		lu__assert(self);
		lu__assert(self->super.mem);

		if (self->cells)
			lu_mem__free(self->super.mem, (lu_p_byte) self->cells);

		lu_s_comp_cell__deinit(&self->conf);

		lu_s_base_layer__deinit(&self->super);
	}

	//
	// Lu_S_Pixel_Layer
	//
	
	static inline Lu_S_Pixel_Layer lu_s_pixel_layer__init(Lu_S_Pixel_Layer self, Lu_Mem mem, lu_size w, lu_size h)
	{
		lu__assert(self);
		lu__assert(mem);

		lu__assert(w > 0);
		lu__assert(h > 0);

		lu_s_base_layer__init(&self->super, mem, LU_SLT_PIXEL, 0, w, h);

		self->cells_size = w * h;
		self->cells = (Lu_S_Pixel_Cell*) lu_mem__alloc(mem, sizeof(Lu_S_Pixel_Cell) * self->cells_size);
		lu__assert(self->cells);

		return self;
	}

	static inline void lu_s_pixel_layer__deinit(Lu_S_Pixel_Layer self)
	{
		lu__assert(self);
		lu__assert(self->super.mem);

		lu_mem__free(self->super.mem, (lu_p_byte) self->cells);

		lu_s_base_layer__deinit(&self->super);
	}

	//
	// Lu_S_Rec_Layer
	//

	static inline Lu_S_Rec_Layer lu_s_rec_layer__init(Lu_S_Rec_Layer self, Lu_Mem mem, lu_size id, lu_size w, lu_size h)
	{
		lu__assert(self);
		lu__assert(w > 0);
		lu__assert(h > 0);

		lu_s_base_layer__init(&self->super, mem, LU_SLT_REC, id, w, h); 

		self->cells_size = w * h;
		self->cells = (Lu_S_Rec_Cell*) lu_mem__alloc(mem, sizeof(Lu_S_Rec_Cell) * self->cells_size);
		lu__assert(self->cells);

		return self;
	}

	static inline void lu_s_rec_layer__deinit(Lu_S_Rec_Layer self)
	{
		lu__assert(self);
		lu__assert(self->super.mem);

		lu_mem__free(self->super.mem, (lu_p_byte) self->cells);

		lu_s_base_layer__deinit(&self->super);
	}

	//
	// Lu_S_Seq_Nx_Layer
	//

	static inline Lu_S_Seq_Nx_Layer lu_s_seq_nx_layer__init(Lu_S_Seq_Nx_Layer self, Lu_Mem mem, lu_size w)
	{
		lu__assert(self);
		lu__assert(w > 0);

		lu_s_base_layer__init(&self->super, mem, LU_SLT_SEQ_NX, 0, w, 1);
	}

	static inline void lu_s_seq_nx_layer__deinit(Lu_S_Seq_Nx_Layer self)
	{
		lu__assert(self);
		lu__assert(self->super.mem);

		//...

		lu_s_base_layer__deinit(&self->super);
	}

	//
	// Lu_S_Seq_Layer
	//

	static inline Lu_S_Seq_Layer lu_s_seq_layer__init(Lu_S_Seq_Layer self, Lu_Mem mem, lu_size w)
	{
		lu__assert(self);
		lu__assert(w > 0);

		lu_s_base_layer__init(&self->super, mem, LU_SLT_SEQ, 0, w, 1);
	}

	static inline void lu_s_seq_layer__deinit(Lu_S_Seq_Layer self)
	{
		lu__assert(self);
		lu__assert(self->super.mem);

		//...

		lu_s_base_layer__deinit(&self->super);
	}

	//
	// Lu_S_Story_Nx_Layer
	//

	static inline Lu_S_Story_Nx_Layer lu_s_story_nx_layer__init(Lu_S_Story_Nx_Layer self, Lu_Mem mem, lu_size w)
	{
		lu__assert(self);
		lu__assert(w > 0);

		lu_s_base_layer__init(&self->super, mem, LU_SLT_SEQ, 0, w, 1);
	}

	static inline void lu_s_story_nx_layer__deinit(Lu_S_Story_Nx_Layer self)
	{
		lu__assert(self);
		lu__assert(self->super.mem);

		//...

		lu_s_base_layer__deinit(&self->super);
	}