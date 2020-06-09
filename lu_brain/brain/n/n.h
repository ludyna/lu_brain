/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

#ifndef _LU_N_H
#define _LU_N_H


///////////////////////////////////////////////////////////////////////////////
// Neu

	struct n_v {
		lin_ix 					c_last;
		lu_value 				val;
	};

	struct n_p {
		lin_ix 					p_last; 		
		lu_value 				p_l_count; 	// linky do componentiv + t_1 componentiv, 
											// my ne znayemo tochne chyslo bo ne znayemo kilkist component

		lin_ix					c_last;
	}

	struct n_cb {
		neu_ix 					tlp1;		// zavzhdy tilky 8 batkiv
		neu_ix					trp1;
		neu_ix 					blp1;
		neu_ix 					brp1;

		neu_ix 					tlp0;		
		neu_ix					trp0;
		neu_ix 					blp0;
		neu_ix 					brp0;1

		// ale
		lin_ix 					c_last; 
	};

	struct n_lin_1 {
		enum n_lin_type 		lin_type;

	};

	struct n_neu2 {
		lu_size 				p_l; 		
		lu_value 				p_l_count;

		lu_size 				c_l;

		enum n_comp_type		comp_type;
		lu_size 				comp;		// cia componenta vkluchaye name abo value abo shos inshe
	};

	struct n_lin2 {
		enum n_lin_type 		lin_type;
		lu_size 				p;			// p i c potribni bo po tomu samomu zviazku my mozhemo jty vverh abo vnyz
		lu_size 				c;

		// ce dva spysky
		// odyn z storony p, inshyy z storony c
		lu_size 				p_p;
		lu_size 				p_n;

		lu_size 				c_p; 		// prev i next potribni u vypadku yakshou my vydaliayemo zviazok?
		lu_size 				c_n; 		// yaksho my vydaliayemo zviazok, to my mozhemo podyvytys prev ale my neznayemo next
		 		   							// tomu naspravdi i prev i next potribni
	};

	struct n_mem {

		// vlasnyk
		S_Mem s_mem; 

	};

	static N_Mem n_mem_create(S_Mem s_mem);
	

#endif // _LU_N_H