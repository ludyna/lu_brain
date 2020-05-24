/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

#ifndef _LU_S_H
#define _LU_S_H

///////////////////////////////////////////////////////////////////////////////
// S
 
 	// n_cols dlia kolioru i perp
	struct s_col {
		// vlasnyk
		S_Cell				s_cell;		
		S_Rec 				s_rec; 		

		N_Col*				n_cols; 	
	};

	static inline S_Col s_col_create(Mem mem, S_Cell s_cell);
	static inline lu_value s_col_norm(S_Col self, lu_value request);
	static inline lu_size n_col_indx(S_Col self, lu_value val);
	static inline struct lu_size_range s_col_indx_range(S_Col self, lu_value val);
	static inline lu_value s_col_calc_sig(S_Col self, lu_size val_step_i, lu_value val);
	static inline lu_value s_col_step_norm_dist(S_Col self);
	static inline N_Col s_col_n_get(S_Col self, lu_value input_val);

	// p or v cell
	struct s_cell {
		// vlasnyk
		S_Rec 				s_rec; 		

		enum s_cell_type 	type;

		lu_size 			data_x;
		lu_size 			data_y;
		lu_size 			x;
		lu_size 			y; 

		// p or v 
		Arr 				s_cells;    	
	};

	static S_Cell s_cell_create(Mem mem, S_Rec rec, lu_size data_x, lu_size data_y, lu_size x, lu_size y, enum s_cell_type);
	static inline S_Col s_cell_s_col_get(S_Cell self, lu_size indx) { return (S_Col) arr_get(self->s_cells, indx); }
	static N_Cell s_cell_n_get(S_Cell, lu_p_value components);

	struct s_cb_pos {
		lu_size 	lvl;
		lu_size 	x;
		lu_size 	y; 
	};

	struct s_cb {
		S_Cb 				parent;

		S_Cb 				cl;
		S_Cb 				cr;
		S_Cb 				pl;
		S_Cb 				pr;

		struct s_cb_pos 	pos;
	};

	struct s_rec {
		// vlasnyk
		S_Mem 				s_mem; 			

		// poviazanyy z rec
		Lu_Rec 				rec;			

		lu_size 			id;

		lu_size 			pers_w;
		lu_size 			pers_h;

		lu_size 			s_cells_w;
		lu_size 			s_cells_h; 
		S_Cell* 			s_cells;			

		// Ci dani spilni dlia vsih s_cells i s_col
		// i odnakovi dlia znachen i perepadiv
		lu_size 			component_size; 
		lu_value 			orig_min_val;
		lu_value 			orig_max_val;
		lu_value 			max_val;
		lu_value 			val_step;

		lu_value*			val_steps;  	// preobchysleni kroky
		lu_size 			val_ssp_i; 		// (tilky dlia poshuku) signif similarity percent 
		lu_size 			val_neu_size;
	};

	static S_Rec s_rec_create(S_Mem s_mem, Lu_Rec s_rec);

	static inline void s_rec_s_cell_set(S_Rec self, lu_size x, lu_size y, S_Cell s_cell) { self->s_cells[y * self->s_cells_w + x] = s_cell; }
	static inline S_Cell s_rec_s_cell_get(S_Rec self, lu_size x, lu_size y) { return self->s_cells[y * self->s_cells_w + x]; }

	static void s_rec_debug_print(S_Rec self);

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
	
	static S_Mem s_mem_create(Lu_Brain brain);

///////////////////////////////////////////////////////////////////////////////
// Neu creators

	static lu_size s_mem_c_neu_create(S_Mem self, S_Col s_col);


///////////////////////////////////////////////////////////////////////////////
// S_Mem getters

	static inline S_Rec s_mem_s_rec_get(S_Mem self, lu_size indx) { return arr_get(self->n_recs, indx); }

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
