/**
	Copyright © 2021 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Layers Inline Inits

	static inline Lu_S_Base_Layer lu_s_base_layer_init(
		Lu_S_Base_Layer self, 
		enum lu_s_layer_type type, 
		lu_size number, 
		lu_size w, 
		lu_size h
	)
	{
		lu_assert(self);
		lu_assert(w > 0);
		lu_assert(h > 0);
		lu_assert(type >= 0 && type < LU_SLT_END);

		self->type = type;
		self->number = number;
		self->w = w;
		self->h = h;

		return self;
	}

	static inline Lu_S_Component_Layer lu_s_component_layer_init(
		Lu_S_Component_Layer self, 
		lu_size w, 
		lu_size h,
		lu_size d,
		struct lu_s_layer_conf conf
	)
	{
		lu_assert(self);
		lu_assert(d > 0);

		lu_s_base_layer_init(&self->super, LU_SLT_COMPONENT, 0, w, h);

		self->d = d;
		self->conf = conf;

		self->cells = (Lu_S_Component_Cell*) 

		return Lu_S_Component_Layer;
	}

