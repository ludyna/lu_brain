/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// W_Cell 

	struct w_cell {
		N_Cell 					neu;
		lu_value 				p;
	};

///////////////////////////////////////////////////////////////////////////////
// W_Cell_3

	struct w_cell_3 {
		struct w_cell 			super;

	};

	static void w_cell_3_save_value(W_Cell_3 w_cell_3, lu_value value);
 
 ///////////////////////////////////////////////////////////////////////////////
// W_Layer

	struct w_layer {
		lu_size 				cells_size;
		W_Cell* 				cells;
	};

	static W_Layer w_layer_create(S_Layer s_layer);
	static void w_layer_destroy(W_Layer self);

///////////////////////////////////////////////////////////////////////////////
// W_Layer_2

	struct w_layer_2 {
		struct w_layer 			super;

		lu_size 				w;
		lu_size 				h;
		lu_size 				d;

		 
	};

	static W_Layer_2 w_layer_2_create(S_Layer s_layer);
	static void w_layer_2_destroy(W_Layer_2 self);
	static inline W_Cell w_layer_2_cell_get(W_Layer_2 self, lu_size x, lu_size y, lu_size z)
	{
		lu_user_assert(x < self->w, "x index out of range");
		lu_user_assert(y < self->h, "y index out of range");
		lu_user_assert(z < self->d, "z index out of range");

		return self->super.cells[z * self->w * self->h + y * self->w + x]; 
	}

///////////////////////////////////////////////////////////////////////////////
// W_Rec

	struct w_rec {
		// vlasnyk
		W_Mem 							w_mem; 			

		// poviazanyy z rec
		S_Rec 							s_rec;	
		struct lu_rec_config 			config;  
		
		W_Layer_2 						layer_0;
		W_Layer 						layer_1;
		W_Layer 						layer_2;
	};

	// w_rec.lu
	static W_Rec w_rec_create(W_Mem mem, S_Rec s_rec);
	static void w_rec_destroy(W_Rec self);
 	static void w_rec_data_save(W_Rec self, Lu_Data data, lu_size block_i);

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
	};
	
	// w_mem.lu
	static W_Mem w_mem_init(W_Mem self, Lu_Brain brain);
	static void w_mem_deinit(W_Mem self);
	static void w_mem_reset(W_Mem self);

	static W_Rec w_mem_rec_get(W_Mem self, lu_size rec_id);

	static void w_mem_save_async(W_Mem self, Lu_Story story);

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