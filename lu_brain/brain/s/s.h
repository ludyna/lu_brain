/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

#ifndef _LU_S_H
#define _LU_S_H

///////////////////////////////////////////////////////////////////////////////
// S_Mem

	struct s_col {
		S_Rec 				s_rec; 		// vlasnyk

		enum n_col_type 	type;

		lu_size 			data_x;
		lu_size 			data_y;
		lu_size 			x;
		lu_size 			y; 

		// // tut ciho ne mozhe buty bo ce mozhe buty tilky v wave
		// lu_p_size 			exc_neus;   
					
		lu_p_size			v_neus; 	// value neus, mozhe buty prostoryvym perepadom, 
										// odnomirnyy masyv (optymizaciya: ne zalezhyt vid kilkosti komponent)
		lu_p_size 			p_neus;		// t perepad neus
	};

	static S_Col s_col_create(Mem mem, S_Rec rec, lu_size data_x, lu_size data_y, lu_size x, lu_size y, enum n_col_type);

	static lu_value s_col_norm(S_Col self, lu_value request); 
	static struct lu_size_range s_col_indx_range(S_Col self, lu_value val);
	static lu_value s_col_calc_sig(S_Col self, lu_size val_step_i, lu_value val);
	static lu_value s_col_step_norm_dist(S_Col self); 
	static lu_size s_col_neu_ent_get(S_Col self, lu_value input_val);

	struct s_cb {
		S_Cb parent;

		S_Cb cl;
		S_Cb cr;
		S_Cb pl;
		S_Cb pr;
		
	};

	struct s_rec {
		S_Mem 				s_mem; 			// vlasnyk

		Lu_Rec 				rec;			// poviazanyy z rec

		lu_size 			id;
		lu_size 			component_size;

		lu_size 			pers_w;
		lu_size 			pers_h;

		lu_size 			n_cols_w;
		lu_size 			n_cols_h; 
		S_Col* 				n_cols;			// vsi N_Cols

		// Ci dani spilni dlia vsih n_cols
		// i odnakovi dlia znachen i perepadiv
		lu_value 			orig_min_val;
		lu_value 			orig_max_val;
		lu_value 			max_val;
		lu_value 			val_step;

		lu_value*			val_steps;  	// preobchysleni kroky
		lu_size 			val_ssp_i; 		// (tilky dlia poshuku) signif similarity percent 
		lu_size 			val_neu_size;
	};

	static S_Rec n_rec_create(S_Mem s_mem, Lu_Rec s_rec);

	static inline void n_rec_n_cols_set(S_Rec self, lu_size x, lu_size y, S_Col s_col) { self->n_cols[y * self->n_cols_w + x] = s_col; }
	static inline S_Col n_rec_n_cols_get(S_Rec self, lu_size x, lu_size y) { return self->n_cols[y * self->n_cols_w + x]; }

	static void n_rec_debug_print(S_Rec self);

	struct s_mem {
		Lu_Brain 			brain;

		Mem_Table 			neu_ents;
		Mem_Table 			lin_ents;

		Mem_Table 			neu_bs;
		Mem_Table 			neu_names;

		Mem_Table 			lin_bs;
		// Mem_Table 		lin_weights;

		Arr 				n_recs;
	};
	
	static S_Mem n_mem_create(Lu_Brain brain);

///////////////////////////////////////////////////////////////////////////////
// Neu creators

	static lu_size n_mem_c_neu_create(S_Mem self, S_Col s_col);


///////////////////////////////////////////////////////////////////////////////
// S_Mem getters

	static inline S_Rec n_mem_n_rec_get(S_Mem self, lu_size indx) { return arr_get(self->n_recs, indx); }

///////////////////////////////////////////////////////////////////////////////
// S_Mem Neu getters

	static inline N_Ent neu_ent_get(S_Mem s_mem, lu_size neu_ent_id) 
	{  	
		return (N_Ent) mem_table_get(s_mem->neu_ents, neu_ent_id);
	} 

	static inline N_Base neu_b_get(S_Mem s_mem, lu_size neu_b_id) 
	{  	
		return (N_Base) mem_table_get(s_mem->neu_bs, neu_b_id);
	} 

	static inline N_Name neu_name_get(S_Mem s_mem, lu_size neu_name_id) 
	{  	
		return (N_Name) mem_table_get(s_mem->neu_names, neu_name_id);
	}

	static inline N_Base neu_ent_b_get(S_Mem s_mem, lu_size neu_ent_id) 
	{  	
		N_Ent ne = (N_Ent) mem_table_get(s_mem->neu_ents, neu_ent_id);
		lu_size com_id = ne->coms[NEU_B_ID];
		return com_id ? neu_b_get(s_mem, com_id) : NULL;
	}

	static inline N_Name neu_ent_name_get(S_Mem s_mem, lu_size neu_ent_id)
	{
		N_Ent ne = (N_Ent) mem_table_get(s_mem->neu_ents, neu_ent_id);
		lu_size com_id = ne->coms[NEU_NAME_ID];
		return com_id ? neu_name_get(s_mem, com_id) : NULL;
	}

///////////////////////////////////////////////////////////////////////////////
// S_Mem Lin getters

	static inline Lin_Ent lin_ent_get(S_Mem s_mem, lu_size lin_ent_id) 
	{  	
		return (Lin_Ent) mem_table_get(s_mem->lin_ents, lin_ent_id);
	} 

	static inline Lin_B lin_b_get(S_Mem s_mem, lu_size lin_b_id) 
	{  	
		return (Lin_B) mem_table_get(s_mem->lin_bs, lin_b_id);
	} 

	static inline Lin_B lin_ent_b_get(S_Mem s_mem, lu_size lin_ent_id)
	{
		Lin_Ent lin_ent = (Lin_Ent) mem_table_get(s_mem->lin_ents, lin_ent_id);
		lu_size com_id = lin_ent->coms[LIN_B_ID];
		return com_id ? lin_b_get(s_mem, com_id) : NULL;
	}

#endif // _LU_S_H
