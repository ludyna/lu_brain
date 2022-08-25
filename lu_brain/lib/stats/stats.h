/**
	Copyright © 2022 Oleh Ihorovych Novosad 

	Structs to collect statistics about system
*/



///////////////////////////////////////////////////////////////////////////////
// Lu_N_Table_Net_Stats

	struct lu_s_table_net_stats {
		lu_size column_count;


		lu_size cells_used_min;
		lu_size cells_used_mean;
		lu_size cells_used_max;
		lu_size cells_size;
		lu_size total_cells_count;
		lu_size total_cells_size;

		lu_size max_z_min;
		lu_size max_z_mean;
		lu_size max_z_max;
		lu_size d;

		lu_size links_count_min;
		lu_size links_count_mean;
		lu_size links_count_max;
		lu_size links_size;
		lu_size total_links_count;
		lu_size total_links_size;
	};

	static inline Lu_N_Table_Net_Stats lu_s_table_stats__reset(Lu_N_Table_Net_Stats self)
	{
		lu__assert(self);

		self->column_count = 0;

		self->cells_used_min = LU_SIZE__MAX;
		self->cells_used_mean = 0;
		self->cells_used_max = 0;
		self->cells_size = 0;
		self->total_cells_count = 0;
		self->total_cells_size = 0;

		self->max_z_min = LU_SIZE__MAX;
		self->max_z_mean = 0;
		self->max_z_max = 0;
		self->d = 0;

		self->links_count_min = LU_SIZE__MAX;
		self->links_count_mean = 0;
		self->links_count_max = 0;
		self->links_size = 0;
		self->total_links_count = 0;
		self->total_links_size = 0;

		return self;
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_S_Layer_Net_Stats
//

	struct lu_s_layer_net_stats {
		lu_size cells_count;
		lu_size cells_size;
		lu_size links_count;
		lu_size links_size;
	};

	static inline void lu_s_layer_net_stats__reset(Lu_S_Layer_Net_Stats self)
	{
		self->cells_count = 0;
		self->cells_size = 0;
		self->links_count = 0;
		self->links_size = 0;
	}

 	static inline void lu_s_layer_net_stats__collect(Lu_S_Layer_Net_Stats self, Lu_N_Table_Net_Stats table_ns)
 	{
 		lu__assert(self);
 		lu__assert(table_ns);

		self->cells_count += table_ns->total_cells_count;
		self->cells_size  += table_ns->total_cells_size;
		self->links_count += table_ns->total_links_count;
		self->links_size += table_ns->total_links_size;
 	}

///////////////////////////////////////////////////////////////////////////////
// Lu_S_Area_Net_Stats
//

	struct lu_s_area_net_stats {
		lu_size cells_count;
		lu_size cells_size;
		lu_size links_count;
		lu_size links_size;
	};

	static inline void lu_s_area_net_stats__reset(Lu_S_Area_Net_Stats self)
	{
		self->cells_count = 0;
		self->cells_size = 0;
		self->links_count = 0;
		self->links_size = 0;
	}

 	static inline void lu_s_area_net_stats__collect(Lu_S_Area_Net_Stats self, Lu_S_Layer_Net_Stats ns)
 	{
 		lu__assert(self);
 		lu__assert(ns);

		self->cells_count += ns->cells_count;
		self->cells_size  += ns->cells_size;
		self->links_count += ns->links_count;
		self->links_size += ns->links_size;
 	}

///////////////////////////////////////////////////////////////////////////////
// Lu_S_Net_Stats
//

	struct lu_s_net_stats {
		lu_size cells_count;
		lu_size cells_size;
		lu_size links_count;
		lu_size links_size;
	};

	static inline void lu_s_net_stats__reset(Lu_S_Net_Stats self)
	{
		self->cells_count = 0;
		self->cells_size = 0;
		self->links_count = 0;
		self->links_size = 0;
	}

	static inline void lu_s_net_stats__collect(Lu_S_Net_Stats self, Lu_S_Area_Net_Stats ns)
 	{
 		lu__assert(self);
 		lu__assert(ns);

		self->cells_count += ns->cells_count;
		self->cells_size  += ns->cells_size;
		self->links_count += ns->links_count;
		self->links_size += ns->links_size;
 	}

 	static inline void lu_s_net_stats__print(Lu_S_Net_Stats self)
 	{
 		lu__assert(self);

 		lu__debug(
 			"\nTotal cells: %ld/%ld, Total links: %ld/%ld", 
 			self->cells_count,
 			self->cells_size,
 			self->links_count,
 			self->links_size
 		);
 	}

///////////////////////////////////////////////////////////////////////////////
// Lu_W_Processor_Stats
//

 	struct lu_w_processor_stats {
 		lu_size cells_processed;
 	};

 	static inline void lu_w_processor_stats__reset(Lu_W_Processor_Stats self)
 	{
 		lu__assert(self);

 		self->cells_processed = 0;
 	}


///////////////////////////////////////////////////////////////////////////////
// Lu_Brain_Net_Stats
//

 	static inline Lu_Brain_Net_Stats lu_brain_net_stats__reset(Lu_Brain_Net_Stats self)
 	{
 		self->n_cells_count = 0;
 		self->n_cells_size = 0;
 		self->n_links_count = 0;
 		self->n_links_size = 0;

 		return self;
 	}

 	static inline void lu_brain_net_stats__collect(Lu_Brain_Net_Stats self, Lu_S_Net_Stats s_ns)
 	{
 		self->n_cells_count = s_ns->cells_count;
 		self->n_cells_size = s_ns->cells_size;
 		self->n_links_count = s_ns->links_count;
 		self->n_links_size = s_ns->links_size;
 	} 