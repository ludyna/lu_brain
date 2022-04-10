/**
	Copyright © 2022 Oleh Ihorovych Novosad 

	n_tables are always "3d"
*/

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
// Lu_N_Addr

	union lu_n_addr {
		struct {
			lu_size cell_ix : 24;
			lu_size column_ix: 24;
			lu_size layer_ix: 16;
		};
		lu_size value;
	};

	// NULL addr
	extern const union lu_n_addr LU_N_ADDR__NULL; 

	static inline Lu_N_Addr lu_n_addr__init(Lu_N_Addr self, lu_size cell_ix, lu_size column_ix, lu_size layer_ix)
	{
		lu__debug_assert(self);

		self->cell_ix = cell_ix;
		self->column_ix = column_ix;
		self->layer_ix = layer_ix;

		return self;
	}

	static inline lu_bool lu_n_addr__is_blank(Lu_N_Addr self)
	{
		return (self->value == 0);
	}

	static inline lu_bool lu_n_addr__is_present(Lu_N_Addr self)
	{
		return (self->value != 0);
	}

	static inline void lu_n_addr__set_to_null(Lu_N_Addr self)
	{
		self->value = 0;
	}

	static inline void lu_n_addr__print(Lu_N_Addr self)
	{
		lu__debug("%d:%d:%d", self->layer_ix, self->column_ix, self->cell_ix);
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
		lu_size z;
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
		union lu_n_addr addr
	)
	{
		self->addr = addr;

		self->value = value;
		self->x = x;
		self->y = y;
		self->z = z;
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
		lu_size size;

		// w x h x d, empty by default
		struct lu_n_cell_vp* cells;
	};

	static Lu_N_Table_Comp lu_n_table_comp__create(
		Lu_Config config, 
		Lu_Comp_Calc comp_calc, 
		lu_size width, 
		lu_size height, 
		lu_size depth, 
		lu_size layer_ix
	);

	static void lu_n_table_comp__destroy(Lu_N_Table_Comp self);

	static inline lu_size lu_n_table_comp__calc_cell_ix(Lu_N_Table_Comp self, lu_size x, lu_size y, lu_size z)
	{
		return z * self->wh + y * self->w + x;
	}

	static inline Lu_N_Cell_VP lu_n_table_comp__get_cell(Lu_N_Table_Comp self, lu_size x, lu_size y, lu_size z)
	{
		lu_size i = lu_n_table_comp__calc_cell_ix(self, x, y, z);

		lu__debug_assert(i < self->size);

		return &self->cells[i];
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
// Lu_N_Label
//

	struct lu_n_label {
		union lu_n_addr links[1000]; // dlia prostoty ce mozhe buty
	};

///////////////////////////////////////////////////////////////////////////////
// Lu_N_Cell
//

	////
	// Insead of adding +1 when saving index, we dont use 0 index cells
	struct lu_n_cell { 
		// addr can be removed later to save memory, but useful for testing and debugging
		// can be wrapped in #ifdef LU__DEBUG
		union lu_n_addr addr; 

		union lu_n_addr children[LU_N_CELL__LINKS_MAX];
	};

	static inline Lu_N_Cell lu_n_cell__init(
		Lu_N_Cell self, 
		lu_size cell_ix, 
		lu_size column_ix, 
		lu_size layer_ix
	)
	{
		lu__debug_assert(self);

		lu_n_addr__init(&self->addr, cell_ix, column_ix, layer_ix);

		self->children[0].value = 0;

		return self;
	}

	static inline lu_bool lu_n_cell__is_blank(Lu_N_Cell self)
	{
		return self->children[0].value == 0;
	}

	static inline lu_bool lu_n_cell__eq(Lu_N_Cell self, const union lu_n_addr* children)
	{
		return lu_n_str__eq(self->children, children);
	}

	static inline void lu_n_cell__save(Lu_N_Cell self, const union lu_n_addr* children)
	{
		lu_n_str__copy(self->children, children);
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_N_Column
// 


	////
	// Having separete columns helps with parallelization in the future, but takes a little bit more memory.
	// my mozhemo vykorystovuvaty columns, ale treba
	// prosto znaty v yakomu poriadku zberihayemo string, sho prosto
	// size parne, 0-size/2 cells, size/2-size - free cells
	// p_reg mozhna vykorystaty ya dlia zberihannia string tak i dlia
	// zberihannia n_cell
	//   xxxxx
	// y
	// y 
	// y 
	// y 

	// de y ce index, y x - ce znachenia strichky, prychomu maksymum 4?
	// mozhna zrobyty z dlia vypadku koly my mayemo povtorennia, 
	// yasho z > max_z robymo povnyy realloc i vse
	// , te same dlia komirok
	// komirka bude maty z i ix, de z i ix toy samyy dlia strichky i dlia komirky
	struct lu_n_column {
		Lu_Mem mem;

		lu_size column_ix;

		lu_size h;
		lu_size d;

		struct lu_n_cell* cells;
	};

	static Lu_N_Column lu_n_column__init(Lu_N_Column self, Lu_Mem mem, lu_size h, lu_size d, lu_size layer_ix, lu_size column_ix);
	static void lu_n_column__deinit(Lu_N_Column self);
	static void lu_n_column__realloc(Lu_N_Column self, lu_size h, lu_size d);

	// static inline lu_size lu_n_column__get_cell_ix(Lu_N_Column self, Lu_N_Cell cell)
	// {
	// 	return cell - self->cells;
	// }

	static inline lu_size lu_n_column__hash_to_ix(Lu_N_Column self, lu_size hash)
	{
		return hash % self->h; 
	}

	static inline Lu_N_Cell lu_n_column__get_cell(Lu_N_Column self, lu_size z, lu_size ix)
	{
		return &self->cells[z * self->h + ix];
	}

	static inline lu_size lu_n_column__children_to_ix(Lu_N_Column self, union lu_n_addr* children)
	{
		return lu_n_column__hash_to_ix(self, lu_n_str__hash_comb(children));
	}

	static inline union lu_n_addr lu_n_column__cell_to_ix(Lu_N_Column self, Lu_N_Cell cell)
	{ 
		union lu_n_addr ix;
		ix.column_ix = 0;
		ix.cell_ix = ((cell - self->cells) / sizeof(struct lu_n_cell));
		return ix;
	}

	static union lu_n_addr lu_n_column__save(Lu_N_Column self, union lu_n_addr* children)
	{
		lu__debug_assert(self);
		lu__debug_assert((*children).value);

		lu_size ix = lu_n_column__children_to_ix(self, children);

		for (lu_size z = 0; z < self->d; z++)
		{
			Lu_N_Cell cell = lu_n_column__get_cell(self, z, ix);

			if (lu_n_cell__is_blank(cell))
			{
				lu_n_cell__save(cell, children);
				return lu_n_column__cell_to_ix(self, cell);
			}
			else if (lu_n_cell__eq(cell, children)) 
			{
				return lu_n_column__cell_to_ix(self, cell); // no need to do anything, we already have that cell
			}
		}

		// should replace with column reallocation, should not normally happen
		lu__assert(false);
		return LU_N_ADDR__NULL;
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_N_Table

	struct lu_n_table {
		Lu_Mem mem;

		lu_size w;
		lu_size h;

		struct lu_n_column* columns;
	};

	Lu_N_Table lu_n_table__create(Lu_Mem mem, lu_size w, lu_size h, Lu_Config config, lu_size layer_ix);
 	void lu_n_table__destroy(Lu_N_Table self);

 	static inline Lu_N_Column lu_n_table__get_column(Lu_N_Table self, lu_size x, lu_size y)
 	{
 		return &self->columns[y * self->w + x];
 	}

	static inline union lu_n_addr lu_n_table__save(Lu_N_Table self, lu_size x, lu_size y, union lu_n_addr *links)
	{
		return lu_n_column__save(lu_n_table__get_column(self, x, y), links);
	}
