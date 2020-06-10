/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

#ifndef _LU_N_H
#define _LU_N_H


///////////////////////////////////////////////////////////////////////////////
// Neu

	struct n_neu {
		v_lin_ix 				p_l; 		
		lu_value 				p_count;

		v_lin_ix 				c_l;

		h_lin_ix 				p;
		h_lin_ix 				c;

		enum n_com_type			com_type;
		com_ix 					com;		
	};

	struct n_h_lin {
		neu_ix	 				p;			
		neu_ix					c;
	};

	struct n_v_lin {
		neu_ix	 				p;			// p i c potribni bo po tomu samomu zviazku my mozhemo jty vverh abo vnyz
		neu_ix					c;

		// ce dva spysky
		// odyn z storony p, inshyy z storony c
		v_lin_ix	 			p_p;
		v_lin_ix	 			p_n;

		v_lin_ix	 			c_p; 		// p i n potribni u vypadku yakshou my vydaliayemo zviazok?
		v_lin_ix				c_n; 		// yaksho my vydaliayemo zviazok, to my mozhemo podyvytys p ale my neznayemo n
		 		   							// tomu naspravdi i p i n potribni
	};

	struct n_mem {

		// vlasnyk
		S_Mem 					s_mem; 

		// n 
		Mem_Table 				neus; 
		Mem_Table 				h_lins;
		Mem_Table				v_lins;

		// komponenty
		Mem_Table 				names;
		Mem_Table 				values;
	};

	static N_Mem n_mem_create(S_Mem s_mem);
	

#endif // _LU_N_H