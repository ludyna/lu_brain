/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Globals

	extern Mem g_mem_temp;

///////////////////////////////////////////////////////////////////////////////
// Mem

	// Debugger interface
	struct i_mem_debugger
	{
		void (*register_alloc)(	I_Mem_Debugger self, lu_p_byte address, lu_size size,  
								const char* func, const char* file, int line);
		void (*register_free)(	I_Mem_Debugger self, lu_p_byte address, 
								const char* func, const char* file, int line);
	};

	struct mem {
		I_Mem_Debugger 			debugger;
		lu_p_byte 				(*alloc)(Mem, lu_size size, const char* func, const char* file, int line);
		lu_p_byte 				(*realloc)(Mem, lu_p_byte, lu_size, const char* func, const char* file, int line);
		void 					(*free)(Mem, lu_p_byte, const char* func, const char* file, int line);
		void 					(*destroy)(Mem, Mem, const char* func, const char* file, int line);

		Mem_Table 				(*table_create)(
			Mem 				mem, 
	 		lu_size 			record_size_in_bytes, 
	 		lu_size 			table_size_in_records, 
	 		lu_value 			percent,
	 		lu_flags 			flags,
	 		const char* 		func, 
	 		const char* 		file,
	 		int 				line
	 	);

		
	};

	#define mem_alloc(mem, size) mem->alloc(mem, size, __func__, __FILE__, __LINE__)
	#define mem_realloc(mem, p, size) mem->realloc(mem, p, size, __func__, __FILE__, __LINE__)
	#define mem_free(mem, p) mem->free(mem, p, __func__, __FILE__, __LINE__)
	#define mem_destroy(mem, parent_mem) mem->destroy(mem, parent_mem, __func__, __FILE__, __LINE__)
	#define mem_table_create(mem, r_size, t_size, p, f) mem->table_create(mem, r_size, t_size, p, f, __func__, __FILE__, __LINE__)

	#define mem_temp_alloc(size) g_mem_temp->alloc(g_mem_temp, size, __func__, __FILE__, __LINE__)
	#define mem_temp_realloc(p, size) g_mem_temp->realloc(g_mem_temp, p, size, __func__, __FILE__, __LINE__)
	#define mem_temp_free(p) g_mem_temp->free(g_mem_temp, p, __func__, __FILE__, __LINE__)
	#define mem_temp_table_create(r_size, t_size, p, f) g_mem_temp->table_create(g_mem_temp, r_size, t_size, p, f, __func__, __FILE__, __LINE__)

	Mem mem_create();

///////////////////////////////////////////////////////////////////////////////
// Mem_Table

	enum mem_table_flags {
		MTF_FREEABLE = 1
	};

	struct mem_table {
		void 		(*realloc)(Mem_Table, lu_size new_size_in_bytes, lu_flags flags, const char* func, const char* file, int line);
	 	void 		(*destroy)(Mem_Table, const char* func, const char* file, int line);

		lu_p_byte 	(*record_alloc)(Mem_Table, const char* func, const char* file, int line);
		void 		(*record_free)(Mem_Table, lu_p_byte record, const char* func, const char* file, int line);

		lu_size 	(*size_in_bytes)(Mem_Table);
		Mem 		(*mem_get)(Mem_Table);			// return Mem associated with the Mem_Table

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

	static inline lu_p_byte mem_table_get(Mem_Table self, lu_size index)
	{
		return (self->records_start + index * self->record_size_in_bytes); 
	} 