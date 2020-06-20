/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

#ifndef _LU_N_H
#define _LU_N_H


///////////////////////////////////////////////////////////////////////////////
// N Net

// serializaciya bude duzhe prostoyu, 
// treba prosto zberehty N Net ta parametry za yakymy buv stvorenyy brain
// vse reshtu perestvoruyetsia. Tak samo perevydilenia pamiati (z mozhlyvym peremishcheniam v inshe misce).

	struct n_name {
		n_neu_ix 				neu;
		lu_char 				name[255];
	};	

	struct n_val {
		n_neu_ix 				neu;
		lu_value 				val;
	};

	struct n_time {
		n_neu_ix				neu;
		lu_size 				val;
	};

	struct n_neu {
		lu_size 				sid;

		n_v_lin_ix 				p_l; 		
		lu_value 				p_count;

		n_v_lin_ix 				c_l;

		n_h_lin_ix 				tp;
		n_h_lin_ix 				tc;

		enum n_com_type			com_type;
		n_com_ix 				com;		
	};

	struct n_h_lin {
		n_neu_ix	 			p;			
		n_neu_ix				c;
	};

	struct n_v_lin {
		n_neu_ix	 			p;			// p i c potribni bo po tomu samomu zviazku my mozhemo jty vverh abo vnyz
		n_neu_ix				c;

		// ce dva spysky
		// odyn z storony p, inshyy z storony c
		n_v_lin_ix	 			p_p;
		n_v_lin_ix	 			p_n;

		n_v_lin_ix	 			c_p; 		// p i n potribni u vypadku yakshou my vydaliayemo zviazok?
		n_v_lin_ix				c_n; 		// yaksho my vydaliayemo zviazok, to my mozhemo podyvytys p ale my neznayemo n
		 		   							// tomu naspravdi i p i n potribni
	};

///////////////////////////////////////////////////////////////////////////////
// N Dopomizhni
	
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