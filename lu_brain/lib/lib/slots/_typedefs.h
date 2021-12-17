/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Slots
//

	enum lu_slot_type {
		LU_ST_ONE,
		LU_ST_ARR,
		LU_ST_END
	};

	typedef struct lu_slot_base* Lu_Slot_Base;
	typedef struct lu_slot_one* Lu_Slot_One;
	typedef struct lu_slot_arr* Lu_Slot_Arr;