/**
	Copyright © 2020 Oleh Ihorovych Novosad 

	Memory Abstractors

		help with managing memory, debuging memory, memory preallocation, etc.
	
	Usage: 

		1. Always assign created memory type to Mem pointer

			Mem mem2 = (Mem) mem_preallocated_create(mem1, 512);

		2. Always use only mem_alloc(), mem_realloc(), mem_free(), mem_realloc()
		   and mem_destroy() macroses.

			Arr a = (Arr) mem_alloc(mem2, sizeof(struct arr));

			Use mem_preallocated_create() but don't use mem_preallocated_destroy(), 
			intead use mem_destroy().

		3. Memories could be compositional. Every memory could be based on another memory. 

	       	For example mem1 here:
		   	Mem mem2 = mem_preallocated_create(mem1, 512); 
		   	could be another Mem_Preallocated or Mem_Arr or just Mem or something else.
*/			
#ifndef _LU_MEM_ABSTRACTORS_H
#define _LU_MEM_ABSTRACTORS_H


///////////////////////////////////////////////////////////////////////////////
// Nouns
	
	typedef struct mem* 				Mem;
	typedef struct mem_preallocated*	Mem_Preallocated;
	typedef struct mem_arr* 			Mem_Arr;

///////////////////////////////////////////////////////////////////////////////
// Globals

	extern Mem g_mem_default;

///////////////////////////////////////////////////////////////////////////////
// Mem

	enum mem_type {
		MEM_TYPE_DYNAMIC 		= 1,
		MEM_TYPE_PREALLOCATED 	= 2
	};

	struct mem {
		lu_flags 	(*type)(Mem);
		lu_p_byte 	(*alloc)(Mem, lu_size size, const char* file, int line);
		lu_p_byte 	(*realloc)(Mem, lu_p_byte, lu_size, const char* file, int line);
		void 		(*free)(Mem, lu_p_byte, const char* file, int line);
		void 		(*destroy)(Mem, Mem, const char* file, int line);
	};

	//
	// mem_init() useful when we dont want to allocate memory for mem instance from heap.
	// For example:
	// 		struct mem mem;
	//		mem_init(&mem);
	//		My_Struct ms = mem_alloc(&mem, sizeof(struct mystruct));
	//
	void mem_init(Mem self);
	Mem mem_create();

	lu_p_byte mem_alloc_internal(Mem self, lu_size size_in_bytes, const char* file, int line);
	lu_p_byte mem_realloc_internal(Mem self, lu_p_byte p, lu_size size_in_bytes, const char* file, int line);
	lu_p_byte mem_free_internal(Mem self, lu_p_byte p, const char* file, int line);
	void mem_destroy_internal(Mem self, Mem parent_mem, const char* file, int line);

	#define mem_type(mem) mem_type_internal(mem)
	#define mem_alloc(mem, size) mem_alloc_internal(mem, size, __FILE__, __LINE__)
	#define mem_realloc(mem, p, size) mem_realloc_internal(mem, p, size, __FILE__, __LINE__)
	#define mem_free(mem, p) mem_free_internal(mem, p, __FILE__, __LINE__)
	#define mem_destroy(mem, parent_mem) mem_destroy_internal(mem, parent_mem, __FILE__, __LINE__)

///////////////////////////////////////////////////////////////////////////////
// Mem_Preallocated

	struct mem_preallocated {

		struct mem 		super;

		Mem 			parent_mem;
		lu_size 		size_in_bytes;
		lu_p_byte 		buff_start;
		lu_p_byte 		buff_end;
		lu_p_byte 		buff_pos;
	};

	void mem_preallocated_init(
		Mem_Preallocated 	self, 
		Mem 				parent_mem, 
		lu_p_byte 			buff_start, 
		lu_size 			size_in_bytes, 
		lu_size 			self_struct_size
	);

	Mem_Preallocated mem_preallocated_create(Mem parent_mem, lu_size size_in_bytes);

	lu_bool mem_preallocated_is_out_of_mem(Mem_Preallocated self);

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

		struct mem 		super;

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

#endif // _LU_MEM_ABSTRACTORS_H
