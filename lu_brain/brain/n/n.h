/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

#ifndef _LU_N_H
#define _LU_N_H

///////////////////////////////////////////////////////////////////////////////
// Neu

	enum n_comp_type {
		NCI_VALUE = 0,
		NCI_NAME = 1,

		NCI_SIZE
	};

	struct n_neu {

		lu_size 				p_l; 		
		lu_value 				p_l_count;

		lu_size 				c_l;

		enum n_comp_type		comp_type;
		lu_size 				comp;		// cia componenta vkluchaye name abo value abo shos inshe
	};


	struct n_lin {
		lu_size 		p;			// p i c potribni bo po tomu samomu zviazku my mozhemo jty vverh abo vnyz
		lu_size 		c;

		// ce dva spysky
		// odyn z storony p, inshyy z storony c
		lu_size 		p_p;
		lu_size 		p_n;

		lu_size 		c_p; 	// prev i next potribni u vypadku yakshou my vydaliayemo zviazok?
		lu_size 		c_n; 	// yaksho my vydaliayemo zviazok, to my mozhemo podyvytys prev ale my neznayemo next
		 		   				// tomu naspravdi i prev i next potribni
	};

	struct n_mem {

		// vlasnyk
		S_Mem s_mem; 

	};

	static N_Mem n_mem_create(S_Mem s_mem);
	

#endif // _LU_N_H