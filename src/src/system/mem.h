/**
	Copyright © 2020 Oleh Ihorovych Novosad 
	App Mem
*/
#ifndef _LU_MEM_H
#define _LU_MEM_H

///////////////////////////////////////////////////////////////////////////////
// Nouns
	
	typedef struct mem* 				Mem;
	typedef struct preallocated_mem*	Preallocated_Mem;
	typedef struct mem_arr* 			Mem_Arr;


///////////////////////////////////////////////////////////////////////////////
// Mem

	enum mem_flags {
		MEM_DYNAMIC = 1,
		MEM_PREALLOCATED = 2
	};

	struct mem {
		lu_flags 	flags;
		lu_p_byte 	(*alloc)(Mem, lu_size size);
		void 		(*free)(Mem, lu_p_byte);
		void 		(*destroy)(Mem);
	};

	Mem mem_create();
	void mem_destroy(Mem self);

	lu_p_byte mem_alloc(Mem self, lu_size size_in_bytes);
	lu_p_byte mem_free(Mem self, lu_p_byte p);

///////////////////////////////////////////////////////////////////////////////
// Preallocated_Mem

	struct preallocated_mem {

		struct mem 		super;

		lu_size 		size_in_bytes;
		lu_p_byte 		buff_start;
		lu_p_byte 		buff_end;
		lu_p_byte 		buff_pos;
	};

	Preallocated_Mem preallocated_mem_create(lu_size size_in_bytes);
	void preallocated_mem_destroy(Mem self);

	lu_p_byte preallocated_mem_alloc(Mem self, lu_size size_in_bytes); 

	static inline lu_size preallocated_mem_avail(Preallocated_Mem self)
	{
		return self->buff_end - self->buff_pos;
	}

///////////////////////////////////////////////////////////////////////////////
// Mem_Arr

	enum mem_arr_flags {
		MEM_ARR_ITEM_FREEABLE = 1
	};

	struct mem_arr {
		lu_size 		item_size;
		lu_size			size;
		lu_flags		flags;

		lu_p_byte		items_start;
		lu_p_byte		items_end;
		lu_p_byte		items_pos;
		lu_size 		items_count;

		lu_p_byte* 		free_start;
		lu_size 		free_count;
	};

	// 
	//	If percent is provided (>0 && <= 100), sisa size is calculated from currently
	//  available space with minimum one item_size.
	//
	Mem_Arr mem_arr_create (
		Mem 			mem, 
		lu_size 		item_size, 
		lu_size 		size, 
		lu_value 		percent,
		lu_flags 		flags
	);

	lu_p_byte mem_arr_item_alloc(Mem_Arr self);
	void mem_arr_item_free(Mem_Arr, lu_p_byte item);

#endif // _LU_MEM_H
