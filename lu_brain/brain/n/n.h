/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

#ifndef _LU_N_H
#define _LU_N_H

///////////////////////////////////////////////////////////////////////////////
// Neu

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
		lu_size 				comp_ent;
	};

	struct n_name {
		lu_char 		name[255];
	};



	struct n_base {
		S_Base 			s_base;

	};

	struct n_v_neu {
		
		lu_value 		val;

		N_Lin 			c_l;
	};

	struct n_v_lin { // ce ne bude pracuvaty, bo n_neu ne maye n_v_linka nazad, treba shos rozumnishe
		N_V_Neu 		p;
		N_Neu 			c;

		N_V_Lin         p_p;
		N_V_Lin         p_n;

		N_V_Lin 		c_p;
		N_V_Lin 		c_n;
	};

	struct n_neu {
		S_Base 			s_base;
		lu_size 		lid; 		
		lu_value	 	count;

		// ostanni linky
		N_Lin 			c_l;
		N_Lin 			p_l;
	};

	union n_pointer {
		N_Neu 		neu;
		N_V_Neu 	v_neu;
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