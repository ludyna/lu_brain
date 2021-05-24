/**
	Copyright © 2021 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Lu_Mem_With_Stats
// The same as parent mem, but adds track of stats.
//

	struct lu_mem_with_stats {
		struct lu_mem super;

		Lu_Mem parent_mem;

		lu_size alloc_count;
		lu_size free_count;
		lu_size realloc_count;
		lu_size allocated_size;
		lu_size freed_size;
	};

	static inline size_t lu_mem_with_stats_allocated_size(void * ptr) 
	{
		return ((size_t*)ptr)[-1];
	}

	Lu_Mem_With_Stats lu_mem_with_stats_create(Lu_Mem parent_mem);