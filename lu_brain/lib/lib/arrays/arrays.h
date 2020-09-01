/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

#ifndef _LU_ARRAYS_H
#define _LU_ARRAYS_H

///////////////////////////////////////////////////////////////////////////////
// Nouns

	typedef struct arr* 		Arr;
	typedef struct arr2* 		Arr2;
	
///////////////////////////////////////////////////////////////////////////////
// Arr

	struct arr {
		lu_size 	size;
		lu_size 	count;
		lu_p_void* 	items;
		lu_bool 	allow_realloc;
		Mem 		mem;
	};

	// Create and destroy 

	Arr arr_create(Mem mem, lu_size size, lu_bool allow_realloc);
	static inline Arr arr_temp_create(lu_size size) { return arr_create(g_mem_temp, size, true); }
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

///////////////////////////////////////////////////////////////////////////////
//  Arr2 

	struct arr2 {
		lu_size width;
		lu_size height;
		Arr items;
	};

	static inline lu_size arr2_width(Arr2 self) { return self->width; }
	static inline lu_size arr2_height(Arr2 self) { return self->height; }

	// Create and destroy

	static inline Arr2 arr2_create(Mem mem, lu_size width, lu_size height, lu_bool allow_realloc)
	{
		Arr2 self = (Arr2) mem_alloc(mem, sizeof(struct arr2));
		
		self->width 	= width;
		self->height 	= height;
		self->items 	= arr_create(mem, width * height, allow_realloc);

		return self;
	} 

	static inline void arr2_destroy(Arr2 self)
	{
		lu_user_assert_void(self, "Arr2 is NULL");

		Mem mem = self->items->mem;
		lu_user_assert_void(mem, "Mem is NULL");

		arr_destroy(self->items);
		mem_free(mem, (lu_p_byte) self);
	}

	// Main public methods

	static inline void arr2_each(Arr2 self, void (*block)(lu_p_void item))
	{
		arr_each(self->items, block);
	}

	static inline void arr2_each_2p(
		Arr2 self, 
		void (*block)(lu_p_void item, lu_p_void p1, lu_p_void p2), 
		lu_p_void p1, 
		lu_p_void p2
	)
	{
		arr_each_2p(self->items, block, p1, p2);
	}

	static inline lu_p_void arr2_get_internal(Arr2 self, lu_size x, lu_size y)
	{
		return arr_get(self->items, (y * self->width) + x);
	}

	static inline void arr2_set_internal(Arr2 self, lu_size x, lu_size y, lu_p_void value)
	{
		lu_size index = (y * self->width) + x;

		arr_set(self->items, (y * self->width) + x, value);
	}

	static inline lu_p_void arr2_get_internal_debug(Arr2 self, lu_size x, lu_size y, const char* func, const char* file, int line)
	{
		// lu_user_debug_args_internal(func, file, line, "arr2_get_internal_debug: (x=%lu, y=%lu, index=%lu)", x, y, (y * self->width) + x);
		return arr_get_internal_debug(self->items, (y * self->width) + x, func, file, line);
	}

	static inline void arr2_set_internal_debug(Arr2 self, lu_size x, lu_size y, lu_p_void value, const char* func, const char* file, int line)
	{
		lu_size index = (y * self->width) + x;

		arr_set_internal_debug(self->items, (y * self->width) + x, value, func, file, line);
	}

	#ifdef LU_DEBUG

	#define arr2_get(self, x, y) arr2_get_internal_debug(self, x, y, __func__, __FILE__, __LINE__)
	#define arr2_set(self, x, y, v) arr2_set_internal_debug(self, x, y, v, __func__, __FILE__, __LINE__)

	#else

	#define arr2_get(self, x, y) arr2_get_internal(self, x, y)
	#define arr2_set(self, x, y, v) arr2_set_internal(self, x, y, v)

	#endif

	static inline void arr2_realloc(Arr2 self, lu_size w, lu_size h)  
	{ 
		lu_assert(w + h > self->width + self->height);

		self->width = w;
		self->height = h;

		arr_realloc(self->items, self->width * self->height);
	}


#endif // _LU_ARRAYS_H
