/**
	Copyright © 2020 Oleh Ihorovych Novosad 
	App Mem
*/
#ifndef _LU_A_MEM_H
#define _LU_A_MEM_H

///////////////////////////////////////////////////////////////////////////////
// Nouns
	
	typedef struct mem* 		Mem;
	typedef struct mem_arr* 	Mem_Arr;


///////////////////////////////////////////////////////////////////////////////
// Mem

	struct mem {
		lu_size 		size_in_bytes;
		lu_p_byte 		buff_start;
		lu_p_byte 		buff_end;
		lu_p_byte 		buff_pos;


	};

	Mem mem_create(lu_size size_in_bytes);
	void mem_destroy(Mem self);

	lu_p_byte mem_alloc(Mem self, lu_size size_in_bytes); 

	static inline lu_size mem_avail(Mem self)
	{
		return self->buff_end - self->buff_pos;
	}

///////////////////////////////////////////////////////////////////////////////
// Mem_Arr

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

	enum mem_arr_flags {
		MEM_ARR_ITEM_FREEABLE = 1
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

#endif // _LU_A_MEM_H
