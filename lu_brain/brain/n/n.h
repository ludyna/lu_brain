/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

#ifndef _LU_N_H
#define _LU_N_H

///////////////////////////////////////////////////////////////////////////////
// Neu

	// predstavliye znachenia komponenty
	struct n_col {
		lu_value 		val;
	};

	// neu yakyy vidpovidaye za vsi komponenty
	// same n_cell predstavliaye s_cell
	struct n_cell {
		S_Col 			s_col;
		
	};

	// predstavliaye s_cb
	struct n_cb {
		S_Cb 			s_cb;
	};

///////////////////////////////////////////////////////////////////////////////
// Neu

	enum neu_ent_id {
		NEU_B_ID = 0,
		NEU_NAME_ID,

		NEU_ENT_ID_SIZE
	};

	// "generic" zviazky pracuvaty ne budut, bo ne nesut prostorovoy 
	// informaciyi. My mayemo znaty prostorove i chasove "znachennia"
	// zviazkiv
	struct n_ent {
		lu_size 		coms[NEU_ENT_ID_SIZE];

		// tut mozhna bulo prosto postvoruvaty zminni dlia kozhnoyi componenty
		// lu_size 	n_base;
		// lu_size 	n_name;
	};

	struct n_base {
		lu_value 		count;

		lu_size 		l_p_lin_ent;
		lu_size 		l_c_lin_ent;
	};

	struct n_name {
		lu_char 		name[255];
	};

///////////////////////////////////////////////////////////////////////////////
// Lin

	enum lin_ent_id {
		LIN_B_ID = 0,

		LIN_ENT_ID_SIZE
	};

	struct lin_ent {
		lu_size 		coms[LIN_ENT_ID_SIZE];
	};

	// basic
	struct lin_b {
		lu_size 		p_neu_ent;			// p i c potribni bo po tomu samomu zviazku my mozhemo jty vverh abo vnyz
		lu_size 		c_neu_ent;

		lu_size 		p_lin_ent_prev;
		lu_size 		p_lin_ent_next;

		lu_size 		c_lin_ent_prev; 	// prev i next potribni u vypadku yakshou my vydaliayemo zviazok?
		lu_size 		c_lin_ent_next; 	// yaksho my vydaliayemo zviazok, to my mozhemo podyvytys prev ale my neznayemo next
		 		   							// tomu naspravdi i prev i next potribni
	};


	// // ┣
	// // ┣
	// // ┣
	// // █
	// // ┣
	// // ┣
	// // ┣
	// struct lin2 {

	// 	Neu 	np; // dlia vsih output lin p bude odyn i toy samyy ale ce zrobleno dlia optymizaciyi
	// 	Neu 	nc;	// shvydkosti ruhy nazad po linku (shob ne potribno bulo shukaty nayvyshchyy lin)

	// 	Lin 	lp; // p link, bude NULL dlia pershoho lin, i my budemo dobavliaty lin speredu
	// 				// tobto samyy blyzhchyy do neu lin bude takozh samyy ostaniy
	// 	Lin 	lc; // c link 

	// 	// ce ne bude pracuvaty, bo nam treba robyty dva takyh linka (input i output), sho znachno bilshe
	// 	// pamiati, abo link tilky v odnomu napriamku
	// };

#endif // _LU_N_H