/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/
#ifndef _LU_PH_MEM_H
#define _LU_PH_MEM_H

///////////////////////////////////////////////////////////////////////////////
// Nouns
	
	typedef struct ph_mem* 		Ph_Mem;
	typedef struct ph_sisa* 	Ph_Sisa;


///////////////////////////////////////////////////////////////////////////////
// Ph_Mem

	struct ph_mem {
		lu_size 		size_in_bytes;
		lu_p_byte 		buff_start;
		lu_p_byte 		buff_end;
		lu_p_byte 		buff_pos;


	};

	Ph_Mem ph_mem_create(lu_size size_in_bytes);
	void ph_mem_destroy(Ph_Mem self);

	lu_p_byte ph_mem_alloc(Ph_Mem self, lu_size size_in_bytes); 

	static inline lu_size ph_mem_avail(Ph_Mem self)
	{
		return self->buff_end - self->buff_pos;
	}

///////////////////////////////////////////////////////////////////////////////
// Ph_Sisa

	struct ph_sisa {
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

	enum ph_sisa_flags {
		PH_S_ITEM_FREEABLE = 1
	};

	// 
	//	If percent is provided (>0 && <= 100), sisa size is calculated from currently
	//  available space with minimum one item_size.
	//
	Ph_Sisa ph_sisa_create (
		Ph_Mem 			ph_mem, 
		lu_size 		item_size, 
		lu_size 		size, 
		lu_value 		percent,
		lu_flags 		flags
	);

	lu_p_byte ph_sisa_item_alloc(Ph_Sisa self);
	void ph_sisa_item_free(Ph_Sisa, lu_p_byte item);

#endif // _LU_PH_MEM_H
