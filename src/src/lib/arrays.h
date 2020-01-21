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

	Arr arr_create(lu_size size);
	void arr_destroy(Arr*);

	// Setters / getters

	static inline lu_size arr_count(Arr self) { return self->count; }
	static inline lu_size arr_size(Arr self) { return self->size; }

	// Main public methods

	lu_size arr_append(Arr, lu_p_void);

	void arr_each(Arr self, void (*block)(lu_p_void item));
	void arr_each_1p(Arr self, void (*block)(lu_p_void item, lu_p_void p1), lu_p_void p1);
	void arr_each_2p(Arr self, void (*block)(lu_p_void item, lu_p_void p1, lu_p_void p2), lu_p_void p1, lu_p_void p2);

	static inline lu_p_void arr_get(Arr self, lu_size index)
	{
		if (index >= self->count)
		{
			return NULL;
		}

		return self->items[index];
	}

	void arr_set(Arr, lu_size, lu_p_void);

	void arr_nullify(Arr);

	static inline void arr_reset(Arr self) { self->count = 0; }

	void arr_realloc(Arr self, lu_size new_size);
	Arr arr_merge(Arr self, Arr src);

///////////////////////////////////////////////////////////////////////////////
//  Arr2 

	struct arr2 {
		lu_size width;
		lu_size height;
		Arr items;
	};

	// Create and destroy

	Arr2 arr2_create(lu_size width, lu_size height);
	void arr2_destroy(Arr2*);

	// Main public methods

	void arr2_each(Arr2 self, void (*block)(lu_p_void item));
	void arr2_each_2p(Arr2 self, void (*block)(lu_p_void item, lu_p_void p1, lu_p_void p2), lu_p_void p1, lu_p_void p2);

	static inline lu_p_void arr2_get(Arr2 self, lu_size x, lu_size y)
	{
		return arr_get(self->items, (y * self->width) + x);
	}

	void arr2_set(Arr2, lu_size, lu_size, lu_p_void);


#endif // _LU_ARRAYS_H
