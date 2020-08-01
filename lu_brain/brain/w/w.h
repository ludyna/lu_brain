/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// 

	struct w_cell {
		N_Cell 					neu;
		lu_value 				p;
	};

	struct w_cell_3 {
		struct w_cell 			super;

	};

	static void w_cell_3_save_value(W_Cell_3 w_cell_3, lu_value value);

	struct w_layer {
		lu_size 				cells_size;
		W_Cell* 				cells;
	};

	static W_Layer w_layer_create(S_Layer s_layer);
	static void w_layer_destroy(W_Layer self);

	struct w_layer_2 {
		struct w_layer 			super;

		lu_size 				w;
		lu_size 				h;
		lu_size 				d;
	};

	static W_Layer_2 w_layer_2_create(S_Layer s_layer);
	static void w_layer_2_destroy(W_Layer_2 self);

	static inline W_Cell w_layer_cell_get(W_Layer_2 self, lu_size x, lu_size y, lu_size z)
	{
		lu_user_assert(x < self->w, "x index out of range");
		lu_user_assert(y < self->h, "y index out of range");
		lu_user_assert(z < self->d, "z index out of range");

		return self->super.cells[z * self->w * self->h + y * self->w + x]; 
	}

	struct w_rec {
		// vlasnyk
		W_Mem 					w_mem; 			

		// poviazanyy z rec
		S_Rec 					s_rec;		

		W_Layer_2 				layer_0;
		W_Layer 				layer_1;
		W_Layer 				layer_2;

		lu_size 				hold_blocks_count;
		lu_size					hold_blocks_size;
	};

	// w_rec.lu
	static W_Rec w_rec_create(W_Mem mem, S_Rec s_rec);
	static void w_rec_destroy(W_Rec self);
 	static void w_rec_data_save(W_Rec self, Data data, lu_size block_i);

	struct w_mem {
		// vlasnyk
		Lu_Wave 				wave;

		Arr 					recs;
	};
	
	// w_mem.lu
	static W_Mem w_mem_create(Lu_Wave wave, S_Mem s_mem);
	static void w_mem_destroy(W_Mem self);
	static W_Rec w_mem_rec_get(W_Mem self, lu_size rec_id);

///////////////////////////////////////////////////////////////////////////////
// 

	struct lu_neu {
		struct w_cell 			super;
	};

	lu_size lu_neu_name_get(Lu_Neu);
	void lu_neu_name_set(Lu_Neu, lu_size);

	// wave_mem.lu
	Lu_Neu lu_wave_mem_name_neu(Lu_Wave);
	Lu_Neu lu_wave_mem_top_neu(Lu_Wave self);

	struct lu_wave {
		struct w_mem 			super;

		// Other opts
		lu_value 				contrast_vs_color;			// blyzhche do 1 ce contrast
		lu_value 				fire_breakpoint;

		// Refs
		Lu_Brain 				brain;
		S_Mem 					s_mem; 
		N_Mem 					n_mem;
		Lu_Story 				story;

		// Internal
		W_Mem 					w_mem;
	};

	// wave.lu
	Lu_Wave lu_wave_create(Lu_Brain brain);
	void lu_wave_destroy(Lu_Wave); 
	Lu_Wave lu_wave_join(Lu_Wave);
	static Lu_Wave wave_prepare(Lu_Wave);

	// wave_save.lu
	Lu_Wave lu_wave_save(Lu_Wave, Lu_Story); 
	void lu_wave_save_async(Lu_Wave, Lu_Story);
	static void wave_save_async_internal(Lu_Wave self, Lu_Story story);
	static void wave_data_save(Lu_Wave self, S_Rec s_rec, Data data, lu_size block_i);

	// wave_find.lu 
	Lu_Wave lu_wave_find(Lu_Wave, Lu_Story);
	void lu_wave_find_async(Lu_Wave, Lu_Story);

	// wave_restore.lu
	Lu_Wave lu_wave_restore(Lu_Wave, Lu_Neu);
	void lu_wave_restore_async(Lu_Wave, Lu_Story);

	// wave_properties.lu
	lu_value lu_wave_contrast_vs_color_get(Lu_Wave);
	void lu_wave_contrast_vs_color_set(Lu_Wave, lu_value);

	lu_value lu_wave_fire_breakpoint_get(Lu_Wave);
	void lu_wave_fire_breakpoint_set(Lu_Wave, lu_value);



