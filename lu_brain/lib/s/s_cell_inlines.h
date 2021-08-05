/**
	Copyright © 2021 Oleh Ihorovych Novosad 
*/ 
 
///////////////////////////////////////////////////////////////////////////////
// Cell Inlines 

	static inline Lu_S_Base_Cell lu_s_base_cell_init(Lu_S_Base_Cell self, enum lu_s_cell_type type, Lu_S_Layer layer)
	{
		lu_assert(self);
		self->type = type;
		self->layer = layer;
		
		lu_s_slot_1_init(&self->c);

		return self;
	}

	static inline Lu_S_Component_Cell lu_s_component_cell_init(
		Lu_S_Component_Cell self, 
		enum lu_s_cell_type type, 
		Lu_S_Layer layer,
		Hnn_Cell_Value* cells 
	)
	{
		lu_assert(self);
		lu_s_base_cell_init(&self->super, type, layer);

		self->cells = cells;

		return self;
	}

	static inline Lu_S_Component_Cell lu_s_pixel_cell_init(
		Lu_S_Component_Cell self, 
		enum lu_s_cell_type type, 
		Lu_S_Layer layer, 
		lu_size x, 
		lu_size y
	)
	{
		lu_assert(self);
		lu_assert(v);
		lu_assert(p);

		lu_s_base_cell_init(&self->super, type, layer);

		self->x = x;
		self->y = y;

		lu_s_slot_1_init(&self->p);

		return self;
	}

	static inline Lu_S_Component_Cell lu_s_rec_cell_init(
		Lu_S_Component_Cell self, 
		enum lu_s_cell_type type, 
		Lu_S_Layer layer
	)
	{
		lu_assert(self);
		lu_assert(v);
		lu_assert(p);

		lu_s_base_cell_init(&self->super, type, layer);
		lu_s_slot_4_init(&self->p);

		return self;
	}

	static inline Lu_S_Component_Cell lu_s_seq_cell_init(
		Lu_S_Component_Cell self, 
		enum lu_s_cell_type type, 
		Lu_S_Layer layer
	)
	{
		lu_assert(self);
		lu_assert(v);
		lu_assert(p);

		lu_s_base_cell_init(&self->super, type, layer);
		lu_s_slot_4_init(&self->p);

		return self;
	}
