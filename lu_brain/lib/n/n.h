/**
	Copyright © 2022 Oleh Ihorovych Novosad 

	n_tables are always "3d"
*/

///////////////////////////////////////////////////////////////////////////////
// 

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

	static inline Lu_N_Link lu_n_link__prepend(Lu_N_Link self, Lu_N_Link_Mem link_mem, union lu_n_addr addr)
	{
		Lu_N_Link prev_n_link = self;

		// new child link
		Lu_N_Link n_link = lu_n_link_mem__link_alloc(link_mem);
		lu__assert(n_link);

		n_link->next = prev_n_link ? lu_n_link_mem__get_addr(link_mem, prev_n_link) : LU_N_LINK_ADDR__NULL;

		n_link->cell_addr = addr;

		return n_link;
	}

	static inline lu_bool lu_n_link__is_vp_children_eq(
		Lu_N_Link self, 
		Lu_W_Save_Cell_P* children, 
		lu_size children_count, 
		Lu_N_Link_Mem link_mem
	)
	{
		lu__debug_assert(children);
		lu__debug_assert(children[0]);
		lu__debug_assert(children_count > 0);
		lu__debug_assert(link_mem);

		if (self == NULL) return false;

		Lu_W_Save_Cell_P w_cell;
		for(lu_size i = 0; i < children_count; i++)
		{
			if (self == NULL) return false;

			w_cell = children[i];
			lu__debug_assert(w_cell);
			lu__debug_assert(w_cell->n_cell);

			if (!lu_n_addr__is_eq(&self->cell_addr, lu_n_cell_vp__get_cell_addr(w_cell->n_cell))) return false;

			self = lu_n_link_mem__get_link(link_mem, self->next);
		}

		return true;
	}

	static inline lu_bool lu_n_link__is_children_eq(
		Lu_N_Link self, 
		Lu_W_Save_Cell* children, 
		lu_size children_count, 
		Lu_N_Link_Mem link_mem
	)
	{
		lu__debug_assert(children);
		lu__debug_assert(children[0]);
		lu__debug_assert(children_count > 0);
		lu__debug_assert(link_mem);

		if (self == NULL) return false;

		Lu_W_Save_Cell w_cell;
		for(lu_size i = 0; i < children_count; i++)
		{
			if (self == NULL) return false;

			w_cell = children[i];
			lu__debug_assert(w_cell);
			lu__debug_assert(w_cell->n_cell);

			if (!lu_n_addr__is_eq(&self->cell_addr, lu_n_cell__get_cell_addr(w_cell->n_cell))) return false;

			self = lu_n_link_mem__get_link(link_mem, self->next);
		}

		return true;
	}


///////////////////////////////////////////////////////////////////////////////
// Lu_N_Link_Mem
//

	struct lu_n_link_mem {
		Lu_Mem_Table mem_table;

	};

	Lu_N_Link_Mem lu_n_link_mem__init(Lu_N_Link_Mem self, Lu_Mem mem, lu_size size);
	void lu_n_link_mem__deinit(Lu_N_Link_Mem self);

	static inline Lu_N_Link lu_n_link_mem__link_alloc(Lu_N_Link_Mem self)
	{
		lu__debug_assert(self);

		lu_p_byte record = lu_mem_record__alloc(self->mem_table);

		if (!record)
		{
			lu_mem_table__realloc(
				self->mem_table, 
				lu_mem_table__records_count(self->mem_table) * 2, 
				LU_MEM_TABLE__DEFAULT
			); 

			record = lu_mem_record__alloc(self->mem_table);
			lu__assert(record);
		}

		return (Lu_N_Link) record;
	}

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
			p_reg = lu_hash_comb(p_reg, (*p).value);
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

		Lu_N_Link parents;
	};

	static inline void lu_n_cell_vp__null_init(Lu_N_Cell_VP self)
	{
		self->addr.value = 0;

		self->value = 0;
		self->x = 0;
		self->y = 0;
		self->z = 0;
	}

	static inline Lu_N_Cell_VP lu_n_cell_vp__init(
		Lu_N_Cell_VP self, 
		lu_value value,
		lu_size x,
		lu_size y,
		lu_size z,
		union lu_n_addr addr,
		lu_size w_match_cells_size
	)
	{
		self->addr = addr;

		self->value = value;
		self->x = x;
		self->y = y;
		self->z = z;

		return self;
	}

	static inline void lu_n_cell_vp__deinit(Lu_N_Cell_VP self, Lu_Mem mem)
	{

	}

	static inline Lu_N_Link lu_n_cell_vp__parent_prepend(Lu_N_Cell_VP self, Lu_N_Link_Mem link_mem, union lu_n_addr addr)
	{
		Lu_N_Link prev_n_link = self->parents;

		// new child link
		Lu_N_Link n_link = lu_n_link_mem__link_alloc(link_mem);
		lu__assert(n_link);

		n_link->next = prev_n_link ? lu_n_link_mem__get_addr(link_mem, prev_n_link) : LU_N_LINK_ADDR__NULL;

		n_link->cell_addr = addr;

		self->parents = n_link;

		return n_link;
	}

	static inline Lu_N_Addr lu_n_cell_vp__get_cell_addr(Lu_N_Cell_VP self)
	{
		lu__debug_assert(self);

		return &self->addr;
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

	struct lu_n_cell { 
		union lu_n_addr addr; 

		Lu_La_Link labels;

		Lu_N_Link tl;
		Lu_N_Link tr;
		Lu_N_Link bl;
		Lu_N_Link br;

		Lu_N_Link children; 

		lu_value default_sig;
		
		union lu_w_match_addr* w_cells;
	};

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

		self->labels = NULL;
		self->tl = NULL;
		self->tr = NULL;
		self->bl = NULL;
		self->br = NULL;
		self->children = NULL; 
		self->default_sig = 0;

		lu_size size = sizeof(union lu_w_match_addr*) * w_cells_size;
		self->w_cells = (union lu_w_match_addr*) lu_mem__alloc(mem, size);
		lu__alloc_assert(self->w_cells);

		memset(self->w_cells, 0, size);

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

		lu_n_addr__set_to_null(&self->addr);

		lu_mem__free(mem, (lu_p_byte) self->w_cells);

		self->w_cells = NULL;

		return self;
	}

	static inline Lu_N_Addr lu_n_cell__get_cell_addr(Lu_N_Cell self)
	{
		lu__debug_assert(self);

		return &self->addr;
	}

	static inline lu_bool lu_n_cell__is_blank(Lu_N_Cell self)
	{
		lu__debug_assert(self);

		return self->children == NULL;
	}

	static inline lu_bool lu_n_cell__is_n_column_null_cell(Lu_N_Cell self)
	{
		lu__debug_assert(self);

		return self->addr.cell_ix == 0;
	}

	static inline Lu_N_Link lu_n_cell__children_prepend(Lu_N_Cell self, Lu_N_Link_Mem link_mem, union lu_n_addr addr)
	{
		Lu_N_Link prev_n_link = self->children;

		// New child link
		Lu_N_Link n_link = lu_n_link_mem__link_alloc(link_mem);
		lu__assert(n_link);

		n_link->next = prev_n_link ? lu_n_link_mem__get_addr(link_mem, prev_n_link) : LU_N_LINK_ADDR__NULL;

		n_link->cell_addr = addr;

		self->children = n_link;

		// For every children we have minus sig potential, that should be overcome by child signal
		--self->default_sig;

		return n_link;
	}	

	static inline void lu_n_cell__vp_save( 
		Lu_N_Cell self, 
		Lu_W_Save_Cell_P* children, 
		lu_size children_count,
		Lu_N_Link_Mem link_mem,
		lu_size non_null_count
	)
	{
		lu__assert(self);
		lu__assert(children); // we don't even save NULL cell

		lu_size i;
		lu_size ix;

		Lu_W_Save_Cell_P w_cell = NULL;

		// We dont need to use default_sig because all links present (even if they are to NULL cells)

		for (i = 0; i < children_count; i++)
		{
			ix = children_count - i - 1;

			w_cell = children[ix]; 
			lu__assert(w_cell);
			lu__debug_assert(w_cell->n_cell);

			// We create links even if sig > 0.
			// We dont create links only if all children are NULL (which means we will not get here).

			lu_n_cell__children_prepend(self, link_mem, w_cell->n_cell->addr);

			lu_n_cell_vp__parent_prepend(w_cell->n_cell, &w_cell->n_column->link_mem, self->addr);
		}

		lu__debug("\n lu_n_cell__vp_save()"); 
	}

	static inline void lu_n_cell__save( 
		Lu_N_Cell self, 
		Lu_W_Save_Cell* children, 
		lu_size children_count,
		Lu_N_Link_Mem link_mem,
		lu_size non_null_count
	)
	{
		lu__assert(self);
		lu__assert(children); // we don't even save NULL cell

		lu_size i;
		lu_size ix;

		Lu_W_Save_Cell w_cell = NULL;
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
					n_cell->tl = lu_n_link__prepend(n_cell->tl, lu_n_column__get_link_mem(n_column), self->addr);
					break;
				case 1:
					n_cell->tr = lu_n_link__prepend(n_cell->tr, lu_n_column__get_link_mem(n_column), self->addr);
					break;
				case 2:
					n_cell->bl = lu_n_link__prepend(n_cell->bl, lu_n_column__get_link_mem(n_column), self->addr);
					break;
				case 3:
					n_cell->br = lu_n_link__prepend(n_cell->br, lu_n_column__get_link_mem(n_column), self->addr);
					break;
				default:
					lu__assert(false);
			}
		}

		lu__debug("\n lu_n_cell__save()");
	}

	static inline Lu_La_Link lu_n_cell__prepend_label(
		Lu_N_Cell self, 
		union lu_la_addr la_addr, 
		Lu_La_Link_Mem la_link_mem
	)
	{
		Lu_La_Link prev_la_link = self->labels;

		// new child link
		Lu_La_Link la_link = lu_la_link_mem__link_alloc(la_link_mem);
		lu__assert(la_link);

		lu_la_link__init(
			la_link, 
			la_addr,
			prev_la_link ? lu_la_link_mem__get_addr(la_link_mem, prev_la_link) : LU_LA_LINK_ADDR__NULL
		);

		return la_link;
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_N_Column
// 
	
	struct lu_n_column {
		Lu_Mem mem;

		lu_size column_ix;

		lu_size h;
		lu_size d;

		struct lu_n_cell* cells;
		lu_size cells_size;

		struct lu_n_link_mem link_mem;

		lu_size w_match_cells_size;
	};

	static Lu_N_Column lu_n_column__init(
		Lu_N_Column self, 
		Lu_Mem mem, 
		lu_size h, 
		lu_size d, 
		lu_size area_ix,
		lu_size layer_ix, 
		lu_size column_ix,
		Lu_Config config
	);
	static void lu_n_column__deinit(Lu_N_Column self);
	static void lu_n_column__realloc(Lu_N_Column self, lu_size h, lu_size d);

	// static inline lu_size lu_n_column__get_cell_ix(Lu_N_Column self, Lu_N_Cell cell)
	// {
	// 	return cell - self->cells;
	// }

	static inline Lu_N_Link_Mem lu_n_column__get_link_mem(Lu_N_Column self)
	{
		lu__debug_assert(self);

		return &self->link_mem;
	}

	static inline lu_size lu_n_column__hash_to_ix(Lu_N_Column self, lu_size hash)
	{
		return hash % self->h; 
	}

	static inline Lu_N_Cell lu_n_column__get_null_cell(Lu_N_Column self)
	{
		lu__debug_assert(self);

		return &self->cells[0];
	}

	static inline Lu_N_Cell lu_n_column__get_cell(Lu_N_Column self, lu_size z, lu_size ix)
	{
		lu__debug_assert(self);

		lu_size column_ix = z * self->h + ix;

		lu__debug_assert(column_ix < self->cells_size);

		return &self->cells[column_ix];
	}

	static inline lu_size lu_n_column__vp_children_to_ix(
		Lu_N_Column self, 
		Lu_W_Save_Cell_P* children, 
		lu_size children_count
	)
	{
		return lu_n_column__hash_to_ix(self, lu_w_save_cell_p__children_hash_comp(children, children_count));
	} 

	static inline lu_size lu_n_column__children_to_ix(
		Lu_N_Column self, 
		Lu_W_Save_Cell* children, 
		lu_size children_count
	)
	{
		return lu_n_column__hash_to_ix(self, lu_w_save_cell__children_hash_comp(children, children_count));
	}

	static inline Lu_N_Cell lu_n_column__save_with_vp_children(
		Lu_N_Column self, 
		Lu_W_Save_Cell_P* children, 
		lu_size children_count,
		lu_size non_null_count
	)
	{
		lu__debug_assert(self);
		lu__debug_assert(children);
		lu__debug_assert(children_count > 0);

		lu_size ix = lu_n_column__vp_children_to_ix(self, children, children_count);

		for (lu_size z = 0; z < self->d; z++)
		{
			Lu_N_Cell cell = lu_n_column__get_cell(self, z, ix);

			lu__debug_assert(cell);

			// We don't save INTO n_column null cell (which is for z = 0 only), find another.
			if (z == 0 && lu_n_cell__is_n_column_null_cell(cell)) continue;

			if (lu_n_cell__is_blank(cell))
			{
				lu_n_cell__vp_save(cell, children, children_count, &self->link_mem, non_null_count);
				return cell;
			}
			else if (lu_n_link__is_vp_children_eq(cell->children, children, children_count, &self->link_mem)) 
			{
				return cell; // no need to do anything, we already have that cell
			}
		}

		// should replace with column reallocation, should not normally happen
		return NULL;
	}

	static inline Lu_N_Cell lu_n_column__save_with_children(
		Lu_N_Column self, 
		Lu_W_Save_Cell* children, 
		lu_size children_count,
		lu_size non_null_count
	)
	{
		lu__debug_assert(self);
		lu__debug_assert(children);
		lu__debug_assert(children_count > 0);

		lu_size ix = lu_n_column__children_to_ix(self, children, children_count);

		for (lu_size z = 0; z < self->d; z++)
		{
			Lu_N_Cell cell = lu_n_column__get_cell(self, z, ix);

			lu__debug_assert(cell);

			// We don't save INTO n_column null cell (which is for z = 0 only), find another.
			if (z == 0 && lu_n_cell__is_n_column_null_cell(cell)) continue;

			if (lu_n_cell__is_blank(cell))
			{
				lu_n_cell__save(cell, children, children_count, &self->link_mem, non_null_count);
				return cell;
			}
			else if (lu_n_link__is_children_eq(cell->children, children, children_count, &self->link_mem)) 
			{
				return cell; // no need to do anything, we already have that cell
			}
		}

		// should replace with column reallocation, should not normally happen
		return NULL;

	}

///////////////////////////////////////////////////////////////////////////////
// Lu_N_Table

	struct lu_n_table {
		Lu_Mem mem;

		lu_size w;
		lu_size h;
		lu_size h_max;

		struct lu_n_column* columns;
	};

	Lu_N_Table lu_n_table__create(
		Lu_Mem mem, 
		lu_size w, 
		lu_size h, 
		lu_size h_max, 
		Lu_Config config, 
		lu_size layer_ix,
		lu_size area_ix
	);

 	void lu_n_table__destroy(Lu_N_Table self);

 	static inline Lu_N_Column lu_n_table__get_column(Lu_N_Table self, lu_size x, lu_size y)
 	{
 		return &self->columns[y * self->w + x];
 	}

	////
	// Returns true if was able to expand
	static inline lu_bool lu_n_table__expand(Lu_N_Table self)
	{
		if (self->h + 1 >= self->h_max) return false;

		++self->h;

		return true;
	}
