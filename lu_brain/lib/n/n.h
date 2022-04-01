/**
	Copyright © 2022 Oleh Ihorovych Novosad 

	n_tables are always "3d"
*/

///////////////////////////////////////////////////////////////////////////////
// Lu_N_Cell_Base

	struct lu_n_cell_base {
		lu_byte type;
	};
	
	static inline Lu_N_Cell_Base lu_n_cell_base__init(Lu_N_Cell_Base self, lu_byte type)
	{
		lu__assert(self);
		self->type = type;

		return self;
	}

///////////////////////////////////////////////////////////////////////////////
// Lu_N_Cell_VP

	struct lu_n_cell_vp {
		lu_value value; 
		lu_size x;
		lu_size y;
		lu_size z;
	};

	static inline void lu_n_cell__null_init(Lu_N_Cell_VP self)
	{
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
		lu_size z
	)
	{
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

		// w x h x d, empty by default
		struct lu_n_cell_vp* cells;
	};

	static Lu_N_Table_Comp lu_n_table_comp__create(
		Lu_Config config, 
		Lu_Comp_Calc comp_calc, 
		lu_size width, 
		lu_size height, 
		lu_size depth 
	);

	static void lu_n_table_comp__destroy(Lu_N_Table_Comp self);

	static inline Lu_N_Cell_VP lu_n_table_comp__get_cell(Lu_N_Table_Comp self, lu_size x, lu_size y, lu_size z)
	{
		return &(self->cells + 1)[z * self->w * self->h + y * self->w + x];
	}

	static inline lu_size lu_n_table_comp__get_cell_ix(Lu_N_Table_Comp self, Lu_N_Cell_VP cell)
	{
		return cell - self->cells;
	} 


///////////////////////////////////////////////////////////////////////////////
// Lu_N_String
//

	static inline lu_bool lu_n_string__eq(const lu_size* a, const lu_size* b)
	{
		while (1)
		{
			if (*a != *b)
			{
				return false;
			}

			if (*a == 0 || *b == 0) break;

			++a;
			++b;
		}	
		
		return true;
	}

	////
	// This method doesn't check if <dest> has enough space for <src>
	static inline void lu_n_string__copy(lu_size* dest, const lu_size* src)
	{
		while(*src)
		{
			*dest = *src;
			++src;
			++dest;
		};

		*dest = 0;
	}

	static inline void lu_n_string__print(const lu_size* s)
	{
		lu__debug("\n N_STRING: {");
		const lu_size *p = s;

		while(*p)
		{
			if (p != s) lu__debug(", ");
			lu__debug("%d", *p);
			++p;
		} 
		if (p==s) lu__debug("0");
		else lu__debug(", 0");

		lu__debug("}");
	}


///////////////////////////////////////////////////////////////////////////////
// Lu_N_Cell
//

	#define LU_N_IX__NULL 0 
	#define LU_N_CELL__LINKS_MAX 4

	////
	// Insead of adding +1 when saving index, we dont use 0 index cells
	struct lu_n_cell {
		lu_size label; 		// every cell potentially can be labeled for something
		lu_size links[LU_N_CELL__LINKS_MAX];
	};

	static inline lu_bool lu_n_cell_compare(Lu_N_Cell a, Lu_N_Cell b)
	{
		// a.p_ix != b.p_ix && (return false); 

		// // we can make so the same strings have the same index, so comparing 
		// // string index is enough
		// a.c_ix != b.c_ix && (return false); 

		return true;
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

		lu_size h;
		lu_size d;

		struct lu_n_cell* cells;
	};

	static Lu_N_Column lu_n_column__init(Lu_N_Column self, Lu_Mem mem, lu_size h, lu_size d);
	static void lu_n_column__deinit(Lu_N_Column self);
	static void lu_n_column__realloc(Lu_N_Column self, lu_size h, lu_size d);

	// static inline lu_size lu_n_column__get_cell_ix(Lu_N_Column self, Lu_N_Cell cell)
	// {
	// 	return cell - self->cells;
	// }

	static Lu_N_Cell lu_n_column__save(Lu_N_Column self, lu_size* s)
	{
		lu__debug_assert(self);

		lu_size p_reg = 0;
		lu_size ix;
		lu_size *p = s;
		while((ix = *p))
		{
			p_reg = lu_hash_comb(p_reg, ix);
			++p;
		}

		struct lu_n_cell* cells = self->cells + 1;

		// y
		ix = p_reg % self->h;

		lu_size z = 0;

		// p = &self->strings[z * wh + ix * self->w]

	}

///////////////////////////////////////////////////////////////////////////////
// Lu_N_Table

	struct lu_n_table {
		Lu_Mem mem;

		lu_size w;
		lu_size h;

		lu_byte cell_type; // nema smyslu davaty cell_type v komirku koly to vse povtoruyetsia

		struct lu_n_column* columns;
	};

	Lu_N_Table lu_n_table__create(Lu_Mem mem, lu_size w, lu_size h, lu_byte cell_type, Lu_Config config);
 	void lu_n_table__destroy(Lu_N_Table self);


	static inline Lu_N_Cell lu_n_table__save(Lu_N_Table self, lu_size x, lu_size y, lu_size *links)
	{
		return lu_n_column__save(&self->columns[y * self->w + x], links);
	}