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
	};

	// Create and destroy 

	Arr arr_create(Mem mem, lu_size size);
	static inline Arr arr_temp_create(lu_size size) { return arr_create(g_mem_temp, size); }
	void arr_destroy(Arr, Mem);
	static inline void arr_temp_destroy(Arr self) { arr_destroy(self, g_mem_temp); }

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

	static inline lu_p_void arr_get(Arr self, lu_size index)
	{
		if (index >= self->count)
		{
			return NULL;
		}

		return self->items[index];
	}

	static inline void arr_set(Arr self, lu_size index, lu_p_void value)
	{
		if (index >= self->size)
			return;

		if (index >= self->count)
			self->count = index + 1;

		self->items[index] = value;
	}

	void arr_nullify(Arr);

	static inline void arr_reset(Arr self) { self->count = 0; }

	void arr_realloc(Arr self, lu_size new_size, Mem mem);
	Arr arr_merge(Arr self, Arr src);

	lu_p_void arr_find_first_1p(Arr self, bool (*block)(lu_p_void item, lu_p_void p1), lu_p_void p1);

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

	static inline Arr2 arr2_create(Mem mem, lu_size width, lu_size height)
	{
		Arr2 self = (Arr2) mem_alloc(mem, sizeof(struct arr2));
		
		self->width 	= width;
		self->height 	= height;
		self->items 	= arr_create(mem, width * height);

		return self;
	} 

	static inline void arr2_destroy(Arr2 self, Mem mem)
	{
		arr_destroy(self->items, mem);
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

	static inline lu_p_void arr2_get(Arr2 self, lu_size x, lu_size y)
	{
		return arr_get(self->items, (y * self->width) + x);
	}

	static inline void arr2_set(Arr2 self, lu_size x, lu_size y, lu_p_void value)
	{
		lu_size index = (y * self->width) + x;

		arr_set(self->items, (y * self->width) + x, value);
	}

	static inline void arr2_realloc(Arr2 self, lu_size w, lu_size h, Mem mem)  
	{ 
		lu_assert(w + h > self->width + self->height);

		self->width = w;
		self->height = h;

		arr_realloc(self->items, self->width * self->height, mem);
	} 


#endif // _LU_ARRAYS_H
