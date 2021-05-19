/**
	Copyright © 2021 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Globals

	extern Lu_Mem lu_g_mem;

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

	#define lu_mem_alloc(mem, size) mem->alloc(mem, size, __func__, __FILE__, __LINE__)
	#define lu_mem_realloc(mem, p, size) mem->realloc(mem, p, size, __func__, __FILE__, __LINE__)
	#define lu_mem_free(mem, p) mem->free(mem, p, __func__, __FILE__, __LINE__)
	#define lu_mem_destroy(mem, parent_mem) mem->destroy(mem, parent_mem, __func__, __FILE__, __LINE__)
	#define lu_mem_table_create(mem, r_size, t_size, p, f) mem->table_create(mem, r_size, t_size, p, f, __func__, __FILE__, __LINE__)

	#define lu_g_mem_alloc(size) lu_g_mem->alloc(lu_g_mem, size, __func__, __FILE__, __LINE__)
	#define lu_g_mem_realloc(p, size) lu_g_mem->realloc(lu_g_mem, p, size, __func__, __FILE__, __LINE__)
	#define lu_g_mem_free(p) lu_g_mem->free(lu_g_mem, p, __func__, __FILE__, __LINE__)
	#define lu_g_mem_table_create(r_size, t_size, p, f) lu_g_mem->table_create(lu_g_mem, r_size, t_size, p, f, __func__, __FILE__, __LINE__)

	Lu_Mem mem_create();

///////////////////////////////////////////////////////////////////////////////
// Lu_Mem_Table

	enum lu_mem_table_flags {
		MTF_FREEABLE = 1
	};

	struct lu_mem_table {
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

	#define mem_table_realloc(mt, n_size, f) mt->realloc(mem, n_size, f, __func__, __FILE__, __LINE__)
	#define mem_table_destroy(mt) mt->destroy(mt, __func__, __FILE__, __LINE__)

	#define mem_record_alloc(mt) mt->record_alloc(mt, __func__, __FILE__, __LINE__)
	#define mem_record_free(mt, p) mt->record_free(mt, p, __func__, __FILE__, __LINE__) 

	#define mem_table_size_in_bytes(mt) mt->size_in_bytes(mt)
	#define mem_table_mem_get(mt) mt->mem_get(mt)

	static inline lu_p_byte mem_table_get(Lu_Mem_Table self, lu_size index)
	{
		return (self->records_start + index * self->record_size_in_bytes); 
	} 

	static inline lu_size mem_table_record_shift(Lu_Mem_Table self, lu_p_byte record_addr)
	{
		lu_assert(self);
		lu_assert(record_addr);

		return (lu_size) (record_addr - self->records_start);
	}