/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// 

	struct lu_neu {
		N_Neu 					neu;
		lu_value 				p;
	};

	// asociyuyetsia do s_neu, a ne n_neu
	struct lu_space {
		Lu_Neu 					sigs; 	// velykyy masyv, de sigs[n_neu_1->sid] vidpovidaye za w_sig dlia n_neu_1
										// kozhne vykorystania n_neu miniaye misciamy n_neu->sid z vyshchym n_neu->sid
										// takym chynom my mozhemo vyddaliaty neu z sid sho perevyshchuye pevne znachennia (starinnia neuroniv)

		Lu_Neu 					w;		// peremozhec
	};

	struct lu_layer {
		lu_size 				w;
		lu_size 				h;

		Lu_Space* 				neus;  // asociyuyutsia z s_neu
	};

	struct lu_net {

	};

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
		Lu_Net 					net;
	};

	Lu_Wave lu_wave_create(Lu_Brain);
	void lu_wave_destroy(Lu_Wave); 

	// Save
	Lu_Net lu_wave_save(Lu_Wave, Lu_Story); 
	void lu_wave_save_async(Lu_Wave, Lu_Story);
	static void wave_save_async_internal(Lu_Wave self, Lu_Story story);
	static void wave_data_save(Lu_Wave self, S_Rec s_rec, Data data, lu_size block_i);

	// Find 
	Lu_Net lu_wave_find(Lu_Wave, Lu_Story);
	void lu_wave_find_async(Lu_Wave, Lu_Story);

	// Restore
	Lu_Net lu_wave_restore(Lu_Wave, Lu_Neu);
	void lu_wave_restore_async(Lu_Wave, Lu_Story);

	// Other
	Lu_Net lu_wave_join(Lu_Wave);
	static Lu_Wave wave_prepare(Lu_Wave);

	// Properties

	lu_flags lu_wave_flags_get(Lu_Wave);
	void lu_wave_flags_set(Lu_Wave, lu_flags);
	void lu_wave_flags_remove(Lu_Wave self, lu_flags flags);

	lu_value lu_wave_color_get(Lu_Wave);
	void lu_wave_color_set(Lu_Wave, lu_value);

	lu_value lu_wave_contrast_get(Lu_Wave);
	void lu_wave_contrast_set(Lu_Wave, lu_value);

	lu_value lu_wave_breakpoint_get(Lu_Wave);
	void lu_wave_breakpoint_set(Lu_Wave, lu_value);



