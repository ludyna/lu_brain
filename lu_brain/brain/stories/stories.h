/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Nouns


///////////////////////////////////////////////////////////////////////////////
// Story 
	
	#define STORY_INITIAL_BLOCKS_SIZE 8

	struct story {
		Brain 				brain;
		Arr2 				data;
		lu_size				data_y;
	};

	static inline lu_p_value story_data_get(Story self, lu_size rec_index, lu_size block_index, lu_size channel_index)
	{
		Arr channels = (Arr)arr2_get(self->data, rec_index, block_index);

		lu_user_assert(channels, "Channels should be present");

		//lu_user_debug_args("ch_count=%ld, ch_size=%ld, ch_index=%ld", channels->count, channels->size, channel_index);

		return (lu_p_value) arr_get(channels, channel_index);
	}
