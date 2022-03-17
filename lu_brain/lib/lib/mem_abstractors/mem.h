/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Globals

	extern Lu_Mem lu_g_mem;

	// Alloc, realloc and free
	#define lu_g_mem__alloc(size) lu_g_mem->alloc(lu_g_mem, size, __func__, __FILE__, __LINE__)
	#define lu_g_mem__realloc(p, size) lu_g_mem->realloc(lu_g_mem, p, size, __func__, __FILE__, __LINE__)
	#define lu_g_mem__free(p) lu_g_mem->free(lu_g_mem, p, __func__, __FILE__, __LINE__)

	// Memory stats
	#define lu_g_mem__preallocated(mem) 0
	#define lu_g_mem__used(mem) 0

	// Memory tables
	#define lu_g_mem_table__create(r_size, t_size, p, f) lu_g_mem->table_create(lu_g_mem, r_size, t_size, p, f, __func__, __FILE__, __LINE__)


///////////////////////////////////////////////////////////////////////////////
// Lu_Mem

	// Debugger interface
	struct lu_i_mem_debugger
	{
		void (*register_alloc)(		Lu_I_Mem_Debugger self, lu_p_byte address, lu_size size,  
									const char* func, const char* file, int line);
		
		void (*register_realloc)(	Lu_I_Mem_Debugger self, lu_p_byte address, lu_size size,  
									const char* func, const char* file, int line);

		void (*register_free)(		Lu_I_Mem_Debugger self, lu_p_byte address, 
									const char* func, const char* file, int line);
	};

	// Memory
	struct lu_mem {

		// Memory debugger
		Lu_I_Mem_Debugger 		debugger;

		// Alloc, realloc and free
		lu_p_byte 				(*alloc)(Lu_Mem, lu_size size, const char* func, const char* file, int line);
		lu_p_byte 				(*realloc)(Lu_Mem, lu_p_byte, lu_size, const char* func, const char* file, int line);
		void 					(*free)(Lu_Mem, lu_p_byte, const char* func, const char* file, int line); 

		// Destroy memory
		void 					(*destroy)(Lu_Mem, Lu_Mem, const char* func, const char* file, int line);

		// Memory stats
		lu_size 				(*preallocated)(Lu_Mem self); 
		lu_size 				(*used)(Lu_Mem self);

		// Memory tables
		Lu_Mem_Table 			(*table_create)(
			Lu_Mem 				mem, 
	 		lu_size 			record_size_in_bytes, 
	 		lu_size 			table_size_in_records, 
	 		lu_value 			percent,
	 		lu_flags 			flags,
	 		const char* 		func, 
	 		const char* 		file,
	 		int 				line
	 	);
	};

	Lu_Mem lu_mem_create();

	// Alloc, realloc and free
	#define lu_mem__alloc(mem, size) mem->alloc(mem, size, __func__, __FILE__, __LINE__)
	#define lu_mem__realloc(mem, p, size) mem->realloc(mem, p, size, __func__, __FILE__, __LINE__)
	#define lu_mem__free(mem, p) mem->free(mem, p, __func__, __FILE__, __LINE__)

	// Destroy memory
	#define lu_mem__destroy(mem, parent_mem) mem->destroy(mem, parent_mem, __func__, __FILE__, __LINE__)

	// Memory stats
	#define lu_mem__preallocated(mem) mem->preallocated(mem)
	#define lu_mem__used(mem) mem->used(mem)

	// Memory tables
	#define lu_mem_table__create(mem, r_size, t_size, p, f) mem->table_create(mem, r_size, t_size, p, f, __func__, __FILE__, __LINE__)

///////////////////////////////////////////////////////////////////////////////
// Lu_Mem_Table

	enum lu_mem_table_flags {
		LU_MEM_TABLE__DEFAULT = 0,
		LU_MEM_TABLE__FREEABLE = 1
	};

	struct lu_mem_table {
		void 		(*reset)(Lu_Mem_Table, const char* func, const char* file, int line);
		void 		(*realloc)(Lu_Mem_Table, lu_size new_size_in_bytes, lu_flags flags, const char* func, const char* file, int line);
	 	void 		(*destroy)(Lu_Mem_Table, const char* func, const char* file, int line);

		lu_p_byte 	(*record_alloc)(Lu_Mem_Table, const char* func, const char* file, int line);
		void 		(*record_free)(Lu_Mem_Table, lu_p_byte record, const char* func, const char* file, int line);

		lu_size 	(*size_in_bytes)(Lu_Mem_Table);
		Lu_Mem 		(*mem_get)(Lu_Mem_Table);			// return Lu_Mem associated with the Lu_Mem_Table

		lu_size 		record_size_in_bytes;
		lu_size			table_size_in_records;
		lu_flags		flags;

		lu_p_byte		records_start;
		lu_p_byte		records_end;
		lu_p_byte		records_pos;
		lu_size 		records_count;

		lu_p_byte* 		free_start;
		lu_size 		free_count;

		lu_size 		full_size_in_bytes;
	};

	// Careful: reset "invalidates" record pointers. Make sure you are not using any.
	#define lu_mem_table__reset(mt) mt->reset(mt, __func__, __FILE__, __LINE__)
	#define lu_mem_table__realloc(mt, n_size, f) mt->realloc(mem, n_size, f, __func__, __FILE__, __LINE__)
	#define lu_mem_table__destroy(mt) mt->destroy(mt, __func__, __FILE__, __LINE__)

	#define lu_mem_record__alloc(mt) mt->record_alloc(mt, __func__, __FILE__, __LINE__)
	#define lu_mem_record__free(mt, p) mt->record_free(mt, p, __func__, __FILE__, __LINE__) 

	#define lu_mem_table__size_in_bytes(mt) mt->size_in_bytes(mt)
	#define lu_mem_table__mem_get(mt) mt->mem_get(mt)

	#define lu_mem_table__records_count(mt) mt->records_count

	static inline lu_p_byte lu_mem_table__get(Lu_Mem_Table self, lu_size index)
	{
		return (self->records_start + index * self->record_size_in_bytes); 
	} 

	static inline lu_size lu_mem_table__record_shift(Lu_Mem_Table self, lu_p_byte record_addr)
	{
		lu__assert(self);
		lu__assert(record_addr);

		return (lu_size) (record_addr - self->records_start);
	}

	static inline lu_size lu_mem_table__record_ix(Lu_Mem_Table self, lu_p_byte record_addr)
	{
		return lu_mem_table__record_shift(self, record_addr) / self->record_size_in_bytes;
	}