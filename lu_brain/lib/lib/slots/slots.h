/**
	Copyright © 2021 Oleh Ihorovych Novosad 

	Slot is a structure with a pointer to one item or many items.
*/

///////////////////////////////////////////////////////////////////////////////
// Base
//

	struct lu_slot_base {
		enum lu_slot_type type;

		// virtual destructor
		void (*destroy)(Lu_Slot_Base, Lu_Mem);
	};

	static inline Lu_Slot_Base lu_slot_base__init(
		 Lu_Slot_Base self, 
		 enum lu_slot_type type,
		 void (*destroy)(Lu_Slot_Base, Lu_Mem)
	)
	{
		lu__assert(self);
		lu__assert(type < LU_ST_END); 
		lu__assert(destroy);

		self->type = type;
		self->destroy = destroy;

		return self;
	}

///////////////////////////////////////////////////////////////////////////////
// One
//

	struct lu_slot_one {
		struct lu_slot_base super;
		lu_p_void item;
	};

	static Lu_Slot_One lu_slot_one__create(Lu_Mem, lu_p_void item);
	static void lu_slot_one__destroy(Lu_Slot_Base, Lu_Mem);

///////////////////////////////////////////////////////////////////////////////
// Arr
//
	struct lu_slot_arr {
		struct lu_slot_base super;

		Lu_Arr items;
	};

	static Lu_Slot_Arr lu_slot_arr__create(Lu_Mem, lu_size items_count, lu_bool allow_realloc);
	static void lu_slot_arr__destroy(Lu_Slot_Base, Lu_Mem);