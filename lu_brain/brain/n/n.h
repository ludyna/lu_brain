/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

#ifndef _LU_N_H
#define _LU_N_H


///////////////////////////////////////////////////////////////////////////////
// Neu

	struct n_neu {
		lin_ix 					par_last; 		
		lu_value 				par_count;

		lin_ix 					chi_last;

		enum n_com_type			com_type;
		com_ix 					com;		// cia componenta vkluchaye name abo value abo shos inshe
	};

	struct n_lin {
		enum n_lin_type 		lin_type;
		neu_ix	 				par;			// p i c potribni bo po tomu samomu zviazku my mozhemo jty vverh abo vnyz
		neu_ix					chi;

		// ce dva spysky
		// odyn z storony p, inshyy z storony c
		lin_ix	 				par_p;
		lin_ix	 				par_n;

		lin_ix	 				chi_p; 		// prev i next potribni u vypadku yakshou my vydaliayemo zviazok?
		lin_ix					chi_n; 		// yaksho my vydaliayemo zviazok, to my mozhemo podyvytys prev ale my neznayemo next
		 		   							// tomu naspravdi i prev i next potribni
	};

	struct n_mem {

		// vlasnyk
		S_Mem 					s_mem; 

		Mem_Table 				neus;
		Mem_Table				lins;

		// komponenty
		Mem_Table 				names;
	};

	static N_Mem n_mem_create(S_Mem s_mem);
	

#endif // _LU_N_H