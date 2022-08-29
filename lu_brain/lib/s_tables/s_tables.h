/**
	Copyright © 2022 Oleh Ihorovych Novosad 
*/

///////////////////////////////////////////////////////////////////////////////
// Lu_S_Column_Comp
//

	struct lu_s_column_comp {
		Lu_Mem mem;

		lu_size column_ix;

		struct lu_n_cell_vp* cells;
		lu_size cells_size;

		struct lu_n_link_mem link_mem;

		lu_size w_match_cells_size;
	};

	//
	// Constructors / Destructors
	//

	static Lu_S_Column_Comp lu_s_column_comp__init(
		Lu_S_Column_Comp self, 
		Lu_Mem mem, 
		lu_size cell_size, 
		lu_size x, 
		lu_size y, 
		lu_size area_ix,
		lu_size layer_ix, 
		lu_size column_ix,
		Lu_Comp_Calc comp_calc, 
		Lu_Config config
	);

	static void lu_s_column_comp__deinit(Lu_S_Column_Comp self);

	//
	// Get
	//

	static inline Lu_N_Cell_VP lu_s_column_comp__get_cell_by_ix(Lu_S_Column_Comp self, lu_size cell_ix)
	{
		lu__debug_assert(self);
		lu__debug_assert(cell_ix < self->cells_size);

		return &self->cells[cell_ix];
	}

	static inline Lu_N_Link_Mem lu_s_column_comp__get_n_link_mem(Lu_S_Column_Comp self)
	{
		return &self->link_mem;
	}

	//
	// Methods
	//

	static inline void lu_s_column_comp__find_n_cell(
		Lu_S_Column_Comp self, 
		union lu_n_addr addr, 
		Lu_N_Cell_VP* p_n_cell_vp
	)
	{
		Lu_N_Cell_VP n_cell_vp = lu_s_column_comp__get_cell_by_ix(self, addr.cell_ix);

		// Make sure everything is correct
		lu__assert(lu_n_addr__is_eq(&n_cell_vp->addr, &addr));

		*p_n_cell_vp = n_cell_vp;
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_S_Table_Comp
//

	struct lu_s_table_comp {
		Lu_Mem mem;
		lu_size w;
		lu_size h;
		lu_size d;
		lu_size wh;

		struct lu_s_column_comp* columns;
	};

	//
	// Constructors / Destructors
	//

	static Lu_S_Table_Comp lu_s_table_comp__create(
		Lu_Config config, 
		Lu_Comp_Calc comp_calc, 
		lu_size width, 
		lu_size height, 
		lu_size depth, 
		lu_size layer_ix,
		lu_size area_ix
	);

	static void lu_s_table_comp__destroy(Lu_S_Table_Comp self);

	//
	// Get
	//

	static inline Lu_S_Column_Comp lu_s_table_comp__get_column(Lu_S_Table_Comp self, lu_size x, lu_size y)
	{
		lu__debug_assert(self);

		lu_size column_ix = y * self->w + x;

		lu__debug_assert(column_ix < self->wh);

		return &self->columns[column_ix];
	}

	static inline Lu_N_Cell_VP lu_s_table_comp__get_cell(Lu_S_Table_Comp self, lu_size x, lu_size y, lu_size z)
	{
		Lu_S_Column_Comp column = lu_s_table_comp__get_column(self, x, y);

		return lu_s_column_comp__get_cell_by_ix(column, z);
	}

	static inline Lu_S_Column_Comp lu_s_table_comp__get_column_by_ix(Lu_S_Table_Comp self, lu_size column_ix)
	{
		lu__assert(column_ix < (self->w * self->h * self->d));

		return &self->columns[column_ix];	
	}

	//
	// Methods
	//
		
	static inline lu_size lu_s_table_comp__calc_cell_ix(Lu_S_Table_Comp self, lu_size x, lu_size y, lu_size z)
	{
		return z * self->wh + y * self->w + x;
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_S_Column
// 
	
	// struct lu_s_column {
	// 	Lu_Mem mem;

	// 	Lu_S_Table s_table;

	// 	lu_size column_ix;

	// 	lu_size h;
	// 	lu_size d;

	// 	struct lu_n_cell* cells;
	// 	lu_size cells_size;

	// 	struct lu_n_link_mem link_mem;

	// 	lu_size w_match_cells_size;

	// 	//
	// 	// Position, mostly for debugging
	// 	//
	// 	lu_size x;
	// 	lu_size y;

	// 	//
	// 	// Stats
	// 	// 

	// 	lu_size stat_cells_used;
	// 	lu_size stat_max_z;

	// 	// We have to use cell addr here, because pointer to Lu_N_Cell gets invalidated when reallocated
	// 	union lu_n_addr stat_max_n_cell_addr;

	// };

	// //
	// // Constructors / Destructors
	// // 

	// static Lu_S_Column lu_s_column__init(
	// 	Lu_S_Column self, 
	// 	Lu_S_Table s_table,
	// 	Lu_Mem mem, 
	// 	lu_size h, 
	// 	lu_size d, 
	// 	lu_size area_ix,
	// 	lu_size layer_ix, 
	// 	lu_size column_ix,
	// 	Lu_Config config,
	// 	lu_size x,
	// 	lu_size y
	// );
	// static void lu_s_column__deinit(Lu_S_Column self);


	// //
	// // Get
	// //

	// static inline Lu_N_Link_Mem lu_s_column__get_link_mem(Lu_S_Column self)
	// {
	// 	lu__debug_assert(self);

	// 	return &self->link_mem;
	// }

	// static inline Lu_N_Cell lu_s_column__get_null_cell(Lu_S_Column self)
	// {
	// 	lu__debug_assert(self);

	// 	return &self->cells[0];
	// } 

	// static inline Lu_N_Cell lu_s_column__get_cell_by_ix(Lu_S_Column self, lu_size cell_ix)
	// {
	// 	lu__assert(self);
	// 	lu__assert(cell_ix < self->cells_size);

	// 	return &self->cells[cell_ix];
	// }

	// static inline Lu_N_Cell lu_s_column__get_cell(Lu_S_Column self, lu_size z, lu_size ix)
	// {
	// 	return lu_s_column__get_cell_by_ix(self, z * self->h + ix);
	// }

	// static inline lu_size lu_s_column__get_column_ix(Lu_S_Column self)
	// {
	// 	return self->column_ix;
	// }

	// //
	// // Methods
	// //

	// static inline lu_size lu_s_column__hash_to_ix(Lu_S_Column self, lu_size hash)
	// {
	// 	return hash % self->h; 
	// }

	// static inline lu_size lu_s_column__vp_children_to_ix(
	// 	Lu_S_Column self, 
	// 	Lu_W_Cell_P* children, 
	// 	lu_size children_count
	// )
	// {
	// 	return lu_s_column__hash_to_ix(self, lu_w_cell_p__children_hash_comp(children, children_count));
	// } 

	// static inline lu_size lu_s_column__children_to_ix(
	// 	Lu_S_Column self, 
	// 	Lu_W_Cell* children, 
	// 	lu_size children_count
	// )
	// {
	// 	return lu_s_column__hash_to_ix(self, lu_w_cell__children_hash_comp(children, children_count));
	// }

	// static void lu_s_column__realloc(Lu_S_Column self);


	// static inline void lu_s_column__increase_stats(Lu_S_Column self, lu_size z, Lu_N_Cell n_cell)
	// {
	// 	lu__assert(self);
	// 	lu__assert(n_cell);
	// 	lu__assert(z < self->d);

	// 	if (z > self->stat_max_z) 
	// 	{

	// 		self->stat_max_z = z;
	// 		self->stat_max_n_cell_addr = n_cell->addr;
	// 	}
	// 	++self->stat_cells_used;

	// 	//
	// 	// Sanity checks
	// 	//
	// 	lu__assert(self->stat_cells_used <= self->cells_size);
	// 	lu__assert(self->stat_max_z < self->d);
	// }

	// static inline void lu_s_column__find_n_cell(
	// 	Lu_S_Column self, 
	// 	union lu_n_addr addr, 
	// 	Lu_N_Cell* p_n_cell
	// )
	// {
	// 	Lu_N_Cell n_cell = lu_s_column__get_cell_by_ix(self, addr.cell_ix);

	// 	// Make sure everything is correct
	// 	lu__assert(lu_n_addr__is_eq(&n_cell->addr, &addr));

	// 	*p_n_cell = n_cell;
	// }

	// static inline void lu_s_column__print_net_stats(Lu_S_Column self)
	// {
	// 	if (lu_n_addr__is_present(&self->stat_max_n_cell_addr))
	// 	{
	// 		lu__debug(
	// 			"[%ld, %ld] cells: %ld/%ld, max_z: %ld/%ld, max_cell: %ld, links: %ld/%ld",
	// 			self->x,
	// 			self->y,
	// 			self->stat_cells_used,
	// 			self->cells_size,
	// 			self->stat_max_z,
	// 			self->d,
	// 			self->stat_max_n_cell_addr.cell_ix,
	// 			lu_n_link_mem__get_links_count(&self->link_mem),
	// 			lu_n_link_mem__get_links_size(&self->link_mem)
	// 		);
	// 	}
	// 	else
	// 	{
	// 		lu__debug(
	// 			"[%ld, %ld] cells: %ld/%ld, max_z: %ld/%ld, max_cell: NA, links: %ld/%ld",
	// 			self->x,
	// 			self->y,
	// 			self->stat_cells_used,
	// 			self->cells_size,
	// 			self->stat_max_z,
	// 			self->d,
	// 			lu_n_link_mem__get_links_count(&self->link_mem),
	// 			lu_n_link_mem__get_links_size(&self->link_mem)
	// 		);
	// 	}
	// }

	// static inline void lu_s_column__print_distribution_symbols(Lu_S_Column self, lu_size blocks_count)
	// {
	// 	lu__assert(self);
	// 	lu__assert(blocks_count > 0);	

	// 	lu_size per_block = self->h / blocks_count;

	// 	lu__debug("]");
	// 	lu_size i;
	// 	lu_size curr_block = 0;
	// 	lu_size ix;
	// 	Lu_N_Cell n_cell;
	// 	lu_bool cell_used;

	// 	for (curr_block = 0; curr_block < blocks_count; curr_block++)
	// 	{
	// 		cell_used = false;
	// 		for (i = 0; i < per_block; i++)
	// 		{
	// 			ix = curr_block * per_block + i;
	// 			if (ix >= self->cells_size) break;

	// 			n_cell = &self->cells[ix];

	// 			if (!lu_n_cell__is_blank(n_cell))
	// 			{
	// 				cell_used = true;
	// 				break;
	// 			}

	// 		}

	// 		if (cell_used) lu__debug("█");
	// 		else lu__debug(" ");
	// 	}

	// 	lu__debug("[");

	// }

	// static inline void lu_s_column__print_distribution_stats(Lu_S_Column self, lu_size blocks_count)
	// {
	// 	lu__assert(self);
	// 	lu__assert(blocks_count > 0);	

	// 	lu_size per_block = self->h / blocks_count;

	// 	lu__debug("[");
	// 	lu_size i;
	// 	lu_size curr_block = 0;
	// 	lu_size ix;
	// 	Lu_N_Cell n_cell;
	// 	lu_size count_per_block;

	// 	for (curr_block = 0; curr_block < blocks_count; curr_block++)
	// 	{
	// 		count_per_block = 0;
	// 		for (i = 0; i < per_block; i++)
	// 		{
	// 			ix = curr_block * per_block + i;
	// 			if (ix >= self->cells_size) break;

	// 			n_cell = &self->cells[ix];

	// 			if (!lu_n_cell__is_blank(n_cell))
	// 			{
	// 				++count_per_block;
	// 			}

	// 		}

	// 		lu__debug("%ld", count_per_block);

	// 		if (curr_block + 1 < blocks_count)
	// 			lu__debug(",");
	// 	}

	// 	lu__debug("]");

	// }

	// static inline void lu_s_column__collect_net_stats(Lu_S_Column self, Lu_N_Table_Net_Stats ts)
	// {
	// 	++ts->column_count;

	// 	if (self->stat_cells_used < ts->cells_used_min) ts->cells_used_min = self->stat_cells_used;
	// 	ts->cells_used_mean += self->stat_cells_used;
	// 	if (self->stat_cells_used > ts->cells_used_max) ts->cells_used_max = self->stat_cells_used;
	// 	if (self->cells_size > ts->cells_size) ts->cells_size = self->cells_size;

	// 	ts->total_cells_count += self->stat_cells_used;
	// 	ts->total_cells_size += self->cells_size;

	// 	if (self->stat_max_z < ts->max_z_min) ts->max_z_min = self->stat_max_z;
	// 	ts->max_z_mean += self->stat_max_z;
	// 	if (self->stat_max_z > ts->max_z_max) ts->max_z_max = self->stat_max_z;
	// 	ts->d = self->d;

	// 	lu_size links_count = lu_n_link_mem__get_links_count(&self->link_mem);

	// 	if (links_count < ts->links_count_min) ts->links_count_min = links_count;
	// 	ts->links_count_mean += links_count;
	// 	if (links_count > ts->links_count_max) ts->links_count_max = links_count;

	// 	lu_size links_size = lu_n_link_mem__get_links_size(&self->link_mem);
	// 	if (links_size > ts->links_size) ts->links_size = links_size;

	// 	ts->total_links_count += links_count;
	// 	ts->total_links_size += links_size;
	// }

	// static inline void lu_s_column__print_mem_stats(Lu_S_Column self)
	// {
	// 	lu__debug("\nREALL n_col ");
	// 	lu_s_column__print_net_stats(self);
	// 	lu__debug(" ");
	// 	lu_s_layer_base__print_basic_info(lu_s_table__get_layer(self->s_table));
	// 	lu__debug(" ");
	// 	lu_s_column__print_distribution_stats(self, 10);
	// }


	// static Lu_N_Cell lu_s_column__create_or_find_n_cell_by_vp_children(
	// 	Lu_S_Column self, 
	// 	Lu_W_Cell_P* children, 
	// 	lu_size children_count
	// );

	// static Lu_N_Cell lu_s_column__create_or_find_n_cell_by_children(
	// 	Lu_S_Column self, 
	// 	Lu_W_Cell* children, 
	// 	lu_size children_count
	// );


///////////////////////////////////////////////////////////////////////////////
// Lu_S_Column
// 

	struct lu_s_column {
		Lu_Mem mem;
		Lu_S_Table s_table;

		union lu_n_addr col_addr;

		struct lu_n_cell* cells;
		lu_size cells_size;
		lu_size cells_count;
		lu_size free_count;

		// we can build indexes later to speed up save
		// whene hash => i where indexes[i] contains index to N_Cell in cells
		// that way we can avoid iterating (one below one above) to find our n_cell using hash
		// also this way we can FREE n_cells easily!
		// what if we get hash1 => 3 and hash2=>3, zvychayno my mozhemo zrobyty indexes 2d array
		// prychomu komirky v cells vydiliayutsia v poslidovnomu poriadku
		// yaksho komirka dlia hash1=>3 vydalena, my prosto poznachayemo yiyi yak vydalenu i 
		// pry nastupnomu save , mozhna she raz reuse it
		// pershyy layer budut counters?

		// lu_size* indexes; 

		struct lu_n_link_mem link_mem;

		//
		lu_size w_match_cells_size;

		//
		// Position, mostly for debugging
		//
		lu_size x;
		lu_size y;

		//
		// 
		//

		// pry save my mayemo tilky 4 neurona, nam ne potribno zberihaty nichosho
		// 
		// struct lu_w_save_processor* w_save_processor;

		// dlia w_match processor my zberihayemo vsi sho zbudylysia
		// ale ce poky sho ne oboviazkovo realizovuvaty
		// struct lu_w_match_processor* w_match_processor;
	};


	//
	// Constructors / Destructors
	// 

	static Lu_S_Column lu_s_column__init(
		Lu_S_Column self, 
		Lu_S_Table s_table,
		Lu_Mem mem, 
		lu_size cell_size, 
		lu_size area_ix,
		lu_size layer_ix, 
		lu_size column_ix,
		Lu_Config config,
		lu_size x,
		lu_size y
	);
	static void lu_s_column__deinit(Lu_S_Column self);


	//
	// Get
	//

	static inline Lu_N_Link_Mem lu_s_column__get_link_mem(Lu_S_Column self)
	{
		lu__debug_assert(self);

		return &self->link_mem;
	}

	static inline Lu_N_Cell lu_s_column__get_null_cell(Lu_S_Column self)
	{
		lu__debug_assert(self);

		return &self->cells[0];
	} 

	static inline Lu_N_Cell lu_s_column__get_cell_by_ix(Lu_S_Column self, lu_size cell_ix)
	{
		lu__assert(self);
		lu__assert(cell_ix < self->cells_size);

		return &self->cells[cell_ix];
	}

	static inline lu_size lu_s_column__get_column_ix(Lu_S_Column self)
	{
		return self->col_addr.column_ix;
	}

	static inline Lu_N_Cell lu_s_column__get_n_cell(Lu_S_Column self, union lu_n_addr n_addr)
	{
		lu__assert(n_addr.cell_ix < self->cells_count);

		return &self->cells[n_addr.cell_ix];
	}

	static inline lu_size lu_s_column__get_n_cell_count(Lu_S_Column self)
	{
		return self->cells_count - self->free_count;
	}

	static inline lu_size lu_s_column__get_n_cell_size(Lu_S_Column self)
	{
		return self->cells_size;
	}


	//
	// Methods
	//

	static inline void lu_s_column__realloc(Lu_S_Column self);

	static inline Lu_N_Cell lu_s_column__alloc_n_cell(Lu_S_Column self)
	{
		lu__assert(self);

		if (self->cells_count >= self->cells_size) return NULL;

		Lu_N_Cell n_cell = &self->cells[self->cells_count];

		++self->cells_count;

		return n_cell;
	}

	static inline void lu_s_column__free_n_cell(Lu_S_Column self, Lu_N_Cell n_cell)
	{
		lu__assert(self);

		//
		// We need to implement indexes to reuse n_cell memory correctly. 
		// For now, just increase counter
		++self->free_count;
	}

	static inline void lu_s_column__find_n_cell(
		Lu_S_Column self, 
		union lu_n_addr addr, 
		Lu_N_Cell* p_n_cell
	)
	{
		Lu_N_Cell n_cell = lu_s_column__get_cell_by_ix(self, addr.cell_ix);

		// Make sure everything is correct
		lu__assert(lu_n_addr__is_eq(&n_cell->addr, &addr));

		*p_n_cell = n_cell;
	}

	static inline void lu_s_column__print_net_stats(Lu_S_Column self)
	{
		lu__debug(
			"[%ld, %ld] cells: %ld/%ld, links: %ld/%ld",
			self->x,
			self->y,
			lu_s_column__get_n_cell_count(self),
			self->cells_size,
			lu_n_link_mem__get_links_count(&self->link_mem),
			lu_n_link_mem__get_links_size(&self->link_mem)
		);
	}

	static inline void lu_s_column__collect_net_stats(Lu_S_Column self, Lu_N_Table_Net_Stats ts)
	{
		++ts->column_count;

		lu_size cells_count = lu_s_column__get_n_cell_count(self); 
		lu_size cells_size = lu_s_column__get_n_cell_size(self);

		if (cells_count < ts->cells_used_min) ts->cells_used_min = cells_count;
		ts->cells_used_mean += cells_count;
		if (cells_count > ts->cells_used_max) ts->cells_used_max = cells_count;
		if (cells_size > ts->cells_size) ts->cells_size = cells_size;
		
		ts->total_cells_count += cells_count;
		ts->total_cells_size += cells_size;

		lu_size links_count = lu_n_link_mem__get_links_count(&self->link_mem);

		if (links_count < ts->links_count_min) ts->links_count_min = links_count;
		ts->links_count_mean += links_count;
		if (links_count > ts->links_count_max) ts->links_count_max = links_count;

		lu_size links_size = lu_n_link_mem__get_links_size(&self->link_mem);
		if (links_size > ts->links_size) ts->links_size = links_size;

		ts->total_links_count += links_count;
		ts->total_links_size += links_size;
	}

	static inline void lu_s_column__print_mem_stats(Lu_S_Column self)
	{
		lu__debug("\nREALL n_col ");
		lu_s_column__print_net_stats(self);
		lu__debug(" ");
		lu_s_layer_base__print_basic_info(lu_s_table__get_layer(self->s_table));
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_S_Table

	struct lu_s_table {
		Lu_Mem mem;
		Lu_S_Layer_Base layer;

		lu_size w;
		lu_size h;
		lu_size h_max;

		struct lu_s_column* columns;
		lu_size columns_size;
	};

	//
	// Constructors / Destructors
	//

	Lu_S_Table lu_s_table__init(
		Lu_S_Table self,
		Lu_Mem mem, 
		lu_size w, 
		lu_size h, 
		lu_size h_max, 
		Lu_Config config, 
		lu_size layer_ix,
		lu_size area_ix,
		Lu_S_Layer_Base layer
	);

 	void lu_s_table__deinit(Lu_S_Table self);

 	//
 	// Get
 	// 

 	static inline Lu_S_Column lu_s_table__get_column_by_ix(Lu_S_Table self, lu_size column_ix)
 	{
 		lu__assert(self);
 		lu__assert(column_ix < self->columns_size);

 		return &self->columns[column_ix];
 	}

 	static inline Lu_S_Column lu_s_table__get_s_column(Lu_S_Table self, lu_size x, lu_size y)
 	{
 		return lu_s_table__get_column_by_ix(self, lu_macro__xy_to_ix(x, y, self->w));
 	}

 	static inline Lu_S_Layer_Base lu_s_table__get_layer(Lu_S_Table self)
 	{
 		lu__assert(self);
 		return self->layer;
 	}

 	static inline lu_size lu_s_table__get_w(Lu_S_Table self) { return self->w; }
 	static inline lu_size lu_s_table__get_h(Lu_S_Table self) { return self->h; }

 	static inline Lu_N_Cell lu_s_table__get_n_cell(Lu_S_Table self, union lu_n_addr n_addr)
 	{
 		lu__assert(n_addr.column_ix < self->columns_size);

 		return lu_s_column__get_n_cell(&self->columns[n_addr.column_ix], n_addr);
 	}

 	//
 	// Methods
 	//

	////
	// Returns true if was able to expand
	static inline lu_bool lu_s_table__expand(Lu_S_Table self)
	{
		if (self->h + 1 >= self->h_max) return false;

		++self->h;

		return true;
	}

	static inline void lu_s_table__print_net_stats(Lu_S_Table self, Lu_S_Layer_Net_Stats layer_ns)
	{
		lu__assert(self);

		lu_size x;
		lu_size y;
		Lu_S_Column s_column;

		struct lu_s_table_net_stats ts;

		lu_s_table_stats__reset(&ts);

		for (y = 0; y < self->h_max; y++)
		{
			for (x = 0; x < self->w; x++)
			{
				s_column = lu_s_table__get_s_column(self, x, y);
				lu__assert(s_column);
				lu__assert(s_column->x == x);
				lu__assert(s_column->y == y);

				lu_s_column__collect_net_stats(s_column, &ts);
			}
		}

		lu__debug(
			"\n\t\tS_TABLE [%ldx%ld] cells: %ld/%ld, links: %ld/%ld",
 			self->w, 
 			self->h_max,
 			
 		// 	ts.cells_used_min,
			// ts.cells_used_mean / ts.column_count,
			// ts.cells_used_max,
			// ts.cells_size,

			ts.total_cells_count,
			ts.total_cells_size,

			// ts.max_z_min,
			// ts.max_z_mean / ts.column_count,
			// ts.max_z_max,
			// ts.d,

			// ts.links_count_min,
			// ts.links_count_mean / ts.column_count,
			// ts.links_count_max,
			// ts.links_size,

			ts.total_links_count,
			ts.total_links_size
		);
 	
 		lu_s_layer_net_stats__collect(layer_ns, &ts);
	}

	static inline void lu_s_table__get_net_stats(Lu_S_Table self, Lu_S_Layer_Net_Stats layer_ns)
	{
		lu__assert(self);

		lu_size x;
		lu_size y;
		Lu_S_Column s_column;

		struct lu_s_table_net_stats ts;

		lu_s_table_stats__reset(&ts);

		for (y = 0; y < self->h_max; y++)
		{
			for (x = 0; x < self->w; x++)
			{
				s_column = lu_s_table__get_s_column(self, x, y);
				lu__assert(s_column);
				lu__assert(s_column->x == x);
				lu__assert(s_column->y == y);

				lu_s_column__collect_net_stats(s_column, &ts);
			}
		}
		
 		lu_s_layer_net_stats__collect(layer_ns, &ts);
	}

