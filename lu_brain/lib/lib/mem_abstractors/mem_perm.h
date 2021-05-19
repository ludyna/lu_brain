/**
	Copyright © 2021 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Mem_Perm
// Permanent memory means that allocations should stay until the end of life of 
// brain.

	struct lu_mem_perm {
		struct lu_mem 			super;

		lu_size 			size_in_bytes;
		lu_p_byte 			buff_start;
		lu_p_byte 			buff_end;
		lu_p_byte 			buff_pos;
	};


	Mem_Perm mem_perm_create(Lu_Mem parent_mem, lu_size size_in_bytes);

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

	static inline lu_size mem_perm_allocated(Mem_Perm self) { return self->size_in_bytes; }
	static inline lu_size mem_perm_used(Mem_Perm self) { return self->buff_pos - self->buff_start; }

///////////////////////////////////////////////////////////////////////////////
// Mem_Perm_Table

	struct lu_mem_table_perm {
		struct lu_mem_table 	super;
		Mem_Perm 			mem_perm;
	};

	Mem_Table_Perm mem_table_perm_create(
		Mem_Perm 			mem, 
		lu_size 			record_size_in_bytes, 
		lu_size 			table_size_in_records, 
		lu_value 			percent,
		lu_flags 			flags,
		const char* 		func, 
		const char* 		file,
		int 				line
	);