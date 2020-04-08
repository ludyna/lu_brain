/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/
#ifndef _LU_N_MEM_H
#define _LU_N_MEM_H

	typedef struct n_mem* 	N_Mem;
	typedef struct neu* 	Neu;
	typedef struct lin* 	Lin;
	typedef struct sig* 	Sig;

///////////////////////////////////////////////////////////////////////////////
// N Primitives

	enum neu_ent_id {
		NEU_BASIC_ID = 0,
		NEU_NAME_ID,

		NEU_ENT_ID_SIZE
	};

	struct neu_ent {
		lu_size ent_ids[NEU_ENT_ID_SIZE];
	};

	struct neu_basic {
		lu_value 	count;

		lu_size 	l_p_lin;
		lu_size 	l_c_lin;
	};

	enum lin_ent_id {
		LIN_BASIC_ID = 0,

		LIN_ENT_ID_SIZE
	};

	struct lin_ent {
		lu_size lin_ent[LIN_ENT_ID_SIZE];
	};

	struct lin_basic {
		lu_size 	p_neu;		// p i c potribni bo po tomu samomu zviazku my mozhemo jty vverh abo vnyz
		lu_size 	c_neu;

		lu_size 	p_lin_prev;
		lu_size 	p_lin_next;

		lu_size 	c_lin_prev; // prev i next potribni u vypadku yakshou my vydaliayemo zviazok?
		lu_size 	c_lin_next; // yaksho my vydaliayemo zviazok, to my mozhemo podyvytys prev ale my neznayemo next
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


///////////////////////////////////////////////////////////////////////////////
// N_Rec



///////////////////////////////////////////////////////////////////////////////
// Val_Layer

	/*
		Val layer is optimized for standard PC CPUs but it is easy to build it 
		as a pure NN for NN hardware implementations.
	*/
	struct val_layer {
		N_Mem 			n_mem;

		lu_value 		orig_min_val, orig_max_val;
		lu_value 		max_val;
		lu_value 		val_step;

		lu_size 		val_neu_size;
		Neu*			val_neus;
		lu_value*		val_steps; 
		lu_size 		ssp_i; // significant similarity percent
	};

	typedef struct val_layer* ValLayer;

	///////////////////////////////////////////////////////////////////////////////
	// Create and destroy

	ValLayer val_layer_create(N_Mem mem, lu_value min_val, lu_value max_val, lu_size val_neu_size, lu_value val_ssp);
	void val_layer_destroy(ValLayer*);

	///////////////////////////////////////////////////////////////////////////////
	// Main public methods

	Neu val_layer_save(ValLayer self, lu_value input_val, lu_time);
	//void val_layer_find(ValLayer self, lu_value input_val, FindWave);

	///////////////////////////////////////////////////////////////////////////////
	// Other public methods

	lu_value val_layer_norm(ValLayer self, lu_value request); 
	struct lu_size_range val_layer_indx_range(ValLayer self, lu_value val);
	lu_value val_layer_calc_potent(ValLayer self, lu_size val_step_i, lu_value val);
	lu_value val_layer_step_norm_dist(ValLayer self);


///////////////////////////////////////////////////////////////////////////////
// N_Mem


	struct n_mem {
		Brain 			brain;

		Mem_Table 		neu_ents;
		Mem_Table 		lin_ents;

		Mem_Table 		neu_basics;
		Mem_Table 		lin_basics;
		Mem_Table 		lin_names;


	};
	
	N_Mem n_mem_create(Brain brain);



#endif // _LU_N_MEM_H
