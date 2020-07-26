/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// 

	struct lu_neu {
		N_Cell 					neu;
		lu_value 				p;
	};
	#define w_cell lu_neu

	struct w_cell_3 {
		struct lu_neu 			super;


	};

	lu_size lu_neu_name_get(Lu_Neu);
	void lu_neu_name_set(Lu_Neu, lu_size);

	struct w_layer {
		lu_size 				cells_size;
		W_Cell* 				cells;
	};

	struct w_rec {
		// vlasnyk
		Lu_Wave_Mem 			mem; 			

		// poviazanyy z rec
		Lu_Rec 					rec;			

		lu_size 				id;

		lu_size 				cells_w;
		lu_size 				cells_h; 
		lu_size 				cells_d;		
	};

	struct lu_wave_mem {
		Lu_Brain 				brain;

		Arr 					recs;
	};
	#define w_mem lu_wave_mem

	// w_mem.lu
	static W_Mem w_mem_create(Lu_Wave wave, S_Mem s_mem);
	static W_Rec w_mem_rec_get(W_Mem self, lu_size rec_id);

	// wave_mem.lu
	Lu_Neu lu_wave_mem_name_neu(Lu_Wave_Mem);
	Lu_Neu lu_wave_mem_top_neu(Lu_Wave_Mem self);

	struct lu_wave {
		// Opts
		lu_flags 				flags;
		lu_value 				color;
		lu_value 				contrast;
		lu_value 				breakpoint;

		// Refs
		S_Mem 					s_mem; 
		N_Mem 					n_mem;
		Lu_Story 				story;

		// Internal
		W_Mem 					w_mem;
	};

	// wave.lu
	Lu_Wave lu_wave_create(Lu_Brain);
	void lu_wave_destroy(Lu_Wave); 
	Lu_Wave_Mem lu_wave_join(Lu_Wave);
	static Lu_Wave wave_prepare(Lu_Wave);

	// wave_save.lu
	Lu_Wave_Mem lu_wave_save(Lu_Wave, Lu_Story); 
	void lu_wave_save_async(Lu_Wave, Lu_Story);
	static void wave_save_async_internal(Lu_Wave self, Lu_Story story);
	static void wave_data_save(Lu_Wave self, lu_size s_rec_id, Data data, lu_size block_i);

	// wave_find.lu 
	Lu_Wave_Mem lu_wave_find(Lu_Wave, Lu_Story);
	void lu_wave_find_async(Lu_Wave, Lu_Story);

	// wave_restore.lu
	Lu_Wave_Mem lu_wave_restore(Lu_Wave, Lu_Neu);
	void lu_wave_restore_async(Lu_Wave, Lu_Story);

	// wave_properties.lu
	lu_flags lu_wave_flags_get(Lu_Wave);
	void lu_wave_flags_set(Lu_Wave, lu_flags);
	void lu_wave_flags_remove(Lu_Wave self, lu_flags flags);

	lu_value lu_wave_color_get(Lu_Wave);
	void lu_wave_color_set(Lu_Wave, lu_value);

	lu_value lu_wave_contrast_get(Lu_Wave);
	void lu_wave_contrast_set(Lu_Wave, lu_value);

	lu_value lu_wave_breakpoint_get(Lu_Wave);
	void lu_wave_breakpoint_set(Lu_Wave, lu_value);



