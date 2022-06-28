/**
	Copyright © 2022 Oleh Ihorovych Novosad 
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
// Lu_Mem_Debugger 

	#define LU_MD_INDEX_MASK 	0xFFFF
	#define LU_MD_HASH_SIZE 	LU_MD_INDEX_MASK + 1

	struct lu_mem_debugger {
		struct lu_i_mem_debugger 	super;

		Lu_Mem 					mem;
		Lu_Md_Item* 	 		items;
		lu_size 				items_size;

		lu_size 				alloc_size;
		lu_size 				alloc_count;
		lu_size 				freed_size;
		lu_size 				freed_count;
		lu_size 				realloc_count;
	};

	static inline lu_size lu_mem_debugger__get_ix(lu_p_byte address)
	{
		lu_size addr = (lu_size) address;
		return addr & LU_MD_INDEX_MASK;
	}

	static inline lu_bool lu_mem_debugger__is_all_freed(Lu_Mem_Debugger self)
	{
		return self->alloc_size == self->freed_size;
	}

	Lu_Mem_Debugger lu_mem_debugger__create(Lu_Mem mem);
	void lu_mem_debugger__destroy(Lu_Mem_Debugger self, lu_bool deallocate_leaks);


	void lu_mem_debugger__print(Lu_Mem_Debugger self);


	void mem_debugger_register_alloc(	Lu_I_Mem_Debugger self, lu_p_byte address, lu_size size,  
										const char* func, const char* file, int line);

	void mem_debugger_register_realloc(	Lu_I_Mem_Debugger self, lu_p_byte old_address, lu_p_byte new_address, lu_size size,  
										const char* func, const char* file, int line);

	void mem_debugger_register_free(	Lu_I_Mem_Debugger self, lu_p_byte address, 
										const char* func, const char* file, int line);

