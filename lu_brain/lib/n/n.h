/**
	Copyright © 2022 Oleh Ihorovych Novosad 

	n_tables are always "3d"
*/

///////////////////////////////////////////////////////////////////////////////
// 
	typedef struct lu_s_layer_base* Lu_S_Layer_Base;
	static inline void lu_s_layer_base__print_basic_info(Lu_S_Layer_Base self);


	static inline Lu_N_Link lu_n_link_mem__link_alloc(Lu_N_Link_Mem self);
	static inline union lu_n_link_addr lu_n_link_mem__get_addr(Lu_N_Link_Mem self, Lu_N_Link link);
	static inline Lu_N_Link lu_n_link_mem__get_link(Lu_N_Link_Mem self, union lu_n_link_addr addr);
	static inline Lu_N_Link_Mem lu_n_column__get_link_mem(Lu_N_Column self);

	typedef union lu_la_addr* Lu_La_Addr;
	typedef struct lu_la_link* Lu_La_Link;
	typedef struct lu_la_link_mem* Lu_La_Link_Mem;

	static inline Lu_La_Link lu_la_link_mem__link_alloc(Lu_La_Link_Mem self);
	static inline union lu_la_link_addr lu_la_link_mem__get_addr(Lu_La_Link_Mem self, Lu_La_Link link);
	static inline Lu_La_Link lu_la_link__init(Lu_La_Link self, union lu_la_addr la_addr, union lu_la_link_addr next);

	static inline union lu_n_link_addr lu_n_link_addr__prepend(union lu_n_link_addr self, Lu_N_Link_Mem link_mem, union lu_n_addr addr);

	static inline Lu_S_Layer_Base lu_n_table__get_layer(Lu_N_Table self);

///////////////////////////////////////////////////////////////////////////////
// Lu_N_Link_Addr
//

	////
	// We need it because we want to avoid using Lu_N_Link pointers because 
	// Lu_N_Link_Mem can do reallocate, instead we want to have index insied of Lu_N_Link_Mem
	// which stays the same independently of real memory position
	union lu_n_link_addr {
		lu_size value;
	};

	// NULL addr
	extern union lu_n_link_addr LU_N_LINK_ADDR__NULL;

	static inline lu_bool lu_n_link_addr__is_blank(Lu_N_Link_Addr self)
	{
		return self->value == LU_N_LINK_ADDR__NULL.value;
	}

	static inline lu_bool lu_n_link_addr__is_present(Lu_N_Link_Addr self)
	{
		return self->value != LU_N_LINK_ADDR__NULL.value;
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_N_Link
//

	struct lu_n_link {
		// We cannot use pointer because of reallocations
		union lu_n_addr cell_addr;

		union lu_n_link_addr next;
	};

	static inline lu_bool lu_n_link__eq(Lu_N_Link self, const union lu_n_addr* b, Lu_N_Link_Mem link_mem)
	{
		while (1)
		{
			if (!self || self->cell_addr.value != (*b).value)
			{
				return false;
			}

			if (self->cell_addr.value == 0 || (*b).value == 0) break;

			self = lu_n_link_mem__get_link(link_mem, self->next);
			++b;
		}	
		
		return true;
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_N_Link_Mem
//

	struct lu_n_link_mem {
		Lu_Mem_Table mem_table;
	};

	//
	// Constructors / Destructors
	// 

	Lu_N_Link_Mem lu_n_link_mem__init(Lu_N_Link_Mem self, Lu_Mem mem, lu_size size);
	void lu_n_link_mem__deinit(Lu_N_Link_Mem self);
 
 	//
 	// Get
 	//

	static inline lu_size lu_n_link_mem__get_links_count(Lu_N_Link_Mem self)
	{
		lu__assert(self);
		lu__assert(self->mem_table);

		return lu_mem_table__records_count(self->mem_table);
	}

	static inline lu_size lu_n_link_mem__get_links_size(Lu_N_Link_Mem self)
	{
		lu__assert(self);
		lu__assert(self->mem_table);

		return lu_mem_table__records_size(self->mem_table);
	}

	////
	// Important(!!): returns NULL for addr.value == 0
	static inline Lu_N_Link lu_n_link_mem__get_link(Lu_N_Link_Mem self, union lu_n_link_addr addr)
	{
		lu__debug_assert(self);
		lu__debug_assert(self->mem_table);

		if (addr.value == 0) return NULL;

		return (Lu_N_Link) lu_mem_table__get(self->mem_table, addr.value);
	}

	////
	// 
	static inline union lu_n_link_addr lu_n_link_mem__get_addr(Lu_N_Link_Mem self, Lu_N_Link link)
	{
		lu__debug_assert(self);
		lu__debug_assert(link);

		union lu_n_link_addr addr;

		addr.value = lu_mem_table__record_ix(self->mem_table, (lu_p_byte) link);

		return addr;
	}

	//
	// Methods
	//

	static inline Lu_N_Link lu_n_link_mem__link_alloc(Lu_N_Link_Mem self)
	{
		lu__debug_assert(self);

		lu_p_byte record = lu_mem_record__alloc(self->mem_table);

		if (!record)
		{
			self->mem_table = lu_mem_table__realloc(
				self->mem_table, 
				lu_mem_table__records_count(self->mem_table) * 2
			); 
			lu__alloc_assert(self->mem_table);

			lu__mem_debug("\n (!) n_link_mem realloc");

			record = lu_mem_record__alloc(self->mem_table);
			lu__assert(record);
		}

		return (Lu_N_Link) record;
	}



///////////////////////////////////////////////////////////////////////////////
// Lu_N_Pos 

	struct lu_n_pos {
		lu_size x;
		lu_size y;
	};

	static inline lu_size lu_n_pos__to_column_ix(Lu_N_Pos self, lu_size w)
	{
		lu__debug_assert(self->x < w);
		return self->y * w + self->x;
	}

	static inline struct lu_n_pos lu_n_pos__from_column_ix(lu_size column_ix, lu_size w)
	{
		struct lu_n_pos pos;

		pos.y =  column_ix / w;
		pos.x = column_ix % w;

		return pos;
	}

	struct lu_n_pos_3d {
		lu_size x;
		lu_size y;
		lu_size z;
	};

	static inline lu_size lu_n_pos_3d__to_column_ix(Lu_N_Pos_3d self, lu_size w, lu_size h)
	{
		lu__debug_assert(self->x < w);
		lu__debug_assert(self->y < h);

		return self->z * w * h + self->y * w + self->x;
	}

	static inline struct lu_n_pos_3d lu_n_pos_3d__from_column_ix(lu_size column_ix, lu_size w, lu_size h)
	{
		struct lu_n_pos_3d pos;

		lu_size wh = w * h;

		pos.z = column_ix / wh;
		pos.y = (column_ix - (pos.z * wh)) / w;
		pos.x = column_ix % w;

		return pos;
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_N_Str
//

	static inline lu_bool lu_n_str__eq(const union lu_n_addr* a, const union lu_n_addr* b)
	{
		while (1)
		{
			if ((*a).value != (*b).value)
			{
				return false;
			}

			if ((*a).value == 0 || (*b).value == 0) break;

			++a;
			++b;
		}	
		
		return true;
	}

	////
	// (!) This method (intentionally!) doesn't check if <dest> has enough space for <src>
	static inline void lu_n_str__copy(union lu_n_addr* dest, const union lu_n_addr* src)
	{
		while((*src).value)
		{
			*dest = *src;
			++src;
			++dest;
		};

		(*dest).value = 0;
	}

	static inline void lu_n_str__print(union lu_n_addr* s)
	{
		lu__debug("\n N_STRING: {");
		union lu_n_addr *p = s;

		while((*p).value)
		{
			if (p != s) lu__debug(", ");
			lu_n_addr__print(&(*p));
			++p;
		} 
		if (p==s) lu__debug("0");
		else lu__debug(", 0");

		lu__debug("}");
	}

	static inline lu_size lu_n_str__hash_comb(const union lu_n_addr* p)
	{
		lu_size p_reg = 0;
		while((*p).value)
		{
			p_reg = lu_calc__hash_comb(p_reg, (*p).value);
			++p;
		}

		return p_reg;
	}


///////////////////////////////////////////////////////////////////////////////
// Lu_N_Cell_VP

	struct lu_n_cell_vp { 
		// addr can be removed later to save memory, but useful for testing and debugging
		// can be wrapped in #ifdef LU__DEBUG
		union lu_n_addr addr; 

		lu_value value; 
		lu_size x;
		lu_size y;
		lu_size z;  // if z = 0, this cell is "NULL" cell

		union lu_n_link_addr parents;
	};

	//
	// Constructors / Destructors
	//

	static inline void lu_n_cell_vp__null_init(Lu_N_Cell_VP self)
	{
		self->addr.value = 0;

		self->value = 0;
		self->x = 0;
		self->y = 0;
		self->z = 0;
		self->parents = LU_N_LINK_ADDR__NULL;
	}

	static inline Lu_N_Cell_VP lu_n_cell_vp__init(
		Lu_N_Cell_VP self, 
		lu_value value,
		lu_size x,
		lu_size y,
		lu_size z,
		union lu_n_addr addr
	)
	{
		self->addr = addr;

		self->value = value;
		self->x = x;
		self->y = y;
		self->z = z; 
		self->parents = LU_N_LINK_ADDR__NULL;

		return self;
	}

	static inline void lu_n_cell_vp__deinit(Lu_N_Cell_VP self, Lu_Mem mem)
	{

	}

	//
	// Get
	//

	static inline Lu_N_Addr lu_n_cell_vp__get_cell_addr(Lu_N_Cell_VP self)
	{
		lu__debug_assert(self);

		return &self->addr;
	}

	//
	// Methods
	// 

	static inline Lu_N_Link lu_n_cell_vp__parent_prepend(Lu_N_Cell_VP self, Lu_N_Link_Mem link_mem, union lu_n_addr addr)
	{
		// new child link
		Lu_N_Link n_link = lu_n_link_mem__link_alloc(link_mem);
		lu__assert(n_link);

		n_link->next = self->parents;

		n_link->cell_addr = addr;

		self->parents = lu_n_link_mem__get_addr(link_mem, n_link);

		lu__assert(lu_n_link_addr__is_present(&self->parents));

		return n_link;
	}


///////////////////////////////////////////////////////////////////////////////
// Lu_N_Column_Comp
//

	struct lu_n_column_comp {
		Lu_Mem mem;

		lu_size column_ix;

		struct lu_n_cell_vp* cells;
		lu_size cells_size;

		struct lu_n_link_mem link_mem;

		lu_size w_match_cells_size;
	};

	static Lu_N_Column_Comp lu_n_column_comp__init(
		Lu_N_Column_Comp self, 
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

	static void lu_n_column_comp__deinit(Lu_N_Column_Comp self);

	static inline Lu_N_Cell_VP lu_n_column_comp__get_cell(Lu_N_Column_Comp self, lu_size z)
	{
		lu__debug_assert(self);
		lu__debug_assert(z < self->cells_size);

		return &self->cells[z];
	}


///////////////////////////////////////////////////////////////////////////////
// Lu_N_Table_Comp
//

	struct lu_n_table_comp {
		Lu_Mem mem;
		lu_size w;
		lu_size h;
		lu_size d;
		lu_size wh;

		struct lu_n_column_comp* columns;
	};

	static Lu_N_Table_Comp lu_n_table_comp__create(
		Lu_Config config, 
		Lu_Comp_Calc comp_calc, 
		lu_size width, 
		lu_size height, 
		lu_size depth, 
		lu_size layer_ix,
		lu_size area_ix
	);

	static void lu_n_table_comp__destroy(Lu_N_Table_Comp self);

	static inline lu_size lu_n_table_comp__calc_cell_ix(Lu_N_Table_Comp self, lu_size x, lu_size y, lu_size z)
	{
		return z * self->wh + y * self->w + x;
	}

	static inline Lu_N_Column_Comp lu_n_table_comp__get_column(Lu_N_Table_Comp self, lu_size x, lu_size y)
	{
		lu__debug_assert(self);

		lu_size column_ix = y * self->w + x;

		lu__debug_assert(column_ix < self->wh);

		return &self->columns[column_ix];
	}

	static inline Lu_N_Cell_VP lu_n_table_comp__get_cell(Lu_N_Table_Comp self, lu_size x, lu_size y, lu_size z)
	{
		Lu_N_Column_Comp column = lu_n_table_comp__get_column(self, x, y);

		return lu_n_column_comp__get_cell(column, z);
	}


///////////////////////////////////////////////////////////////////////////////
// Lu_N_Cell
//

	////
	// TODO: Need to replace this later with lu_mem_table , with dynamic w_cells size and access to list of w_cells
	// using lu_n_cell.addr
	#define LU_N_CELL__W_MATCH_CELLS_SIZE 1

	struct lu_n_cell { 
		union lu_n_addr addr; 

		union lu_la_link_addr labels;

		union lu_n_link_addr tl;
		union lu_n_link_addr tr;
		union lu_n_link_addr bl;
		union lu_n_link_addr br;

		union lu_n_link_addr children; 

		lu_value default_sig;
		
		union lu_w_match_addr w_cells[LU_N_CELL__W_MATCH_CELLS_SIZE];
	};

	//
	// Constructors / Destructors
	//

	static inline Lu_N_Cell lu_n_cell__init(
		Lu_N_Cell self, 
		lu_size cell_ix, 
		lu_size column_ix, 
		lu_size layer_ix, 
		lu_size area_ix,
		Lu_Mem mem,
		lu_size w_cells_size
	)
	{
		lu__debug_assert(self);
		lu__debug_assert(w_cells_size > 0);
		lu__debug_assert(area_ix >= LU_N_AREA__SPECIAL_AREA_SKIP);

		lu_n_addr__init(&self->addr, cell_ix, column_ix, layer_ix, area_ix);

		lu__debug_assert(self->addr.cell_ix == cell_ix);
		lu__debug_assert(self->addr.column_ix == column_ix);
		lu__debug_assert(self->addr.layer_ix == layer_ix);
		lu__debug_assert(self->addr.area_ix == area_ix);

		self->labels = LU_LA_LINK_ADDR__NULL;
		self->tl = LU_N_LINK_ADDR__NULL;
		self->tr = LU_N_LINK_ADDR__NULL;
		self->bl = LU_N_LINK_ADDR__NULL;
		self->br = LU_N_LINK_ADDR__NULL;
		self->children = LU_N_LINK_ADDR__NULL; 
		self->default_sig = 0;

		lu_w_match_addr__reset(&self->w_cells[0]);
		lu_w_match_addr__reset(&self->w_cells[1]);

		return self;
	}

	static inline Lu_N_Cell lu_n_cell__deinit(
		Lu_N_Cell self,
		Lu_Mem mem
	)
	{
		lu__assert(self);
		lu__assert(mem);
		lu__assert(self->w_cells);

		lu__debug_assert(self);

		lu_n_addr__reset(&self->addr);

		// lu_mem__free(mem, (lu_p_byte) self->w_cells);

		// self->w_cells = NULL;

		return self;
	}

	//
	// Get / Set
	//

	static inline lu_value lu_n_cell__get_default_sig(Lu_N_Cell self)
	{
		return self->default_sig;
	}

	static inline union lu_w_match_addr lu_n_cell__get_w_match_cell_addr(Lu_N_Cell self, lu_size wave_ix)
	{
		return self->w_cells[wave_ix];
	}

	static inline void lu_n_cell__set_w_mach_cell_addr(Lu_N_Cell self, lu_size wave_ix, union lu_w_match_addr w_addr)
	{
		self->w_cells[wave_ix] = w_addr;
	}

	static inline Lu_N_Addr lu_n_cell__get_cell_addr(Lu_N_Cell self)
	{
		lu__debug_assert(self);

		return &self->addr;
	}

	//
	// Is
	//

	static inline lu_bool lu_n_cell__is_blank(Lu_N_Cell self)
	{
		lu__debug_assert(self);

		return lu_n_link_addr__is_blank(&self->children);
	}

	static inline lu_bool lu_n_cell__is_n_column_null_cell(Lu_N_Cell self)
	{
		lu__debug_assert(self);

		return self->addr.cell_ix == 0;
	}

	//
	// Methods
	//

	static inline Lu_N_Link lu_n_cell__children_prepend(Lu_N_Cell self, Lu_N_Link_Mem link_mem, union lu_n_addr addr)
	{
		// New child link
		Lu_N_Link n_link = lu_n_link_mem__link_alloc(link_mem);
		lu__assert(n_link);

		n_link->next = self->children;

		n_link->cell_addr = addr;

		self->children = lu_n_link_mem__get_addr(link_mem, n_link);

		// For every children we have plus sig potential, that should be overcome by child signal
		++self->default_sig;

		return n_link;
	}	

	static inline void lu_n_cell__vp_save( 
		Lu_N_Cell self, 
		Lu_W_Cell_P* children, 
		lu_size children_count,
		Lu_N_Link_Mem link_mem
	)
	{
		lu__assert(self);
		lu__assert(children); // we don't even save NULL cell

		lu_size i;
		lu_size ix;

		Lu_W_Cell_P w_cell = NULL;

		// We dont need to use default_sig because all links present (even if they are to NULL cells)

		for (i = 0; i < children_count; i++)
		{
			ix = children_count - i - 1;

			w_cell = children[ix]; 
			lu__assert(w_cell);
			lu__debug_assert(w_cell->n_cell);

			// We create links even if sig = 0.
			// We dont create links only if all children are NULL (which means we will not get here).

			lu_n_cell__children_prepend(self, link_mem, w_cell->n_cell->addr);

			lu_n_cell_vp__parent_prepend(w_cell->n_cell, &w_cell->n_column->link_mem, self->addr);
		}
	}

	static inline void lu_n_cell__save( 
		Lu_N_Cell self, 
		Lu_W_Cell* children, 
		lu_size children_count,
		Lu_N_Link_Mem link_mem
	)
	{
		lu__assert(self);
		lu__assert(children); // we don't even save NULL cell

		lu_size i;
		lu_size ix;

		Lu_W_Cell w_cell = NULL;
		Lu_N_Cell n_cell;
		Lu_N_Column n_column;

		for (i = 0; i < children_count; i++)
		{
			ix = children_count - i - 1;

			w_cell = children[ix]; 
			
			// Out of bounds situation
			if (w_cell == NULL) continue;
			
			n_cell = w_cell->n_cell;
			lu__assert(n_cell); // should never happen, it should be "null" cell or normal cell

			n_column = w_cell->n_column;
			lu__assert(n_column);
	
			lu_n_cell__children_prepend(self, link_mem, n_cell->addr);

			switch(i)
			{
				case 0:
					n_cell->tl = lu_n_link_addr__prepend(n_cell->tl, lu_n_column__get_link_mem(n_column), self->addr);
					break;
				case 1:
					n_cell->tr = lu_n_link_addr__prepend(n_cell->tr, lu_n_column__get_link_mem(n_column), self->addr);
					break;
				case 2:
					n_cell->bl = lu_n_link_addr__prepend(n_cell->bl, lu_n_column__get_link_mem(n_column), self->addr);
					break;
				case 3:
					n_cell->br = lu_n_link_addr__prepend(n_cell->br, lu_n_column__get_link_mem(n_column), self->addr);
					break;
				default:
					lu__assert(false);
			}
		}

		// lu__debug("\n lu_n_cell__save()");
	}

	static inline void lu_n_cell__prepend_label(
		Lu_N_Cell self, 
		union lu_la_addr la_addr, 
		Lu_La_Link_Mem la_link_mem
	)
	{
		// new child link
		Lu_La_Link la_link = lu_la_link_mem__link_alloc(la_link_mem);
		lu__assert(la_link);

		lu_la_link__init(
			la_link, 
			la_addr,
			self->labels
		);

		self->labels = lu_la_link_mem__get_addr(la_link_mem, la_link);
		lu__assert(lu_la_link_addr__is_present(&self->labels));
	}

	static inline Lu_W_Match_Cell lu_n_cell__get_and_reset_match_cell(
		Lu_N_Cell self,
		struct lu_block_id block_id,
		lu_size wave_ix,
		Lu_W_Match_Cell_Mem match_cell_mem
	)
	{
		union lu_w_match_addr match_addr = lu_n_cell__get_w_match_cell_addr(self, wave_ix);

		Lu_W_Match_Cell match_cell = NULL;
		if (lu_w_match_addr__is_blank(&match_addr))
		{
			match_cell = lu_w_match_cell_mem__cell_alloc(match_cell_mem);
			match_addr = lu_w_match_cell_mem__get_addr(match_cell_mem, match_cell);

			lu_n_cell__set_w_mach_cell_addr(self, wave_ix, match_addr);

			lu_w_match_cell__init(match_cell, block_id);
			
			return match_cell;
		}

		match_cell = lu_w_match_cell_mem__get_cell(match_cell_mem, match_addr);
		lu__assert(match_cell);

		if (lu_block_id__is_not_eq(&match_cell->block_id, &block_id))
		{
			// reset
			lu_w_match_cell__init(match_cell, block_id);
		}

		return match_cell;
	}


///////////////////////////////////////////////////////////////////////////////
// Lu_N_Link_Addr
//

	static inline lu_bool lu_n_link_addr__is_vp_eq(
		union lu_n_link_addr self, 
		Lu_W_Cell_P* children, 
		lu_size children_count, 
		Lu_N_Link_Mem link_mem
	)
	{
		lu__debug_assert(children);
		lu__debug_assert(children[0]);
		lu__debug_assert(children_count > 0);
		lu__debug_assert(link_mem);

		if (lu_n_link_addr__is_blank(&self)) return false;

		Lu_N_Link n_link;
		Lu_W_Cell_P w_cell;
		for(lu_size i = 0; i < children_count; i++)
		{
			if (lu_n_link_addr__is_blank(&self)) return false;

			w_cell = children[i];
			lu__debug_assert(w_cell);
			lu__debug_assert(w_cell->n_cell);

			n_link = lu_n_link_mem__get_link(link_mem, self);
			if (!n_link) return false;

			if (!lu_n_addr__is_eq(&n_link->cell_addr, lu_n_cell_vp__get_cell_addr(w_cell->n_cell))) return false;

			self = n_link->next;
		}

		return true;
	}

	static inline lu_bool lu_n_link_addr__is_eq(
		union lu_n_link_addr self, 
		Lu_W_Cell* children, 
		lu_size children_count, 
		Lu_N_Link_Mem link_mem
	)
	{
		lu__debug_assert(children);
		lu__debug_assert(children[0]);
		lu__debug_assert(children_count > 0);
		lu__debug_assert(link_mem);

		if (lu_n_link_addr__is_blank(&self)) return false;

		Lu_N_Link n_link;
		Lu_W_Cell w_cell;
		for(lu_size i = 0; i < children_count; i++)
		{
			if (lu_n_link_addr__is_blank(&self)) return false;

			w_cell = children[i];
			lu__debug_assert(w_cell);
			lu__debug_assert(w_cell->n_cell);

			n_link = lu_n_link_mem__get_link(link_mem, self);
			if (!n_link) return false;

			if (!lu_n_addr__is_eq(&n_link->cell_addr, lu_n_cell__get_cell_addr(w_cell->n_cell))) return false;

			self = n_link->next;
		}

		return true;
	}

	static inline union lu_n_link_addr lu_n_link_addr__prepend(union lu_n_link_addr self, Lu_N_Link_Mem link_mem, union lu_n_addr addr)
	{
		// new child link
		Lu_N_Link n_link = lu_n_link_mem__link_alloc(link_mem);
		lu__assert(n_link);

		n_link->next = self;

		n_link->cell_addr = addr;

		return lu_n_link_mem__get_addr(link_mem, n_link);
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_N_Col
// 

	struct lu_n_col {
		Lu_Mem mem;
		Lu_N_Table n_table;

		lu_size column_ix;

		struct lu_n_cell* cells;
		lu_size cells_size;
		lu_size cells_count;

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

		struct lu_w_save_proc* w_save_procs;
		struct lu_w_match_proc* w_match_procs;
	};


	//
	// Constructors / Destructors
	// 

	static Lu_N_Col lu_n_col__init(
		Lu_N_Col self, 
		Lu_N_Table n_table,
		Lu_Mem mem, 
		lu_size cell_size, 
		lu_size area_ix,
		lu_size layer_ix, 
		lu_size column_ix,
		Lu_Config config,
		lu_size x,
		lu_size y
	);
	static void lu_n_col__deinit(Lu_N_Col self);


	//
	// Get
	//

	static inline Lu_N_Link_Mem lu_n_col__get_link_mem(Lu_N_Col self)
	{
		lu__debug_assert(self);

		return &self->link_mem;
	}

	static inline Lu_N_Cell lu_n_col__get_null_cell(Lu_N_Col self)
	{
		lu__debug_assert(self);

		return &self->cells[0];
	} 

	static inline Lu_N_Cell lu_n_col__get_cell_by_ix(Lu_N_Col self, lu_size cell_ix)
	{
		lu__assert(self);
		lu__assert(cell_ix < self->cells_size);

		return &self->cells[cell_ix];
	}

	//
	// Methods
	//


	static void lu_n_col__realloc(Lu_N_Col self);


	static inline void lu_n_col__find_n_cell(
		Lu_N_Col self, 
		union lu_n_addr addr, 
		Lu_N_Cell* p_n_cell
	)
	{
		Lu_N_Cell n_cell = lu_n_col__get_cell_by_ix(self, addr.cell_ix);

		// Make sure everything is correct
		lu__assert(lu_n_addr__is_eq(&n_cell->addr, &addr));

		*p_n_cell = n_cell;
	}

	static inline void lu_n_col__print_net_stats(Lu_N_Col self)
	{
		lu__debug(
			"[%ld, %ld] cells: %ld/%ld, links: %ld/%ld",
			self->x,
			self->y,
			self->cells_count,
			self->cells_size,
			lu_n_link_mem__get_links_count(&self->link_mem),
			lu_n_link_mem__get_links_size(&self->link_mem)
		);
	}

	static inline void lu_n_col__collect_net_stats(Lu_N_Col self, Lu_N_Table_Net_Stats ts)
	{
		++ts->column_count;

		if (self->cells_count < ts->cells_used_min) ts->cells_used_min = self->cells_count;
		ts->cells_used_mean += self->cells_count;
		if (self->cells_count > ts->cells_used_max) ts->cells_used_max = self->cells_count;
		if (self->cells_size > ts->cells_size) ts->cells_size = self->cells_size;
		
		ts->total_cells_count += self->cells_count;
		ts->total_cells_size += self->cells_size;


		lu_size links_count = lu_n_link_mem__get_links_count(&self->link_mem);

		if (links_count < ts->links_count_min) ts->links_count_min = links_count;
		ts->links_count_mean += links_count;
		if (links_count > ts->links_count_max) ts->links_count_max = links_count;

		lu_size links_size = lu_n_link_mem__get_links_size(&self->link_mem);
		if (links_size > ts->links_size) ts->links_size = links_size;

		ts->total_links_count += links_count;
		ts->total_links_size += links_size;

	}

	static inline void lu_n_col__print_mem_stats(Lu_N_Col self)
	{
		lu__debug("\nREALL n_col ");
		lu_n_col__print_net_stats(self);
		lu__debug(" ");
		lu_s_layer_base__print_basic_info(lu_n_table__get_layer(self->n_table));
	}


	static Lu_N_Cell lu_n_col__save_with_vp_children(
		Lu_N_Col self, 
		Lu_W_Cell_P* children, 
		lu_size children_count
	);

	static Lu_N_Cell lu_n_col__save_with_children(
		Lu_N_Col self, 
		Lu_W_Cell* children, 
		lu_size children_count
	);

///////////////////////////////////////////////////////////////////////////////
// Lu_N_Column
// 
	
	struct lu_n_column {
		Lu_Mem mem;

		Lu_N_Table n_table;

		lu_size column_ix;

		lu_size h;
		lu_size d;

		struct lu_n_cell* cells;
		lu_size cells_size;

		struct lu_n_link_mem link_mem;

		lu_size w_match_cells_size;

		//
		// Position, mostly for debugging
		//
		lu_size x;
		lu_size y;

		//
		// Stats
		// 

		lu_size stat_cells_used;
		lu_size stat_max_z;

		// We have to use cell addr here, because pointer to Lu_N_Cell gets invalidated when reallocated
		union lu_n_addr stat_max_n_cell_addr;

	};

	//
	// Constructors / Destructors
	// 

	static Lu_N_Column lu_n_column__init(
		Lu_N_Column self, 
		Lu_N_Table n_table,
		Lu_Mem mem, 
		lu_size h, 
		lu_size d, 
		lu_size area_ix,
		lu_size layer_ix, 
		lu_size column_ix,
		Lu_Config config,
		lu_size x,
		lu_size y
	);
	static void lu_n_column__deinit(Lu_N_Column self);


	//
	// Get
	//

	static inline Lu_N_Link_Mem lu_n_column__get_link_mem(Lu_N_Column self)
	{
		lu__debug_assert(self);

		return &self->link_mem;
	}

	static inline Lu_N_Cell lu_n_column__get_null_cell(Lu_N_Column self)
	{
		lu__debug_assert(self);

		return &self->cells[0];
	} 

	static inline Lu_N_Cell lu_n_column__get_cell_by_ix(Lu_N_Column self, lu_size cell_ix)
	{
		lu__assert(self);
		lu__assert(cell_ix < self->cells_size);

		return &self->cells[cell_ix];
	}

	static inline Lu_N_Cell lu_n_column__get_cell(Lu_N_Column self, lu_size z, lu_size ix)
	{
		return lu_n_column__get_cell_by_ix(self, z * self->h + ix);
	}

	//
	// Methods
	//

	static inline lu_size lu_n_column__hash_to_ix(Lu_N_Column self, lu_size hash)
	{
		return hash % self->h; 
	}

	static inline lu_size lu_n_column__vp_children_to_ix(
		Lu_N_Column self, 
		Lu_W_Cell_P* children, 
		lu_size children_count
	)
	{
		return lu_n_column__hash_to_ix(self, lu_w_cell_p__children_hash_comp(children, children_count));
	} 

	static inline lu_size lu_n_column__children_to_ix(
		Lu_N_Column self, 
		Lu_W_Cell* children, 
		lu_size children_count
	)
	{
		return lu_n_column__hash_to_ix(self, lu_w_cell__children_hash_comp(children, children_count));
	}

	static void lu_n_column__realloc(Lu_N_Column self);


	static inline void lu_n_column__increase_stats(Lu_N_Column self, lu_size z, Lu_N_Cell n_cell)
	{
		lu__assert(self);
		lu__assert(n_cell);
		lu__assert(z < self->d);

		if (z > self->stat_max_z) 
		{

			self->stat_max_z = z;
			self->stat_max_n_cell_addr = n_cell->addr;
		}
		++self->stat_cells_used;

		//
		// Sanity checks
		//
		lu__assert(self->stat_cells_used <= self->cells_size);
		lu__assert(self->stat_max_z < self->d);
	}

	static inline void lu_n_column__find_n_cell(
		Lu_N_Column self, 
		union lu_n_addr addr, 
		Lu_N_Cell* p_n_cell
	)
	{
		Lu_N_Cell n_cell = lu_n_column__get_cell_by_ix(self, addr.cell_ix);

		// Make sure everything is correct
		lu__assert(lu_n_addr__is_eq(&n_cell->addr, &addr));

		*p_n_cell = n_cell;
	}

	static inline void lu_n_column__print_net_stats(Lu_N_Column self)
	{
		if (lu_n_addr__is_present(&self->stat_max_n_cell_addr))
		{
			lu__debug(
				"[%ld, %ld] cells: %ld/%ld, max_z: %ld/%ld, max_cell: %ld, links: %ld/%ld",
				self->x,
				self->y,
				self->stat_cells_used,
				self->cells_size,
				self->stat_max_z,
				self->d,
				self->stat_max_n_cell_addr.cell_ix,
				lu_n_link_mem__get_links_count(&self->link_mem),
				lu_n_link_mem__get_links_size(&self->link_mem)
			);
		}
		else
		{
			lu__debug(
				"[%ld, %ld] cells: %ld/%ld, max_z: %ld/%ld, max_cell: NA, links: %ld/%ld",
				self->x,
				self->y,
				self->stat_cells_used,
				self->cells_size,
				self->stat_max_z,
				self->d,
				lu_n_link_mem__get_links_count(&self->link_mem),
				lu_n_link_mem__get_links_size(&self->link_mem)
			);
		}
	}

	static inline void lu_n_column__print_distribution_symbols(Lu_N_Column self, lu_size blocks_count)
	{
		lu__assert(self);
		lu__assert(blocks_count > 0);	

		lu_size per_block = self->h / blocks_count;

		lu__debug("]");
		lu_size i;
		lu_size curr_block = 0;
		lu_size ix;
		Lu_N_Cell n_cell;
		lu_bool cell_used;

		for (curr_block = 0; curr_block < blocks_count; curr_block++)
		{
			cell_used = false;
			for (i = 0; i < per_block; i++)
			{
				ix = curr_block * per_block + i;
				if (ix >= self->cells_size) break;

				n_cell = &self->cells[ix];

				if (!lu_n_cell__is_blank(n_cell))
				{
					cell_used = true;
					break;
				}

			}

			if (cell_used) lu__debug("█");
			else lu__debug(" ");
		}

		lu__debug("[");

	}

	static inline void lu_n_column__print_distribution_stats(Lu_N_Column self, lu_size blocks_count)
	{
		lu__assert(self);
		lu__assert(blocks_count > 0);	

		lu_size per_block = self->h / blocks_count;

		lu__debug("[");
		lu_size i;
		lu_size curr_block = 0;
		lu_size ix;
		Lu_N_Cell n_cell;
		lu_size count_per_block;

		for (curr_block = 0; curr_block < blocks_count; curr_block++)
		{
			count_per_block = 0;
			for (i = 0; i < per_block; i++)
			{
				ix = curr_block * per_block + i;
				if (ix >= self->cells_size) break;

				n_cell = &self->cells[ix];

				if (!lu_n_cell__is_blank(n_cell))
				{
					++count_per_block;
				}

			}

			lu__debug("%ld", count_per_block);

			if (curr_block + 1 < blocks_count)
				lu__debug(",");
		}

		lu__debug("]");

	}

	static inline void lu_n_column__collect_net_stats(Lu_N_Column self, Lu_N_Table_Net_Stats ts)
	{
		++ts->column_count;

		if (self->stat_cells_used < ts->cells_used_min) ts->cells_used_min = self->stat_cells_used;
		ts->cells_used_mean += self->stat_cells_used;
		if (self->stat_cells_used > ts->cells_used_max) ts->cells_used_max = self->stat_cells_used;
		if (self->cells_size > ts->cells_size) ts->cells_size = self->cells_size;

		ts->total_cells_count += self->stat_cells_used;
		ts->total_cells_size += self->cells_size;

		if (self->stat_max_z < ts->max_z_min) ts->max_z_min = self->stat_max_z;
		ts->max_z_mean += self->stat_max_z;
		if (self->stat_max_z > ts->max_z_max) ts->max_z_max = self->stat_max_z;
		ts->d = self->d;

		lu_size links_count = lu_n_link_mem__get_links_count(&self->link_mem);

		if (links_count < ts->links_count_min) ts->links_count_min = links_count;
		ts->links_count_mean += links_count;
		if (links_count > ts->links_count_max) ts->links_count_max = links_count;

		lu_size links_size = lu_n_link_mem__get_links_size(&self->link_mem);
		if (links_size > ts->links_size) ts->links_size = links_size;

		ts->total_links_count += links_count;
		ts->total_links_size += links_size;
	}

	static inline void lu_n_column__print_mem_stats(Lu_N_Column self)
	{
		lu__debug("\nREALL n_col ");
		lu_n_column__print_net_stats(self);
		lu__debug(" ");
		lu_s_layer_base__print_basic_info(lu_n_table__get_layer(self->n_table));
		lu__debug(" ");
		lu_n_column__print_distribution_stats(self, 10);
	}


	static Lu_N_Cell lu_n_column__save_with_vp_children(
		Lu_N_Column self, 
		Lu_W_Cell_P* children, 
		lu_size children_count
	);

	static Lu_N_Cell lu_n_column__save_with_children(
		Lu_N_Column self, 
		Lu_W_Cell* children, 
		lu_size children_count
	);

///////////////////////////////////////////////////////////////////////////////
// Lu_N_Table

	struct lu_n_table {
		Lu_Mem mem;
		Lu_S_Layer_Base layer;

		lu_size w;
		lu_size h;
		lu_size h_max;

		struct lu_n_column* columns;
		lu_size columns_size;
	};

	//
	// Constructors / Destructors
	//

	Lu_N_Table lu_n_table__init(
		Lu_N_Table self,
		Lu_Mem mem, 
		lu_size w, 
		lu_size h, 
		lu_size h_max, 
		Lu_Config config, 
		lu_size layer_ix,
		lu_size area_ix,
		Lu_S_Layer_Base layer
	);

 	void lu_n_table__deinit(Lu_N_Table self);

 	//
 	// Get
 	// 

 	static inline Lu_N_Column lu_n_table__get_column_by_ix(Lu_N_Table self, lu_size column_ix)
 	{
 		lu__assert(self);
 		lu__assert(column_ix < self->columns_size);

 		return &self->columns[column_ix];
 	}

 	static inline Lu_N_Column lu_n_table__get_n_column(Lu_N_Table self, lu_size x, lu_size y)
 	{
 		return lu_n_table__get_column_by_ix(self, lu_macro__xy_to_ix(x, y, self->w));
 	}

 	static inline Lu_S_Layer_Base lu_n_table__get_layer(Lu_N_Table self)
 	{
 		lu__assert(self);
 		return self->layer;
 	}

 	//
 	// Methods
 	//

	////
	// Returns true if was able to expand
	static inline lu_bool lu_n_table__expand(Lu_N_Table self)
	{
		if (self->h + 1 >= self->h_max) return false;

		++self->h;

		return true;
	}

	static inline void lu_n_table__print_net_stats(Lu_N_Table self, Lu_S_Layer_Net_Stats layer_ns)
	{
		lu__assert(self);

		lu_size x;
		lu_size y;
		Lu_N_Column n_column;

		struct lu_n_table_net_stats ts;

		lu_n_table_stats__reset(&ts);

		for (y = 0; y < self->h_max; y++)
		{
			for (x = 0; x < self->w; x++)
			{
				n_column = lu_n_table__get_n_column(self, x, y);
				lu__assert(n_column);
				lu__assert(n_column->x == x);
				lu__assert(n_column->y == y);

				lu_n_column__collect_net_stats(n_column, &ts);
			}
		}

		lu__debug(
			"\n\t\tN_TABLE [%ldx%ld]: cells: %ld/%ld/%ld(max size: %ld, total: %ld/%ld), max_z: %ld/%ld/%ld(%ld), links: %ld/%ld/%ld(max size: %ld, total: %ld/%ld)",
 			self->w, 
 			self->h_max,
 			
 			ts.cells_used_min,
			ts.cells_used_mean / ts.column_count,
			ts.cells_used_max,
			ts.cells_size,

			ts.total_cells_count,
			ts.total_cells_size,

			ts.max_z_min,
			ts.max_z_mean / ts.column_count,
			ts.max_z_max,
			ts.d,

			ts.links_count_min,
			ts.links_count_mean / ts.column_count,
			ts.links_count_max,
			ts.links_size,

			ts.total_links_count,
			ts.total_links_size
		);
 	
 		lu_s_layer_net_stats__collect(layer_ns, &ts);
	}



