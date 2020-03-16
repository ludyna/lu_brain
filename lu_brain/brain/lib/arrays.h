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

	void arr_realloc(Arr self, lu_size new_size);
	Arr arr_merge(Arr self, Arr src);

	lu_p_void arr_find_first_1p(Arr self, bool (*block)(lu_p_void item, lu_p_void p1), lu_p_void p1);

///////////////////////////////////////////////////////////////////////////////
//  Arr2 

	struct arr2 {
		lu_size width;
		lu_size height;
		Arr items;
	};

	// Create and destroy

	Arr2 arr2_create(Mem, lu_size width, lu_size height);
	void arr2_destroy(Arr2, Mem);

	// Main public methods

	void arr2_each(Arr2 self, void (*block)(lu_p_void item));
	void arr2_each_2p(Arr2 self, void (*block)(lu_p_void item, lu_p_void p1, lu_p_void p2), lu_p_void p1, lu_p_void p2);

	static inline lu_p_void arr2_get(Arr2 self, lu_size x, lu_size y)
	{
		return arr_get(self->items, (y * self->width) + x);
	}

	void arr2_set(Arr2, lu_size, lu_size, lu_p_void);


#endif // _LU_ARRAYS_H
