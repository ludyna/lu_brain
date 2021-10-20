/**
	Copyright © 2021 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Typedefs

	typedef struct lu_arr* Lu_Arr;

///////////////////////////////////////////////////////////////////////////////
// Lu_Arr

	struct lu_arr {
		lu_size 	size;
		lu_size 	count;
		lu_p_void* 	items;
		lu_bool 	allow_realloc;
		Lu_Mem 		mem;
	};

	// Create and destroy 

	Lu_Arr lu_arr__create(Lu_Mem mem, lu_size size, lu_bool allow_realloc);
	static inline Lu_Arr lu_arr__temp_create(lu_size size, lu_bool allow_realloc) { return lu_arr__create(lu_g_mem, size, allow_realloc); }
	void lu_arr__destroy(Lu_Arr);
	static inline void lu_arr__temp_destroy(Lu_Arr self) { lu_arr__destroy(self); }

	// Setters / getters

	static inline lu_size lu_arr__count(Lu_Arr self) { return self->count; }
	static inline lu_size lu_arr__size(Lu_Arr self) { return self->size; }
	static inline lu_p_void lu_arr__last(Lu_Arr self) { return self->items[self->count-1]; }

	// Main public methods

	// 
	// Appends next value, if needed tries to resize array.
	//
	lu_size lu_arr__append(Lu_Arr, lu_p_void);

	void lu_arr__each(Lu_Arr self, void (*block)(lu_p_void item));
	void lu_arr__each_1p(Lu_Arr self, void (*block)(lu_p_void item, lu_p_void p1), lu_p_void p1);
	void lu_arr__each_2p(Lu_Arr self, void (*block)(lu_p_void item, lu_p_void p1, lu_p_void p2), lu_p_void p1, lu_p_void p2);

	void lu_arr__each_with_index_1p(Lu_Arr self, void (*block)(Lu_Arr self, lu_p_void item, lu_size index, lu_p_void p1), lu_p_void p1);


	static inline lu_p_void lu_arr__get_internal(Lu_Arr self, lu_size index)
	{
		return self->items[index];
	}

	static inline void lu_arr__set_internal(Lu_Arr self, lu_size index, lu_p_void value)
	{
		if (index >= self->count)
			self->count = index + 1;

		self->items[index] = value;
	}

	static inline lu_p_void lu_arr__get_internal_debug(Lu_Arr self, lu_size index, const char* func, const char* file, int line)
	{
		if (g_user_assert && index >= self->size)
			lu_user_debug_args_internal(func, file, line, "lu_arr__get: Out of range(index=%lu, size=%lu)", index, self->size);
		
		return lu_arr__get_internal(self, index);
	}

	static inline void lu_arr__set_internal_debug(Lu_Arr self, lu_size index, lu_p_void value, const char* func, const char* file, int line)
	{
		if (g_user_assert && index >= self->size)
			lu_user_debug_args_internal(func, file, line, "lu_arr__set: Out of range(index=%lu, size=%lu)", index, self->size);

		lu_arr__set_internal(self, index, value);
	}

	#ifdef LU_DEBUG

	#define lu_arr__get(self, index) lu_arr__get_internal_debug(self, index, __func__, __FILE__, __LINE__)
	#define lu_arr__set(self, index, value) lu_arr__set_internal_debug(self, index, value, __func__, __FILE__, __LINE__);

	#else

	#define lu_arr__get(self, index) lu_arr__get_internal(self, index)
	#define lu_arr__set(self, index, value) lu_arr__set_internal(self, index, value);

	#endif

	void lu_arr__nullify(Lu_Arr);

	static inline void lu_arr__reset(Lu_Arr self) { self->count = 0; }

	void lu_arr__realloc(Lu_Arr self, lu_size new_size);
	Lu_Arr lu_arr__merge(Lu_Arr self, Lu_Arr src);

	lu_p_void lu_arr__find_first_1p(Lu_Arr self, lu_bool (*block)(lu_p_void item, lu_p_void p1), lu_p_void p1);