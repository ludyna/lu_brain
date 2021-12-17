/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/


///////////////////////////////////////////////////////////////////////////////
// Lu_Rec_Config

 	static Lu_Wave_Config lu_wave_config_init(Lu_Wave_Config self);
 	static inline lu_bool lu_wave_config_is_set(Lu_Wave_Config self) { return self->flags != 0; }

///////////////////////////////////////////////////////////////////////////////
// Lu_Rec_Config Predefined 

	extern struct lu_wave_config lu_g_wc_predefined[LU_WAVE_CONFIG_END];