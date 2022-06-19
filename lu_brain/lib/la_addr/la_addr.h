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

	static inline lu_size lu_la_addr__get_la_ix(Lu_La_Addr self)
	{
		return self->la_ix;
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