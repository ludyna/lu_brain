/**
	Copyright © 2021 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Typedefs

	typedef struct arr* 		Arr;

///////////////////////////////////////////////////////////////////////////////
// Arr

	struct arr {
		lu_size 	size;
		lu_size 	count;
		lu_p_void* 	items;
		lu_bool 	allow_realloc;
		Lu_Mem 		mem;
	};

	// Create and destroy 

	Arr arr_create(Lu_Mem mem, lu_size size, lu_bool allow_realloc);
	static inline Arr arr_temp_create(lu_size size, lu_bool allow_realloc) { return arr_create(lu_g_mem, size, allow_realloc); }
	void arr_destroy(Arr);
	static inline void arr_temp_destroy(Arr self) { arr_destroy(self); }

	// Setters / getters

	static inline lu_size arr_count(Arr self) { return self->count; }
	static inline lu_size arr_size(Arr self) { return self->size; }
	static inline lu_p_void arr_last(Arr self) { return self->items[self->count-1]; }

	// Main public methods

	// 
	// Appends next value, if needed tries to resize array.
	//
	lu_size arr_append(Arr, lu_p_void);

	void arr_each(Arr self, void (*block)(lu_p_void item));
	void arr_each_1p(Arr self, void (*block)(lu_p_void item, lu_p_void p1), lu_p_void p1);
	void arr_each_2p(Arr self, void (*block)(lu_p_void item, lu_p_void p1, lu_p_void p2), lu_p_void p1, lu_p_void p2);

	void arr_each_with_index_1p(Arr self, void (*block)(Arr self, lu_p_void item, lu_size index, lu_p_void p1), lu_p_void p1);


	static inline lu_p_void arr_get_internal(Arr self, lu_size index)
	{
		return self->items[index];
	}

	static inline void arr_set_internal(Arr self, lu_size index, lu_p_void value)
	{
		if (index >= self->count)
			self->count = index + 1;

		self->items[index] = value;
	}

	static inline lu_p_void arr_get_internal_debug(Arr self, lu_size index, const char* func, const char* file, int line)
	{
		if (g_user_assert && index >= self->size)
			lu_user_debug_args_internal(func, file, line, "arr_get: Out of range(index=%lu, size=%lu)", index, self->size);
		
		return arr_get_internal(self, index);
	}

	static inline void arr_set_internal_debug(Arr self, lu_size index, lu_p_void value, const char* func, const char* file, int line)
	{
		if (g_user_assert && index >= self->size)
			lu_user_debug_args_internal(func, file, line, "arr_set: Out of range(index=%lu, size=%lu)", index, self->size);

		arr_set_internal(self, index, value);
	}

	#ifdef LU_DEBUG

	#define arr_get(self, index) arr_get_internal_debug(self, index, __func__, __FILE__, __LINE__)
	#define arr_set(self, index, value) arr_set_internal_debug(self, index, value, __func__, __FILE__, __LINE__);

	#else

	#define arr_get(self, index) arr_get_internal(self, index)
	#define arr_set(self, index, value) arr_set_internal(self, index, value);

	#endif

	void arr_nullify(Arr);

	static inline void arr_reset(Arr self) { self->count = 0; }

	void arr_realloc(Arr self, lu_size new_size);
	Arr arr_merge(Arr self, Arr src);

	lu_p_void arr_find_first_1p(Arr self, lu_bool (*block)(lu_p_void item, lu_p_void p1), lu_p_void p1);