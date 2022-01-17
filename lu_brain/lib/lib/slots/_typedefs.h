/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Slots
//

	enum lu_slot_type {
		LU_ST__ONE,
		LU_ST__ARR,
		LU_ST__END
	};

	typedef struct lu_slot_base* Lu_Slot_Base;
	typedef struct lu_slot_one* Lu_Slot_One;
	typedef struct lu_slot_arr* Lu_Slot_Arr;