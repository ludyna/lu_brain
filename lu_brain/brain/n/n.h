/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

#ifndef _LU_N_H
#define _LU_N_H

///////////////////////////////////////////////////////////////////////////////
// Neu

	struct n_v_neu {
		S_Base 			s_base;
		lu_value 		val;

		N_Lin 			c_l;
	};

	struct n_neu {
		S_Base 			s_base;
		lu_size 		lid; 		
		lu_value	 	count;

		// ostanni linky
		N_Lin 			c_l;
		N_Lin 			p_l;
	};

	struct n_lin {
		N_Neu 			p;
		N_Neu 			c;
	
		N_Lin   		p_p;
		N_Lin 			p_n;

		N_Lin 			c_p;
		N_Lin   		c_n;
	};

	struct n_mem {

		// vlasnyk
		S_Mem s_mem; 

	};

	static N_Mem n_mem_create(S_Mem s_mem);
	

#endif // _LU_N_H