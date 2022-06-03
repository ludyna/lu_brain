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

///////////////////////////////////////////////////////////////////////////////
// Lu_La_Link_Addr

	union lu_la_link_addr {
		struct {
			lu_size link_ix;
		};

		lu_size value;
	};

	extern union lu_la_link_addr LU_LA_LINK_ADDR__NULL; 