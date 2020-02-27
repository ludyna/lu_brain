/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Nouns

	typedef struct mem* 						Mem;
	typedef struct mem_table* 					Mem_Table;
	typedef struct mem_perm* 			Mem_Perm;
	typedef struct mem_table_perm* 		Mem_Table_Perm;

///////////////////////////////////////////////////////////////////////////////
// Globals
	extern Mem g_mem_temp;

///////////////////////////////////////////////////////////////////////////////
// Mem

	struct mem {

		lu_p_byte 	(*alloc)(Mem, lu_size size, const char* file, int line);
		lu_p_byte 	(*realloc)(Mem, lu_p_byte, lu_size, const char* file, int line);
		void 		(*free)(Mem, lu_p_byte, const char* file, int line);
		void 		(*destroy)(Mem, Mem, const char* file, int line);

		Mem_Table 	(*table_create)(
			Mem 		mem, 
	 		lu_size 	record_size_in_bytes, 
	 		lu_size 	table_size_in_records, 
	 		lu_value 	percent,
	 		lu_flags 	flags,
	 		const char* file,
	 		int line
	 	);
	};

	#define mem_alloc(mem, size) mem->alloc(mem, size, __FILE__, __LINE__)
	#define mem_realloc(mem, p, size) mem->realloc(mem, p, size, __FILE__, __LINE__)
	#define mem_free(mem, p) mem->free(mem, p, __FILE__, __LINE__)
	#define mem_destroy(mem, parent_mem) mem->destroy(mem, parent_mem, __FILE__, __LINE__)
	#define mem_table_create(mem, r_size, t_size, p, f) mem->table_create(mem, r_size, t_size, p, f, __FILE__, __LINE__)

	#define mem_temp_alloc(size) g_mem_temp->alloc(g_mem_temp, size, __FILE__, __LINE__)
	#define mem_temp_realloc(p, size) g_mem_temp->realloc(g_mem_temp, p, size, __FILE__, __LINE__)
	#define mem_temp_free(p) g_mem_temp->free(g_mem_temp, p, __FILE__, __LINE__)
	#define mem_temp_table_create(r_size, t_size, p, f) g_mem_temp->table_create(g_mem_temp, r_size, t_size, p, f, __FILE__, __LINE__)

	Mem mem_create();

///////////////////////////////////////////////////////////////////////////////
// Mem_Table

	enum mem_table_flags {
		MEM_TABLE_CAN_FREE_ITEMS = 1
	};

	struct mem_table {
		void 		(*realloc)(Mem_Table, lu_size new_size_in_bytes, lu_flags flags, const char* file, int line);
	 	void 		(*destroy)(Mem_Table, Mem, const char* file, int line);

		lu_p_byte 	(*record_alloc)(Mem_Table, const char* file, int line);
		void 		(*record_free)(Mem_Table, lu_p_byte record, const char* file, int line);

		lu_size 		record_size_in_bytes;
		lu_size			table_size_in_records;
		lu_flags		flags;

		lu_p_byte		records_start;
		lu_p_byte		records_end;
		lu_p_byte		records_pos;
		lu_size 		records_count;

		lu_p_byte* 		free_start;
		lu_size 		free_count;
	};

	#define mem_table_realloc(mt, n_size, f) mt->realloc(mem, n_size, f, __FILE__, __LINE__)
	#define mem_table_destroy(mt, parent_mem) mt->destroy(mt, parent_mem, __FILE__, __LINE__)

	#define mem_record_alloc(mt) mt->record_alloc(mt, __FILE__, __LINE__)
	#define mem_record_free(mt, p) mt->record_free(mt, p, __FILE__, __LINE__)

///////////////////////////////////////////////////////////////////////////////
// Mem_Perm
// Permanent memory means that allocations should stay until the end of life of 
// brain.

	struct mem_perm {
		struct mem 			super;

		lu_size 			size_in_bytes;
		lu_p_byte 			buff_start;
		lu_p_byte 			buff_end;
		lu_p_byte 			buff_pos;
	};


	Mem_Perm mem_perm_create(Mem parent_mem, lu_size size_in_bytes);

	static inline lu_bool mem_perm_is_out_of_mem(Mem_Perm self)
	{
		if (self->buff_pos >= self->buff_end)
			return true;

		return false;
	}

	static inline lu_size mem_perm_avail(Mem_Perm self)
	{
		return self->buff_end - self->buff_pos;
	}

///////////////////////////////////////////////////////////////////////////////
// Mem_Perm_Table

	struct mem_table_perm {
		struct mem_table 	super;
		Mem_Perm 	mem_perm;
	};

	Mem_Table_Perm mem_table_perm_create(
		Mem_Perm 	mem, 
		lu_size 			record_size_in_bytes, 
		lu_size 			table_size_in_records, 
		lu_value 			percent,
		lu_flags 			flags,
		const char* 		file,
		int 				line
	);