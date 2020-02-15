/**
	Copyright © 2020 Oleh Ihorovych Novosad 
*/
#ifndef _LU_N_MEM_H
#define _LU_N_MEM_H

///////////////////////////////////////////////////////////////////////////////
// Nouns

	typedef struct m_neuron* 			M_Neto;
	typedef struct m_val_neu* 		M_Val_Neu;
	typedef struct m_neu*			M_Neu;
	typedef struct m_perception* 	M_Perception;
	typedef struct m_rec* 			M_Rec;
	typedef struct m_block* 		M_Block;
	typedef struct m_story* 		M_Story;
	typedef struct m_time* 			M_Time;
	typedef struct n_mem* 			N_Mem;

///////////////////////////////////////////////////////////////////////////////
// MNeto

	enum m_neuron_type {
		MNT_VAL_NEU
	};

	// struct m_neuron { 
	// 	enum m_neuron_type type;

	// 	void 	(*consume)(MNeto self, MNeto src, lu_value p);
	// 	void	(*bconsume)(MNeto self, MNeto src, lu_value p);
	// 	void	(*debug)(MNeto self);

	// 	#ifdef LU_DEBUG
	// 	char 				lbl[20];
	// 	#endif 
	// };

	struct m_neuron {
		lu_size 		with_parents_id;
		lu_size 		with_children_id;
		lu_size 		with_p_id;
		lu_size 		with_name_id;
		lu_size 		with_debug_id;
	}; 

///////////////////////////////////////////////////////////////////////////////
// MValNeu

	struct m_val_neu {
		struct m_neuron sup;
	};

///////////////////////////////////////////////////////////////////////////////
// MNeu

	struct m_neu {
		struct m_neuron sup;
	};

///////////////////////////////////////////////////////////////////////////////
// MPerception

	struct m_perception {
		struct m_neuron sup;
	};

///////////////////////////////////////////////////////////////////////////////
// MRec

	struct m_rec {
		struct m_neuron sup;
	};

///////////////////////////////////////////////////////////////////////////////
// MBlock

	struct m_block {
		struct m_neuron sup;
	};

///////////////////////////////////////////////////////////////////////////////
// MStory

	struct m_story {
		struct m_neuron sup;
	};

///////////////////////////////////////////////////////////////////////////////
// MTime

	struct m_time {
		struct m_neuron sup;
	};

///////////////////////////////////////////////////////////////////////////////
// 

	struct m_netable {
		lu_size 		m_entity_id;

		lu_value 		p;

		void* 			l_p; 
		void* 			l_c;
	};

	struct m_nameable {
		lu_size 		name;
	};

	struct m_debugable {

	};

	struct m_wave_queue {

	};


	struct m_entity {

	};

///////////////////////////////////////////////////////////////////////////////
// Waves

	struct m_s_wave {
		//M_S_Wave_Queue 	q;
	};

	struct m_f_wave {
		//M_S_Wave_Queue 	q;
	};

	struct m_r_wave {
		//M_S_Wave_Queue 	q;
	};


///////////////////////////////////////////////////////////////////////////////
// N_Mem

	struct n_mem {
		Brain 			brain;
		//M_Time 		time;

		Mem_Arr 		m_neulable;
		
		Mem_Arr 		s_waves;
		Mem_Arr 		f_waves;
		Mem_Arr 		r_waves;
	};
	
	N_Mem n_mem_create(Brain brain);
	void n_mem_preallocated_destroy(N_Mem* self);

#endif // _LU_N_MEM_H
