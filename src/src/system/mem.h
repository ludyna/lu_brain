/**
	Copyright © 2020 Oleh Ihorovych Novosad 

	Memory Abstractors
		help with managing memory, debuging memory, memory preallocation, etc.
	
	Usage: 
		1. Always assign created memory type to Mem pointer

			Mem mem2 = mem_preallocated_create(mem1, 512);

		2. Always use only mem_alloc(), mem_realloc() and mem_free() macroses.

			Arr a = (Arr) mem_alloc(mem2, sizeof(struct arr));

		3. Memories could be compositional. Every memory could be based on another memory. 

	       	For example mem1 here:
		   	Mem mem2 = mem_preallocated_create(mem1, 512); 
		   	could be another Mem_Preallocated or Mem_Arr or just Mem or something else.
*/			
#ifndef _LU_MEM_H
#define _LU_MEM_H

///////////////////////////////////////////////////////////////////////////////
// Nouns
	
	typedef struct mem* 				Mem;
	typedef struct mem_preallocated*	Mem_Preallocated;
	typedef struct mem_arr* 			Mem_Arr;


///////////////////////////////////////////////////////////////////////////////
// Mem

	enum mem_type {
		MEM_DYNAMIC = 1,
		MEM_PREALLOCATED = 2
	};

	struct mem {
		lu_flags 	(*type)(Mem);
		lu_p_byte 	(*alloc)(Mem, lu_size size);
		lu_p_byte 	(*realloc)(Mem, lu_p_byte, lu_size);
		void 		(*free)(Mem, lu_p_byte);
		void 		(*destroy)(Mem);
	};

	Mem mem_create();
	void mem_destroy(Mem self);

	#define mem_type(mem) mem_type_internal(mem)
	#define mem_alloc(mem, size) mem_alloc_internal(mem, size, __FILE__, __LINE__)
	#define mem_realloc(mem, p, size) mem_realloc_internal(mem, p, size, __FILE__, __LINE__)
	#define mem_free(mem, p) mem_free_internal(mem, p, __FILE__, __LINE__)

	lu_p_byte mem_alloc_internal(Mem self, lu_size size_in_bytes, const char* file, int line);
	lu_p_byte mem_realloc_internal(Mem self, lu_p_byte p, lu_size size_in_bytes, const char* file, int line);
	lu_p_byte mem_free_internal(Mem self, lu_p_byte p, const char* file, int line);

///////////////////////////////////////////////////////////////////////////////
// Mem_Preallocated

	struct mem_preallocated {

		struct mem 		super;

		lu_size 		size_in_bytes;
		lu_p_byte 		buff_start;
		lu_p_byte 		buff_end;
		lu_p_byte 		buff_pos;
	};

	Mem_Preallocated mem_preallocated_create(lu_size size_in_bytes);
	void mem_preallocated_destroy(Mem self);

	static inline lu_size mem_preallocated_avail(Mem_Preallocated self)
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
