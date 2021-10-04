/**
	Copyright © 2021 Oleh Ihorovych Novosad 
*/ 
 
///////////////////////////////////////////////////////////////////////////////
// Cell Inits 

	static inline Lu_S_Base_Cell lu_s_base_cell_init(Lu_S_Base_Cell self, enum lu_s_cell_type type, Lu_S_Base_Layer layer)
	{
		lu__assert(self);
		self->type = type;
		self->layer = layer;
		
		lu_s_slot_1_init(&self->c);

		return self;
	}

	static inline Lu_S_Component_Cell lu_s_component_cell_init(
		Lu_S_Component_Cell self, 
		enum lu_s_cell_type type, 
		Lu_S_Base_Layer layer,
		Hnn_Cell_Value* cells 
	)
	{
		lu__assert(self);
		lu_s_base_cell_init(&self->super, type, layer);

		self->cells = cells;

		return self;
	}

	static inline Lu_S_Pixel_Cell lu_s_pixel_cell_init(
		Lu_S_Pixel_Cell self, 
		enum lu_s_cell_type type, 
		Lu_S_Base_Layer layer, 
		lu_size x, 
		lu_size y
	)
	{
		lu__assert(self);

		lu_s_base_cell_init(&self->super, type, layer);
		lu_s_slot_2_init(&self->p);

		self->x = x;
		self->y = y;

		return self;
	}

	static inline Lu_S_Rec_Cell lu_s_rec_cell_init(
		Lu_S_Rec_Cell self, 
		enum lu_s_cell_type type, 
		Lu_S_Base_Layer layer
	)
	{
		lu__assert(self);

		lu_s_base_cell_init(&self->super, type, layer);
		lu_s_slot_4_init(&self->p);

		return self;
	}

	static inline Lu_S_Seq_Nx_Cell lu_s_seq_nx_cell_init(
		Lu_S_Seq_Nx_Cell self, 
		enum lu_s_cell_type type, 
		Lu_S_Base_Layer layer,
		Lu_Rec rec
	)
	{
		lu__assert(self);

		lu_s_base_cell_init(&self->super, type, layer);
		lu_s_slot_4_init(&self->p);

		self->rec = rec;

		return self;
	}

	static inline Lu_S_Seq_Cell lu_s_seq_cell_init(
		Lu_S_Seq_Cell self, 
		enum lu_s_cell_type type, 
		Lu_S_Base_Layer layer
	)
	{
		lu__assert(self);

		lu_s_base_cell_init(&self->super, type, layer);
		lu_s_slot_2_init(&self->p);

		return self;
	}

	static inline Lu_S_Story_Nx_Cell lu_s_story_nx_cell_init(
		Lu_S_Story_Nx_Cell self, 
		enum lu_s_cell_type type, 
		Lu_S_Base_Layer layer
	)
	{
		lu__assert(self);

		lu_s_base_cell_init(&self->super, type, layer);
		lu_s_slot_2_init(&self->p);

		return self;
	}
