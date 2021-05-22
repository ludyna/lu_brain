/**
	Copyright © 2021 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Lu_Mem_Perm
// Permanent memory means that allocations should stay until the end of life of 
// brain.

	struct lu_mem_stack {
		struct lu_mem 		super;

		lu_size 			size_in_bytes;
		lu_p_byte 			buff_start;
		lu_p_byte 			buff_end;
		lu_p_byte 			buff_pos;
	};


	Lu_Mem_Perm lu_mem_stack_create(Lu_Mem parent_mem, lu_size size_in_bytes);

	static inline lu_bool lu_mem_stack_is_out_of_mem(Lu_Mem_Perm self)
	{
		if (self->buff_pos >= self->buff_end)
			return true;

		return false;
	}

	static inline lu_size lu_mem_stack_avail(Lu_Mem_Perm self)
	{
		return self->buff_end - self->buff_pos;
	}

	static inline lu_size lu_mem_stack_preallocated(Lu_Mem_Perm self) { return self->size_in_bytes; }
	static inline lu_size lu_mem_stack_used(Lu_Mem_Perm self) { return self->buff_pos - self->buff_start; }

///////////////////////////////////////////////////////////////////////////////
// Mem_Perm_Table

	struct lu_mem_stack_table {
		struct lu_mem_table 	super;
		Lu_Mem_Perm 			mem_stack;
	};

	Lu_Mem_Stack_Table lu_mem_stack_table_create(
		Lu_Mem_Perm 			mem, 
		lu_size 			record_size_in_bytes, 
		lu_size 			table_size_in_records, 
		lu_value 			percent,
		lu_flags 			flags,
		const char* 		func, 
		const char* 		file,
		int 				line
	);