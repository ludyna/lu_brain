/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Nouns


///////////////////////////////////////////////////////////////////////////////
// Story 
	
	#define STORY_INITIAL_BLOCKS_SIZE 256

	struct story {
		Brain 				brain;
		Arr2 				data;
		lu_size				data_y;
	};

	static inline lu_p_value story_data_get(Story self, lu_size rec_index, lu_size block_index, lu_size channel_index)
	{
		return (lu_p_value) arr_get((Arr)arr2_get(self->data, rec_index, block_index), channel_index);
	}
