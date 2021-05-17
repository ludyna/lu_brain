/**
	Copyright © 2021 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// W_Cell - w_

	struct w_cell {
		// N_Cell 					neu;
		lu_value 				p;
	};

///////////////////////////////////////////////////////////////////////////////
// W_Cell_3 w_receptor_cell (c1, p, c2)

	struct w_cell_3 {
		struct w_cell 			super;

	};

	static void w_cell_3_save_value(W_Cell_3 w_cell_3, lu_value value);
 
///////////////////////////////////////////////////////////////////////////////
// W_Layer active w_list_layer

	struct w_layer {
		// vlasnyk
		W_Rec 					rec;

		lu_size 				cells_size;
		W_Cell* 				cells;
	};

	static W_Layer w_layer_init(W_Layer, W_Rec);
	static void w_layer_deinit(W_Layer self);

///////////////////////////////////////////////////////////////////////////////
// W_Rec

	struct w_rec {
		// vlasnyk
		W_Mem 							w_mem; 			

		// poviazanyy z rec
		S_Rec 							s_rec;	
		struct lu_rec_config 			config;  
		
		lu_size 						datum_lost_count;
		Lu_Lim_List 					datum;

		// struct w_layer_2 				layer_0;
		struct w_layer 					layer_1;
		struct w_layer 					layer_2;
	};

	// w_rec.lu
	static W_Rec w_rec_create(W_Mem mem, S_Rec s_rec);
	static void w_rec_destroy(W_Rec self);
 	static void w_rec_data_save(W_Rec self, Lu_Data data, lu_size block_i);

 	static void w_rec_hold(W_Rec self, Lu_Data data);
	static inline lu_bool w_rec_is_empty(W_Rec self) { return lu_lim_list_is_empty(self->datum); }
	static inline lu_bool w_rec_is_full(W_Rec self) { return lu_lim_list_count(self->datum) >= lu_lim_list_size(self->datum); }

	static void w_rec_save(W_Rec self);
	static void w_rec_reset(W_Rec self);

///////////////////////////////////////////////////////////////////////////////
// Lu_Rec_Config

 	static Lu_Wave_Config lu_wave_config_init(Lu_Wave_Config self);
 	static inline lu_bool lu_wave_config_is_set(Lu_Wave_Config self) { return self->flags != 0; }

///////////////////////////////////////////////////////////////////////////////
// Lu_Rec_Config Predefined 

	extern struct lu_wave_config lu_g_wc_predefined[LU_WC_END];

	Lu_Wave_Config lu_wave_config_predefined_get(lu_size id);

///////////////////////////////////////////////////////////////////////////////
// W_Mem

	struct w_mem {
		struct lu_wave_config  	config;

		// Refs
		Lu_Brain 				brain;

		// Internal
		Arr 					recs;

		// BH
		Mem_Table 				cells;				
	};
	
	// w_mem.lu
	static W_Mem w_mem_init(W_Mem self, Lu_Brain brain);
	static void w_mem_deinit(W_Mem self);
	static void w_mem_reset(W_Mem self);

	static W_Rec w_mem_rec_get(W_Mem self, lu_size rec_id);

	static void w_mem_save_async(W_Mem self, Lu_Story story);

	// static void w_mem_propagate(W_Mem self, 

///////////////////////////////////////////////////////////////////////////////
// Wave 

	struct lu_neu {
		struct w_cell 			super;
	};

	lu_size lu_neu_name_get(Lu_Neu);
	void lu_neu_name_set(Lu_Neu, lu_size);

	struct lu_wave {
		struct w_mem 			super;

	};

	// wave.lu
	Lu_Wave lu_wave_create(Lu_Brain brain);
	void lu_wave_destroy(Lu_Wave); 
	Lu_Wave lu_wave_join(Lu_Wave);

	// wave_save.lu
	Lu_Wave lu_wave_save(Lu_Wave, Lu_Story); 
	void lu_wave_save_async(Lu_Wave, Lu_Story);

	// wave_find.lu 
	Lu_Wave lu_wave_find(Lu_Wave, Lu_Story);
	void lu_wave_find_async(Lu_Wave, Lu_Story);

	// wave_restore.lu
	Lu_Wave lu_wave_restore(Lu_Wave, Lu_Neu);
	void lu_wave_restore_async(Lu_Wave, Lu_Story);

	Lu_Neu lu_wave_top_name_get(Lu_Wave);
	Lu_Neu lu_wave_top_neu_get(Lu_Wave self);