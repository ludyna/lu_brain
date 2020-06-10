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

	struct n_lin {
		enum n_lin_type  c_type;
		n_neu_ix 			 c;




	};

	struct n_pointer {
		lu_size 	ix;
		enum n_type type;
	};

	struct n_cb {
		// zavzhdy tilky 8 batkiv, pry ciomu pidhodi problema z vydaleniam? 
		// my mozhemo pity v parent, v parenti znayty cherez c_last link cioho child i vydalyty
		// takozh v ciomu n_cb my vydaliayemo vsi zviazky v c_last

		// povnyy link pidhid bilsh universalnyy i link ody na dva neu
		// yaksho link vydalenyy to vin vydalenyy z dvoh neu  
		// vydalenia linka potrebuvatyme lokania dvoh neu (abo prynaymi c_last i p_last v riznyh neu)

		enum n_type 			p_type; 	// zavzhdy odyn typ dlia p
		lin_ix 					tlp1;		
		lin_ix					trp1;
		lin_ix 					blp1;
		lin_ix 					brp1;

		lin_ix 					tlp0;		
		lin_ix					trp0;
		lin_ix 					blp0;
		lin_ix 					brp0;

		// ale
		lin_ix 					c_last; 
	};

	struct n_p_lin {
		n_neu_ix	 				p;			// p i c potribni bo po tomu samomu zviazku my mozhemo jty vverh abo vnyz
		n_neu_ix					c;

		lin_ix	 				p_p; 		// c_p, c_n ne potribni, bo my znayemo yaki i skily batkiv v child ye 
		lin_ix	 				p_n;		// deyaki neu budut maty neubmezhenu kilkist batkiv (name neu), tomu tam krashce vykorystov 
											// n_lin. Ale todi vazhche bude ih vydalyty, yaksho skazhem my vydaliayemo odyn z 6 zviazkiv
											// nam treba bude proytysia po 6 zviazkam v n_cb shob znayty toy yakyy treba zanulyty
											// tomu ce trohy meh
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
		n_neu_ix	 				p;			// p i c potribni bo po tomu samomu zviazku my mozhemo jty vverh abo vnyz
		n_neu_ix					c;

		// ce dva spysky
		// odyn z storony p, inshyy z storony c
		lin_ix	 				p_p;
		lin_ix	 				p_n;

		lin_ix	 				c_p; 		// prev i next potribni u vypadku yakshou my vydaliayemo zviazok?
		lin_ix					c_n; 		// yaksho my vydaliayemo zviazok, to my mozhemo podyvytys prev ale my neznayemo next
		 		   							// tomu naspravdi i prev i next potribni
	};

	struct n_mem {

		// vlasnyk
		S_Mem s_mem; 

	};

	static N_Mem n_mem_create(S_Mem s_mem);
	

#endif // _LU_N_H