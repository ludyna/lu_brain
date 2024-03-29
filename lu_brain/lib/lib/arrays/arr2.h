/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
//  Arr2 

	struct arr2 {
		lu_size width;
		lu_size height;
		Lu_Arr items;
	};

	static inline lu_size arr2__width(Arr2 self) { return self->width; }
	static inline lu_size arr2__height(Arr2 self) { return self->height; }

	// Create and destroy

	static inline Arr2 arr2__create(Lu_Mem mem, lu_size width, lu_size height, lu_bool allow_realloc)
	{
		Arr2 self = (Arr2) lu_mem__alloc(mem, sizeof(struct arr2));
		
		self->width 	= width;
		self->height 	= height;
		self->items 	= lu_arr__create(mem, width * height, allow_realloc);

		return self;
	} 

	static inline void arr2__destroy(Arr2 self)
	{
		lu__user_assert_void(self, "Arr2 is NULL");

		Lu_Mem mem = self->items->mem;
		lu__user_assert_void(mem, "Lu_Mem is NULL");

		lu_arr__destroy(self->items);
		lu_mem__free(mem, (lu_p_byte) self);
	}

	// Main public methods

	static inline void arr2__each(Arr2 self, void (*block)(lu_p_void item))
	{
		lu_arr__each(self->items, block);
	}

	static inline void arr2__each_2p(
		Arr2 self, 
		void (*block)(lu_p_void item, lu_p_void p1, lu_p_void p2), 
		lu_p_void p1, 
		lu_p_void p2
	)
	{
		lu_arr__each_2p(self->items, block, p1, p2);
	}

	static inline lu_p_void arr2__get_internal(Arr2 self, lu_size x, lu_size y)
	{
		return lu_arr__get(self->items, (y * self->width) + x);
	}

	static inline void arr2__set_internal(Arr2 self, lu_size x, lu_size y, lu_p_void value)
	{
		lu_arr__set(self->items, (y * self->width) + x, value);
	}

	static inline lu_p_void arr2__get_internal_debug(Arr2 self, lu_size x, lu_size y, const char* func, const char* file, int line)
	{
		// lu__user_debug_args_internal(func, file, line, "arr2__get_internal_debug: (x=%lu, y=%lu, index=%lu)", x, y, (y * self->width) + x);
		return lu_arr__get_internal_debug(self->items, (y * self->width) + x, func, file, line);
	}

	static inline void arr2__set_internal_debug(Arr2 self, lu_size x, lu_size y, lu_p_void value, const char* func, const char* file, int line)
	{
		lu_arr__set_internal_debug(self->items, (y * self->width) + x, value, func, file, line);
	}

	#ifdef LU__DEBUG

	#define arr2__get(self, x, y) arr2__get_internal_debug(self, x, y, __func__, __FILE__, __LINE__)
	#define arr2__set(self, x, y, v) arr2__set_internal_debug(self, x, y, v, __func__, __FILE__, __LINE__)

	#else

	#define arr2__get(self, x, y) arr2__get_internal(self, x, y)
	#define arr2__set(self, x, y, v) arr2__set_internal(self, x, y, v)

	#endif

	static inline void arr2__realloc(Arr2 self, lu_size w, lu_size h)  
	{ 
		lu__assert(w + h > self->width + self->height);

		self->width = w;
		self->height = h;

		lu_arr__realloc(self->items, self->width * self->height);
	}
