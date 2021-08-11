/**
	Copyright © 2021 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Layers Inline Inits

	static inline Lu_S_Base_Layer lu_s_base_layer_init(
		Lu_S_Base_Layer self, 
		Lu_Mem mem,
		enum lu_s_layer_type type, 
		lu_size number, 
		lu_size w, 
		lu_size h
	)
	{
		lu_assert(self);
		lu_assert(mem);
		lu_assert(w > 0);
		lu_assert(h > 0);
		lu_assert(type >= 0 && type < LU_SLT_END);

		self->mem = mem;
		self->type = type;
		self->number = number;
		self->w = w;
		self->h = h;

		return self;
	}

	static inline void lu_s_base_layer_deinit(Lu_S_Base_Layer self)
	{
		lu_assert(self);

		self->mem = NULL;
		self->type = LU_SLT_END;
		self->number = 0;
		self->w = 0;
		self->h = 0;
	}

	static inline Lu_S_Component_Layer lu_s_component_layer_init(
		Lu_S_Component_Layer self, 
		Lu_Mem mem, 
		lu_size w, 
		lu_size h,
		lu_size d,
		lu_value min_val,
		lu_value max_val,
		lu_size cells_size 
	)
	{
		lu_assert(self);
		lu_assert(mem);
		lu_assert(d > 0);

		lu_s_base_layer_init(&self->super, mem, LU_SLT_COMPONENT, 0, w, h);

		self->d = d;
		lu_s_layer_conf_init(&self->conf, mem, min_val, max_val, cells_size);

		self->cells_size = w * h * d;
		self->cells = (Lu_S_Component_Cell*) lu_mem_alloc(mem, sizeof(Lu_S_Component_Cell) * self->cells_size);

		return self;
	} 

	static inline void lu_s_component_layer_deinit(Lu_S_Component_Layer self)
	{
		lu_assert(self);
		lu_s_base_layer_deinit(&self->super);

		if (self->cells)
			lu_mem_free(self->super.mem, (lu_p_byte) self->cells);
	}

