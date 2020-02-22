/**
	Copyright © 2020 Oleh Ihorovych Novosad 

	Mem_Db: manages memory allocations, reallocations, resizes. Also helps with
	memory debugging. More complicated than memory abstractors. 
*/
#ifndef _LU_MEM_DB_H
#define _LU_MEM_DB_H

///////////////////////////////////////////////////////////////////////////////
// Nouns

	typedef struct mem_db* 			Mem_Db;
	typedef struct mem_instance* 	Mem_Instance;
	typedef struct mem_table* 		Mem_Table;
	typedef struct mem_record* 		Mem_Record;

///////////////////////////////////////////////////////////////////////////////
// Mem_Db

	struct mem_db {
		struct mem_preallocated super;
	};

	Mem_Db mem_db_create(Mem mem, lu_size);
	void mem_db_destroy(Mem_Db, Mem);

///////////////////////////////////////////////////////////////////////////////
// Mem_Instance

	struct mem_instance {
		// reserved for later for debug mode
	};

	lu_p_byte mem_instance_alloc_internal(Mem_Db self, lu_size, const char* file, int line);
	#define mem_instance_alloc(mem_db, size) mem_instance_alloc_internal(mem_db, size, __FILE__, __LINE__)

///////////////////////////////////////////////////////////////////////////////
// Mem_Table

	struct mem_table {
		Mem_Db 			mem_db; // this might be NULL

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


	Mem_Table mem_table_create_from_mem_internal(
 		Mem 		mem, 
 		lu_size 	record_size_in_bytes, 
 		lu_size 	table_size_in_records, 
 		lu_flags 	flags,
 		const char* file,
 		int line
 	);
	#define mem_table_create_from_mem(mem, r_size, t_size, f) mem_table_create_from_mem_internal(mem, r_size, t_size, f, __FILE__, __LINE__)

	Mem_Table mem_table_create_internal(
 		Mem_Db 		mem_table, 
 		lu_size 	record_size_in_bytes, 
 		lu_size 	table_size_in_records, 
 		lu_value 	percent,
 		lu_flags 	flags,
 		const char* file,
 		int line
 	);
	#define mem_table_create(mem_db, r_size, t_size, p, f) mem_table_create_internal(mem_db, r_size, t_size, p, f, __FILE__, __LINE__)


	void mem_table_resize_internal(Mem_Table, lu_size new_size_in_bytes, lu_flags flags, const char* file, int line);
	#define mem_table_resize(mem_table, new_size, f) mem_table_resize_internal(mem_table, new_size, f, __FILE__, __LINE__)

///////////////////////////////////////////////////////////////////////////////
// Mem_Record

	struct mem_record {
		// reserved for later for debug mode
	};

 	lu_p_byte mem_record_alloc_internal(Mem_Table, const char* file, int line);
 	#define mem_record_alloc(mem_table) mem_record_alloc_internal(mem_table, __FILE__, __LINE__)
 
 	void mem_record_free_internal(Mem_Table, lu_p_byte record, const char* file, int line);
	#define mem_record_free(mem_table, rec) mem_record_free_internal(mem_table, rec, __FILE__, __LINE__)

#endif // _LU_ECS_H