/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Lu_La_Addr

	union lu_la_addr {
		struct {
			lu_size la_ix;
		};

		lu_size value;
	};

	extern union lu_la_addr LU_LA_ADDR__NULL; 

	//
	// Get
	//

	static inline lu_size lu_la_addr__get_la_ix(Lu_La_Addr self)
	{
		return self->la_ix;
	}

	//
	// Is
	//

	static inline lu_bool lu_la_addr__is_present(Lu_La_Addr self)
	{
		return self->value != LU_LA_ADDR__NULL.value;
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_La_Link_Addr

	union lu_la_link_addr {
		struct {
			lu_size link_ix;
		};

		lu_size value;
	};

	extern union lu_la_link_addr LU_LA_LINK_ADDR__NULL; 

	//
	// Is 
	//

	static inline lu_bool lu_la_link_addr__is_present(Lu_La_Link_Addr self)
	{
		return self->value != LU_LA_LINK_ADDR__NULL.value;
	}
