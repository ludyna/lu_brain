/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

#ifndef _LU_N_H
#define _LU_N_H

///////////////////////////////////////////////////////////////////////////////
// Neu
	// struct n_v {
	// 	S_V_Col s_v_col;


	// };

	// struct n_p {
	// 	S_P_Col s_v_col;

	// };

	// typedef struct n_col* 		N_Col;
	// typedef struct n_cell* 		N_Cell;
	// typedef struct n_cb* 		N_Cb;
	typedef struct n_mem* 		N_Mem;

	// typedef struct n_ent* 		N_Ent;
	// typedef struct n_base* 		N_Base;
	// typedef struct n_name* 		N_Name;

	// typedef struct lin_ent* 	Lin_Ent;
	// typedef struct lin_b* 		Lin_B;
	
	struct n_col {
		S_Col 			s_v_col;

		lu_value 		val;
	};

	// predstavliaye s_cb
	struct n_cb {
		S_Cb 			s_cb;


	};

	struct n_mem {

		// vlasnyk
		S_Mem s_mem; 

	};

	static N_Mem n_mem_create(S_Mem s_mem);

///////////////////////////////////////////////////////////////////////////////
// Neu (nam neu potribne tilky dlia zviazkiv bilshe nichoho)


// struct some_info {
//   int type; // set accordingly
//   union {
//     struct TYPEA a;
//     struct TYPEB b;
//   } data; // access with some_info_object.data.a or some_info_object.data.b
// };

// struct some_info {
//   int type; // set accordingly
//   union {
//     struct TYPEA a;
//     struct TYPEB b;
//   } data; // access with some_info_object.data.a or some_info_object.data.b
// };

	enum n_comp_type {
		NCI_VALUE = 0,
		NCI_NAME = 1,

		NCI_SIZE
	};

	// "generic" zviazky pracuvaty budut, yaksho link na structurno-prostorovu info 
	struct n_ent {
		// spilni dlia vsih neu dani
		// S_Base 					s_base;
		// lu_value 				count;  		

		// lu_size 				l_p_lin_ent;
		// lu_size 				l_c_lin_ent;

		// // odna dodatkova componenta
		// enum n_comp_type		comp_type;
		// lu_size 				comp_ent;

		// mozhna zrobyty dvi componenty i vsi dani tudy pomistity
		// napryklad comp1 ce zavzhdy typ zviazku (p i c, tilky p, tilky c i vidpovidno count yaksho treba)

		// druha componenta ce specyfichni dani like name (s_base skorishe vsioho ne treba bude, tam bude shos zaviazane z w_)

		// vzhe todi krashce 3 comp,
		// 1) ce linky z p + count
		// 2) ce linky do c
		// 3) dodatkove shos (yak name)

		lu_size 				l_p_lin_ent; // cia componenta vkluchaye count
		lu_size 				l_c_lin_ent;

		enum n_comp_type		comp_type;
		lu_size 				comp_ent;	// cia componenta vkluchaye name abo value abo shos inshe
	};


	enum neu_ent_id {
		NEU_B_ID = 0,
		NEU_NAME_ID,

		NEU_ENT_ID_SIZE
	};

	// "generic" zviazky pracuvaty budut, yaksho link na structurno-prostorovu info 
	struct n_ent {
		lu_size 		coms[NEU_ENT_ID_SIZE];  // yaksho zrobyty ce dynamichne, to problem z pam nema

		// tut mozhna bulo prosto postvoruvaty zminni dlia kozhnoyi componenty
		// lu_size 	n_base;
		// lu_size 	n_name;

		lu_value 		count;  		

		lu_size 		l_p_lin_ent;
		lu_size 		l_c_lin_ent;
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

		// ce dva spysky
		// odyn z storony p, inshyy z storony c
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