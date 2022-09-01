/**
	Copyright © 2022 Oleh Ihorovych Novosad 

	s_tables are always "3d"
*/

///////////////////////////////////////////////////////////////////////////////
// Lu_N_Located_Cell
//
	struct lu_n_located_cell {
		enum lu_n_cell_type n_cell_type;
		union {
			struct {
				Lu_N_Cell n_cell;
				Lu_S_Column s_column;
			};

			struct {
				Lu_N_Cell_VP n_cell_vp;
				Lu_S_Column_Comp s_column_comp;
				Lu_S_Layer_Comp s_layer_comp;
			};
		};	
	};

	static inline Lu_N_Located_Cell lu_n_located_cell__reset(Lu_N_Located_Cell self)
	{
		self->n_cell_type = LU_N_CELL__END; // none
		self->n_cell = NULL;
		self->s_column = NULL;
		self->n_cell_vp = NULL;
		self->s_column_comp = NULL;
		self->s_layer_comp = NULL;

		return self;
	}

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
		union lu_n_addr n_cell_addr;

		union lu_n_link_addr next;
	};

	static inline lu_bool lu_n_link__eq(Lu_N_Link self, const union lu_n_addr* b, Lu_N_Link_Mem link_mem)
	{
		while (1)
		{
			if (!self || self->n_cell_addr.value != (*b).value)
			{
				return false;
			}

			if (self->n_cell_addr.value == 0 || (*b).value == 0) break;

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

		// -1 because we should not count NULL links
		return lu_mem_table__records_count(self->mem_table) - 1;
	}

	static inline lu_size lu_n_link_mem__get_links_size(Lu_N_Link_Mem self)
	{
		lu__assert(self);
		lu__assert(self->mem_table);

		// -1 because we should not count NULL links
		return lu_mem_table__records_size(self->mem_table) - 1;
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

	static inline Lu_N_Link lu_n_link_mem__alloc_link(Lu_N_Link_Mem self)
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

	static inline void lu_n_link_mem__free_link(Lu_N_Link_Mem self, Lu_N_Link link)
	{
		lu__assert(self);
		lu__assert(self->mem_table);
		lu__assert(link);

		lu_mem_record__free(self->mem_table, (lu_p_byte) link);
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
		Lu_N_Link n_link = lu_n_link_mem__alloc_link(link_mem);
		lu__assert(n_link);

		n_link->next = self->parents;

		n_link->n_cell_addr = addr;

		self->parents = lu_n_link_mem__get_addr(link_mem, n_link);

		lu__assert(lu_n_link_addr__is_present(&self->parents));

		return n_link;
	}

	static inline void lu_n_cell_vp__remove_link_to_parent(
		Lu_N_Cell_VP self, 
		union lu_n_addr n_addr, // parent
		Lu_N_Link_Mem n_link_mem,
		union lu_n_link_addr *links
	)
	{
		lu__assert(self);
		lu__assert(n_link_mem);

		union lu_n_link_addr n_link_addr = *links;

		
		Lu_N_Link n_link_prev = NULL;
		Lu_N_Link n_link = NULL;
		while(lu_n_link_addr__is_present(&n_link_addr))
		{
			n_link = lu_n_link_mem__get_link(n_link_mem, n_link_addr);

			if (lu_n_addr__is_eq(&n_link->n_cell_addr, &n_addr))
			{
				if (n_link_prev)
				{
					n_link_prev->next = n_link->next;
				}
				else
				{
					*links = n_link->next;
				}

				lu_n_link_mem__free_link(n_link_mem, n_link);

				break;
			}

			n_link_prev = n_link;
			n_link_addr = n_link->next;
		}
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_N_Cell
//

	// enum lu_n_rel_pos {
	// 	LU_N_CHILD_POS__TL = 0,
	// 	LU_N_CHILD_POS__TR,
	// 	LU_N_CHILD_POS__BL,
	// 	LU_N_CHILD_POS__BR,
	// 	LU_N_CHILD_POS__END,
	// };

	// union lu_n_link_2 {

	// };

	// union lu_n_rel_pos {
	// 	struct {

	// 	};
	// 	lu_size value;
	// };

	// struct lu_n_column_link {
	// 	lu_size column_ix;

	// }:

	// struct lu_n_link_23 {
	// 	  // if its parent link, then it is child pos, if its child link, then it is parent pos
	// 	// lu_size column_ix; // dont need column_ix since i have rel pos
	// 	union lu_n_link_addr link;
	// };

	struct lu_n_cell { 
		
		// If s_table will be reallocated, we need to reinit pointers to s_column for every n_cell involved.
		// And it is OK.
		// Lu_S_Column s_column;

		union lu_n_addr addr; 

		union lu_la_link_addr labels;

		union lu_n_link_addr tl;
		union lu_n_link_addr tr;
		union lu_n_link_addr bl;
		union lu_n_link_addr br;

		// Potentially in the future we will have direct links to n_cells in higher layers (skipping 
		// immediate parent layer). 
		// union lu_n_link_addr other_parents;

		union lu_n_link_addr children; 

		lu_value default_sig;
		
		union lu_w_match_addr w_match_cells[LU_N_CELL__W_MATCH_CELLS_SIZE];

		// This is temp info, that will not be persistent, so I will try to use 
		// struct directly here
		struct lu_w_save_cell w_save_cells[LU_N_CELL__W_SAVE_CELLS_SIZE];
		struct lu_w_restore_cell w_restore_cells[LU_N_CELL__W_RESTORE_CELLS_SIZE];
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

		lu_size i;
		for (i = 0; i < LU_N_CELL__W_MATCH_CELLS_SIZE; i++)
		{
			lu_w_match_addr__reset(&self->w_match_cells[i]);
		}
		
		for (i = 0; i < LU_N_CELL__W_SAVE_CELLS_SIZE; i++)
		{
			// lu_w_save_addr__reset(&self->w_save_cells[i]);
			lu_w_save_cell__reset(&self->w_save_cells[i]);
		}

		for (i = 0; i < LU_N_CELL__W_RESTORE_CELLS_SIZE; i++)
		{
			// lu_w_save_addr__reset(&self->w_save_cells[i]);
			lu_w_restore_cell__reset(&self->w_restore_cells[i]);
		}
		
		return self;
	}

	static inline Lu_N_Cell lu_n_cell__deinit(
		Lu_N_Cell self,
		Lu_Mem mem
	)
	{
		lu__assert(self);
		lu__assert(mem);
		lu__assert(self->w_match_cells);

		lu__debug_assert(self);

		lu_n_addr__reset(&self->addr);

		// lu_mem__free(mem, (lu_p_byte) self->w_match_cells);

		// self->w_match_cells = NULL;

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
		return self->w_match_cells[wave_ix];
	}

	static inline void lu_n_cell__set_w_mach_cell_addr(Lu_N_Cell self, lu_size wave_ix, union lu_w_match_addr w_addr)
	{
		self->w_match_cells[wave_ix] = w_addr;
	}

	static inline Lu_N_Addr lu_n_cell__get_cell_addr(Lu_N_Cell self)
	{
		lu__debug_assert(self);

		return &self->addr;
	}

	static inline Lu_W_Save_Cell lu_n_cell__get_w_save_cell(Lu_N_Cell self, lu_size wave_ix)
	{
		lu__assert(self);
		lu__assert(wave_ix < LU_N_CELL__W_SAVE_CELLS_SIZE);

		return &self->w_save_cells[wave_ix];
	}

	static inline Lu_W_Restore_Cell lu_n_cell__get_w_restore_cell(Lu_N_Cell self, lu_size wave_ix)
	{
		lu__assert(self);
		lu__assert(wave_ix < LU_N_CELL__W_RESTORE_CELLS_SIZE);

		return &self->w_restore_cells[wave_ix];
	}

	//
	// Is
	//

	static inline lu_bool lu_n_cell__is_blank(Lu_N_Cell self)
	{
		lu__debug_assert(self);

		return lu_n_link_addr__is_blank(&self->children);
	}

	static inline lu_bool lu_n_cell__is_s_column_null_cell(Lu_N_Cell self)
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
		Lu_N_Link n_link = lu_n_link_mem__alloc_link(link_mem);
		lu__assert(n_link);

		n_link->next = self->children;

		n_link->n_cell_addr = addr;

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
		lu__assert(children); 

		lu_size i;
		lu_size ix;

		Lu_W_Cell_P w_cell_p = NULL;

		for (i = 0; i < children_count; i++)
		{
			ix = children_count - i - 1;

			w_cell_p = children[ix]; 
			lu__assert(w_cell_p);
			lu__debug_assert(w_cell_p->n_cell_vp);

			lu_n_cell__children_prepend(self, link_mem, w_cell_p->n_cell_vp->addr);

			lu_n_cell_vp__parent_prepend(w_cell_p->n_cell_vp, lu_s_column_comp__get_n_link_mem(w_cell_p->s_column_comp), self->addr);
		}
	}

	static inline void lu_n_cell__save( 
		Lu_N_Cell self, // parent
		struct lu_w_child* children, 
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
		Lu_S_Column s_column;

		for (i = 0; i < children_count; i++)
		{
			ix = children_count - i - 1;

			w_cell = children[ix].w_cell; 
			
			// Out of bounds situation
			if (w_cell == NULL) continue;
			
			n_cell = w_cell->n_cell;
			lu__assert(n_cell); // should never happen, it should be "null" cell or normal cell

			s_column = w_cell->s_column;
			lu__assert(s_column);
	
			lu_n_cell__children_prepend(self, link_mem, n_cell->addr);

			// NOTE!: link from child to parent is saved in link with name (TL, TR, ..) that child pos was 
			// relative to parent
			switch(children[ix].child_pos)
			{
				case LU_W_CHILD_POS__TL:
					n_cell->tl = lu_n_link_addr__prepend(n_cell->tl, lu_s_column__get_link_mem(s_column), self->addr);
					break;
				case LU_W_CHILD_POS__TR:
					n_cell->tr = lu_n_link_addr__prepend(n_cell->tr, lu_s_column__get_link_mem(s_column), self->addr);
					break;
				case LU_W_CHILD_POS__BL:
					n_cell->bl = lu_n_link_addr__prepend(n_cell->bl, lu_s_column__get_link_mem(s_column), self->addr);
					break;
				case LU_W_CHILD_POS__BR:
					n_cell->br = lu_n_link_addr__prepend(n_cell->br, lu_s_column__get_link_mem(s_column), self->addr);
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

	static inline void lu_n_cell__remove_link_to_label(
		Lu_N_Cell self, 
		union lu_la_addr la_addr, // label addr
		Lu_La_Link_Mem la_link_mem
	)
	{
		lu__assert(self);
		lu__assert(la_link_mem);

		union lu_la_link_addr la_link_addr = self->labels;

		Lu_La_Link la_link = NULL;
		Lu_La_Link la_link_prev = NULL;
		while(lu_la_link_addr__is_present(&la_link_addr))
		{
			la_link = lu_la_link_mem__get_link(la_link_mem, la_link_addr);

			if (lu_la_addr__is_eq(&la_link->la_addr, &la_addr))
			{
				if (la_link_prev)
				{
					la_link_prev->next = la_link->next;
				}
				else
				{
					self->labels = la_link->next;
				}

				lu_la_link_mem__free_link(la_link_mem, la_link);

				break;
			}

			la_link_prev = la_link;
			la_link_addr = la_link->next;
		}
	}

	static inline void lu_n_cell__remove_link_to_parent(
		Lu_N_Cell self, 
		union lu_n_addr n_addr, // parent
		Lu_N_Link_Mem n_link_mem,
		union lu_n_link_addr *links
	)
	{
		lu__assert(self);
		lu__assert(n_link_mem);

		union lu_n_link_addr n_link_addr = *links;

		
		Lu_N_Link n_link_prev = NULL;
		Lu_N_Link n_link = NULL;
		while(lu_n_link_addr__is_present(&n_link_addr))
		{
			n_link = lu_n_link_mem__get_link(n_link_mem, n_link_addr);

			if (lu_n_addr__is_eq(&n_link->n_cell_addr, &n_addr))
			{
				if (n_link_prev)
				{
					n_link_prev->next = n_link->next;
				}
				else
				{
					*links = n_link->next;
				}

				lu_n_link_mem__free_link(n_link_mem, n_link);

				break;
			}

			n_link_prev = n_link;
			n_link_addr = n_link->next;
		}
	}

	static inline void lu_n_cell__free_children_links(Lu_N_Cell self, Lu_N_Link_Mem n_link_mem)
	{
		lu__assert(self);

		union lu_n_link_addr n_link_addr = self->children;

		Lu_N_Link n_link = NULL;
		while(lu_n_link_addr__is_present(&n_link_addr))
		{
			n_link = lu_n_link_mem__get_link(n_link_mem, n_link_addr);
			n_link_addr = n_link->next;

			lu_n_link_mem__free_link(n_link_mem, n_link);
		}

		self->children = LU_N_LINK_ADDR__NULL;
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
		Lu_W_Cell_P w_cell_p;
		for(lu_size i = 0; i < children_count; i++)
		{
			if (lu_n_link_addr__is_blank(&self)) return false;

			w_cell_p = children[i];
			lu__debug_assert(w_cell_p);
			lu__debug_assert(w_cell_p->n_cell_vp);

			n_link = lu_n_link_mem__get_link(link_mem, self);
			if (!n_link) return false;

			if (!lu_n_addr__is_eq(&n_link->n_cell_addr, lu_n_cell_vp__get_cell_addr(w_cell_p->n_cell_vp))) return false;

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

			if (!lu_n_addr__is_eq(&n_link->n_cell_addr, lu_n_cell__get_cell_addr(w_cell->n_cell))) return false;

			self = n_link->next;
		}

		return true;
	}

	static inline union lu_n_link_addr lu_n_link_addr__prepend(union lu_n_link_addr self, Lu_N_Link_Mem link_mem, union lu_n_addr addr)
	{
		// new child link
		Lu_N_Link n_link = lu_n_link_mem__alloc_link(link_mem);
		lu__assert(n_link);

		n_link->next = self;

		n_link->n_cell_addr = addr;

		return lu_n_link_mem__get_addr(link_mem, n_link);
	}
 
