/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Lu_Md_Item 

	#define LU_MD_ITEM_FILE_SIZE 40

	struct lu_md_item {
		lu_p_byte 				address;
		lu_size 				size;
		char 					alloc_path[LU_MD_ITEM_FILE_SIZE];
		char 					freed_path[LU_MD_ITEM_FILE_SIZE];
		int 					line;

		Lu_Md_Item 				prev;
		Lu_Md_Item 				next;
	};

	Lu_Md_Item lu_md_item_create();
	void lu_md_item_destroy(Lu_Md_Item, lu_bool deallocate_address);

///////////////////////////////////////////////////////////////////////////////
// Mem_Debugger 

	#define LU_MD_INDEX_MASK 	0xFFFF
	#define LU_MD_HASH_SIZE 	LU_MD_INDEX_MASK + 1

	struct mem_debugger {
		struct i_mem_debugger 	super;

		Mem 					mem;
		Lu_Md_Item* 	 		items;
		lu_size 				items_size;

		lu_size 				alloc_size;
		lu_size 				alloc_count;
		lu_size 				freed_size;
		lu_size 				freed_count;
		lu_size 				realloc_count;
	};

	static inline lu_size mem_debugger_index(lu_p_byte address)
	{
		lu_size addr = (lu_size) address;
		return addr & LU_MD_INDEX_MASK;
	}

	static inline lu_bool mem_debugger_is_all_clear(Mem_Debugger self)
	{
		return self->alloc_size == self->freed_size;
	}

	Mem_Debugger mem_debugger_create(Mem mem);
	void mem_debugger_destroy(Mem_Debugger self, lu_bool deallocate_leaks);


	void mem_debugger_print(Mem_Debugger self);


	void mem_debugger_register_alloc(	I_Mem_Debugger self, lu_p_byte address, lu_size size,  
										const char* func, const char* file, int line);

	void mem_debugger_register_realloc(	I_Mem_Debugger self, lu_p_byte address, lu_size size,  
										const char* func, const char* file, int line);

	void mem_debugger_register_free(	I_Mem_Debugger self, lu_p_byte address, 
										const char* func, const char* file, int line);

