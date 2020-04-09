/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

#ifndef _LU_N_MEM_H
#define _LU_N_MEM_H

///////////////////////////////////////////////////////////////////////////////
// Nouns



	typedef struct neu_ent* 	Neu_Ent;
	typedef struct neu_b* 		Neu_B;
	typedef struct neu_name* 	Neu_Name;

	typedef struct lin_ent* 	Lin_Ent;
	typedef struct lin_b* 		Lin_B;

	typedef struct n_channel*	N_Channel; 
	typedef struct n_rec*		N_Rec;
	typedef struct n_mem* 		N_Mem;

///////////////////////////////////////////////////////////////////////////////
// Neu

	enum neu_ent_id {
		NEU_B_ID = 0,
		NEU_NAME_ID,

		NEU_ENT_ID_SIZE
	};

	struct neu_ent {
		lu_size 		coms[NEU_ENT_ID_SIZE];
	};

	// basic 
	struct neu_b {
		lu_value 		count;

		lu_size 		l_p_lin_ent;
		lu_size 		l_c_lin_ent;
	};

	struct neu_name {
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


///////////////////////////////////////////////////////////////////////////////
// Val_Layer

	//
	//	Val layer is optimized for standard PC CPUs but it is easy to build it 
	//	as a pure NN for NN hardware implementations.
	// 
	// 	Napryklad val neu ce specialnyy neu yakyy maye specialnu componentu neu_val
	// 	Cia neu_val maye znachenia value. neu_val zbudzhuyetsia tilky todi koly
	// 	vhidnyy impuls znahodytsia na ssp vidstani vid neu_val value. Dlia PC CPU 
	// 	ce oznachaye perebir vsih val neuroniv shob zbudyty potribnyy. Dlia hardware neural 
	// 	network ce ne problema. Shob optymizuvaty dlia PC CPU ya vykorystovuyu hash-like 
	// 	pidhid.
	//
	// 	Odyn val layer na percepciyu.
	//
	struct val_layer {
		N_Mem 				n_mem;

		lu_size 			w, h;

		lu_value 			orig_min_val, orig_max_val;
		lu_value 			max_val;
		lu_value 			val_step;

		lu_size 			val_neu_size;
		lu_size*			val_neus;			// triohmirnyy masyv, x i y - ce posyciya v percepciyi
												// z - ce prostir znachen 
		lu_value*			val_steps; 
		lu_size 			ssp_i; 				// signif similarity percent
	};

	typedef struct val_layer* Val_Layer;

	///////////////////////////////////////////////////////////////////////////////
	// Create and destroy

	static Val_Layer val_layer_create(N_Mem mem, Rec rec);
	static void val_layer_destroy(Val_Layer*);

	///////////////////////////////////////////////////////////////////////////////
	// Main public methods

	static lu_size val_layer_save(Val_Layer self, lu_value input_val, lu_time);
	//void val_layer_find(Val_Layer self, lu_value input_val, FindWave);

	///////////////////////////////////////////////////////////////////////////////
	// Other public methods

	static lu_value val_layer_norm(Val_Layer self, lu_value request); 
	static struct lu_size_range val_layer_indx_range(Val_Layer self, lu_value val);
	static lu_value val_layer_calc_potent(Val_Layer self, lu_size val_step_i, lu_value val);
	static lu_value val_layer_step_norm_dist(Val_Layer self);


///////////////////////////////////////////////////////////////////////////////
// N_Mem

	struct n_channel {
		Val_Layer 		color;		// colir
		Val_Layer 		cont;  		// kontur
	}; 

	

	struct n_rec {
		Arr 			channels;
	};

	static N_Rec n_rec_create(Rec rec);

	struct n_mem {
		Brain 			brain;

		Mem_Table 		neu_ents;
		Mem_Table 		lin_ents;

		Mem_Table 		neu_bs;
		Mem_Table 		neu_names;

		Mem_Table 		lin_bs;
		// Mem_Table 	lin_weights;

		Arr 			n_recs;
	};
	
	static N_Mem n_mem_create(Brain brain);


///////////////////////////////////////////////////////////////////////////////
// N_Mem Neu getters

	static inline Neu_Ent neu_ent_get(N_Mem n_mem, lu_size neu_ent_id) 
	{  	
		return (Neu_Ent) mem_table_get(n_mem->neu_ents, neu_ent_id);
	} 

	static inline Neu_B neu_b_get(N_Mem n_mem, lu_size neu_b_id) 
	{  	
		return (Neu_B) mem_table_get(n_mem->neu_bs, neu_b_id);
	} 

	static inline Neu_Name neu_name_get(N_Mem n_mem, lu_size neu_name_id) 
	{  	
		return (Neu_Name) mem_table_get(n_mem->neu_names, neu_name_id);
	}

	static inline Neu_B neu_ent_b_get(N_Mem n_mem, lu_size neu_ent_id) 
	{  	
		Neu_Ent neu_ent = (Neu_Ent) mem_table_get(n_mem->neu_ents, neu_ent_id);
		lu_size com_id = neu_ent->coms[NEU_B_ID];
		return com_id ? neu_b_get(n_mem, com_id) : NULL;
	}

	static inline Neu_Name neu_ent_name_get(N_Mem n_mem, lu_size neu_ent_id)
	{
		Neu_Ent neu_ent = (Neu_Ent) mem_table_get(n_mem->neu_ents, neu_ent_id);
		lu_size com_id = neu_ent->coms[NEU_NAME_ID];
		return com_id ? neu_name_get(n_mem, com_id) : NULL;
	}

///////////////////////////////////////////////////////////////////////////////
// N_Mem Lin getters

	static inline Lin_Ent lin_ent_get(N_Mem n_mem, lu_size lin_ent_id) 
	{  	
		return (Lin_Ent) mem_table_get(n_mem->lin_ents, lin_ent_id);
	} 

	static inline Lin_B lin_b_get(N_Mem n_mem, lu_size lin_b_id) 
	{  	
		return (Lin_B) mem_table_get(n_mem->lin_bs, lin_b_id);
	} 

	static inline Lin_B lin_ent_b_get(N_Mem n_mem, lu_size lin_ent_id)
	{
		Lin_Ent lin_ent = (Lin_Ent) mem_table_get(n_mem->lin_ents, lin_ent_id);
		lu_size com_id = lin_ent->coms[LIN_B_ID];
		return com_id ? lin_b_get(n_mem, com_id) : NULL;
	}

#endif // _LU_N_MEM_H
